#pragma once
#include <vector>
#include <cstdarg>

using std::vector;

template <typename T>
class matrix {
public:
	matrix();
	matrix(int M, int N);
	matrix(const matrix<T>&);
	~matrix();
	void newMatrix(int M, int N);
	void setMatrix(T Element ...);
	template <typename T>
	friend vector<T> operator*(const matrix<T>&, const vector<T>& a);
	matrix& operator=(const matrix<T>&);
private:
	int rows;
	int cols;
	vector<T>* data;
};

template <typename T>
matrix<T>::matrix() : data(nullptr), rows(0), cols(0) {}
template <typename T>
matrix<T>::matrix(int N, int M) {
	data = nullptr;
	newMatrix(N, M);
}
template <typename T>
matrix<T>::matrix(const matrix<T>& B) {
	int i;
	data = nullptr;
	newMatrix(B.rows, B.cols);
	for (i = 0; i < cols; ++i)
		data[i] = B.data[i];
}
template <typename T>
matrix<T>::~matrix() {
	newMatrix(0, 0);
}
template <typename T>
void matrix<T>::newMatrix(int N, int M) {
	int i;
	if (data) delete[] data;
	if (N && M) {
		data = new vector<T>[M];
		for (i = 0; i < M; ++i)
			data[i].resize(N);
		rows = N;
		cols = M;
	}
	else {
		data = nullptr;
		rows = cols = 0;
	}
}
template <typename T>
void matrix<T>::setMatrix(T Element ...) {
	int i, j;
	va_list ap;
	va_start(ap, Element);
	data[0][0] = Element;
	for (j = 1; j < cols; j++) {
		data[j][0] = (T)va_arg(ap, double);
	}
	for (i = 1; i < rows; ++i)
		for (j = 0; j < cols; j++) {
			data[j][i] = (T)va_arg(ap, double);
		}
	va_end(ap);
}
template <typename T>
matrix<T>& matrix<T>::operator=(const matrix& B) {
	int i;
	if (this != &B) {
		if (rows != B.rows || cols != B.cols) {
			delete[] data;
			newMatrix(B.rows, B.cols);
		}
		for (i = 0; i < cols; ++i)
			data[i] = B.data[i];
	}
	return *this;
}
template <typename T>
vector<T> operator*(const matrix<T>& A, const vector<T>& a) {
	int i, j;
	vector<T> resVector;
	resVector.resize(a.size());
	for (i = 0; i < A.rows; ++i) {
		resVector[i] = 0;
		for (j = 0; j < A.cols; ++j) {
			resVector[i] += A.data[j][i] * a[j];
		}
	}
	return resVector;
}
