#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct cvor* node;

struct cvor {

	int el;
	node left;
	node right;

};

int insert(node);
int sum(node);
int replace(node);
int inorder(node);


int main() {

	srand(time(NULL));


	int niz[] = { 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 };


	int niz2[10];
	niz2[0] = rand() % 90 + 1;

	node root2 = (node)malloc(sizeof(struct cvor));

	if (!root2) {

		printf("Can't allocate memory\n");

	}

	root2->el = niz[0];
	root2->left = NULL;
	root2->right = NULL;

	node root = (node)malloc(sizeof(struct cvor));

	if (!root) {

		printf("Can't allocate memory\n");

	}

	root->el = niz[0];
	root->left = NULL;
	root->right = NULL;

	for (int i = 1; i < 10; i++) {

		niz2[i] = rand() % 90 + 1;

		insert(root2, niz2[i]);

	}


	for (int i = 1; i < (sizeof(niz) / sizeof(int)); i++) {

		insert(root, niz[i]);

	}

	FILE* fptr = NULL;

	fptr = fopen("Text.txt", "w");


	if (!fptr) {

		printf("File not opened correctly\n");

	}

	inorder(root2, fptr);


	return 1;
}


int insert(node root, int x) {

	node newNode = (node)malloc(sizeof(struct cvor));

	if (!newNode) {

		printf("Can't allocate memory\n");

	}

	newNode->el = x;
	newNode->left = NULL;
	newNode->right = NULL;

	int done = 0;

	while (done != 1) {

		if (newNode->el >= root->el && root->left != NULL) {

			root = root->left;

		}

		else if (newNode->el < root->el && root->right != NULL) {

			root = root->right;

		}

		else if (newNode->el >= root->el && root->left == NULL) {

			root->left = newNode;
			done = 1;

		}
		else if (newNode->el < root->el && root->right == NULL) {

			root->right = newNode;
			done = 1;

		}


	}



	return 1;
}


int sum(node root) {

	if (root->left == NULL && root->right == NULL) {

		return root->el;

	}

	else if (root->left == NULL && root->right != NULL) {

		return root->el + sum(root->right);

	}

	else if (root->left != NULL && root->right == NULL) {

		return root->el + sum(root->left);

	}

	else if (root->left != NULL && root->right != NULL) {

		return root->el + sum(root->left) + sum(root->right);

	}


}


int replace(node root) {

	int s = sum(root) - root->el;
	root->el = s;

	if (root->left != NULL) {

		replace(root->left);

	}

	if (root->right != NULL) {

		replace(root->right);

	}




	return 1;
}


int inorder(node root, FILE* fptr) {

	if (root->left != NULL) {

		inorder(root->left, fptr);

	}

	printf("%d\t", root->el);
	fprintf(fptr, "%d\t", root->el);

	if (root->right != NULL) {

		inorder(root->right, fptr);

	}


	return 1;
}