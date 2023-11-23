#pragma once
#include "point.h"
#include <iostream>
#define MAX(x,y) ((x)>(y))?(x):(y)
#define MIN(x,y) ((x)<(y))?(x):(y)

using namespace std;

//다음 조건의 RECT class를 작성하시오.
//- 두 개의 Point로 정의되는 직사각형 Class

class rect {
private:
	point LowerLeft, UpperRight, LowerRight, UpperLeft;
	int x_min, x_max, y_min, y_max;
public:
	/*-생성자와 소멸자를 정의*/
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
	~rect() { /*cout << "rect 소멸자가 호출되었습니다." << endl;*/ };

	/*-Show 함수정의 : LowerLeft, UpperRight Point 출력 함수*/
	void show();
	int get_area() const ; 
	rect operator+(const rect& ref); //두 RECT를 포함하는 최소 사각형 생성
	rect operator-(const rect& ref); //두 RECT의 중복영역 사각형 생성
	int operator*(const rect& ref); //두 RECT의 면적(중복영역 배제)
};
