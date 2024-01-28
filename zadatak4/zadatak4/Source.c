#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct polynom listpoly;

struct polynom {

	int coef;
	int exp;
	listpoly* next;


};



int main() {

	FILE* fptr1;
	FILE* fptr2;

	listpoly* head1 = (listpoly*)malloc(sizeof(listpoly));
	listpoly* head2 = (listpoly*)malloc(sizeof(listpoly));
	listpoly* head3 = (listpoly*)malloc(sizeof(listpoly));
	listpoly* head4 = (listpoly*)malloc(sizeof(listpoly));

	head1->next = NULL;
	head2->next = NULL;
	head3->next = NULL;
	head4->next = NULL;



	fptr1 = fopen("polinom1.txt", "r");
	fptr2 = fopen("polinom2.txt", "r");

	while (!feof(fptr1)) {

		int a, b;
		fscanf(fptr1, "%d %d", &a, &b);

		add_element(a, b, head1);

	}

	while (!feof(fptr2)) {

		int a, b;
		fscanf(fptr2, "%d %d", &a, &b);

		add_element(a, b, head2);

	}

	fclose(fptr1);
	fclose(fptr2);

	print_polynom(head1->next);
	print_polynom(head2->next);

	sum_polynoms(head1->next, head2->next, head3);
	product_polynoms(head1->next, head2->next, head4);

	print_polynom(head3->next);
	print_polynom(head4->next);


	return 1;
}



int add_element(int x, int y, listpoly* prev) {

	listpoly* p = prev->next;
	listpoly* q = (listpoly*)malloc(sizeof(listpoly));

	q->coef = x;
	q->exp = y;
	q->next = NULL;

	if (prev->next == NULL) {

		prev->next = q;

	}

	else {

		while (p != NULL) {

			if (q->exp == p->exp) {

				p->coef += q->coef;
				free(q);
				break;

			}

			else if (q->exp > p->exp) {

				prev->next = q;
				q->next = p;
				break;

			}


			prev = p;
			p = p->next;
		}

		if (p == NULL) {

			prev->next = q;

		}



		return 1;
	}
}


int print_polynom(listpoly* p) {

	while (p != NULL) {

		printf("%dx^%d ", p->coef, p->exp);
		p = p->next;

	}
	printf("\n");


	return 1;
}



int sum_polynoms(listpoly* p1, listpoly* p2, listpoly* sum) {

	while (p1 != NULL) {

		add_element(p1->coef, p1->exp, sum);
		p1 = p1->next;

	}

	while (p2 != NULL) {

		add_element(p2->coef, p2->exp, sum);
		p2 = p2->next;

	}



	return 1;
}


int product_polynoms(listpoly* p1, listpoly* p2, listpoly* product) {

	while (p1 != NULL) {

		listpoly* tmp = p2;

		while (tmp != NULL) {

			add_element(p1->coef * tmp->coef, p1->exp + tmp->exp, product);
			tmp = tmp->next;

		}

		p1 = p1->next;

	}


}