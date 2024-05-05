#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // 读取图像
    Mat image = imread("C:\\Users\\tguxr\\Desktop\\1.png");
    if (image.empty()) {
        cout << "无法打开图片" << endl;
        return -1;
    }

    // 转换颜色空间为HSV
    Mat hsvImage;
    cvtColor(image, hsvImage, COLOR_BGR2HSV);

    // 定义红色和蓝色的HSV范围
    Scalar lowerRed = Scalar(100,43,46);  
    Scalar upperRed = Scalar(180, 255,255); 
    Scalar lowerBlue = Scalar(100,43,46);
    Scalar upperBlue = Scalar(124, 255, 255);

    // 根据HSV范围提取红色和蓝色色块
    Mat redMask, blueMask;
    inRange(hsvImage, lowerRed, upperRed, redMask);
    inRange(hsvImage, lowerBlue, upperBlue, blueMask);

    // 寻找红色和蓝色色块的轮廓
    vector<vector<Point>> redContours, blueContours;
    findContours(redMask, redContours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    findContours(blueMask, blueContours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // 绘制红色和蓝色色块的矩形轮廓并标出中心点
    for (const auto& redContour : redContours) {
        Moments M = moments(redContour);
        if (M.m00 > 0) {
            int cX = static_cast<int>(M.m10 / M.m00);
            int cY = static_cast<int>(M.m01 / M.m00);
            rectangle(image, boundingRect(redContour), Scalar(0, 255, 0), 2);
            circle(image, Point(cX, cY), 5, Scalar(0, 255, 0), -1);
        }
    }

    for (const auto& blueContour : blueContours) {
        Moments M = moments(blueContour);
        if (M.m00 > 0) {
            int cX = static_cast<int>(M.m10 / M.m00);
            int cY = static_cast<int>(M.m01 / M.m00);
            rectangle(image, boundingRect(blueContour), Scalar(255, 0, 0), 2);
            circle(image, Point(cX, cY), 5, Scalar(255, 0, 0), -1);
        }
    }

    // 显示结果图像
    imshow("Result", image);
    waitKey(0);

    return 0;
}


