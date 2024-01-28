#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stog stog;

struct stog {

	int value;
	stog* next;

};

int main() {

	stog* head = (stog*)malloc(sizeof(stog));

	if (!head) {

		printf("Can't allocate memory\n");

	}

	head->value = NULL;
	head->next = NULL;

	FILE* fptr;
	fptr = NULL;

	fptr = fopen("postfiks.txt", "r");

	if (!fptr) {

		printf("File not opened correctly\n");

	}

	char buff[100];
	fgets(buff, 100, fptr);

	for (int i = 0; i < strlen(buff); i++) {


		if (buff[i] != '+' && buff[i] != '-' && buff[i] != '*' && buff[i] != '/') {

			push((int)buff[i] - 48, head);

		}

		else {

			if (buff[i] == '+') {

				int result;
				stog* p = head->next;
				stog* q = p->next;

				result = p->value + q->value;

				pop(head);
				pop(head);
				push(result, head);

				printf("%d\n", result);
			}

			else if (buff[i] == '-') {

				int result;
				stog* p = head->next;
				stog* q = p->next;

				result = p->value - q->value;

				pop(head);
				pop(head);
				push(result, head);
				printf("%d\n", result);


			}

			else if (buff[i] == '*') {

				int result;
				stog* p = head->next;
				stog* q = p->next;

				result = p->value * q->value;

				pop(head);
				pop(head);
				push(result, head);
				printf("%d\n", result);


			}

			else if (buff[i] == '/') {

				int result;
				stog* p = head->next;
				stog* q = p->next;

				result = p->value / q->value;

				pop(head);
				pop(head);
				push(result, head);

				printf("%d\n", result);


			}
		}


	}

	fclose(fptr);

	return 1;
}


int push(int x, stog* head) {

	stog* q = (stog*)malloc(sizeof(stog));

	if (!q) {

		printf("Can't allocate memory\n");

	}

	q->value = x;
	q->next = NULL;


	if (head->next == NULL) {

		head->next = q;
		q->next = NULL;

	}

	else {

		q->next = head->next;
		head->next = q;

	}


	return 1;
}


int pop(stog* head) {

	stog* p = head->next;

	head->next = p->next;
	free(p);

	return 1;
}