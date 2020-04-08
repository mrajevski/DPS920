#include <opencv2/opencv.hpp>

using namespace std;

int main(int argc, char** argv) {

    cv::namedWindow("Capture", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Detected Frame", cv::WINDOW_AUTOSIZE);

    cv::VideoCapture cap;

    cap.open(0);
    if (!cap.isOpened()) {
        cerr << "Couldn't open capture." << std::endl;
        return -1;
    }

    cv::Mat frame, frameHLS, frameGrouped = cv::Mat(frame.rows, frame.cols, CV_8UC3), frameEdges, frameFinal;

    for (;;) {
        frame = cv::imread("./16468.jpg", cv::IMREAD_COLOR);
        //cap >> frame;

        frame.copyTo(frameFinal);
        cv::pyrMeanShiftFiltering(frame, frame, 1, 2);
        cv::cvtColor(frame, frameHLS, CV_BGR2HLS);
        cv::medianBlur(frameHLS, frameHLS, 7);

        cv::erode(frameHLS, frameHLS, cv::Mat());
        cv::dilate(frameHLS, frameHLS, cv::Mat());
        cv::erode(frameHLS, frameHLS, cv::Mat());
        cv::dilate(frameHLS, frameHLS, cv::Mat());
        cv::erode(frameHLS, frameHLS, cv::Mat());

        for (int i = 0; i < frame.rows; i++) {
            for (int j = 0; j < frame.cols; j++) {
                cv::Vec3b k = frameHLS.at<cv::Vec3b>(i, j);
                if ((k[0] <= 10 || k[0] >= 175) && k[2] >= 0.2 && (0.5 < (k[1] / k[2]) && 3.0 > (k[1] / k[2]))) {}
                else {
                    frameFinal.at<cv::Vec3b>(i, j) = cv::Vec3b(0, 0, 0);
                }
            }
        }

        cv::cvtColor(frameFinal, frameEdges, cv::COLOR_BGR2GRAY);

        vector<vector<cv::Point>> contours, contours_;
        vector<cv::Vec4i> hierarchy;
        cv::findContours(frameEdges, contours_, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);
        contours.resize(contours_.size());
        for (size_t k = 0; k < contours_.size(); k++)
            approxPolyDP(cv::Mat(contours_[k]), contours[k], 3, true);

        cv::drawContours(frameEdges, contours, -1, cv::Scalar(200, 200, 200), 1, cv::LINE_AA, hierarchy, 3);
        
        vector<cv::Point> *l1 = nullptr, *l2 = nullptr, *l3 = nullptr;
        for (auto&& c : contours) {
            if (l1 == nullptr || l1->size() < c.size()) {
                l3 = l2;
                l2 = l1;
                l1 = &c;
            }
            else {
                if (l2 == nullptr || l2->size() < c.size()) {
                    l3 = l2;
                    l2 = &c;
                }
                else if (l3 == nullptr || l3->size() < c.size()) {
                    l3 = &c;
                }
            }
        }

        if (l1 != nullptr) {
            cv::Rect r1 = cv::boundingRect(*l1);
            r1.x -= 10; r1.y -= 10; r1.width += 20;  r1.height += 20;
            cv::rectangle(frameFinal, r1, cv::Scalar(0, 0, 255), 2);
            cv::rectangle(frame, r1.tl(), cv::Point(r1.br().x, r1.tl().y + r1.width), cv::Scalar(0, 255, 0), 1);
            if (l2 != nullptr) {
                cv::Rect r2 = cv::boundingRect(*l2);
                r2.x -= 10; r2.y -= 10; r2.width += 20;  r2.height += 20;
                cv::rectangle(frameFinal, r2, cv::Scalar(0, 0, 255), 2);
                cv::rectangle(frame, r2.tl(), cv::Point(r2.br().x, r2.tl().y + r2.width), cv::Scalar(0, 255, 0), 1);
                if (l3 != nullptr) {
                    cv::Rect r3 = cv::boundingRect(*l3);
                    r3.x -= 10; r3.y -= 10; r3.width += 20;  r3.height += 20;
                    cv::rectangle(frameFinal, r3, cv::Scalar(0, 0, 255), 2);
                    cv::rectangle(frame, r3.tl(), cv::Point(r3.br().x, r3.tl().y + r3.width), cv::Scalar(0, 255, 0), 1);
                }
            }
        }

        cv::imshow("Capture", frame);
        cv::imshow("Edges Frame", frameEdges);
        cv::imshow("Detected Frame", frameFinal);

        cv::waitKey(/*25*/);

    }

	return 0;
}



