#include <conio.h>
#include "prism.h"
#include "paral.h"


int main() {

	system("color 38");



	int c;
	char flag = '+';
	BitMap bmp_one(
		2 * (int)(DIM_BMP_ONE::width),
		(int)(DIM_BMP_ONE::height),
		(int)(DIM_BMP_ONE::left_margin),
		(int)(DIM_BMP_ONE::top_margin),
		(COLORREF)(COL_BMP::clear)
	);
	prism mc(&bmp_one);
	parallelepiped mp(&bmp_one);
	figure* ptr = &mc;

	bmp_one.DrawBitmap();
	while (1) {
		c = _getch();
		switch (c) {
		case 43:
			ptr->move('z', '+');
			mc.Refrash();
			mp.Refrash();
			bmp_one.DrawBitmap();
			break;
		case 45:
			ptr->move('z', '-');
			mc.Refrash();
			mp.Refrash();
			bmp_one.DrawBitmap();
			break;
		case 72:
			ptr->move('y', '-');
			mc.Refrash();
			mp.Refrash();
			bmp_one.DrawBitmap();
			break;
		case 77:
			ptr->move('x', '+');
			mc.Refrash();
			mp.Refrash();
			bmp_one.DrawBitmap();
			break;
		case 80:
			ptr->move('y', '+');
			mc.Refrash();
			mp.Refrash();
			bmp_one.DrawBitmap();
			break;
		case 75:
			ptr->move('x', '-');
			mc.Refrash();
			mp.Refrash();
			bmp_one.DrawBitmap();
			break;
		case 49:
			ptr = &mc;
			break;
		case 50:
			ptr = &mp;
			break;
		case 32:
			(flag == '+') ? flag = '-' : flag = '+';
			break;
		case 120:
			ptr->rotate('x', flag);
			mc.Refrash();
			mp.Refrash();
			bmp_one.DrawBitmap();
			break;
		case 121:
			ptr->rotate('y', flag);
			mc.Refrash();
			mp.Refrash();
			bmp_one.DrawBitmap();
			break;
		case 122:
			ptr->rotate('z', flag);
			mc.Refrash();
			mp.Refrash();
			bmp_one.DrawBitmap();
			break;
		case 115:
			ptr->zoom('-');
			mc.Refrash();
			mp.Refrash();
			bmp_one.DrawBitmap();
			break;
		case 116:
			ptr->zoom('+');
			mc.Refrash();
			mp.Refrash();
			bmp_one.DrawBitmap();
			break;
		}
	}


	return 0;
}
