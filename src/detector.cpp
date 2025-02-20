#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;

int HEIGHTH = 16;
int WIDTH = 16;

void preprocessImg(Mat & gray)
{
    
    threshold(gray, gray, 240, 255, THRESH_BINARY);
    imshow("Bin_Gray",gray);

    Mat kernel = getStructuringElement(MORPH_RECT,Size(1,2));
    morphologyEx(gray,gray,MORPH_OPEN,kernel);
    imshow("Open_Gray",gray);
}

void fastCornerDetection(Mat &image)
{
    // 1. 初步处理数据
    Mat gray;

    cvtColor(image, gray, COLOR_BGR2GRAY);
    imshow("Gray", gray);
    GaussianBlur(gray,gray,Size(3,3),1.5);
    imshow("Bin_Gray",gray);
    //preprocessImg(gray);

    // 2. 创建 FAST 检测器
    Ptr<FastFeatureDetector> fast = FastFeatureDetector::create();

    // 3. 设置参数
    fast->setThreshold(20);                        // 设置阈值
    fast->setNonmaxSuppression(true);              // 启用非极大值抑制
    fast->setType(FastFeatureDetector::TYPE_9_16); // 设置邻域类型

    // 4. 检测角点
    vector<KeyPoint> keypoints;
    fast->detect(gray, keypoints);

    image.at<Vec3b>(keypoints[0].pt) = {0,0,255};
    // 5. 绘制角点
    drawKeypoints(image, keypoints, image, Scalar(0, 255, 0), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    
}

void harrisCornerDetection(Mat &img)
{
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    //GaussianBlur(gray, gray, Size(3, 3), 1);
    // threshold(gray,gray,230,255,THRESH_BINARY);

    preprocessImg(gray);

    Mat res = Mat::zeros(gray.size(), CV_32FC1);

    cornerHarris(gray, res, 1, 2, 0.04);
    normalize(res, res, 0, 255, NORM_MINMAX, CV_32FC1);

    Point max;
    double maxVal;

    minMaxLoc(res, nullptr, &maxVal, nullptr, &max);

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
    namedWindow("Bin_Gray",WINDOW_GUI_NORMAL);
    namedWindow("Open_Gray",WINDOW_GUI_NORMAL);
    while (true)
    {

        if (img.empty())
        {
            cout << "No Picture" << endl;
            break;
        }
        //harrisCornerDetection(img);
        fastCornerDetection(img);
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
