#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct treeNode treeNode;
typedef treeNode* Node;

struct treeNode {

	char name[20];
	Node firstChild;
	Node nextBrother;

};


int make_new_directory(char[20], Node);
Node search_directory(char[20], Node);
int directory_output(Node);
Node previous_directory(char[20], Node);


int main() {

	Node root = (Node)malloc(sizeof(treeNode));

	if (!root) {

		printf("Can't allocate memory\n");

	}

	printf("Input main directory name: "); scanf("%s", root->name);
	root->firstChild = NULL;
	root->nextBrother = NULL;

	Node directory = root;

	int choice = 0;
	char a[20];


	while (choice != 4) {

		printf("1 - make new directory\n2 - change current directory\n3 - output directory content\n4 - exit\n\n");

		scanf("%d", &choice);

		if (choice == 1) {

			printf("Inside which directory to put new directory: ");  scanf("%s", &a);
			make_new_directory(a, root);

		}

		else if (choice == 2) {

			printf("Which directory you want to be curent one: "), scanf("%s", &a);
			directory = search_directory(a, root);

		}

		else if (choice == 3) {

			directory_output(directory);


		}


	}

	return 1;
}

Node search_directory(char s[20], Node n) {

	if (strcmp(s, n->name) == 0) {

		return n;

	}

	else if (n->firstChild == NULL && n->nextBrother == NULL) {

		return NULL;

	}

	else {

		if (n->firstChild != NULL && search_directory(s, n->firstChild) != NULL) {

			return search_directory(s, n->firstChild);

		}

		if (n->nextBrother != NULL && search_directory(s, n->nextBrother) != NULL) {

			return search_directory(s, n->nextBrother);

		}

	}



}


int make_new_directory(char s[20], Node n) {

	Node q = (Node)malloc(sizeof(treeNode));


	if (!q) {

		printf("Can't allocate memory\n");

	}

	printf("Input new directory name: "); scanf("%s", q->name);

	q->firstChild = NULL;
	q->nextBrother = NULL;

	Node n1 = search_directory(s, n);

	if (n1->firstChild == NULL) {

		n1->firstChild = q;

	}

	else {

		n1 = n1->firstChild;

		while (n1->nextBrother != NULL) {

			n1 = n1->nextBrother;

		}

		n1->nextBrother = q;

	}


	return 1;
}


int directory_output(Node n) {

	n = n->firstChild;

	while (n != NULL) {

		printf("%s\n", n->name);
		n = n->nextBrother;

	}



	return 1;
}



Node previous_directory(char s[20], Node n) {

	Node n1 = n;

	if (strcmp(n->firstChild->name, s) == 0 && n->firstChild != NULL) {

		return n1;

	}


	else {

		n = n->firstChild;

		if (n->firstChild != NULL) {

			return previous_directory(s, n);

		}

	}

	while (n->nextBrother != NULL) {

		if (strcmp(n->nextBrother->name, s) == 0) {

			return n1;

		}

		else {

			n = n->nextBrother;
			return previous_directory(s, n);

		}
	}

}