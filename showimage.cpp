#include<opencv2/core.hpp>	//�̹��� ����� ���Ǵ� mat, �ڷᱸ�� �Լ��� ����
#include<opencv2/imgcodecs.hpp>	//�̹������� �о���� �Լ� �����ϴ� �Լ� ����
#include<opencv2/highgui.hpp>	//�������̽� �����س��� ���. ����� �Է� �ޱ����� ����ϴ� �Լ�,
#include<opencv2/imgproc.hpp>	//canny�Լ�(���� ����) ������� ��� �߰�
//ȭ�鿡 �̹����� �����ֱ� ���� �Լ� ���ԵǾ�����


//#include<opencv2/opencv.hpp>	//�ϳ��� ������ϸ� include�ص���

#include<iostream>

using namespace cv;
using namespace std;

int main() {
	Mat image;	//�Է� �̹��� ������ ��ü
	image = imread("image/IMG_8651.jpg", IMREAD_GRAYSCALE);	//imread_grayscale, imread_unchanged --> ���� ������ Imread_grayscale�θ� �ؾ� edge ������ �� ����...
	if (image.empty()) {
		cout << "Could not open or find the image" << '\n';
		return -1;
	}

	//�����츦 �����ϴ� namedwindow�� ��������
	//namedWindow("Original", WND_PROP_FULLSCREEN);	//�̹��� ũ�⿡ ���߾� gui size����
	//window_autosize, window_normal, wnd_prop_fullscreen
	//setWindowProperty("Original", WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);
	
	imshow("Original", image);	//original �� �������� �̸���

	Canny(image, image, 50, 150);

	imshow("Canny", image);	//�̸��� �ٸ����ϸ� �ΰ��� �����찡 ��
	waitKey(0);	//�и������� ����

}