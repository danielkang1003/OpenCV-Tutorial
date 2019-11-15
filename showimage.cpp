#include<opencv2/core.hpp>	//이미지 저장시 사용되는 mat, 자료구조 함수들 포함
#include<opencv2/imgcodecs.hpp>	//이미지파일 읽어오는 함수 저장하는 함수 포함
#include<opencv2/highgui.hpp>	//인터페이스 구현해놓은 모듈. 사용자 입력 받기위해 대기하는 함수,
#include<opencv2/imgproc.hpp>	//canny함수(엣지 검출) 사용위해 헤더 추가
//화면에 이미지를 보여주기 위한 함수 포함되어있음


//#include<opencv2/opencv.hpp>	//하나의 헤더파일만 include해도됨

#include<iostream>

using namespace cv;
using namespace std;

int main() {
	Mat image;	//입력 이미지 저장할 객체
	image = imread("image/IMG_8651.jpg", IMREAD_GRAYSCALE);	//imread_grayscale, imread_unchanged --> 오류 문제는 Imread_grayscale로만 해야 edge 가져올 수 잇음...
	if (image.empty()) {
		cout << "Could not open or find the image" << '\n';
		return -1;
	}

	//윈도우를 생성하는 namedwindow는 생략가능
	//namedWindow("Original", WND_PROP_FULLSCREEN);	//이미지 크기에 맞추어 gui size제공
	//window_autosize, window_normal, wnd_prop_fullscreen
	//setWindowProperty("Original", WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);
	
	imshow("Original", image);	//original 은 윈도우의 이름임

	Canny(image, image, 50, 150);

	imshow("Canny", image);	//이름을 다르게하면 두개의 윈도우가 뜸
	waitKey(0);	//밀리세컨드 단위

}