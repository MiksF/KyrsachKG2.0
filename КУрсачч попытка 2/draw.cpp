#include "draw.h"

void shwap(vector<double>** v1, vector<double>** v2, int d) {
	if ((**v1)[d] > (**v2)[d]) {
		vector<double>* V = *v1;
		*v1 = *v2;
		*v2 = V;
	}
}

double get_coor_X(vector<double>& v1, vector<double>& v2, double y) {
	return ((v2[0] - v1[0]) * (y - v1[1]) / (v2[1] - v1[1]) + v1[0]);
}

void paint_trinagle(BitMap* bmp, vector<double>& v1, vector<double>& v2, vector<double>& v3, COLORREF col) {
	double j;
	int k, K;
	double Xa, Xb;

	vector<double>* v1_ptr = &v1, * v2_ptr = &v2, * v3_ptr = &v3;
	shwap(&v1_ptr, &v2_ptr, 1);
	shwap(&v1_ptr, &v3_ptr, 1);
	shwap(&v2_ptr, &v3_ptr, 1);

	for (j = (*v1_ptr)[1]; j < (*v2_ptr)[1]; j += 0.5) {

		if (j < 0) continue;
		if (j >= bmp->height) break;

		Xa = get_coor_X((*v1_ptr), (*v2_ptr), j);
		Xb = get_coor_X((*v1_ptr), (*v3_ptr), j);

		K = int(max(Xa, Xb));
		for (k = int(min(Xa, Xb)); k < K; ++k) {

			if (k < 0) continue;
			if (k >= bmp->width) break;

			(*bmp)(int(j), k) = col;
		}
	}
	for (j = (*v2_ptr)[1]; j < (*v3_ptr)[1]; j += 0.5) {

		if (j < 0) continue;
		if (j >= bmp->height) break;

		Xa = get_coor_X((*v2_ptr), (*v3_ptr), j);
		Xb = get_coor_X((*v1_ptr), (*v3_ptr), j);

		K = int(max(Xa, Xb));
		for (k = int(min(Xa, Xb)); k < K; ++k) {

			if (k < 0) continue;
			if (k >= bmp->width) break;

			(*bmp)(int(j), k) = col;
		}
	}
}

double center_z(vector<double>& v1, vector<double>& v2, vector<double>& v3) {
	return  (v1[2] + v2[2] + v3[2]) / 3;
}
double center_z(vector<double>& v1, vector<double>& v2, vector<double>& v3, vector<double>& v4) {
	return  (v1[2] + v2[2] + v3[2] + v4[2]) / 4;
}