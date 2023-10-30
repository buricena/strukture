#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*3. Prethodnom zadatku dodati funkcije:
A. dinamički dodaje novi element iza određenog elementa,
B. dinamički dodaje novi element ispred određenog elementa,
C. sortira listu po prezimenima osoba,
D. upisuje listu u datoteku,
E. čita listu iz datoteke
*/
typedef struct osoba* position;
struct osoba {
	char ime[50];
	char prezime[50];
	int godrod;
	position next;
};
int unosP(position p);
int ispis(position p);
int unosK(position p);
int trazi(position p);
int brisiEl(position p);
int dodajispred(position p);
int dodajiza(position p);
int sort(position p);
int upis(position p);
int citaj();



int main() {

	struct osoba Head;
	Head.next = NULL;
	char c;
	while (1){
		printf("Izaberite sta zelite:\np(unos na pocetak),i(ispis),k(unos na kraj),t(traziti po prezimenu),b(obrisati element),d(dodavanje ispred nekog elementa),z(dodavanje iza nekog elementa),s(sortiranje),u(ucitavanje datoteke),c(citanje datoteke):\n");
		scanf(" %c", &c);
		if (c == 'p')
			unosP(&Head);
		else if (c == 'i')
			ispis(&Head);
		else if (c == 'k')
			unosK(&Head);
		else if (c == 't')
			trazi(&Head);
		else if (c == 'b')
			brisiEl(&Head);
		else if (c == 'd')
			dodajispred(&Head);
		else if (c == 'z')
			dodajiza(&Head);
		else if (c == 's')
			sort(&Head);
		else if (c == 'u')
			upis(&Head);
		else if (c == 'c')
			citaj(); 
		else
			printf("\nNepoznato slovo\n");

	}

	return 0;
}
int unosP(position p) {
	position q = NULL;
	q = (position)malloc(sizeof(struct osoba));
	printf("Unesite ime osobe:\n");
	scanf("%s", q->ime);
	printf("Unesite prezime osobe:\n");
	scanf("%s", q->prezime);
	printf("Unesite godinu rodenja:\n");
	scanf("%d", &q->godrod);
	q->next = p->next;
	p->next = q;

	return 1;
}
int ispis(position p) {
	while (p!= NULL) {
		printf("\n%s %s(%d)\n", p->ime, p->prezime, p->godrod);
		p = p->next;

	}
	return 0;
}
int unosK(position p) {
	while (p->next != NULL) {
		p = p->next;
	}
	position q = NULL;
	q = (position)malloc(sizeof(struct osoba));
	if (q == NULL) {
		printf("Greska\n");
		return 1;
	}
	printf("Unesite ime osobe:\n");
	scanf("%s", q->ime);
	printf("unesite prezime osobe:\n");
	scanf("%s", q->prezime);
	printf("Unesite godinu rodenja:\n");
	scanf("%d", &q->godrod);

	q->next = p->next;
	p->next = q;
	return 0;
}
int trazi(position p) {
char surname[50];
printf("Unesite prezime koje zelite pretraziti:\n");
scanf(" %s", &surname);
while (p != NULL && strcmp(surname, p->prezime) != 0) {

	p = p->next;
}
if (p == NULL)
printf("Prezime nije u listi.\n");
else
printf("Adresa prezimena je: %p\n", p);
return 0;

}
int brisiEl(position p) {

	position pret = NULL;
	char prez[50];
	printf("Unesite prezime osobe koju zelite izbrisati:\n");
	scanf(" %s", &prez);
	while (p->next != NULL && strcmp(prez, p->prezime) != 0)
	{
		pret = p;
		p = p->next;
	}
	if (pret != NULL && strcmp(prez, p->prezime) == 0)
	{
		p = pret->next;
		pret->next = p->next;
		free(p);
	}
	return 0;
}
int dodajispred(position p) {
	position n = NULL;
	position pret = NULL;
	char sur[50];
	n = (position)malloc(sizeof(struct osoba));
	if (n == NULL) {
		printf("Greska\n");
		return 1;
	}
	printf("Unesite ime osobe:\n");
	scanf(" %s", n->ime);
	printf("Unesite prezime osobe:\n");
	scanf(" %s", n->prezime);
	printf("Unesite godinu rodenja:\n");
	scanf("%d", &n->godrod);
	printf("Unesite prezime osobe ispred koje zelite dodati novu osobu:\n");
	scanf(" %s", &sur);
	pret = p;
	while (p->next != NULL && strcmp(sur, p->prezime) != 0) {

		pret = p;
		p = p->next;
	}

	if (p->next != NULL) {
		n->next = p;
		pret->next = n;
	}
	return 0;
}
int dodajiza(position p) {

	position n = NULL;
	char sur[50];
	n = (position)malloc(sizeof(struct osoba));
	if (n == NULL) {
		printf("Greska\n");
		return 1;
	}
	printf("Unesite ime osobe:\n");
	scanf(" %s", n->ime);
	printf("Unesite prezime osobe:\n");
	scanf(" %s", n->prezime);
	printf("Unesite godinu rodenja:\n");
	scanf("%d", &n->godrod);
	printf("Uneiste prezime osobe iza koje zelite dodati novu:\n");
	scanf(" %s", &sur);
	while (p->next != NULL && strcmp(sur, p->prezime) != 0) {
		p = p->next;
	}
	n->next = p->next;
	p->next = n;

	return 0;
}
int upis(position p) {
	FILE* fp = NULL;
	fp = fopen("lista.txt", "w");
	if (fp == NULL) {
		printf("Greska kod otvoranja datoteke.\n");
		return 1;
	}
	while (p != NULL) {
		fprintf(fp, "%s\t%s\t%d\t\n", p->ime, p->prezime, p->godrod);
		p = p->next;
	}
	fclose(fp);


	return 0;
}
int sort(position p) {

	position j, prev_j, temp, end;

	end = NULL;
	while (p->next != end) {
		prev_j = p;
		j = p->next;
		while (j->next != end) {

			if (strcmp(j->prezime, j->next->prezime) > 0) {

				temp = j->next;
				prev_j->next = temp;
				j->next = temp->next;
				temp->next = j;

				j = temp;

			}


			prev_j = j;
			j = j->next;
		}

		end = j;

	}


	return 1;
}

int citaj() {

	FILE* fptr = NULL;
	fptr = fopen("lista1.txt", "r");

	char buff[1000];
	fgets(buff, 1000, fptr);

	char ime[20];
	char prezime[20];
	int g_r;

	while (!feof(fptr)) {


		fscanf(fptr, "%s\t%s\t%d", ime, prezime, &g_r);

		printf("%s %s %d\n", ime, prezime, g_r);

	}

	fclose(fptr);
	return 0;

}