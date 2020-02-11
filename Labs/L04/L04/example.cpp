#include <opencv2/opencv.hpp>

void my_mouse_callback(
        int event, int x, int y, int flags, void* param
);

cv::Rect box;
bool drawing_box = false;

void draw_box(cv::Mat& img, cv::Rect box) {
    cv::rectangle(
        img,
        box.tl(),
        box.br(),

        cv::Scalar(0x00, 0x00, 0xff)    /* red */
    );
}
void help(char** argv) {
    std::cout << "Example 9-2. Toy program for using a mouse to draw boxes on the screen"
        << "\nCall:\n" << argv[0] <<
        "\n\nshows how to use a mouse to draw regions in an image. Esc to quit\n" << std::endl;
}
int main(int argc, char** argv) {
    help(argv);
    box = cv::Rect(-1, -1, 0, 0);
    cv::Mat image(200, 200, CV_8UC3), temp;
    image.copyTo(temp);
    box = cv::Rect(-1, -1, 0, 0);
    image = cv::Scalar::all(0);
    cv::namedWindow("Box Example");
    cv::setMouseCallback(
        "Box Example",
        my_mouse_callback,
        (void*)&image
    );
    for (;;) {
        image.copyTo(temp);
        if (drawing_box) draw_box(temp, box);
        cv::imshow("Box Example", temp);
        if (cv::waitKey(15) == 27) break;
    }
    return 0;
}

void my_mouse_callback(
    int event, int x, int y, int flags, void* param)
{
    cv::Mat& image = *(cv::Mat*) param;
    switch (event) {
    case cv::EVENT_MOUSEMOVE: {
        if (drawing_box) {
            box.width = x - box.x;
            box.height = y - box.y;
        }
    }
                            break;
    case cv::EVENT_LBUTTONDOWN: {
        drawing_box = true;
        box = cv::Rect(x, y, 0, 0);
    }
                              break;
    case cv::EVENT_LBUTTONUP: {
        drawing_box = false;
        if (box.width < 0) {

            box.x += box.width;
            box.width *= -1;
        }
        if (box.height < 0) {
            box.y += box.height;
            box.height *= -1;
        }
        draw_box(image, box);
    }
                            break;
    }

}