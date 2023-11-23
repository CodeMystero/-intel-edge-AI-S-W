#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct book{
	char book_title[20];
	char book_author[10];
	char book_publisher[20];
	char book_price[10];
	struct book *next;
};
typedef struct book Book;

Book* head = NULL;
Book* current = NULL;

void book_register();
void book_list();
void book_retrieve();

int main() {

	int selector = 0;

	while(selector!=4){

		printf("Mini Project - 도서관리 프로그램\n\n");
		printf("************* 메뉴 *************\n");
		printf("1. 등록\n2. 목록\n3. 검색\n4. 끝내기\n");
		printf("번호를 입력해 주세요 :");
		scanf("%d", &selector);
	
		switch(selector){

			case 1:
				book_register();
				break;
			case 2:
				book_list();
				break;
			case 3:
				book_retrieve();
				break;
			case 4:
				printf("프로그램이 종료됩니다.\n");
				exit(1);
		}
	}
	return 0;
}

void book_register(){

	Book *newbook = (Book *)malloc(sizeof(Book));
	if (newbook == NULL) {
		printf("주소값 할당에 실패하였습니다\n");
	}

	printf("새로운 책의 제목을 입력하세요. :");
	scanf("%s", newbook->book_title);
	printf("새로운 책의 저자를 입력하세요. :");
	scanf("%s", newbook->book_author);
	printf("새로운 책의 출판사를 입력하세요. :");
	scanf("%s", newbook->book_publisher);
	printf("새로운 책의 가격을 입력하세요. :");
	scanf("%s", newbook->book_price);

	if (head == NULL) {
		head = newbook;
		head->next = NULL;
		current = head;
	}
	else {
		current->next = newbook;
		current = newbook;
		current->next = NULL;
	}
	
	printf("새로운 책이 성공적으로 입력되었습니다.\n"); 
}

void book_list() {
	Book* current_point = NULL;
	current_point = head;
	int count = 0;
	printf("Book manage ment _ mini project 도서 리스트\n");
	printf("=====================================================================\n");
	printf("|번호\t\t제목\t\t저자\t\t출판사\t\t가격|\n");
	printf("=====================================================================\n");
	if (head == NULL) {
		printf("**************등록된 책이 발견되지 않았습니다.*************\n");
		printf("=====================================================================\n\n");
	}
	else{
		while (1) {
			if (current_point != NULL) {
				count++;
				printf("|[%2d]%14s%16s%17s%16s|\n", count, current_point->book_title, \
					current_point->book_author, current_point->book_publisher, current_point->book_price);
				current_point = current_point->next;
			}
			else {
				printf("=====================================================================\n\n");
				printf("등록된 책의 정보가 전부 출력되었습니다.\n");
				break;
			}
		}
	}
}

void book_retrieve() {
	Book* current_point = NULL;
	char search[20];
	int count=0;
	current_point = head;



	printf("검색할 책의 제목을 입력하세요 :");
	scanf("%s", &search);

	printf("Book manage ment _ mini project 검색된 도서 리스트\n");
	printf("=====================================================================\n");
	printf("|번호\t\t제목\t\t저자\t\t출판사\t\t가격|\n");
	printf("=====================================================================\n");

	
	while (1) {
		if (current_point != NULL) {
			if (*(current_point->book_title) == *search) {
				count++;
				printf("|[%2d]%14s%16s%17s%16s|\n", count, current_point->book_title, \
						current_point->book_author, current_point->book_publisher, current_point->book_price);
				current_point = current_point->next;
			}
			else {
				current_point = current_point->next;
				continue;
			}
		}
		else{
			printf("=====================================================================\n\n");
			printf("검색된 책의 정보가 전부 출력되었습니다.\n");
			break;
		 }
	}
}

