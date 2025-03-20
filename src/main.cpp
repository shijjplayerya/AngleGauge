#include "opencv2/opencv.hpp"
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;
using namespace cv;
/* Global Value */
vector<Point2i> points;
string imgPath = "test1.jpg";
Mat img = imread(imgPath);
int HEIGHT = 9;
int WIDTH = 9;

void fastCornerDetection(Point &pt)
{
    // 0. 截取click点附近的图像
    Rect roi(pt.x - HEIGHT / 2, pt.y - WIDTH / 2, HEIGHT, WIDTH);
    Mat image = img(roi);
    // 1. 初步处理数据
    Mat gray;

    cvtColor(image, gray, COLOR_BGR2GRAY);
    // imshow("Gray", gray);
    GaussianBlur(gray, gray, Size(3, 3), 1.5);
    // imshow("Bin_Gray",gray);
    // preprocessImg(gray);

    // 2. 创建 FAST 检测器
    Ptr<FastFeatureDetector> fast = FastFeatureDetector::create();

    // 3. 设置参数
    fast->setThreshold(20);                        // 设置阈值
    fast->setNonmaxSuppression(true);              // 启用非极大值抑制
    fast->setType(FastFeatureDetector::TYPE_9_16); // 设置邻域类型

    // 4. 检测角点
    vector<KeyPoint> keypoints;
    fast->detect(gray, keypoints);

    if (keypoints.size() != 0)
        pt = Point(pt.x + keypoints[0].pt.x - HEIGHT / 2 - 1, pt.y + keypoints[0].pt.y - WIDTH / 2 - 1);
    // 5. 绘制角点
    // drawKeypoints(image, keypoints, image, Scalar(0, 255, 0), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
}

/* Function */
double getAngel()
{
    // 计算两个向量的夹角
    Vec2d p1 = {(points[2].x - points[1].x) * 1.0, (points[2].y - points[1].y) * 1.0};
    Vec2d p2 = {(points[0].x - points[1].x) * 1.0, (points[0].y - points[1].y) * 1.0};

    double angleR = acosf(p1.dot(p2) / norm(p1) / norm(p2)); // 计算两个向量的弧度夹角
    double angleD = angleR / 3.1415 * 180;                   // 弧度转角度
    return angleD;
}

/* Mouse Event */
void onMouse(int event, int x, int y, int flag, void *param)
{
    Point click_pt = {x, y};

    if (event == EVENT_LBUTTONUP)
    {
        fastCornerDetection(click_pt); // 快速角点检测
        points.push_back(click_pt);
        circle(img, click_pt, 2, Scalar(0, 0, 255), 2, 8, 0);
        cout << points << endl;

        if (points.size() == 1)
            return;
        line(img, points[points.size() - 2], points.back(), Scalar(0, 255, 0), 1, 8, 0);
        // 当有三个点时
        // 计算角度、清空列表
        if (points.size() == 3)
        {
            double angleR = getAngel();
            cout << "angle = " << angleR << endl;
            points.clear();
        }
        // 不到三个点时
    }
}

int main(int argc, char const *argv[])
{

    namedWindow("Res", WINDOW_NORMAL);

    while (true)
    {
        imshow("Res", img);
        setMouseCallback("Res", onMouse);

        // out
        int Key = waitKey(1);
        if (Key == 27)
            break;
        // clear sceen
        if (Key == 'c')
        {
            img = imread(imgPath);
            points.clear();
        }
    }

    return 0;
}
