#include <iostream>
using namespace std;
/*
템플릿 함수 최대값 찾기:

목표: 템플릿 함수를 사용하여 배열의 최대값을 찾는 프로그램 작성
구현: 정수, 실수 또는 다른 자료형의 배열에서 최대값을 찾는
템플릿 함수를 작성하세요.
설명:템플릿 함수를 사용하여 배열의 최대값을 찾는 프로그램을 작성합니다. 
다양한 자료형에 대해 동작하는 일반적인 함수를 구현합니다. 
*/


template <typename T>
T findMax(const T* arr, int size) {
    T max = arr[0];
    for (int i = 1; i < size; ++i) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

int main() {
    int intArray[] = { 3, 7, 1, 9, 4, 6, 8, 2, 5 };
    int size = sizeof(intArray) / sizeof(int);
    int maxInt = findMax(intArray, size);
    cout << "정수 배열의 최대값: " << maxInt << endl;

 
    double doubleArray[] = { 3.5, 7.2, 1.8, 9.1, 4.6, 6.3, 8.7, 2.4, 5.9 };
    size = sizeof(doubleArray) / sizeof(double);
    double maxDouble = findMax(doubleArray, size);
    cout << "실수 배열의 최대값: " << maxDouble << endl;

    char charArray[] = { 'a', 't', 'e', 'u', 'ㅣ', 'p', 'o', 'q', 'g'};
    size = sizeof(charArray) / sizeof(char);
    char maxChar = findMax(charArray, size);
    cout << "문자 배열의 최후방 문자: " << maxChar << endl;

    return 0;
}
