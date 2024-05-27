#pragma once

#include "framework.h"
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3dx9.lib")
struct vertex {
	float x, y, z, rhw;
	unsigned long color;
};

//
//  HRESULTs are 32 bit values laid out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +-+-+-+-+-+---------------------+-------------------------------+
//  |S|R|C|N|r|    Facility         |               Code            |
//  +-+-+-+-+-+---------------------+-------------------------------+

struct render {
public:
	IDirect3DDevice9* d3d_device = {};
	ID3DXLine* d3d_line = {};
	D3DVIEWPORT9                             d3d_viewport = {};
	IDirect3DStateBlock9* d3d_block = {};

	struct fonts {
	public:
		ID3DXFont* d3d_font = {};

	};
public:
	void initialize(IDirect3DDevice9* device);
	void remove();

	void startrenderstate(IDirect3DDevice9* device);
	void endrenderstate(IDirect3DDevice9* device);

	void create_objects();

	void draw_line(int x0, int y0, int x1, int y1, unsigned long color);
	void draw_rect(int x, int y, int w, int h, unsigned long color);
	void draw_filled_rect(int x, int y, int w, int h, unsigned long color);
	void draw_outlined_rect(int x, int y, int w, int h, unsigned long color);
	void text(std::string text, int x, int y, ID3DXFont* font, unsigned long color, bool center, bool outline);

	unsigned long textcolor(float col[4]);

	RECT text_dimension(std::string text, ID3DXFont* font);
	int text_width(std::string text, ID3DXFont* font);
	int text_height(std::string text, ID3DXFont* font);
};
extern render g_render;
extern render::fonts g_fonts;