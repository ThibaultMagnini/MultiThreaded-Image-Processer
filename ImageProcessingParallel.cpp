#include "image.h"

/*==================================================================================================================================*/
/*
	Step 1:
		Reading in a Image with RBG pixels -> Converting the pixels from RBG to xyY.
		Parallel solution
*/

// TODO Fix image not saving after RBG to xyY conversion -> probalvly because of wrong outputImage Type choice (FIT_FLOAT?, FIT_RBGF?)  
// ERROR Write Violation, PROBABLY also because of wrong type choice

void image::convert() {

	fipImage inputImage;
	if (inputImage.load("Images\\beetle.jpg"))
		std::cout << "Loaded Succesfully!\n";
	else
		std::cout << "Failed to load image!\n";

	inputImage.convertTo24Bits();

	Pixel* inputBuffer = (Pixel*)inputImage.accessPixels();

	uint16_t width = inputImage.getWidth();
	uint16_t height = inputImage.getHeight();

	fipImage outputImage;
	outputImage = fipImage(FIT_FLOAT, width, height, 6);

	PixelxyY* outputBuffer = (PixelxyY*)outputImage.accessPixels();

	std::cout << "Converting... RBG to xyY\n";

	tbb::parallel_for(

		tbb::blocked_range2d<int, int>(0, width, 0, height),
		[&](const tbb::blocked_range2d<int, int>& range) {

			for (uint16_t i = range.rows().begin(); i < range.rows().end(); i++) {

				for (uint16_t j = range.cols().begin(); j < range.cols().end(); j++) {

					UINT index = i * width + j;

					float x_intermediate = 0.4124 * (float)inputBuffer[index].r + 0.3576 * (float)inputBuffer[index].g + 0.1805 * (float)inputBuffer[index].b;
					float y_intermediate = 0.2126 * (float)inputBuffer[index].r + 0.7152 * (float)inputBuffer[index].g + 0.0722 * (float)inputBuffer[index].b;
					float z_intermediate = 0.0193 * (float)inputBuffer[index].r + 0.1192 * (float)inputBuffer[index].g + 0.9505 * (float)inputBuffer[index].b;

					outputBuffer[index].x = x_intermediate / (x_intermediate + y_intermediate + z_intermediate);
					outputBuffer[index].y = y_intermediate / (x_intermediate + y_intermediate + z_intermediate);
					outputBuffer[index].Y = z_intermediate;


				}

			}

		}
	);

	std::cout << "Saving...";
	outputImage.save("Images\\lumin.jpg");

}



/*==============================================================================================================================================*/
/*
	Step 2:
		Reading in a Image with xyY pixels -> Converting the pixels from xyY to RBG.
		Parallel solution
*/


void image::convertback() {
	fipImage inputImage;
	if (inputImage.load("Images\\lumin20.jpg"))
		std::cout << "Loaded Succesfully\n";
	else
		std::cout << "failed to load image!\n";
	

	inputImage.convertTo24Bits();

	PixelxyY* inputBuffer = (PixelxyY*)inputImage.accessPixels();

	uint16_t width = inputImage.getWidth();
	uint16_t height = inputImage.getHeight();

	fipImage outputImage;
	outputImage = fipImage(FIT_BITMAP, width, height, 24);

	Pixel* outputBuffer = (Pixel*)outputImage.accessPixels();

	std::cout << "going at it\n";

	tbb::parallel_for(

		tbb::blocked_range2d<int, int>(0, width, 0, height),
		[&](const tbb::blocked_range2d<int, int>& range) {

			for (uint16_t i = range.rows().begin(); i < range.rows().end(); i++) {

				for (uint16_t j = range.cols().begin(); j < range.cols().end(); j++) {

					UINT index = i * width + j;

					float x_intermediate = inputBuffer[index].x * (inputBuffer[index].Y / inputBuffer[index].y);
					float y_intermediate = inputBuffer[index].Y;
					float z_intermediate = (1 - inputBuffer[index].x - inputBuffer[index].y) * (inputBuffer[index].Y / inputBuffer[index].y);

					outputBuffer[index].r = 3.2405 * x_intermediate + -1.5371 * y_intermediate + -0.4985 * z_intermediate;
					outputBuffer[index].g = -0.9693 * x_intermediate + 1.8760 * y_intermediate + 0.0416 * z_intermediate;
					outputBuffer[index].b = 0.0556 * x_intermediate + -0.2040 * y_intermediate + 1.0572 * z_intermediate;

				}

			}

		}
	);

	std::cout << "saving";
	outputImage.save("Images\\backOrg.jpg");
}

/*============================================================================================================================*/
/*
	Step 3:
		Reading in a Image with xyY pixels -> Decreasing the images luminance (Y) to 20% of its original value.
		Parallel solution
*/


void image::luminance() {

	fipImage inputImage;

	if (inputImage.load("Images\\lumin.jpg")) 
		std::cout << "Loaded Succesfully\n";
	else 
		std::cout << "failed to load image!";

	inputImage.convertTo24Bits();

	PixelxyY* inputBuffer = (PixelxyY*)inputImage.accessPixels();

	uint16_t width = inputImage.getWidth();
	uint16_t height = inputImage.getHeight();

	fipImage outputImage;
	outputImage = fipImage(FIT_FLOAT, width, height, 6);

	PixelxyY* outputBuffer = (PixelxyY*)outputImage.accessPixels();

	tbb::parallel_for(

		tbb::blocked_range2d<int, int>(0, width, 0, height),
		[&](const tbb::blocked_range2d<int, int>& range) {

			for (uint16_t i = range.rows().begin(); i < range.rows().end(); i++) {

				for (uint16_t j = range.cols().begin(); j < range.cols().end(); j++) {

					UINT index = i * width + j;

					outputBuffer[index].Y = inputBuffer[index].Y * 0.2;

				}

			}

		}
	);


	outputImage.save("Images\\lumin20.jpg");
}