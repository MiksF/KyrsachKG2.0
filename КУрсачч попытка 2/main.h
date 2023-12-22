#pragma once

#include <windows.h>
#include "matrix.h"
#include "bitmap.h"
#include "draw.h"

#define PI 3.141592

enum class DIM_BMP_ONE {
	left_margin = 10,
	top_margin = 10,
	width = 600,
	height = 610
};
enum class DIM_BMP_TWO {
	left_margin = 616,
	top_margin = 10,
	width = 600,
	height = 610
};

enum class COL_BMP {
	clear = RGB_BMP(255, 255, 255),
	shadow = RGB_BMP(30, 30, 30),
};

enum class COLS {
	zero = RGB_BMP(200, 50, 200),
	one = RGB_BMP(50, 200, 200),
	two = RGB_BMP(123, 104, 238),
	three = RGB_BMP(255, 165, 31),
	four = RGB_BMP(244, 66, 140),
	five = RGB_BMP(15, 222, 17)
};
enum class NUM_VER {
	prism = 6,
	cube = 8
};

enum class LIGHT {
	x = 400,
	y = -250,
	z = 150,
	offset_Y = 500
};

const double ANGLE = 0.05;
const int STEP = 6;
const double ZOOM_PLUS = 1.25;
const double ZOOM_MINUS = 1 / ZOOM_PLUS;

class figure {
public:
	enum { dim = 4 };
	figure(BitMap* bmp, size_t numVer);
	~figure();

	void rotate(char, char);
	void move(char, char);
	void zoom(char);

	virtual void SetBitMap() = 0;
	virtual void ClrBitMap() = 0;

	void Refrash();
protected:
	double sinAlpha;
	double cosAlpha;

	vector<double> center;
	void SetCenter();

	vector<double>* Ver;
	vector<double>* V;
	size_t numVer;

	matrix<double> ROTATE;
	matrix<double> ZOOM;

	matrix<double> PR;
	void SetPR();

	BitMap* bmp;

	double minY();
	int offset;

	vector<double>* VerSHDW;

	virtual void SetShadow(COLORREF c) = 0;
};
