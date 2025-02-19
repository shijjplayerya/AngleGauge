#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include <string>

using namespace std;
using namespace cv;

string imgPath = "test.jpg";
Mat img = imread(imgPath);


void onMouse(int event, int x, int y, int flag, void* param)
{
    static int count=0;
    if(event == EVENT_LBUTTONUP)
    {
        Rect roi(x-8,y-8,16,16);
        imwrite("./img/"+to_string(count++) + ".jpg",img(roi));
        rectangle(img,roi,Scalar(0,0,255),1);
        
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

    }
    return 0;
}

