#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


/////////////////  Images  //////////////////////

//int main() {
//
//    string path = "Resources/lambo.png";
//    Mat img = imread(path);
//    imshow("Image", img);
//    waitKey(0);
//    return 0;
//
//}


/////////////// video //////////////////////
//int main() {
//
//    string path = "Resources/test_video.mp4";
//    VideoCapture cap(path);
//    Mat img;
//    while (true) {
//        cap.read(img);
//        imshow("Video", img);
//        waitKey(20);
//    }
//    return 0;
//
//}

int main() {
	VideoCapture cap(2);
	Mat img;

	while (true)
	{
		cap.read(img);

		imshow("Image", img);
		waitKey(1);
	}
}