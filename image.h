#ifndef IMAGE_H
#define IMAGE_H

#include <tbb/tbb.h>
#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <cmath>
#include <complex>
#include <tbb/tbb.h>
#include <FreeImage\FreeImagePlus.h>


#pragma once
namespace image {

	struct Pixel
	{
		BYTE r, b, g;
	};

	struct PixelxyY
	{
		float x, y, Y;
	};


	void convert(void);
	void luminance(void);
	void convertback(void);

}

#endif // IMAGE_H