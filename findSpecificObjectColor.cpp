#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;



int threshold1 = 30;

Vec3b lower_blue1, upper_blue1, lower_blue2, upper_blue2, lower_blue3, upper_blue3;
Mat img_color;

//마우스 클릭시 호출되는 콜백 함수
//클릭한 픽셀의 좌표값을 받아 픽셀값 반환
void mouse_callback(int event, int x, int y, int flags, void *param){
	//마우스 왼쪽 버튼만 가능
	if (event == EVENT_LBUTTONDOWN)	{
		//클릭한 위치의 픽셀값 읽어옴
		Vec3b color_pixel = img_color.at<Vec3b>(y, x);

		//cvtcolor로 적용하기 위해 한 픽셀로 된 이미지 저장
		Mat bgr_color = Mat(1, 1, CV_8UC3, color_pixel);


		//cvtcolor함수로 이미지를 visual 색공간에서 hsv색공간으로 변환
		Mat hsv_color;
		cvtColor(bgr_color, hsv_color, COLOR_BGR2HSV);

		//hue 값을 정수 변수에 대입
		int hue = hsv_color.at<Vec3b>(0, 0)[0];
		int saturation = hsv_color.at<Vec3b>(0, 0)[1];
		int value = hsv_color.at<Vec3b>(0, 0)[2];

		cout << "hue = " << hue << endl;
		cout << "saturation = " << saturation << endl;
		cout << "value = " << value << endl;

		//hue 값과 유사한 색 추출하기 위해 범위 정함
		//threshold1가 30으로 선언되있고 saturation과 value의 최소값임
		if (hue < 10)
		{
			cout << "case 1" << endl;
			lower_blue1 = Vec3b(hue - 10 + 180, threshold1, threshold1);
			upper_blue1 = Vec3b(180, 255, 255);
			lower_blue2 = Vec3b(0, threshold1, threshold1);
			upper_blue2 = Vec3b(hue, 255, 255);
			lower_blue3 = Vec3b(hue, threshold1, threshold1);
			upper_blue3 = Vec3b(hue + 10, 255, 255);
		}
		else if (hue > 170)
		{
			cout << "case 2" << endl;
			lower_blue1 = Vec3b(hue, threshold1, threshold1);
			upper_blue1 = Vec3b(180, 255, 255);
			lower_blue2 = Vec3b(0, threshold1, threshold1);
			upper_blue2 = Vec3b(hue + 10 - 180, 255, 255);
			lower_blue3 = Vec3b(hue - 10, threshold1, threshold1);
			upper_blue3 = Vec3b(hue, 255, 255);
		}
		else
		{
			cout << "case 3" << endl;
			lower_blue1 = Vec3b(hue, threshold1, threshold1);
			upper_blue1 = Vec3b(hue + 10, 255, 255);
			lower_blue2 = Vec3b(hue - 10, threshold1, threshold1);
			upper_blue2 = Vec3b(hue, 255, 255);
			lower_blue3 = Vec3b(hue - 10, threshold1, threshold1);
			upper_blue3 = Vec3b(hue, 255, 255);
		}

		cout << "hue = " << hue << endl;
		cout << "#1 = " << lower_blue1 << "~" << upper_blue1 << endl;
		cout << "#2 = " << lower_blue2 << "~" << upper_blue2 << endl;
		cout << "#3 = " << lower_blue3 << "~" << upper_blue3 << endl;
	}
}



int main(){
	
	//윈도우 생성 & 윈도우의 마우스 콜백 함수 등록
	//윈도우에서 마우스 이벤트 발생하면 콜백함수 호출됨
	namedWindow("img_color");
	setMouseCallback("img_color", mouse_callback);


	Mat img_hsv;

	VideoCapture cap(0);
	if (!cap.isOpened()) {

		cout << "카메라를 열 수 없습니다." << endl;
		return -1;
	}


	while (1)
	{
		//카메라 캡쳐 read함수로 이미지 가져오기
		cap.read(img_color);

		//이미지를 비주얼 색공간 -> hsv색공간으로 변환
		cvtColor(img_color, img_hsv, COLOR_BGR2HSV);

		//마우스 클릭시 만들었던 범위로 hsv 이미지에서 마스크 이미지 생성
		//inrange함수는 이미지에서 범위 내 픽셀을 흰색 , 그외는 검은색으로 만듦 --> 그래서 바이너리 이미지라고도 부름
		Mat img_mask1, img_mask2, img_mask3, img_mask;
		inRange(img_hsv, lower_blue1, upper_blue1, img_mask1);
		inRange(img_hsv, lower_blue2, upper_blue2, img_mask2);
		inRange(img_hsv, lower_blue3, upper_blue3, img_mask3);
		img_mask = img_mask1 | img_mask2 | img_mask3;


		//마스크 이미지와 원본이미지를 &연산하여 마스크 이미지에서 흰색 표현 부분만
		//원본 이미지에서 남겨둠
		Mat img_result;
		bitwise_and(img_color, img_color, img_result, img_mask);

		imshow("img_color", img_color);
		imshow("img_mask", img_mask);
		imshow("img_result", img_result);

		if (waitKey(1) > 0)
			break;
	}


	return 0;
}

