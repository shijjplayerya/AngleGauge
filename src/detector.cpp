#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;

int HEIGHTH = 16;
int WIDTH = 16;

void fastCornerDetection(Mat &image)
{
    // 1. 转换为灰度图像
    Mat gray;

    cvtColor(image, gray, COLOR_BGR2GRAY);
    threshold(gray, gray, 127, 255, THRESH_BINARY);

    // 2. 创建 FAST 检测器
    Ptr<FastFeatureDetector> fast = FastFeatureDetector::create();

    // 3. 设置参数
    fast->setThreshold(20);                        // 设置阈值
    fast->setNonmaxSuppression(true);              // 启用非极大值抑制
    fast->setType(FastFeatureDetector::TYPE_9_16); // 设置邻域类型

    // 4. 检测角点
    vector<KeyPoint> keypoints;
    fast->detect(gray, keypoints);

    // 5. 绘制角点
    Mat result;
    drawKeypoints(image, keypoints, image, Scalar(0, 255, 0), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
}

void harrisCornerDetection(Mat &img)
{
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    GaussianBlur(gray, gray, Size(3, 3), 1);
    // threshold(gray,gray,230,255,THRESH_BINARY);

    imshow("Gray", gray);

    Mat res = Mat::zeros(gray.size(), CV_32FC1);

    cornerHarris(gray, res, 2, 3, 0.04);
    normalize(res, res, 0, 255, NORM_MINMAX, CV_32FC1);

    Point max;
    double maxVal;
    Mat mask = Mat::zeros(gray.size(), CV_8UC1);
    mask(Rect(4, 4, 8, 8)) = 1;

    minMaxLoc(res, nullptr, &maxVal, nullptr, &max, mask);

    img.at<Vec3b>(max) = Vec3b(0, 0, 255);
    //
    // for(int i=0;i<img.rows;i++)
    // {
    //     for(int j=0;j<img.cols;j++)
    //     {
    //         if(res.at<float>(i,j) > )

    //     }
    // }
}

int main(int argc, char const *argv[])
{
    int count = -1;
    Mat img = imread("./img/" + to_string(++count) + ".jpg");

    namedWindow("Out", WINDOW_GUI_NORMAL);
    namedWindow("Gray", WINDOW_GUI_NORMAL);

    while (true)
    {

        if (img.empty())
        {
            cout << "No Picture" << endl;
            break;
        }
        harrisCornerDetection(img);
        // fastCornerDetection(img);
        imshow("Out", img);

        int Key = waitKey(0);
        if (Key == 'n')
            img = imread("./img/" + to_string(++count) + ".jpg");
        if (Key == 'r')
            img = imread("./img/" + to_string(--count) + ".jpg");
        if (Key == 27)
            break;
    }

    destroyAllWindows();
    return 0;
}
