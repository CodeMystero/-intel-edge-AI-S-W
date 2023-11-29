#include <iostream>
#include <string>
using namespace std;
/*
String class:

목표: 배열클래스를 이용한 문자열 처리 클래스 작성
구현: 문자열을 다루는 데 적합한 String 클래스를 만들고, 
연산자를 오버로딩하여 문자열에 대한 연산을 수행하세요.
설명: 연산자 오버로딩 -> 찾기, 자르기, 바꾸기 연산 수행 

TURN OFF THE WARNING 
*/
class stringClass {
public:
	char* str;
	stringClass(const char* string1) {
		this->str = new char[strlen(string1) + 1]; 
		strcpy_s(this->str,strlen(string1)+1, string1);
	}
	~stringClass() {
		delete[] str;
	}


	void operator()(const char* find) {
		int cnt = 0;
		char* ptok = strtok(str, " ");
		while (ptok != nullptr) {
			ptok = strtok(nullptr," ");
			if (strcmp(find, ptok) == 0) {
				cout << "해당 단어는 문장의 " << cnt + 2 << "번째 단어입니다." << endl;
			}
			cnt++;
		}
	}
	
	void operator-(int delet){
		int cnt = 0;
		while ((str + cnt) != "\0") {
			cnt++;
		}
		cout << cnt << endl;
	}

};

int main() {
	stringClass s1("The chicken is prepared and ready for someone to eat it.");
	cout << s1.str << endl;
	
	s1 - 5;
	//s1("ready");
	
	return 0;
}
