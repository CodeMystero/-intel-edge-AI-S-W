#include <iostream>
#include <Windows.h>
#include "point.h"
#include "rect.h"
#include<cstdlib>


int main() {
	point p1(2303, 560),p2(-410,-7000),p3(-710,110),p4(180, -809);

	rect rect1(p1, p2);
	printf("rect1(p1,p2) 의 Show 함수 : LowerLeft, UpperRight Point \n");
	rect1.show();
	rect rect2(p3, p4);
	printf("rect2(p3,p4) 의 Show 함수 : LowerLeft, UpperRight Point \n");
	rect2.show();

	rect rect3 = rect1 + rect2;
	printf("\nrect1 + rect2 -> 두 RECT를 포함하는 최소 사각형 생성\n");
	rect3.show();

	printf("\nrect1 - rect2 -> 두 RECT의 중복영역 사각형 생성\n");
	rect rect4 = rect1 - rect2;
	rect4.show();

	int area = rect1 * rect2;
	printf("두 사각형의 면적 (중복제거): %d\n", area);

	return 0;
}