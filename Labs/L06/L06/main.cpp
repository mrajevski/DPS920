#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {

	char opt = '\0';

	while (opt == '\0') {
		cout << "Which part did you want to run?(1 - 2): ";
		cin >> opt;
		if (opt != '1' && opt != '2') {
			opt = '\0';
			cout << "Incorrect value." << endl;
		}
	}

	cout << "Loading part " << opt << endl
		<< "---------------" << endl;

	cv::Mat image;

	if (opt == '1') {

		image = cv::imread("subaruWRX.jpg", cv::IMREAD_GRAYSCALE);
		if (image.empty()) {
			cout << "Could not load image.";
			return -1;
		}

		cv::namedWindow("Before:", cv::WINDOW_AUTOSIZE);
		cv::imshow("Before:", image);

		cv::Mat binaryimage;
		cv::threshold(image, binaryimage, 128, 255, cv::THRESH_BINARY);

		cv::namedWindow("Binary:", cv::WINDOW_AUTOSIZE);
		cv::imshow("Binary:", binaryimage);

		cv::Mat kernel3x3 = 255 * cv::Mat::ones(3, 3, CV_8UC1);
		cv::Mat kernel7x7 = 255 * cv::Mat::ones(7, 7, CV_8UC1);

		cv::Mat morphedopen3x3, morphedclosed3x3, morphedopen7x7, morphedclosed7x7;
		cv::morphologyEx(binaryimage, morphedopen3x3, cv::MORPH_OPEN, kernel3x3);
		cv::morphologyEx(binaryimage, morphedclosed3x3, cv::MORPH_CLOSE, kernel3x3);
		cv::morphologyEx(binaryimage, morphedopen7x7, cv::MORPH_OPEN, kernel7x7);
		cv::morphologyEx(binaryimage, morphedclosed7x7, cv::MORPH_CLOSE, kernel7x7);

		cv::namedWindow("Morphed Open 3x3:", cv::WINDOW_AUTOSIZE);
		cv::imshow("Morphed Open 3x3:", morphedopen3x3);

		cv::namedWindow("Morphed Closed 3x3:", cv::WINDOW_AUTOSIZE);
		cv::imshow("Morphed Closed 3x3:", morphedclosed3x3);

		cv::namedWindow("Morphed Open 7x7:", cv::WINDOW_AUTOSIZE);
		cv::imshow("Morphed Open 7x7:", morphedopen7x7);

		cv::namedWindow("Morphed Closed 7x7:", cv::WINDOW_AUTOSIZE);
		cv::imshow("Morphed Closed 7x7:", morphedclosed7x7);

		cv::waitKey();


	} else if (opt == '2') {

		opt = '\0';
		int rotateangle = 0, angle = 0;
		float xfactor = 1.0f, yfactor = 1.0f;
		cv::Matx<float, 3, 3> H = cv::Matx<float, 3, 3>(0.4, -0.4, 190, 0.15, 0.4, 100, 0, 0, 1);
		image = cv::imread("subaruWRX.jpg", cv::IMREAD_COLOR);
		if (image.empty()) {
			cout << "Could not load image.";
			return -1;
		}

		cv::Mat alteredimage, temp;
		image.copyTo(alteredimage);
		cv::namedWindow("Altered Image:", cv::WINDOW_AUTOSIZE);
		cv::imshow("Altered Image:", alteredimage);

		cv::waitKey(10);

		for (bool i = true; i;) {
			cout << "What would you like to do?" << endl
				<< "---------------------------" << endl
				<< "Rotate: R" << endl
				<< "Resize: S" << endl
				<< "Perspective Transformation: P" << endl
				<< "Exit: X" << endl;
			while (opt == '\0') {
				cin >> opt;
				if (opt >= 65 && opt <= 90) opt += 32;
				switch (opt) {
				case 'r':
					cout << "Rotate selected!" << endl
						<< "What angle would you like to rotate by?:";
					cin >> rotateangle;
					angle += rotateangle;
					cv::warpAffine(image, alteredimage,
						cv::getRotationMatrix2D(cv::Point2f(image.cols / 2, image.rows / 2), angle, 1),
						image.size());
					cv::imshow("Altered Image:", alteredimage);
					cv::waitKey(10);
					break;
				case 's':
					cout << "Resize selected!" << endl
						<< "What would like to set the X scale to?:";
					cin >> xfactor;
					cout << "What would like to set the Y scale to?:";
					cin >> yfactor;
					cv::resize(image, alteredimage, cv::Size(), xfactor, yfactor);
					cv::imshow("Altered Image:", alteredimage);
					cv::waitKey(10);
					break;
				case 'p':
					cv::warpPerspective(image, alteredimage, H, image.size());
					cv::imshow("Altered Image:", alteredimage);
					cv::waitKey(10);
					break;
				case 'x':
					i = false;
					break;
				default:
					cout << "Incorrect value." << endl;
					opt = '\0';
					break;
				}
			}
			opt = '\0';
		}

	} else {
		cout << "Incorrect value.";
		return -1;
	}
	return 0;
}