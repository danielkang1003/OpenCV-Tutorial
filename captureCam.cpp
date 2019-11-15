#include<opencv2/core.hpp>	
#include<opencv2/videoio.hpp>	//������� ����̽� ���� -> ���� ��������
#include<opencv2/highgui.hpp>

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
	while (1) {
		cap.read(frame);	//���� ĸ�� ��ü read �Լ��� ����� ī�޶�κ��� �̹��� ���� ��������

		//���常 ������ ������ loop �����ϸ� ��
		//����ִٸ� ����
		if (frame.empty()) {
			cerr << "ĸó ����" << '\n';
			break;	//�̹��� �������� ������ �� ���� ���� ���������� ���
		}

		imshow("Live", frame);
		//fps ����켭 ���ð� ���
		int wait = int(1.0 / fps * 1000);
		if (waitKey(wait) >= 0) 
			break;	//�ƹ�Ű ������ ����~
		
	}
	return 0;
}

