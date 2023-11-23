#include <iostream>
#include "point.h"

int point::get_x() {
	return this->xpos;
}
int point::get_y() {
	return this->ypos;
}
void point::set_x(int x) {
	this->xpos = x;
}
void point::set_y(int y) {
	this->ypos = y;
}
void point::set_xy(int x, int y) {
	this->xpos = x;
	this->ypos = y;
}
void point::set_xy(point p) {
	this->xpos = p.get_x();
	this->ypos = p.get_y();
}

void point::show_point() {
	printf("coordinate of the point : (%d, %d)\n", this->xpos, this->ypos);
}