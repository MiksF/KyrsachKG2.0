
#pragma once
#include <windows.h>

#define RGB_BMP(r, g ,b)  ((COLORREF)(((BYTE)(b)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(r))<<16)))

class BitMap {
public:
	BitMap(int w, int h, int x0, int y0, COLORREF col);
	~BitMap();
	void DrawBitmap();
	COLORREF& operator()(int i, int j);
	const int width;
	const int height;
	const int x;
	const int y;
private:
	const int k = 8;
	HDC hDC;
	BITMAP bmp;
	HBITMAP hBitmap;
	COLORREF color;
	COLORREF* mapIMG;

	HBITMAP hOldbm;
	HDC hMemDC;
	BITMAP bm;
	POINT  ptSize, ptOrg;
};