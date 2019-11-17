#include <opencv2/opencv.hpp>

#include<iostream>

using namespace cv;



bool mouse_is_pressing = false;	//마우스 버튼이 눌려진 상태인지 체크하기 위해 사용
int start_x = -1, start_y = -1;	//버튼 누를 위치 저장. ROI 시작점
Mat img_color;	//원본 영상 저장할 변수 전역으로 선언

//콜백함수 정의
void mouse_callback(int event, int x, int y, int flags, void *userdata)
{
	//원본 영상 복사해서 결과 영상으로 사용
	Mat img_result = img_color.clone();

	//마우스 왼쪽 버튼 누른 경우 좌표 ROI 시작점으로 저장
	if (event == EVENT_LBUTTONDOWN) {

		mouse_is_pressing = true;
		start_x = x;
		start_y = y;

		//시작점을 원으로 만듦
		circle(img_result, Point(x, y), 10, Scalar(0, 255, 0), -1);
		imshow("img_color", img_result);

	}


	//버튼을 누른채 이동한 경우 ROI 시작점부터 현재 마우스 커서 위치까지
	//초록색 사각형으로 그림
	else if (event == EVENT_MOUSEMOVE) {
		if (mouse_is_pressing) {

			rectangle(img_result, Point(start_x, start_y), Point(x, y),
				Scalar(0, 255, 0), 3);

			imshow("img_color", img_result);
		}
	}
	//왼쪽버튼에서 손 뗀 경우 해당 좌표가 ROI의 끝 좌표가 됨
	else if (event == EVENT_LBUTTONUP) {

		mouse_is_pressing = false;	//위에 마우스 눌렀을때 True 바꾸었던 것을 다시 false 로 바꿈

		Mat img_cat(img_color, Rect(start_x, start_y, x - start_x, y - start_y));
		
		
		cvtColor(img_cat, img_cat, COLOR_BGR2GRAY);	//ROI 영역을 Grayscale로 변환
		cvtColor(img_cat, img_cat, COLOR_GRAY2BGR);
		

		//별도의 윈도우에 grayscale로 수정하여 보여줌
		img_cat.copyTo(img_result(Rect(start_x, start_y, x - start_x, y - start_y)));
		imshow("img_color", img_result);
		imshow("img_cat", img_cat);
	}
}



int main(){
	//이미지 불러와서 화면에 보여주기
	img_color = imread("image/cat.jpg", IMREAD_COLOR);

	imshow("img_color", img_color);
	//마우스 이벤트 발생시켜 호출될 콜백 함수 지정
	setMouseCallback("img_color", mouse_callback);

	//키보드 입력은 종료 (그 전까진 마우스 이벤트에 따라 동작)
	waitKey(0);
	destroyAllWindows();
}