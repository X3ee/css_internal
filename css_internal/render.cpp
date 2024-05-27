#include "render.h"
#include "util.h"

render g_render;
render::fonts g_fonts;

void render::initialize(IDirect3DDevice9* device)
{
	if (!d3d_device)
		d3d_device = device;

	create_objects();
}

void render::remove()
{
	if (d3d_line) {
		d3d_line->Release();
		d3d_line = nullptr;
	}

	if (g_fonts.d3d_font) {
		g_fonts.d3d_font->Release();
		g_fonts.d3d_font = nullptr;
	}


	if (d3d_block) {
		d3d_block->Release();
		d3d_block = nullptr;
	}
}

void render::create_objects()
{
	if (FAILED(D3DXCreateLine(d3d_device, &d3d_line)))
		return;

	if (FAILED(D3DXCreateFontA(d3d_device, 12, 0, FW_DONTCARE, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, NONANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, ("Verdana"), &g_fonts.d3d_font)))
		return;


	if (FAILED(d3d_device->CreateStateBlock(D3DSBT_ALL, &d3d_block)))
		return;
}

void render::startrenderstate(IDirect3DDevice9* device)
{
	if (!d3d_device)
		return;

	d3d_block->Capture();

	device->SetVertexShader(nullptr);
	device->SetPixelShader(nullptr);

	device->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

	device->SetRenderState(D3DRS_LIGHTING, false);
	device->SetRenderState(D3DRS_FOGENABLE, false);
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	device->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
	device->SetRenderState(D3DRS_SCISSORTESTENABLE, true);
	device->SetRenderState(D3DRS_ZWRITEENABLE, false);
	device->SetRenderState(D3DRS_STENCILENABLE, false);

	device->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, false);
	device->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, true);

	device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	device->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	device->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, true);

	device->SetTexture(0, nullptr);
	device->SetTexture(1, nullptr);
	device->SetTexture(2, nullptr);
	device->SetTexture(3, nullptr);

	device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	device->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
	device->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
	device->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
	device->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);

	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	device->SetRenderState(D3DRS_SRCBLENDALPHA, D3DBLEND_INVDESTALPHA);
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	device->SetRenderState(D3DRS_DESTBLENDALPHA, D3DBLEND_ONE);
	device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);

	device->SetRenderState(D3DRS_SRGBWRITEENABLE, false);
	device->SetRenderState(D3DRS_COLORWRITEENABLE, 0xffffffff);
}

void render::endrenderstate(IDirect3DDevice9* device)
{
	d3d_block->Apply();
}

void render::draw_rect(clr_t color, int x, int y, int w, int h) {
	/* testing d3d9 render */
	d3d_vertex_t v[5] = {
		d3d_vertex_t(float(x), float(y), 1.0f, color),
		d3d_vertex_t(float(x + w), float(y), 1.0f, color),
		d3d_vertex_t(float(x + w), float(y + h), 1.0f, color),
		d3d_vertex_t(float(x), float(y + h), 1.0f, color),
		d3d_vertex_t(float(x), float(y), 1.0f, color)
	};

	d3d_device->DrawPrimitiveUP(D3DPT_LINESTRIP, 4, v, VERTEX_SIZE);
}

void render::text(std::string text, int x, int y, ID3DXFont* font, unsigned long color, bool center, bool outline)
{
	auto DrawTextA = [&](std::string _text, int _x, int _y, unsigned long _color) {
		RECT r{ _x, _y, _x, _y };
		font->DrawTextA(NULL, _text.c_str(), -1, &r, DT_NOCLIP, _color);
	};

	if (outline) {
		DrawTextA(text, x - 1, y, D3DCOLOR_RGBA(1, 1, 1, 255));
		DrawTextA(text, x + 1, y, D3DCOLOR_RGBA(1, 1, 1, 255));
		DrawTextA(text, x, y - 1, D3DCOLOR_RGBA(1, 1, 1, 255));
		DrawTextA(text, x, y + 1, D3DCOLOR_RGBA(1, 1, 1, 255));
	}

	DrawTextA(text, center ? x - text_width(text, font) / 2 : x, y, color);
}

unsigned long render::textcolor(float col[4])
{
	return D3DCOLOR_RGBA(util::floatrgba(col[0]), util::floatrgba(col[1]),
		util::floatrgba(col[2]), util::floatrgba(col[3]));
}

RECT render::text_dimension(std::string text, ID3DXFont* font)
{
	RECT r;
	font->DrawTextA(NULL, text.c_str(), -1, &r, DT_CALCRECT, 0xFFFFFFFF);
	return r;
}

int render::text_width(std::string text, ID3DXFont* font)
{
	RECT r = text_dimension(text, font);
	return r.right - r.left;
}

int render::text_height(std::string text, ID3DXFont* font)
{
	RECT r = text_dimension(text, font);
	return r.bottom - r.top;
}
