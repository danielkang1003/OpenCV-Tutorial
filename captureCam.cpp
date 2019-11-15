#include<opencv2/core.hpp>	
#include<opencv2/videoio.hpp>	//비디오모듈 디바이스 접근 -> 영상 가져오기
#include<opencv2/highgui.hpp>

#include<iostream>


using namespace cv;
using namespace std;


int main() {
	Mat frame;	//입력 이미지 저장할 Mat 객체

	VideoCapture cap(0);	//비디오 캡쳐에 연결. pc에 연결된 1번 카메라에 접근(idx 방식)

	//카메라 연결 안될 떄 에러
	if (!cap.isOpened()) {
		cerr << "카메라를 열 수 없습니다." << '\n';
		return -1;
	}

	int fps = cap.get(CAP_PROP_FPS);	//카메라로부터 초당 프레임수 가져옴
	while (1) {
		cap.read(frame);	//비디오 캡쳐 객체 read 함수를 사용해 카메라로부터 이미지 한장 가져오기

		//한장만 가지고 오려면 loop 없이하면 됨
		//비어있다면 에러
		if (frame.empty()) {
			cerr << "캡처 실패" << '\n';
			break;	//이미지 가져오다 실패할 떄 루프 빠져 나오기위해 사용
		}

		imshow("Live", frame);
		//fps 고려헤서 대기시간 계산
		int wait = int(1.0 / fps * 1000);
		if (waitKey(wait) >= 0) 
			break;	//아무키 누르면 종료~
		
	}
	return 0;
}

