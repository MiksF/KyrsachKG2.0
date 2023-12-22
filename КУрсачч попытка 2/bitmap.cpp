#include "bitmap.h"

BitMap::BitMap(int w, int h, int x0, int y0, COLORREF col) : width(w), height(h), x(x0), y(y0) {
	hDC = GetDC(GetConsoleWindow());
	color = col;
	mapIMG = new COLORREF[width * height * k];
	for (int i = 0; i < width * height * k; ++i)
		mapIMG[i] = col;
	bmp = { 0, w, h, 32 * w, 1, 32, NULL };
	bmp.bmBits = (COLORREF*)mapIMG;

	bm = {};
	hOldbm = {};
	ptSize = {};
	ptOrg = {};
	hBitmap = {};
	hMemDC = {};

}
BitMap::~BitMap() {
	delete[] mapIMG;
}
COLORREF& BitMap::operator()(int i, int j) {
	return mapIMG[i * width * k + j];
}
void BitMap::DrawBitmap() {
	hBitmap = CreateBitmapIndirect(&bmp);

	hMemDC = CreateCompatibleDC(hDC);

	hOldbm = (HBITMAP)SelectObject(hMemDC, hBitmap);

	if (hOldbm) {
		SetMapMode(hMemDC, GetMapMode(hDC));

		GetObject(hBitmap, sizeof(BITMAP), (COLORREF*)&bm);

		ptSize.x = bm.bmWidth;
		ptSize.y = bm.bmHeight;

		DPtoLP(hDC, &ptSize, 1);

		ptOrg.x = 0;
		ptOrg.y = 0;


		DPtoLP(hMemDC, &ptOrg, 1);

		BitBlt(hDC, x, y, ptSize.x, ptSize.y,
			hMemDC, ptOrg.x, ptOrg.y, SRCCOPY);

		SelectObject(hMemDC, hOldbm);
	}
	else {
		system("pause");
	}

	DeleteDC(hMemDC);
	DeleteObject(hBitmap);
}