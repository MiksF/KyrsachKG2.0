
#pragma once
#include "main.h"

class parallelepiped : public figure {
public:
	parallelepiped(BitMap* bmp);
	void ClrBitMap();
	void SetBitMap();
private:
	void SetShadow(COLORREF c);
};
