#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

struct ColorRange {
    Scalar lower;
    Scalar upper;
    Scalar displayColor;
    string name;
};

void detectAndDraw(Mat& input, Mat& output, const ColorRange& range) {
    Mat hsv, mask;

    cvtColor(input, hsv, COLOR_BGR2HSV);

    inRange(hsv, range.lower, range.upper, mask);

    Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));
    morphologyEx(mask, mask, MORPH_OPEN, kernel);

    vector<vector<Point>> contours;
    findContours(mask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    for (const auto& contour : contours) {
        if (contourArea(contour) < 500) continue;

        Rect boundRect = boundingRect(contour);

        rectangle(output, boundRect, range.displayColor, 2);
        putText(output, range.name, Point(boundRect.x, boundRect.y - 10),
            FONT_HERSHEY_SIMPLEX, 0.7, range.displayColor, 2);
    }
}

int main(void) {
    Mat image = imread("rubik_cube.png");
    if (image.empty()) {
        cout << "无法加载图像!" << endl;
        return -1;
    }

    Mat result = image.clone();

    vector<ColorRange> colors = {
        {Scalar(100, 150, 50), Scalar(140, 255, 255), Scalar(255, 0, 0), "Blue"},
        {Scalar(20, 100, 100), Scalar(30, 255, 255), Scalar(0, 255, 255), "Yellow"}
    };

    for (const auto& color : colors) {
        detectAndDraw(image, result, color);
    }

    namedWindow("Original", WINDOW_AUTOSIZE);
    namedWindow("Detection Result", WINDOW_AUTOSIZE);
    imshow("Original", image);
    imshow("Detection Result", result);

    imwrite("detection_result.jpg", result);

    waitKey(0);
    destroyAllWindows();
}