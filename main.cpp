
//
// TBB baseline project
//

#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <cmath>
#include <complex>
#include <tbb/tbb.h>
#include <FreeImage\FreeImagePlus.h>

#include "image.h"



void main(void) {

	image::convert_serial();
	//image::luminance_serial();
	//image::convertback_serial();

	//image::convert();
	//image::luminance();
	//image::convertback();

}