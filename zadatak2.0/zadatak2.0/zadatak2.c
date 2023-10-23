//Definirati strukturu osoba (ime, prezime, godina rođenja) i napisati program koji:
//A.dinamički dodaje novi element na početak liste,
//B.ispisuje listu,
//C.dinamički dodaje novi element na kraj liste

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct osoba Osoba;

struct osoba {

    char ime[20];
    char prezime[20];
    int godina;
    Osoba* next;

};

int UnosP(Osoba* p) {

    Osoba* q = (Osoba*)malloc(sizeof(Osoba));
    printf("Unos-\n Ime i prezime: Godina rodenja: ");
    scanf("%s %s %d", q->ime, q->prezime, &q->godina);

    if (p->next != NULL) {

        q->next = p->next;
        p->next = q;

    }

    else {

        p->next = q;
        q->next = NULL;

    }

    return 0;
}

int ispis(Osoba* p) {

    while (p->next != NULL) {

        printf("%s %s %d\n", p->ime, p->prezime, p->godina);

        p = p->next;

    }

    printf("%s %s %d\n", p->ime, p->prezime, p->godina);

    return 0;
}

int UnosK(Osoba* p) {

    while (p->next != NULL) {

        p = p->next;

    }

    Osoba* q = (Osoba*)malloc(sizeof(Osoba));

    printf("Unos- Ime prezime Godina rodenja: ");
    scanf("%s %s %d", q->ime, q->prezime, &q->godina);

    p->next = q;
    q->next = NULL;


    return 0;
}



int main() {

    Osoba* head = (Osoba*)malloc(sizeof(Osoba));
    head->next = NULL;

    UnosP(head);
    UnosP(head);
    UnosK(head);

    ispis(head->next);


    return 0;
}
