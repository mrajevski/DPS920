#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <time.h>

using namespace std;

int main(int argc, char** agrv) {

	cv::Mat m(480, 640, CV_8UC3, cv::Vec3b(0, 0, 0));
	cv::Size size = m.size();
	cout << "Window Size: " << size.width << " x " << size.height << endl << endl;

	int x = 0, y = 0, rectangleCount = 0;
	string color = "";
	cv::Vec3b rgb; // B G R 
	cv::Point2i p1, p2;
	char img[50];
	srand(time(NULL));

	cv::namedWindow("Lab 03", cv::WINDOW_AUTOSIZE);
	cv::imshow("Lab 03", m);

	for (;;) {

		cv::waitKey(33);

		cout << "Rectangle #" << (rectangleCount + 1) << endl
			<< "----------------------" << endl;

		cout << "Top-Left coordinate (x, y): ";
		for (bool i = false; !i;) {
			cin >> x >> y;
			if ((x < size.width && x >= 0) && (y < size.height && y >= 0)) {
				p1.x = x;
				p1.y = y;
				i = true;
			} else {
				cout << "Coordinates not within valid parameters (" << size.width << ", " << size.height << ")" << endl
					<< "Try Again:";
			}
			x = 0;
			y = 0;
		}

		// It is assumed that the second set of coords are actually the lower right //
		cout << "Bottom-Right coordinate (x, y): ";
		for (bool i = false; !i;) {
			cin >> x >> y;
			if ((x <= size.width && x >= 1) && (y <= size.height && y >= 1)) {
				p2.x = x;
				p2.y = y;
				i = true;
			}
			else {
				cout << "Coordinates not within valid parameters (" << size.width << ", " << size.height << ")" << endl
					<< "Try Again:";
			}
			x = 0;
			y = 0;
		}
		
		cv::Rect2i rectangle(p1, p2);
		rectangleCount++;

		// Color input is stored as acsii code //
		cout << "Rectangle color (Black - k, White - w, Red - r, Green - g, Blue - b" << endl
			<< "Cyan - c, Magenta - m, Yellow - y, Random - x): ";
		for (bool i = false; !i;) {
			cin >> color;
			switch ((int)(color.at(0))) {
			case 107: // Black
				rgb = cv::Vec3b(0, 0, 0);
				i = true;
				cout << endl;
				break;
			case 119: // White
				rgb = cv::Vec3b(255, 255, 255);
				i = true;
				cout << endl;
				break;
			case 114: // Red
				rgb = cv::Vec3b(0, 0, 255);
				i = true;
				cout << endl;
				break;
			case 103: // Green
				rgb = cv::Vec3b(0, 255, 0);
				i = true;
				cout << endl;
				break;
			case 98:  // Blue
				rgb = cv::Vec3b(255, 0, 0);
				i = true;
				cout << endl;
				break;
			case 99:  // Cyan
				rgb = cv::Vec3b(255, 255, 0);
				i = true;
				cout << endl;
				break;
			case 109: // Magenta
				rgb = cv::Vec3b(255, 0, 255);
				i = true;
				cout << endl;
				break;
			case 121: // Yellow
				rgb = cv::Vec3b(0, 255, 255);
				i = true;
				cout << endl;
				break;
			case 120: // Random
				rgb = cv::Vec3b((rand()*10000) % 256, (rand() * 10000) % 256, (rand() * 10000) % 256);
				i = true;
				cout << endl;
				break;
			default:
				cout << "Color specified isn't supported, please use on of the colors listed above." << endl
					<< "Try Again: ";
				break;
			}
			color = "";
		}

		for (int i = rectangle.tl().y; i < (rectangle.tl().y + rectangle.height); i++) {
			for (int j = rectangle.tl().x; j < (rectangle.tl().x + rectangle.width); j++) {
				m.at<cv::Vec3b>(i, j)[0] = rgb[0];
				m.at<cv::Vec3b>(i, j)[1] = rgb[1];
				m.at<cv::Vec3b>(i, j)[2] = rgb[2];
			}
		}

		cv::imshow("Lab 03", m);

		cout << "Area: " << rectangle.area() << endl
			<< "Width: " << rectangle.width << endl
			<< "Height: " << rectangle.height << endl << endl;

		cout << "Enter Coordinates of a Point: ";
		cin >> x >> y;

		cout << "The point (" << x << ", " << y << ")"
			<< (rectangle.contains(cv::Point2i(x, y)) ? " is " : " is not ")
			<< "inside the rectangle" << endl;
			
		string c = "";
		cout << "Continue? (Y/N): ";
		cin >> c;
		
		if (c.at(0) == 'N' || c.at(0) == 'n') {

			sprintf_s(img, "Lab03.jpg", "");
			cv::imwrite(img, m);
			break;
		}

	}


	return 0;







}
