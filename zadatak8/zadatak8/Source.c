/*8. Napisati program koji omogućava rad s binarnim stablom pretraživanja. Treba
omogućiti unošenje novog elementa u stablo, ispis elemenata (inorder, preorder, postorder i
level order), brisanje i pronalaženje nekog elementa.*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef struct node node;
typedef struct node* position;
struct node {
	int val;
	position left;
	position right;
};
position createnode(int val);
position insert(position root, int val);
int inorder(position root);
int preorder(position root);
int postorder(position root);
position searchnode(position root, int val);
position deletenode(position root, int val);
position findmin(position root);

int main() {

	int rootVal=0;
	int choice;
	position root = NULL;
	printf("Vrijednost root-a:\n");
	scanf("%d", &rootVal);
	root = insert(root, rootVal);
	while (1) {
		printf("Odaberite sto zelite:\n1-unijeti novu vrijednost\n2-inorder ispis\n3-preorder ispis\n4-postorder ispis\n5-pretrazivanje elementa\n6-Brisanje elementa iz stabla\n");
		scanf("%d", &choice);
		if (choice == 1) {
			int value = 0;
			printf("Unesite vrijednost:\n");
			scanf("%d", &value);
			root = insert(root, value);
		}
		else if (choice == 2) {
			printf("Inorder ispis:\n");
			root = inorder(root);
		}
		else if (choice == 3) {
			printf("Preorder ispis:\n");
			root = preorder(root);
		}
		else if (choice == 4) {
			printf("Postorder ispis:\n");
			root = postorder(root);
		}
		else if (choice == 5) {
			int value = 0;
			printf("Koju vrijednost zelite pretraziti:\n");
			scanf("%d", &value);
			position result = NULL;
			result = searchnode(root, value);
			if (result != NULL)
				printf("\nPronaden je element %d.\n", value);
			else
				printf("Element %d nije pronaden.\n", value);
			
		}
		else if (choice == 6) {
			int val = 0;
			printf("Uneiste element koji zelite obrisati:\n");
			scanf("%d", &val);
			deletenode(root, val);

		}
	
		else {
			printf("Pogresan odabir.\n");
		}
	}

	return 0;
}
position createnode(int val) {
	position newnode = NULL;
	newnode = (position)malloc(sizeof(struct node));
	if (newnode == NULL) {
		printf("Greska pri alociranju memorije.\n");
		return NULL;
	}
	newnode->val = val;
	newnode->left = NULL;
	newnode->right = NULL;
	return newnode;

}
position insert(position root, int val) {
	
	if (root == NULL) {
		root = createnode(val);
	}
	else if (val < root->val) {
		root->left = insert(root->left, val);
	}
	else if (val > root->val) {
		root->right = insert(root->right, val);
	}
	return root;
}
int inorder(position root) {
	if (root != NULL) {
		root->left=inorder(root->left);
		printf("%d ", root->val);
		root->right=inorder(root->right);
	}
	return 0;
}
int preorder(position root) {
	if (root != NULL) {
		printf("%d ", root->val);
		root->left=preorder(root->left);
		root->right=preorder(root->right);
	}
	return 0;
}
int postorder(position root) {
	if (root != NULL) {
		root->left=postorder(root->left);
		root->right=postorder(root->right);
		printf("%d ", root->val);
	}
	return 0;
}
position searchnode(position root, int val) {
	if (root == NULL) {
		return NULL;
	}
	else if (val < root->val) {
		return searchnode(root->left, val);
	}
	else if (val > root->val) {
		return searchnode(root->right, val);
	}
	else
		return root;

}
position findmin(position root) {
	if (root == NULL) {
		return NULL;
	}
	else {
		if (root->left == NULL) {
			return root;
		}
		else {
			return findmin(root->left);
		}
	}
}

position deletenode(position root, int val) {
		if (root == NULL) {
			return root;
		}
		else if (val < root->val) {
			root->left = deletenode(root->left, val);
		}
		else if (val > root->val) {
			root->right = deletenode(root->right, val);
		}
		else {
			if (root->left == NULL) {
				position temp = root->right;
				free(root);
				return temp;
			}
			else if (root->right == NULL) {
				position temp = root->left;
				free(root);
				return temp;
			}

			//u slucaju sa dvoje djece
			position temp = findmin(root->right);
			root->val = temp->val;
			root->right = deletenode(root->right, temp->val);
		}
		return root;
	}


