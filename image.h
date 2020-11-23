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
		BYTE r, g, b;
	};

	struct PixelxyY
	{
		float x, y, Y;
	};


	void convert(void);
	void luminance(void);
	void convertback(void);

	void convert_serial(void);
	void luminance_serial(void);
	void convertback_serial(void);

}

#endif // IMAGE_H