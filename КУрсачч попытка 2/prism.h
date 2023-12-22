#pragma once
#include "main.h"

class prism : public figure {
public:
	prism(BitMap* bmp);
	void ClrBitMap();
	void SetBitMap();
private:
	void SetShadow(COLORREF c);
};
