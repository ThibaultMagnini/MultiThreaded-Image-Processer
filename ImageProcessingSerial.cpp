#include "image.h"

void image::convert_serial() {

	fipImage inputImage;
	if (inputImage.load("Images\\fungus_highres.jpg"))
		std::cout << "Loaded Succesfully!\n";
	else
		std::cout << "Failed to load image!\n";

	inputImage.convertTo24Bits();
	Pixel* inputBuffer = (Pixel*)inputImage.accessPixels();

	int width = inputImage.getWidth();
	int height = inputImage.getHeight();



	fipImage intermediateImage;
	intermediateImage = fipImage(FIT_RGBF, width, height, 96);

	PixelxyY* intermediateBuffer = (PixelxyY*)intermediateImage.accessPixels();



	fipImage outputImage;
	outputImage = fipImage(FIT_BITMAP, width, height, 24);

	Pixel* outputBuffer = (Pixel*)outputImage.accessPixels();



	/*----------------------------------------------------------------------*/

	std::cout << "Converting... RBG to xyY\n";

	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {

			UINT index = i * width + j;

			float x_intermediate = 0.4124 * (float)inputBuffer[index].r + 0.3576 * (float)inputBuffer[index].g + 0.1805 * (float)inputBuffer[index].b;
			float y_intermediate = 0.2126 * (float)inputBuffer[index].r + 0.7152 * (float)inputBuffer[index].g + 0.0722 * (float)inputBuffer[index].b;
			float z_intermediate = 0.0193 * (float)inputBuffer[index].r + 0.1192 * (float)inputBuffer[index].g + 0.9505 * (float)inputBuffer[index].b;

			intermediateBuffer[index].x = x_intermediate / (x_intermediate + y_intermediate + z_intermediate);
			intermediateBuffer[index].y = y_intermediate / (x_intermediate + y_intermediate + z_intermediate);
			intermediateBuffer[index].Y = y_intermediate;

		}
	}

	/*-----------------------------------------------------------------------*/

	std::cout << "Brightness 20% ...\n";


	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {

			UINT index = i * width + j;

			intermediateBuffer[index].Y *= 0.20;

		}
	}

	/*-------------------------------------------------------------------------*/

	std::cout << "Converting Back...\n";

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {

			UINT index = i * width + j;

			float x_intermediate = intermediateBuffer[index].x * (intermediateBuffer[index].Y / intermediateBuffer[index].y);
			float y_intermediate = intermediateBuffer[index].Y;
			float z_intermediate = (1 - intermediateBuffer[index].x - intermediateBuffer[index].y) * (intermediateBuffer[index].Y / intermediateBuffer[index].y);

			outputBuffer[index].r = BYTE(3.2405 * x_intermediate + -1.5371 * y_intermediate + -0.4985 * z_intermediate);
			outputBuffer[index].g = BYTE(-0.9693 * x_intermediate + 1.8760 * y_intermediate + 0.0416 * z_intermediate);
			outputBuffer[index].b = BYTE(0.0556 * x_intermediate + -0.2040 * y_intermediate + 1.0572 * z_intermediate);

		}
	}

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	std::cout << "Time = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microseconds" << std::endl;


	std::cout << "Saving...\n";

	if (outputImage.save("Images\\fungus_highres1.jpg")) {
		std::cout << "Succes Saving!\n";
	}
	else {
		std::cout << "Failed Saving!\n";
	}

}

