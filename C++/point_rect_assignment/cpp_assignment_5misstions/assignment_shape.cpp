#include <iostream>
#include <cmath>
using namespace std;


// 도형 계층

// 구조:목표: 기본 클래스와 파생 클래스를 사용하여 도형의 계층 구조 만들기

// 구현: Shape이라는 기본 클래스를 만들고, Circle, Rectangle, Triangle 등의 도형 클래스를 파생시킵니다. 각 도형 클래스는 넓이를 계산하는 함수를 포함해야 합니다.

// 설명: Shape 클래스를 만들어 기본 도형의 속성과 면적을 계산하는 가상 함수를 구현합니다. 그리고 Circle, Rectangle,
// Triangle 등의 클래스를 만들어 기본 클래스를 상속받아 특정 도형들의 면적을 구합니다.


class shape {
public:
    virtual double area() = 0;
};

class circle : public shape {
private:
    double r;

public:
    circle(double r) { this->r = r; }

    double area() override {
        return 3.14 * pow(r, 2);
    }
};

class rectangle : public shape {
private:
    double w;
    double h;

public:
    rectangle(double w, double h){
        this->w = w;
        this->h = h;
    }

    double area() override {
        return w * h;
    }
};

class triangle : public shape {
private:
    double w;
    double h;

public:
    triangle(double w, double h){
        this->w = w;
        this->h = h;
    }

    double area() override {
        return 0.5 * w * h;
    }
};

int main(){
    circle c(4);
    rectangle r(21, 4);
    triangle t(31, 43);

    cout.precision(2);
    cout << c.area() << endl;
    cout << r.area() << endl;
    cout << t.area() << endl;
    return 0;
}