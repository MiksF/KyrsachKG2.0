#include "main.h"


figure::figure(BitMap* bmp, size_t numVer) {

	Ver = new vector<double>[numVer];
	V = new vector<double>[numVer];
	VerSHDW = new vector<double>[numVer];

	for (size_t i = 0; i < numVer; ++i) {
		Ver[i].resize(figure::dim);
		V[i].resize(figure::dim);
		VerSHDW[i].resize(figure::dim);
	}
	PR.newMatrix(figure::dim, figure::dim);
	PR.setMatrix(
		0.70710678118, -0.40824829046, 0.57735026919, 0.0,
		0.0, 0.81649658092, 0.57735026919, 0.0,
		-0.70710678118, -0.40824829046, 0.57735026919, 0.0,
		0.0, 0.0, 0.0, 1.0
	);
	ROTATE.newMatrix(figure::dim, figure::dim);
	ZOOM.newMatrix(figure::dim, figure::dim);
	center.resize(figure::dim);
	sinAlpha = sin(ANGLE);
	cosAlpha = cos(ANGLE);
	this->numVer = numVer;
	this->bmp = bmp;
	offset = 420;
}
figure::~figure() {
	delete[] Ver;
	delete[] V;
}
void figure::rotate(char ch, char pn) {
	size_t i;
	ClrBitMap();
	switch (ch) {
	case 'x':
		switch (pn) {
		case '+':
			ROTATE.setMatrix(
				1.0, 0.0, 0.0, 0.0,
				0.0, cosAlpha, sinAlpha, -cosAlpha * center[1] + center[1] - sinAlpha * center[2],
				0.0, -sinAlpha, cosAlpha, sinAlpha * center[1] + center[2] - cosAlpha * center[2],
				0.0, 0.0, 0.0, 1.0
			);
			break;
		case '-':
			ROTATE.setMatrix(
				1.0, 0.0, 0.0, 0.0,
				0.0, cosAlpha, -sinAlpha, -cosAlpha * center[1] + center[1] + sinAlpha * center[2],
				0.0, sinAlpha, cosAlpha, -sinAlpha * center[1] + center[2] - cosAlpha * center[2],
				0.0, 0.0, 0.0, 1.0
			);
			break;
		}
		break;
	case 'y':
		switch (pn) {
		case '+':
			ROTATE.setMatrix(
				cosAlpha, 0.0, -sinAlpha, -cosAlpha * center[0] + center[0] + sinAlpha * center[2],
				0.0, 1.0, 0.0, 0.0,
				sinAlpha, 0.0, cosAlpha, -sinAlpha * center[0] + center[2] - cosAlpha * center[2],
				0.0, 0.0, 0.0, 1.0
			);
			break;
		case '-':
			ROTATE.setMatrix(
				cosAlpha, 0.0, sinAlpha, -cosAlpha * center[0] + center[0] - sinAlpha * center[2],
				0.0, 1.0, 0.0, 0.0,
				-sinAlpha, 0.0, cosAlpha, sinAlpha * center[0] + center[2] - cosAlpha * center[2],
				0.0, 0.0, 0.0, 1.0
			);
			break;
		}
		break;
	case 'z':
		switch (pn) {
		case '+':
			ROTATE.setMatrix(
				cosAlpha, sinAlpha, 0.0, -cosAlpha * center[0] + center[0] - sinAlpha * center[1],
				-sinAlpha, cosAlpha, 0.0, sinAlpha * center[0] + center[1] - cosAlpha * center[1],
				0.0, 0.0, 1.0, 0.0,
				0.0, 0.0, 0.0, 1.0
			);
			break;
		case '-':
			ROTATE.setMatrix(
				cosAlpha, -sinAlpha, 0.0, -cosAlpha * center[0] + center[0] + sinAlpha * center[1],
				sinAlpha, cosAlpha, 0.0, -sinAlpha * center[0] + center[1] - cosAlpha * center[1],
				0.0, 0.0, 1.0, 0.0,
				0.0, 0.0, 0.0, 1.0
			);
			break;
		}
		break;
	default:
		return;
	}
	for (i = 0; i < numVer; ++i) {
		Ver[i] = ROTATE * Ver[i];
	}
}
void figure::move(char ch, char pn) {
	size_t i, f = (ch == 'x') ? f = 0 : (ch == 'y') ? f = 1 : f = 2;
	int step;
	ClrBitMap();
	if (pn == '+')
		step = STEP;
	else
		step = -STEP;
	for (i = 0; i < numVer; ++i) {
		Ver[i][f] += step;
	}
	center[f] += step;
}
void figure::zoom(char ch) {
	size_t i;
	ClrBitMap();
	if (ch == '+') {
		ZOOM.setMatrix(
			ZOOM_PLUS, 0.0, 0.0, -ZOOM_PLUS * center[0] + center[0],
			0.0, ZOOM_PLUS, 0.0, -ZOOM_PLUS * center[1] + center[1],
			0.0, 0.0, ZOOM_PLUS, -ZOOM_PLUS * center[2] + center[2],
			0.0, 0.0, 0.0, 1.0
		);
	}
	else {
		ZOOM.setMatrix(
			ZOOM_MINUS, 0.0, 0.0, -ZOOM_MINUS * center[0] + center[0],
			0.0, ZOOM_MINUS, 0.0, -ZOOM_MINUS * center[1] + center[1],
			0.0, 0.0, ZOOM_MINUS, -ZOOM_MINUS * center[2] + center[2],
			0.0, 0.0, 0.0, 1.0
		);
	}
	for (i = 0; i < numVer; ++i) {
		Ver[i] = ZOOM * Ver[i];
	}
}
void figure::SetCenter() {
	center[0] = 0.0;
	center[1] = 0.0;
	center[2] = 0.0;
	center[3] = 1.0;
	for (size_t i = 0; i < numVer; ++i) {
		center[0] += Ver[i][0];
		center[1] += Ver[i][1];
		center[2] += Ver[i][2];
	}
	center[0] /= double(numVer);
	center[1] /= double(numVer);
	center[2] /= double(numVer);
}
double figure::minY() {
	size_t i;
	double min = V[0][1];
	for (i = 1; i < numVer; ++i)
		if (V[i][1] < min)
			min = V[i][1];
	return min;
}
void figure::SetPR() {
	for (size_t i = 0; i < numVer; ++i) {
		V[i] = PR * Ver[i];
		VerSHDW[i] = PR * VerSHDW[i];
	}
}
void figure::Refrash() {
	SetShadow(COLORREF(COL_BMP::shadow));
	SetPR();
	SetBitMap();
}