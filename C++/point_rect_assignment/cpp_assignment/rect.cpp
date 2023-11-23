#include "rect.h"
#include "point.h"
#include <iostream>
#define ABS(x) ((x)<0)?-(x):(x)

using namespace std;


//- Show 함수정의 : LowerLeft, UpperRight Point 출력 함수
void rect::show() {
	printf("LowerLeft Point : (%d, %d)\n", LowerLeft.get_x(), LowerLeft.get_y());
	printf("UpperRight Point : (%d, %d)\n", UpperRight.get_x(), UpperRight.get_y());
	printf("======================================\n");
	//printf("LowerRight Point : (%.1f, %.1f)\n", LowerRight.get_x(), LowerRight.get_y());
	//printf("UpperLeft Point : (%.1f, %.1f)\n", UpperLeft.get_x(), UpperLeft.get_y());
}

//rect의 면적 구하는 함수 
int rect::get_area() const {
	int diff_x, diff_y;
	diff_x = ABS(x_max - x_min);
	diff_y = ABS(y_max - y_min);
	return (diff_x * diff_y);
}

////두 RECT를 포함하는 최소 사각형 생성
rect rect::operator+(const rect& ref) {
	point LowerLeft_temp, Upperright_temp;
	LowerLeft_temp.set_xy(MIN(x_min,ref.x_min),MIN(y_min,ref.y_min)); 
	Upperright_temp.set_xy(MAX(x_max,ref.x_max),MAX(y_max,ref.y_max)); 
	rect wrapping_rect(LowerLeft_temp, Upperright_temp);
	return wrapping_rect;
}

////두 RECT의 중복영역 사각형 생성
rect rect::operator-(const rect& ref) {
	if ((y_min >= ref.y_max) || (y_max <= ref.y_min) || (x_max <= ref.x_min) || (x_min >= ref.x_max)) {

		cout << "두 사각형은 겹치는 부분을 공유하지 않음" << endl;
		rect overlap_rect;
		return overlap_rect;
	} else {
		point LowerLeft_temp, UpperRight_temp;

		int* x_vals = new int[(x_max - x_min) + 1];
		int* y_vals = new int[(y_max - y_min) + 1];
		int* rx_vals = new int[(ref.x_max - ref.x_min) + 1];
		int* ry_vals = new int[(ref.y_max - ref.y_min) + 1];
		int* x_overlap_vals = new int[MIN((x_max - x_min) + 1, (ref.x_max - ref.x_min) + 1)];
		int* y_overlap_vals = new int[MIN((y_max - y_min) + 1, (ref.y_max - ref.y_min) + 1)];

		for (int i = 0; i < ((x_max - x_min) + 1); i++) {x_vals[i] = (i + x_min);}
		for (int i = 0; i < ((y_max - y_min) + 1); i++) {y_vals[i] = (i + y_min);}
		for (int i = 0; i < ((ref.x_max - ref.x_min) + 1); i++) {rx_vals[i] = (i + ref.x_min);}
		for (int i = 0; i < ((ref.y_max - ref.y_min) + 1); i++) {ry_vals[i] = (i + ref.y_min);}

		int count = 0;
		for (int i = 0; i < ((x_max - x_min) + 1); i++) {
			for (int j = 0; j < ((ref.x_max - ref.x_min) + 1); j++) {
				if (x_vals[i] == rx_vals[j]) { x_overlap_vals[count++] = x_vals[i]; }
			}
		}
		int num_of_overlap_x_vals = (count-1);

		count = 0;
		for (int i = 0; i < ((y_max - y_min) + 1); i++) {
			for (int j = 0; j < ((ref.y_max - ref.y_min) + 1); j++) {
				if (y_vals[i] == ry_vals[j]) {y_overlap_vals[count++] = y_vals[i];}
			}
		}
		int num_of_overlap_y_vals = (count-1);

		LowerLeft_temp.set_xy(x_overlap_vals[0],y_overlap_vals[0]);
		UpperRight_temp.set_xy(x_overlap_vals[num_of_overlap_x_vals], y_overlap_vals[num_of_overlap_y_vals]);

		delete[] x_vals;
		delete[] y_vals;
		delete[] rx_vals;
		delete[] ry_vals;
		delete[] x_overlap_vals;
		delete[] y_overlap_vals;

		rect overlap_rect(LowerLeft_temp, UpperRight_temp);
		return overlap_rect;
	}
}
////두 RECT의 면적(중복영역 배제)
int rect::operator*(const rect& ref) {
	int area, ref_area; 
	area = this->get_area();
	ref_area = ref.get_area();
	rect overlapped_rect = *this - ref;
	return (area+ref_area)-overlapped_rect.get_area();
}