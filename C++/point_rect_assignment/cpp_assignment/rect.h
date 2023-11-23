#pragma once
#include "point.h"
#include <iostream>
#define MAX(x,y) ((x)>(y))?(x):(y)
#define MIN(x,y) ((x)<(y))?(x):(y)

using namespace std;

//���� ������ RECT class�� �ۼ��Ͻÿ�.
//- �� ���� Point�� ���ǵǴ� ���簢�� Class

class rect {
private:
	point LowerLeft, UpperRight, LowerRight, UpperLeft;
	int x_min, x_max, y_min, y_max;
public:
	/*-�����ڿ� �Ҹ��ڸ� ����*/
	rect(point p1 = 0, point p2 = 0){
		LowerLeft.set_xy(MIN(p1.get_x(), p2.get_x()), MIN(p1.get_y(), p2.get_y()));
		UpperRight.set_xy(MAX(p1.get_x(), p2.get_x()), MAX(p1.get_y(), p2.get_y()));
		LowerRight.set_xy(MAX(p1.get_x(), p2.get_x()), MIN(p1.get_y(), p2.get_y()));
		UpperLeft.set_xy(MIN(p1.get_x(), p2.get_x()), MAX(p1.get_y(), p2.get_y()));
		x_min = LowerLeft.get_x();
		y_min = LowerLeft.get_y();
		x_max = UpperRight.get_x();
		y_max = UpperRight.get_y();
	}
	~rect() { /*cout << "rect �Ҹ��ڰ� ȣ��Ǿ����ϴ�." << endl;*/ };

	/*-Show �Լ����� : LowerLeft, UpperRight Point ��� �Լ�*/
	void show();
	int get_area() const ; 
	rect operator+(const rect& ref); //�� RECT�� �����ϴ� �ּ� �簢�� ����
	rect operator-(const rect& ref); //�� RECT�� �ߺ����� �簢�� ����
	int operator*(const rect& ref); //�� RECT�� ����(�ߺ����� ����)
};
