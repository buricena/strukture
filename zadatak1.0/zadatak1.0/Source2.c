#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define max_bodovi 25

typedef struct student Student;

struct student {

    char ime[20];
    char prezime[20];
    int bodovi;

};

int main() {

    FILE* fptr;
    fptr = fopen("ljudi.txt", "r");

    Student* l = (Student*)malloc(sizeof(Student) * 0);
    int k = 0;

    while (!feof(fptr)) {

        Student s;

        fscanf(fptr, "%s\t%s\t%d", s.ime, s.prezime, &s.bodovi);
        l = realloc(l, sizeof(Student) * (k + 1));

        l[k] = s;

        k += 1;

    }


    for (int i = 0; i < k; i++) {

        float rbodovi = (float)l[i].bodovi / (float)max_bodovi * 100;
        printf("ime: %s\tprezime: %s\taps. bodovi: %d\trelativni bodovi: %.1f\n", l[i].ime, l[i].prezime, l[i].bodovi, rbodovi);

    }



    return 1;
}