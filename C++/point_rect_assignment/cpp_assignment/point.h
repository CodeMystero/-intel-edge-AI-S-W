#pragma once
#include <iostream>
using namespace std;

class point {
private:
	int xpos;
	int ypos;
public:
	/*-�����ڿ� �Ҹ��ڸ� ����*/
	point(int x = 0, int y = 0) : xpos(x), ypos(y) {}
	~point() { /*cout << "point �Ҹ��ڰ� ȣ��Ǿ����ϴ�." << endl;*/ };

	void set_x(int x);
	void set_y(int y);
	void set_xy(int x, int y);
	void set_xy(point p);
	int get_x();
	int get_y();
	void show_point();

};