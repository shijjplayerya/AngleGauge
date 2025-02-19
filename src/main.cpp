#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;
using namespace cv;
/* Global Value */ 
vector<Point2i> points;
string imgPath = "test.jpg";
Mat img = imread(imgPath);

/* Function */
double getAngel()
{
    Vec2d p1 = {(points[2].x-points[1].x)*1.0,(points[2].y-points[1].y)*1.0};
    Vec2d p2 = {(points[0].x-points[1].x)*1.0,(points[0].y-points[1].y)*1.0};

    double angleR = acosf(p1.dot(p2)/norm(p1)/norm(p2));
    double angleD = angleR/3.1415*180;
    return angleD;

}

void onMouse(int event, int x, int y, int flag, void* param)
{
    if(event == EVENT_LBUTTONUP)
    {
        points.push_back(Point2i(x,y));
        circle(img,Point(x,y),2,Scalar(0,0,255),2,8,0);
        cout<<points<<endl;
        
        if(points.size() == 1)
            return;
        line(img,points[points.size()-2],points.back(),Scalar(0,255,0), 1, 8,0);
        // 当有三个点时
        // 计算角度、清空列表
        if(points.size() == 3)
        {
            double angleR = getAngel();
            cout << "angle = "<<angleR<< endl;
            points.clear();
        }
        // 不到三个点时
        
        
    }
}



int main(int argc, char const *argv[])
{
    
    namedWindow("Res", WINDOW_NORMAL);

    while(true)
    {
        imshow("Res",img);
        setMouseCallback("Res",onMouse);

        //out
        int Key = waitKey(1);
        if(Key == 27)
            break;
        // clear sceen
        if(Key == 'c')
        {
            img = imread(imgPath);
            points.clear();
        }
    }

    return 0;
}
