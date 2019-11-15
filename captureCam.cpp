#include<opencv2/core.hpp>	
#include<opencv2/videoio.hpp>	//비디오모듈 디바이스 접근 -> 영상 가져오기
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>	//cvtColor함수는 imgprocessing에 있음

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
	
	//카메라로부터 가져온 영상을 동영상으로 저장
	//비디오 캡쳐 객체로 부터 가져옴. 카메라 크기와 동영상 파일로 사용할 코덱 지정
	int width = cap.get(CAP_PROP_FRAME_WIDTH);
	int height = cap.get(CAP_PROP_FRAME_HEIGHT);
	int fourcc = VideoWriter::fourcc('X', 'V', 'I', 'D');
	
	//앞에서 가져온 정보로 videowriter 객체 생성
	VideoWriter outputVideo;
	outputVideo.open("output.avi", fourcc, fps, Size(width, height), true);	//그레이 스케일이여서 -1 이고 나머지는 fourcc 로 처리하기
	//실행시 코덱 선택할 수 있는 메세지 생성
	//비디오 생성시 에러 체크
	if (!outputVideo.isOpened()) {
		cerr << "동영상 저장을 위한 초기화중 에러" << '\n';
		return -1;
	}
	
	
	while (1) {
		cap.read(frame);	//비디오 캡쳐 객체 read 함수를 사용해 카메라로부터 이미지 한장 가져오기

		//한장만 가지고 오려면 loop 없이하면 됨
		//비어있다면 에러
		if (frame.empty()) {
			cerr << "캡처 실패" << '\n';
			break;	//이미지 가져오다 실패할 떄 루프 빠져 나오기위해 사용
		}

		//cvtColor(frame, frame, COLOR_BGR2GRAY);	//이미지 grayscale로 변환
		//cvtColor(입력 매개체, 출력 매개체, 색공간 변환코드)
		
		
		imshow("Live", frame);

		
		outputVideo.write(frame);	//캡쳐된 이미지 저장 loop돌며 이미지가 저장됨


		//fps 고려헤서 대기시간 계산
		int wait = int(1.0 / fps * 1000);
		if (waitKey(wait) >= 0) 
			break;	//아무키 누르면 종료~
		
	}
	return 0;
}

