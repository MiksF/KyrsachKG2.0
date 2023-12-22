#include "prism.h"

prism::prism(BitMap* bmp) : figure(bmp, (size_t)(NUM_VER::prism)) {



	Ver[0] = { 90.0, 90.0, 90.0, 1.0 };
	Ver[1] = { 140.0, 90.0, 90.0, 1.0 };
	Ver[2] = { 90.0, 140.0, 90.0, 1.0 };
	Ver[3] = { 90.0, 90.0, 140.0, 1.0 };
	Ver[4] = { 140.0, 90.0, 140.0, 1.0 };
	Ver[5] = { 90.0, 140.0, 140.0, 1.0 };

	SetShadow(COLORREF(COL_BMP::shadow));
	SetPR();
	SetCenter();
	SetBitMap();
}
void prism::ClrBitMap() {

	paint_trinagle(bmp, VerSHDW[0], VerSHDW[1], VerSHDW[2], COLORREF(COL_BMP::clear));
	paint_trinagle(bmp, VerSHDW[0], VerSHDW[1], VerSHDW[3], COLORREF(COL_BMP::clear));
	paint_trinagle(bmp, VerSHDW[1], VerSHDW[3], VerSHDW[4], COLORREF(COL_BMP::clear));
	paint_trinagle(bmp, VerSHDW[1], VerSHDW[2], VerSHDW[5], COLORREF(COL_BMP::clear));
	paint_trinagle(bmp, VerSHDW[1], VerSHDW[4], VerSHDW[5], COLORREF(COL_BMP::clear));
	paint_trinagle(bmp, VerSHDW[0], VerSHDW[2], VerSHDW[5], COLORREF(COL_BMP::clear));
	paint_trinagle(bmp, VerSHDW[0], VerSHDW[3], VerSHDW[5], COLORREF(COL_BMP::clear));
	paint_trinagle(bmp, VerSHDW[3], VerSHDW[4], VerSHDW[5], COLORREF(COL_BMP::clear));

	paint_trinagle(bmp, V[0], V[1], V[2], COLORREF(COL_BMP::clear));
	paint_trinagle(bmp, V[0], V[1], V[3], COLORREF(COL_BMP::clear));
	paint_trinagle(bmp, V[1], V[3], V[4], COLORREF(COL_BMP::clear));
	paint_trinagle(bmp, V[1], V[2], V[5], COLORREF(COL_BMP::clear));
	paint_trinagle(bmp, V[1], V[4], V[5], COLORREF(COL_BMP::clear));
	paint_trinagle(bmp, V[0], V[2], V[5], COLORREF(COL_BMP::clear));
	paint_trinagle(bmp, V[0], V[3], V[5], COLORREF(COL_BMP::clear));
	paint_trinagle(bmp, V[3], V[4], V[5], COLORREF(COL_BMP::clear));

}
void prism::SetShadow(COLORREF c) {

	size_t i;
	double d;
	for (i = 0; i < numVer; ++i) {
		d = Ver[i][0] - double(LIGHT::x);
		d /= (Ver[i][1] - double(LIGHT::y));
		d *= (double(LIGHT::offset_Y) - Ver[i][1]);
		d += Ver[i][0];
		VerSHDW[i][0] = d;
		VerSHDW[i][1] = double(LIGHT::offset_Y);
		d = Ver[i][2] - double(LIGHT::z);
		d /= (Ver[i][1] - double(LIGHT::y));
		d *= (double(LIGHT::offset_Y) - Ver[i][1]);
		d += Ver[i][2];
		VerSHDW[i][2] = d;
		VerSHDW[i][3] = 1.0;
	}

}
void prism::SetBitMap() {
	size_t i, j, k;
	size_t mas[6] = { 0, 1, 2, 3, 4 };
	double swp;
	double center[6];

	center[0] = center_z(V[0], V[1], V[2]);
	center[1] = center_z(V[0], V[1], V[3], V[4]);
	center[2] = center_z(V[1], V[2], V[4], V[5]);
	center[3] = center_z(V[0], V[2], V[3], V[5]);
	center[4] = center_z(V[3], V[4], V[5]);

	for (i = 0; i < 6; ++i) {
		k = i;
		for (j = i; j < 6; ++j)
			if (center[k] > center[j])
				k = j;
		if (i != k) {
			swp = center[i];
			center[i] = center[k];
			center[k] = swp;

			j = mas[i];
			mas[i] = mas[k];
			mas[k] = j;
		}

	}

	paint_trinagle(bmp, VerSHDW[0], VerSHDW[1], VerSHDW[2], COLORREF(COL_BMP::shadow));
	paint_trinagle(bmp, VerSHDW[0], VerSHDW[1], VerSHDW[3], COLORREF(COL_BMP::shadow));
	paint_trinagle(bmp, VerSHDW[1], VerSHDW[3], VerSHDW[4], COLORREF(COL_BMP::shadow));
	paint_trinagle(bmp, VerSHDW[1], VerSHDW[2], VerSHDW[5], COLORREF(COL_BMP::shadow));
	paint_trinagle(bmp, VerSHDW[1], VerSHDW[4], VerSHDW[5], COLORREF(COL_BMP::shadow));
	paint_trinagle(bmp, VerSHDW[0], VerSHDW[2], VerSHDW[5], COLORREF(COL_BMP::shadow));
	paint_trinagle(bmp, VerSHDW[0], VerSHDW[3], VerSHDW[5], COLORREF(COL_BMP::shadow));
	paint_trinagle(bmp, VerSHDW[3], VerSHDW[4], VerSHDW[5], COLORREF(COL_BMP::shadow));

	for (i = 0; i < 6; ++i) {
		switch (mas[i]) {
		case 0:
			paint_trinagle(bmp, V[0], V[1], V[2], COLORREF(COLS::zero));

			break;
		case 1:
			paint_trinagle(bmp, V[0], V[1], V[3], COLORREF(COLS::one));
			paint_trinagle(bmp, V[1], V[3], V[4], COLORREF(COLS::one));

			break;
		case 2:
			paint_trinagle(bmp, V[1], V[2], V[5], COLORREF(COLS::two));
			paint_trinagle(bmp, V[1], V[4], V[5], COLORREF(COLS::two));

			break;
		case 3:
			paint_trinagle(bmp, V[0], V[2], V[5], COLORREF(COLS::three));
			paint_trinagle(bmp, V[0], V[3], V[5], COLORREF(COLS::three));

			break;
		case 4:
			paint_trinagle(bmp, V[3], V[4], V[5], COLORREF(COLS::four));

			break;
		}
	}
}