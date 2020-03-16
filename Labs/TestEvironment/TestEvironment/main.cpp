#include <opencv2/opencv.hpp>

using namespace std;

int lowHue = 50, lowSat = 0, lowV = 0;
int highHue = 255, highSat = 255, highLum = 255;

static void hLowThreshold(int, void*);
static void hHighThreshold(int, void*);
static void lLowThreshold(int, void*);
static void lHighThreshold(int, void*);
static void sLowThreshold(int, void*);
static void sHighThreshold(int, void*);

int main(int argc, char** argv) {


    cv::namedWindow("Capture", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Detected Frame", cv::WINDOW_AUTOSIZE);

    cv::VideoCapture cap;

    cap.open(0);
    if (!cap.isOpened()) {
        cerr << "Couldn't open capture." << std::endl;
        return -1;
    }

    cv::Mat frame, frameHLS, frameDetected, frameFinal;

    for (;;) {
        cap >> frame;
        cv::imshow("Capture", frame);
        frame.copyTo(frameFinal);

        cv::cvtColor(frame, frameHLS, CV_BGR2HLS);
        //cv::GaussianBlur(frameHLS, frameHLS, cv::Size(3, 3), 0);
        frameHLS.copyTo(frameDetected);

        for (int i = 0; i < frame.rows; i++) {
            for (int j = 0; j < frame.cols; j++) {
                cv::Vec3b k = frameHLS.at<cv::Vec3b>(i, j);
                if (k[0] <= 15 || k[0] >= 175 && k[2] >= 20 && (200 < (k[1] / k[2]) && 765 > (k[1] / k[2]))) {}
                else {
                    frameFinal.at<cv::Vec3b>(i, j) = cv::Vec3b(0, 0, 0);
                }
            }
        }

        cv::erode(frameFinal, frameFinal, cv::Mat());

        cv::imshow("Detected Frame", frameFinal);

        cv::waitKey(100);

    }

	return 0;
}



