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

		printf("Mini Project - �������� ���α׷�\n\n");
		printf("************* �޴� *************\n");
		printf("1. ���\n2. ���\n3. �˻�\n4. ������\n");
		printf("��ȣ�� �Է��� �ּ��� :");
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
				printf("���α׷��� ����˴ϴ�.\n");
				exit(1);
		}
	}
	return 0;
}

void book_register(){

	Book *newbook = (Book *)malloc(sizeof(Book));
	if (newbook == NULL) {
		printf("�ּҰ� �Ҵ翡 �����Ͽ����ϴ�\n");
	}

	printf("���ο� å�� ������ �Է��ϼ���. :");
	scanf("%s", newbook->book_title);
	printf("���ο� å�� ���ڸ� �Է��ϼ���. :");
	scanf("%s", newbook->book_author);
	printf("���ο� å�� ���ǻ縦 �Է��ϼ���. :");
	scanf("%s", newbook->book_publisher);
	printf("���ο� å�� ������ �Է��ϼ���. :");
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
	
	printf("���ο� å�� ���������� �ԷµǾ����ϴ�.\n"); 
}

void book_list() {
	Book* current_point = NULL;
	current_point = head;
	int count = 0;
	printf("Book manage ment _ mini project ���� ����Ʈ\n");
	printf("=====================================================================\n");
	printf("|��ȣ\t\t����\t\t����\t\t���ǻ�\t\t����|\n");
	printf("=====================================================================\n");
	if (head == NULL) {
		printf("**************��ϵ� å�� �߰ߵ��� �ʾҽ��ϴ�.*************\n");
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
				printf("��ϵ� å�� ������ ���� ��µǾ����ϴ�.\n");
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



	printf("�˻��� å�� ������ �Է��ϼ��� :");
	scanf("%s", &search);

	printf("Book manage ment _ mini project �˻��� ���� ����Ʈ\n");
	printf("=====================================================================\n");
	printf("|��ȣ\t\t����\t\t����\t\t���ǻ�\t\t����|\n");
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
			printf("�˻��� å�� ������ ���� ��µǾ����ϴ�.\n");
			break;
		 }
	}
}

