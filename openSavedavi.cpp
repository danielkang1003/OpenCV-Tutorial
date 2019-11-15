#include<opencv2/core.hpp>
#include<opencv2/videoio.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>

#include<iostream>

using namespace std;
using namespace cv;

int main() {
	Mat frame;
	VideoCapture cap("output.avi");	// ���� ó���� ����Ǿ��� ���� ����ϱ�
	if (!cap.isOpened()) {
		cerr << "�������� ������ �� �����ϴ�." << '\n';
		return -1;
	}

	int fps = cap.get(CAP_PROP_FPS);

	while (1) {
		cap.read(frame);
		if (frame.empty()) {
			cerr << "ĸ�� ����" << '\n';
			break;
		}

		imshow("Live", frame);

		int wait = int(1.0 / fps * 1000);
		if (waitKey(wait) >= 0)
			break;	//�ƹ�Ű ������ ����~
	}

	return 0;
}