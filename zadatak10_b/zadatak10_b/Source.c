#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE 30

struct _list;
typedef struct _list* LPosition;
typedef struct _list {
    char grad[MAX_LINE];
    int br_stan;
    LPosition next;
}list;

struct _tree;
typedef struct _tree* TPosition;
typedef struct _tree {
    char drzava[MAX_LINE];
    LPosition gradovi;
    TPosition left;
    TPosition right;
}tree;

int InsertInTreeFromFile(TPosition head, char* fileName);
int InsertInListFromFile(LPosition head, char* fileName);
int SortListWhileInserting(LPosition head, LPosition newPerson);
int InsertAfter(LPosition who, LPosition where);
LPosition CreateListElement(char* grad, int br_stan);
int PrintList(LPosition first);
int PrintTreeInOrder(TPosition current);
TPosition SortTreeWhileInserting(TPosition current, TPosition newElement);
TPosition CreateTreeElement(char* drzava);


int main() {

    tree stblDrzava = { .drzava = "", .gradovi = NULL, .left = NULL, .right = NULL };
    TPosition stabloDrzava = &stblDrzava;

    char drzave[MAX_LINE] = { 0 };
    printf("Unesi ime datoteke s kojom zelis raditi\n:");
    scanf(" %[^\n]", drzave);
    InsertInTreeFromFile(stabloDrzava, drzave);
    PrintTreeInOrder(stabloDrzava);

    return EXIT_SUCCESS;

}


int InsertInTreeFromFile(TPosition head, char* fileName) {

    FILE* dat = NULL;
    dat = fopen(fileName, "r");
    char drzava[MAX_LINE] = { 0 }, datotekaGradova[MAX_LINE];

    tree tempp = { .drzava = "", .gradovi = NULL, .left = NULL, .right = NULL };
    TPosition temp = &tempp;

    if (!dat) {
        printf("Greska pri alociranju.\n");
        return EXIT_FAILURE;
    }

    while (!feof(dat)) {

        fscanf(dat, "%s %s", drzava, datotekaGradova);
        //printf("%s", temp -> gradovi);
        temp = CreateTreeElement(drzava);
        //printf("%s %d", temp -> gradovi -> grad, temp -> gradovi -> br_stan);
        InsertInListFromFile(temp->gradovi, datotekaGradova);

        head = SortTreeWhileInserting(head, temp);
    }

    fclose(dat);
    return EXIT_SUCCESS;
}

int InsertInListFromFile(LPosition head, char* fileName) {
    //printf("\nHead u insertu: %s", head);
    FILE* dat = NULL;
    dat = fopen(fileName, "r");

    char grad[MAX_LINE] = { 0 };
    int br_stan = 0;

    list tempp = { .grad = "", .br_stan = 0, .next = NULL };
    LPosition temp = &tempp;

    if (!dat) {
        printf("Greska pri alociranju.\n");
        return EXIT_FAILURE;
    }

    while (!feof(dat)) {
        fscanf(dat, "%s %d", grad, &br_stan);
        temp = CreateListElement(grad, br_stan);
        //printf("prije while petlje u sortiranju liste");
        //printf("%s %d", drzava -> gradovi -> grad, drzava -> gradovi -> br_stan);
        SortListWhileInserting(head, temp);
        //printf("na kraju while petlje u sortiranju liste");
    }

    fclose(dat);

    return EXIT_SUCCESS;

}


int SortListWhileInserting(LPosition head, LPosition newElement) {

    //printf("\nnovi element: %s %d", newElement -> grad, newElement -> br_stan);
    //printf("\nhead element: %s %d", head -> grad, head -> br_stan);

    while (head->next != NULL && head->next->br_stan > newElement->br_stan) { //ne triba next isprid temp!!
        head = head->next;
    }
    InsertAfter(newElement, head);
    return EXIT_FAILURE;
}


int InsertAfter(LPosition who, LPosition where) {

    who->next = where->next;
    where->next = who;

    return EXIT_SUCCESS;
}

LPosition CreateListElement(char* grad, int br_stan) {
    LPosition newElement = NULL;
    newElement = (LPosition)malloc(sizeof(list));

    if (!newElement) {
        perror("\nCan't allocate memory!");
        return NULL;
    }

    strcpy(newElement->grad, grad);
    newElement->br_stan = br_stan;
    newElement->next = NULL;

    return newElement;
}

int PrintList(LPosition first) {

    if (first == NULL) return 0;
    LPosition temp = first->next;

    while (temp) {
        printf("\n\t\tGrad %s sa %d stanovnika", temp->grad, temp->br_stan);
        temp = temp->next;
    }

    return EXIT_SUCCESS;
}

int PrintTreeInOrder(TPosition current) {
    if (current == NULL)
        return EXIT_SUCCESS;

    PrintTreeInOrder(current->left);
    printf("\nDrzava: %s", current->drzava);
    PrintList(current->gradovi);
    PrintTreeInOrder(current->right);

    return EXIT_SUCCESS;
}

TPosition SortTreeWhileInserting(TPosition current, TPosition newElement) {

    if (!current)
        return newElement;

    if (strcmp(current->drzava, newElement->drzava) > 0) {
        current->right = SortTreeWhileInserting(current->right, newElement);
    }

    else if (strcmp(current->drzava, newElement->drzava) < 0) {
        current->left = SortTreeWhileInserting(current->left, newElement);
    }
    else free(newElement);

    return current;
}

TPosition CreateTreeElement(char* drzava) {
    TPosition newElement = NULL;
    newElement = (TPosition)malloc(sizeof(tree));

    if (!newElement) {
        perror("\nCan't allocate memory.");
        return NULL;
    }

    strcpy(newElement->drzava, drzava);
    newElement->gradovi = (LPosition)malloc(sizeof(list));
    if (!newElement->gradovi) {
        perror("Can't allocate!");
        free(newElement);
        return NULL;
    }
    newElement->gradovi->next = NULL;
    newElement->right = NULL;
    newElement->left = NULL;

    //printf("Element je kreiran.\n%s %s %s", newElement -> gradovi -> br_stan, newElement -> drzava, newElement -> left -> drzava);

    return newElement;
}