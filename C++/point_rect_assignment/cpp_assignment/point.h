#pragma once
#include <iostream>
using namespace std;

class point {
private:
	int xpos;
	int ypos;
public:
	/*-생성자와 소멸자를 정의*/
	point(int x = 0, int y = 0) : xpos(x), ypos(y) {}
	~point() { /*cout << "point 소멸자가 호출되었습니다." << endl;*/ };

	void set_x(int x);
	void set_y(int y);
	void set_xy(int x, int y);
	void set_xy(point p);
	int get_x();
	int get_y();
	void show_point();

};