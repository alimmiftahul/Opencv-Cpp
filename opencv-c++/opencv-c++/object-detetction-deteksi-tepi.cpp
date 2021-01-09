///--> name : miftahul alim
///--> create : 2021
// --> camera rusak jadi belajar pake gambar dulu

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;
//---> we find the countours with dilation  and images
void getContours(Mat imgDil, Mat img) {

	// data types countours
	vector<vector<Point>> contours;
	// data types  hierarchy
	vector<Vec4i> hierarchy;

	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	drawContours(img, contours, -1, Scalar(255, 0, 255), 2);

	// data type conPoly and must be above of the loop
	vector<vector<Point>> conPoly(contours.size());
	// data type Rect
	vector<Rect> boundRect(contours.size());

	for (int i = 0; i < contours.size(); i++)
	{
		/// to see or find area 
		int area = contourArea(contours[i]);
		cout << area << endl;
		string objectType;

		if (area > 1000)
		{
			float peri = arcLength(contours[i], true);
			// u can choose 3 or random number after conPoly[i] array an
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
			//cout << conPoly[i].size() << endl;
			boundRect[i] = boundingRect(conPoly[i]);

			int objCor = (int)conPoly[i].size();
			// name  of bound rect based on point object dilation
			if (objCor == 3) { 
				objectType = "segitiga";
			}
			// name of bound rect based on point object dilation
			else if (objCor == 4)
			{
				// find aspect ratio
				float aspRatio = (float)boundRect[i].width / (float)boundRect[i].height;
				//cout << aspRatio << endl;
				if (aspRatio > 0.95 && aspRatio < 1.05) { objectType = "bulat"; }
				else { objectType = "kotak"; }
			}
			else if (objCor > 4) { 
				objectType = "bulat"; 
			}

			drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
			rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);
			putText(img, objectType, { boundRect[i].x,boundRect[i].y - 5 }, FONT_HERSHEY_PLAIN, 1, Scalar(0, 69, 255), 2);
		}
	}
}


void main() {

	string path = "Resources/shapes.png";
	Mat img = imread(path);
	Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;

	// Preprocessing
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
	Canny(imgBlur, imgCanny, 25, 75);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDil, kernel);

	getContours(imgDil, img);

	imshow("Image", img);
	imshow("Image Gray", imgGray);
	imshow("Image Blur", imgBlur);
	imshow("Image Canny", imgCanny);
	imshow("Image Dil", imgDil);

	waitKey(0);

}


