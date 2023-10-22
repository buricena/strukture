//Definirati strukturu osoba (ime, prezime, godina rođenja) i napisati program koji:
//A.dinamički dodaje novi element na početak liste,
//B.ispisuje listu,
//C.dinamički dodaje novi element na kraj liste,
//D.pronalazi element u listi(po prezimenu),
//E.briše određeni element iz liste,
//U zadatku se ne smiju koristiti globalne varijable
#include<stdio.h>
#include<stdlib.h>
typedef struct cvor Cvor;
typedef Cvor* Pozicija;
struct cvor {
	int element;
	Pozicija Next;

};
int UnosIspred(Pozicija P, int x, int y);
int UnosP(Pozicija P, int x);
int Ispis(Pozicija P);
int UnosK(Pozicija P, int x);
int main() {

	Cvor Head;
	Pozicija temp;
	Head.Next = NULL;
	UnosP(&Head, 15);
	UnosP(&Head, 10);
	UnosK(&Head, 20);
	Ispis(Head.Next);

	return 0;
}
int UnosP(Pozicija P, int x) {

	Pozicija q;
	q = (Pozicija)malloc(sizeof(Cvor));
	q->element = x;
	q->Next = P->Next;
	P->Next = q;
	return 0;

}
int UnosK(Pozicija P, int x) {

	Pozicija q;
	q = (Pozicija)malloc(sizeof(Cvor));
	q->element = x;
	while (P->Next != NULL)
		P = P->Next;
	q->Next = P->Next;
	P->Next = q;

	return 0;

}
int Ispis(Pozicija P) {

	printf("\n--------\n");
	while (P != NULL) {
		printf("\n -%d", P->element);
		P = P->Next;

	}
	return 0;
}