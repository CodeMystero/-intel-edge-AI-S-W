#include <iostream>
using namespace std;

//배열 합과 평균:

// 목표: 배열의 합과 평균을 계산하는 함수 작성

// 구현: 정수로 구성된 배열을 받아 해당 배열의 합과 평균을 계산하는 함수를 작성하세요.

// 설명: 정수 배열을 받아 배열의 합과 평균을 계산하는 함수를 작성합니다. 함수의 반환 형식은 구조체나 클래스로 할 수 있습니다.

class arr_Adder{
public:
    int operator()(int *arr_p, int size) { //arr_Adder(arr, sizeof(arr))
        size /= sizeof(int);
        int result = 0;
        for (int i = 0; i < size; i++) result += *(arr_p + i);
        return result;
    }
};

class arr_Avg {
public:
    double operator()(int* arr_p, double size) { //arr_Adder(arr, sizeof(arr))
        size /= sizeof(int);
        double sum_result = 0;
        for (int i = 0; i < size; i++) sum_result += *(arr_p + i);
        double avg_result = sum_result / size;
        return avg_result;
    }
};

int main() {
    arr_Adder arr_adder;
    arr_Avg arr_avg;
    int a[] = {1,2,5};
    int add_result1 = arr_adder(a, sizeof(a));
    cout << add_result1 << endl;
    double add_result2 = arr_avg(a, sizeof(a));
    cout.precision(2);
    cout << add_result2 << endl;
    return 0;
}