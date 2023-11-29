#include <iostream>
#include <string>
using namespace std;
/*
직원 관리 시스템

목표: 클래스 상속을 사용하여 직원 계층 구조 만들기
구현: Employee라는 기본 클래스를 만들고, Manager와 
Developer등의 파생 클래스를 만들어 보세요.
각 클래스에는 직원 정보를 출력하는 가상 함수가 있어야 
합니다. 
설명:Employee 클래스를 만들고, Manager와 Developer등의 
파생 클래스를 생성하여 직원들의 정보를 다룹니다. 
가상 함수를 이용하여 각 직원의 정보를 출력하는 함수를 작성
하세요
*/

class employee{
public:
	string name;
	int age;
	
	employee(string name = "TBD", int age = NULL) {
		this->name = name;
		this->age = age;
	}
	virtual void employeeInfo() = 0;
};

class manager : public employee{
public:
	string position;

	manager(string position = "TBD") {
		this->position = position;
	}

	void employeeInfo() override {
		cout << "이름:" << name << endl;
		cout << "나이:" << age << endl;
		cout << "직책:" << position << endl;
	}

};

class developer : public employee{
public:
	string programming_language;

	developer(string programming_language = "TBD") {
		this->programming_language = programming_language;
	}

	void employeeInfo() override {
		cout << "이름:" << name << endl;
		cout << "나이:" << age << endl;
		cout << "직책:" << programming_language << endl << endl;

	}
};

int main() {
	developer* d_Blaze = new developer;
	d_Blaze->age = 30;
	d_Blaze->name = "Zephyr Blaze";
	d_Blaze->programming_language = "C++";
	d_Blaze->employeeInfo();

	manager* d_Boss = new manager;
	d_Boss->age = 50;
	d_Boss->name = "Hugo Boss";
	d_Boss->position = "RF tech manager";
	d_Boss->employeeInfo();


	return 0;
}
