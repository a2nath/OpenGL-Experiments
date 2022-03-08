#pragma once
#include <math.h>
#include <iostream>
#include <string>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
using namespace cv;
namespace Core
{
	namespace Init
	{
		class EquilizeImage
		{
		public:
			EquilizeImage(std::string name);
		private:
			void imhist(Mat image, int histogram[]);
			void cumhist(int histogram[], int cumhistogram[]);
			void histDisplay(int histogram[], const char* name);
		};
	}
}