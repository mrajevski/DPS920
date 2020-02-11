#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
	char opt = '\0';
	
	while (opt == '\0') {
		cout << "Run part 1 or 2?: ";
		cin >> opt;
		if (opt != '1' && opt != '2') {
			opt = '\0';
			cout << "Invalid option." << endl;
		}
	}

	cv::Mat image = cv::imread("./subaruWRX.jpg", cv::IMREAD_COLOR);

	if (image.empty()) {
		cout << "Could not read image file.";
		cv::waitKey();
		return -1;
	}

	cv::namedWindow("Before:", cv::WINDOW_AUTOSIZE);
	cv::imshow("Before:", image);
	cv::waitKey(10);

	cout << endl << "Running Part " << opt << endl << "---------------" << endl << endl;

	if (opt == '1') {

		cv::Mat greyscale, grey_hist;
			
		cv::cvtColor(image, greyscale, CV_BGR2GRAY);
		cv::namedWindow("After Greyscale:", cv::WINDOW_AUTOSIZE);
		cv::imshow("After Greyscale:", greyscale);

		cv::equalizeHist(greyscale, grey_hist);
		cv::namedWindow("After Histogram Equalization:", cv::WINDOW_AUTOSIZE);
		cv::imshow("After Histogram Equalization:", grey_hist);

		cv::waitKey();
		return 0;

	} else if (opt == '2') {

		cv::Mat x(image.rows, image.cols, CV_32FC1);
		cv::RNG rng;
		rng.fill(x, cv::RNG::UNIFORM, 0.0f, 1.0f);

		float p = 0.0;
		cout << "Please enter a probability value(0.0 - 1.0): ";
		cin >> p;

		// Salt and Pepper //
		cv::Mat saltandpepper;
		image.copyTo(saltandpepper);

		for (int i = 0; i < saltandpepper.rows; i++) {
			for (int j = 0; j < saltandpepper.cols; j++) {
				if (x.at<float>(i, j) < p) {
					uchar y = rng.uniform(0.0f, 1.0f) * 255;
					saltandpepper.at<cv::Vec3b>(i, j) = cv::Vec3b(y, y, y);
				}
			}
		}

		cv::namedWindow("Salt and Pepper Image:", cv::WINDOW_AUTOSIZE);
		cv::imshow("Salt and Pepper Image:", saltandpepper);
		cv::waitKey(10);

		// Blurred //
		cv::Mat blurred;
		cv::blur(saltandpepper, blurred, cv::Size(3, 3));

		cv::namedWindow("Blurred Image:", cv::WINDOW_AUTOSIZE);
		cv::imshow("Blurred Image:", blurred);
		cv::waitKey(10);

		// 3x3 Bilinear Filter //

		cv::Mat bilinear;
		cv::Matx<float, 3, 3> kernel = cv::Matx<float, 3, 3>::all(1.0f / 16.0f);
		kernel = kernel.mul(cv::Matx<int, 3, 1>({ 1, 2, 1 }) * cv::Matx<int, 1, 3>({ 1, 2, 1 }));
		cv::filter2D(saltandpepper, bilinear, CV_8UC3, kernel);

		cv::namedWindow("Bilinear Filtered Image:", cv::WINDOW_AUTOSIZE);
		cv::imshow("Bilinear Filtered Image:", bilinear);
		cv::waitKey(10);

		// Median Filter //

		cv::Mat median;
		cv::medianBlur(saltandpepper, median, 3);

		cv::namedWindow("Median Filtered Image:", cv::WINDOW_AUTOSIZE);
		cv::imshow("Median Filtered Image:", median);
		cv::waitKey(10);

		cv::waitKey();

		return 0;

	} else {

		cout << "Invalid Option: " << opt;
		cv::waitKey();
		return -1;
	
	}

}