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
#include <chrono>


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


	void convert();
	void convert_serial();
}

#endif // IMAGE_H