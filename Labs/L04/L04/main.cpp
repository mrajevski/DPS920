#include <opencv2/opencv.hpp>
#include <string>

void mouseCallback(int event, int x, int y, int flag, void* param), drawBox(cv::Mat& img, cv::Rect box, char shape), configText();
cv::Rect box;
cv::Scalar color(0x00, 0x00, 0xDD);
bool drawing = false, ctrl = false, shift = false;
const std::string text = "My Text Application!";
int fontface = cv::FONT_HERSHEY_SCRIPT_SIMPLEX, baseline = 0;
double fontscale = 1.0;
cv::Point origin;
cv::Size textsize;

using namespace std;

int main(int argc, char** argv) {

	box = cv::Rect(-1, -1, 0, 0);
	cv::Mat image(480, 640, CV_8UC3), tmp;
	image.copyTo(tmp);
	image = cv::Scalar::all(0);

	cv::namedWindow("Lab 04", cv::WINDOW_AUTOSIZE);

	cv::setMouseCallback(
		"Lab 04",
		mouseCallback,
		(void*)&image
	);

	cv::moveWindow("Lab 04", 10, 30);

	configText();

	for (;;) {

		image.copyTo(tmp);

		cv::line(tmp, origin + cv::Point(0, 1), origin + cv::Point(textsize.width, 1), cv::Scalar(0x33, 0x33, 0xFF));
		cv::putText(tmp, text, origin, fontface, fontscale, cv::Scalar(0xFF, 0xFF, 0xFF));

		if (drawing) {
			if (shift) drawBox(tmp, box, 'c');
			else if (ctrl) drawBox(tmp, box, 'e');
			else drawBox(tmp, box, 'r');
		}
		cv::imshow("Lab 04", tmp);
		if (cv::waitKey(15) == 27) {
			cv::destroyWindow("Lab 04");
			break;
		}

	}

	int x = 0;

	cout << "Would you like to save the image? (Y/N): ";
	cin >> x;


	return 0;

}

void mouseCallback(int event, int x, int y, int flag, void* param) {

	cv::Mat& img = *(cv::Mat*)param;
	shift = (flag & cv::EVENT_FLAG_SHIFTKEY) ? true : false;
	ctrl = (flag & cv::EVENT_FLAG_CTRLKEY) ? true : false;

	switch (event) {
	case cv::EVENT_MOUSEMOVE:
		if (drawing) {
			box.width = x - box.x;
			box.height = y - box.y;
		}
		break;
	case cv::EVENT_LBUTTONDOWN:
		drawing = true;
		box = cv::Rect(x, y, 0, 0);
		break;
	case cv::EVENT_LBUTTONUP:
		drawing = false;
		if (box.width < 0) {
			box.x += box.width;
			box.width *= -1;
		}
		if (box.height < 0) {
			box.y += box.height;
			box.height *= -1;
		}

		if (shift) drawBox(img, box, 'c');
		else if (ctrl) drawBox(img, box, 'e');
		else drawBox(img, box, 'r');

		break;
	}

}

void drawBox(cv::Mat& img, cv::Rect box, char shape) {
	int radiusX = (box.br().x - box.tl().x) / 2,
		radiusY = (box.br().y - box.tl().y) / 2;

	if (radiusX < 0) radiusX *= -1;
	if (radiusY < 0) radiusY *= -1;

	switch (shape) {
	case 'r':
		cv::rectangle(img, box.tl(), box.br(), color, 2);
		break;
	case 'c':
		cv::circle(img, cv::Point((box.br().x + box.tl().x) / 2, (box.br().y + box.tl().y) / 2), ((radiusX > radiusY) ? radiusX : radiusY), color, 2);
		break;
	case 'e':
		cv::ellipse(img, cv::RotatedRect(box.tl(), cv::Point2f(box.br().x, box.tl().y), box.br()), color, 2);
		break;
	}

}

void configText() {
	textsize = cv::getTextSize(text, fontface, fontscale, 1, &baseline);
	baseline += 1;
	origin = cv::Point((640 - textsize.width)/ 2, 40);
}









