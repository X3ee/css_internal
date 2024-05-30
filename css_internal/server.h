#pragma once

/*

sub_10050390 proc near
push    offset aMaxBytesSecThe ; "Max bytes/sec the host can receive data"
push    280h
push    offset a80000   ; "80000"
push    offset aRate    ; "rate"
mov     ecx, offset dword_10621B18
call    sub_102477D0
push    offset sub_102E71B0 ; void (__cdecl *)()
mov     dword_10621B18, offset ??_7CBoundedCvar_Rate@@6B@ ; const CBoundedCvar_Rate::`vftable'
mov     dword_10621B30, offset ??_7CBoundedCvar_Rate@@6B@_0 ; const CBoundedCvar_Rate::`vftable'
call    _atexit
pop     ecx
retn
sub_10050390 endp

*/

struct server
{



};