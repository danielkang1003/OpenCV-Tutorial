#include<opencv2/core.hpp>	
#include<opencv2/videoio.hpp>	//������� ����̽� ���� -> ���� ��������
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>	//cvtColor�Լ��� imgprocessing�� ����

#include<iostream>


using namespace cv;
using namespace std;


int main() {
	Mat frame;	//�Է� �̹��� ������ Mat ��ü

	VideoCapture cap(0);	//���� ĸ�Ŀ� ����. pc�� ����� 1�� ī�޶� ����(idx ���)

	//ī�޶� ���� �ȵ� �� ����
	if (!cap.isOpened()) {
		cerr << "ī�޶� �� �� �����ϴ�." << '\n';
		return -1;
	}

	int fps = cap.get(CAP_PROP_FPS);	//ī�޶�κ��� �ʴ� �����Ӽ� ������
	
	//ī�޶�κ��� ������ ������ ���������� ����
	//���� ĸ�� ��ü�� ���� ������. ī�޶� ũ��� ������ ���Ϸ� ����� �ڵ� ����
	int width = cap.get(CAP_PROP_FRAME_WIDTH);
	int height = cap.get(CAP_PROP_FRAME_HEIGHT);
	int fourcc = VideoWriter::fourcc('X', 'V', 'I', 'D');
	
	//�տ��� ������ ������ videowriter ��ü ����
	VideoWriter outputVideo;
	outputVideo.open("output.avi", fourcc, fps, Size(width, height), true);	//�׷��� �������̿��� -1 �̰� �������� fourcc �� ó���ϱ�
	//����� �ڵ� ������ �� �ִ� �޼��� ����
	//���� ������ ���� üũ
	if (!outputVideo.isOpened()) {
		cerr << "������ ������ ���� �ʱ�ȭ�� ����" << '\n';
		return -1;
	}
	
	
	while (1) {
		cap.read(frame);	//���� ĸ�� ��ü read �Լ��� ����� ī�޶�κ��� �̹��� ���� ��������

		//���常 ������ ������ loop �����ϸ� ��
		//����ִٸ� ����
		if (frame.empty()) {
			cerr << "ĸó ����" << '\n';
			break;	//�̹��� �������� ������ �� ���� ���� ���������� ���
		}

		//cvtColor(frame, frame, COLOR_BGR2GRAY);	//�̹��� grayscale�� ��ȯ
		//cvtColor(�Է� �Ű�ü, ��� �Ű�ü, ������ ��ȯ�ڵ�)
		
		
		imshow("Live", frame);

		
		outputVideo.write(frame);	//ĸ�ĵ� �̹��� ���� loop���� �̹����� �����


		//fps ����켭 ���ð� ���
		int wait = int(1.0 / fps * 1000);
		if (waitKey(wait) >= 0) 
			break;	//�ƹ�Ű ������ ����~
		
	}
	return 0;
}

