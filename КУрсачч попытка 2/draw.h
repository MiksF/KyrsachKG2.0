#pragma once
#include "bitmap.h"
#include <vector>

using std::vector;

void shwap(vector<double>** v1, vector<double>** v2, int d);

void paint_trinagle(BitMap* bmp, vector<double>& v1, vector<double>& v2, vector<double>& v3, COLORREF col);

double center_z(vector<double>& v1, vector<double>& v2, vector<double>& v3);
double center_z(vector<double>& v1, vector<double>& v2, vector<double>& v3, vector<double>& v4);