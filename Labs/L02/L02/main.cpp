#define _CRT_SECURE_NO_WARNINGS

#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>
#include <filesystem>
#include <vector>

using namespace std;

int main(int argc, char** argv) {
    
    cv::namedWindow("Lab 02", cv::WINDOW_AUTOSIZE);
    cv::VideoCapture cap;

    cap.open(0); 
    if (!cap.isOpened()) { 
        cerr << "Couldn't open capture." << std::endl;
        return -1;
    }

    cv::Mat frame;

    cout << "Capture Dimensions: " << cap.get(cv::CAP_PROP_FRAME_WIDTH) << "px"
        << " X " << cap.get(cv::CAP_PROP_FRAME_HEIGHT) << "px" << endl
        << "Frametime: 33ms" << endl << "Framerate: 30fps" << endl;    

    string _image = "image", imgNum = "00", _jpg = ".jpg";
    char img[50];

    for (const auto& f : std::filesystem::directory_iterator("./")) {
        string file = f.path().string();
        file.erase(0, 2);
        if (file.substr(0, 5).compare(_image) == 0 && file.find(_jpg) != string::npos) {
            if (stoi(file.substr(5, 2)) > stoi(imgNum)) {
                imgNum = file.substr(5, 2);
            }
        }
    }

    if (imgNum.compare("00") != 0) {
        imgNum = to_string(stoi(imgNum) + 1);
        if (imgNum.length() == 1) imgNum = "0" + imgNum;
    }

    for (;;) {
        cap >> frame;
        if (frame.empty()) break; 

        cv::imshow("Lab 02", frame);

        // To achieve 25fps, the frametime must be increased to 40ms //
        int key = (char)cv::waitKey(33);

        if (key == 120) {

            sprintf_s(img, "image%s.jpg", imgNum.c_str());
            cv::imwrite(img, frame);

            imgNum = to_string(stoi(imgNum) + 1);
            if (imgNum.length() == 1) imgNum = "0" + imgNum;

            cv::waitKey(1000);
        }
        else if (key == 32 || key == 13) break;
    }

    return 0;

}