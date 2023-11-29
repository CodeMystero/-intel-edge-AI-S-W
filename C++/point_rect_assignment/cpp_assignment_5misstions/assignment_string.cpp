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
		strcpy_s(this->str, strlen(string1) + 1, string1);
	}
	~stringClass() {
		delete[] str;
	}


	void operator()(const char* find) {
		const char* char_ptr = find;
		int cnt = 0;
		char* ptok = strtok(str, " ");
		while (ptok != nullptr) {
			ptok = strtok(nullptr, " ");
			if (strcmp(char_ptr, ptok) == 0) {
				cout << "해당 단어는 문장의 " << cnt + 2 << "번째 단어입니다." << endl;
			}
			cnt++;
		}
	}

	stringClass& operator-(size_t delet) {
		size_t length = strlen(str);
		if (delet == 0) return *this; 
		size_t lastSpace = length - 1;

		for (size_t i = 0; i < delet; i++) {
			while (lastSpace > 0 && str[lastSpace - 1] != ' ') {
				lastSpace--;
			}
		}

		if (lastSpace >= length) {this->str = NULL;
		}else {
			char* newStr = new char[lastSpace + 1];
			strncpy(newStr, str, lastSpace);
			newStr[lastSpace] = '\0';
			this->str = newStr;
			return *this;
		}
	}

	stringClass& operator=(const stringClass& other) {
		if (this != &other) {
			delete[] str;
			size_t length = strlen(other.str) + 1;
			str = new char[length] {0, };
			strcpy_s(str, length, other.str);
		}
		return *this;
	}



};

int main() {
	stringClass s1("The chicken is prepared and ready for someone to eat it.");
	stringClass s2("The children were having fun, chasing each other's shadows.");
	cout << s1.str << endl;
	s1 = s2;
	cout << s1.str << endl;
	s1 - 4;
	cout << s1.str << endl;
	s1("having");

	return 0;
}
