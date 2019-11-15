#include<opencv2/core.hpp>
#include<opencv2/videoio.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>

#include<iostream>

using namespace std;
using namespace cv;

int main() {
	Mat frame;
	VideoCapture cap("output.avi");	// 영상 처리로 저장되었던 파일 재생하기
	if (!cap.isOpened()) {
		cerr << "동영상을 실행할 수 없습니다." << '\n';
		return -1;
	}

	int fps = cap.get(CAP_PROP_FPS);

	while (1) {
		cap.read(frame);
		if (frame.empty()) {
			cerr << "캡쳐 실패" << '\n';
			break;
		}

		imshow("Live", frame);

		int wait = int(1.0 / fps * 1000);
		if (waitKey(wait) >= 0)
			break;	//아무키 누르면 종료~
	}

	return 0;
}