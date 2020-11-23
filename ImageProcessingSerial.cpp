#include "image.h"

void image::convert_serial() {

	fipImage inputImage;
	if (inputImage.load("Images\\test.png"))
		std::cout << "Loaded Succesfully!\n";
	else
		std::cout << "Failed to load image!\n";

	inputImage.convertTo24Bits();
	Pixel* inputBuffer = (Pixel*)inputImage.accessPixels();

	int width = inputImage.getWidth();
	int height = inputImage.getHeight();



	fipImage outputImage;
	outputImage = fipImage(FIT_RGBF, width, height, 96);

	PixelxyY* outputBuffer = (PixelxyY*)outputImage.accessPixels();


	std::cout << "Converting... RBG to xyY\n";

	/*----------------------------------------------------------------------*/
	
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {


			UINT index = i * width + j;

			float x_intermediate = 0.4124 * (float)inputBuffer[index].r + 0.3576 * (float)inputBuffer[index].g + 0.1805 * (float)inputBuffer[index].b;
			float y_intermediate = 0.2126 * (float)inputBuffer[index].r + 0.7152 * (float)inputBuffer[index].g + 0.0722 * (float)inputBuffer[index].b;
			float z_intermediate = 0.0193 * (float)inputBuffer[index].r + 0.1192 * (float)inputBuffer[index].g + 0.9505 * (float)inputBuffer[index].b;

			outputBuffer[index].x = x_intermediate / (x_intermediate + y_intermediate + z_intermediate);
			outputBuffer[index].y = y_intermediate / (x_intermediate + y_intermediate + z_intermediate);
			outputBuffer[index].Y = z_intermediate;

		}
	}

	std::cout << "Saving...\n";

	if (outputImage.save("Images\\test1.png")) {
		std::cout << "succes saving\n";
	}
	else {
		std::cout << "Failed Saving\n";
	}

}

/*===========================================================================================*/

void image::luminance_serial() {

	fipImage inputImage;
	if (inputImage.load("Images\\test1.png"))
		std::cout << "Loaded test 2 Succesfully\n";
	else
		std::cout << "failed to load image!\n";



	inputImage.convertToRGBF();

	Pixel* inputBuffer = (Pixel*)inputImage.accessPixels();

	uint16_t width = inputImage.getWidth();
	uint16_t height = inputImage.getHeight();

	fipImage outputImage;
	outputImage = fipImage(FIT_RGBF, width, height, 48);

	Pixel* outputBuffer = (Pixel*)outputImage.accessPixels();

	std::cout << "going at it\n";

	/*-------------------------------------------------------------------------------*/

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
		
			UINT index = i * width + j;

			outputBuffer[index].b *= 0.2;
		
		}
	}


	std::cout << "saving test2\n";
	outputImage.save("Images\\test2.png");

}


/*===========================================================================================*/

void image::convertback_serial() {

	fipImage inputImage;

	if (inputImage.load("Images\\test1.png"))
		std::cout << "\nLoaded test 2 Succesfully\n";
	else
		std::cout << "failed to load image!";

	inputImage.convertToRGBF();

	Pixel* inputBuffer = (Pixel*)inputImage.accessPixels();

	int width = inputImage.getWidth();
	int height = inputImage.getHeight();

	fipImage outputImage;
	outputImage = fipImage(FIT_RGBF, width, height, 96);

	Pixel* outputBuffer = (Pixel*)outputImage.accessPixels();

	std::cout << "going at it\n";

	/*-------------------------------------------------------------*/

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {


			UINT index = i * width + j;

			float x_intermediate = inputBuffer[index].r * (inputBuffer[index].b / inputBuffer[index].g);
			float y_intermediate = inputBuffer[index].b;
			float z_intermediate = (1 - inputBuffer[index].r - inputBuffer[index].g) * (inputBuffer[index].b / inputBuffer[index].g);

			outputBuffer[index].r = 3.2405 * x_intermediate + -1.5371 * y_intermediate + -0.4985 * z_intermediate;
			outputBuffer[index].g = -0.9693 * x_intermediate + 1.8760 * y_intermediate + 0.0416 * z_intermediate;
			outputBuffer[index].b = 0.0556 * x_intermediate + -0.2040 * y_intermediate + 1.0572 * z_intermediate;

		}
	}

	std::cout << "saving test 3";
	outputImage.convertToType(FREE_IMAGE_TYPE::FIT_BITMAP);
	outputImage.convertTo24Bits();
	outputImage.save("Images\\test3.png");
}
