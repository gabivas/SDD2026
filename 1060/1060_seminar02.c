#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Persoana {
	char* nume;
	int varsta;
	float inaltime;
} Persoana;

void preluarePersoanaDinFiser(FILE* fisier, Persoana* persoana) {
	char buffer[20];
	fscanf(fisier, "%s %d %f", buffer, &persoana->varsta, &persoana->inaltime);

	persoana->nume = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
	strcpy(persoana->nume, buffer);
}

void afisarePersoana(Persoana persoana) {
	printf("Nume: %s, varsta: %d, inaltime: %.2f.\n", persoana.nume, persoana.varsta, persoana.inaltime);
}

void afisarePersoane(Persoana* persoane, int size) {
	for (int i = 0; i < size; i++) {
		afisarePersoana(persoane[i]);
	}
}

Persoana* preluarePersoaneDinFisier(const char* numeFisier, int* size) {
	FILE* fisier = fopen(numeFisier, "r");
	if (!fisier)
	{
		printf("Eroare la deschiderea fisierului!\n");
		return NULL;
	}

	fscanf(fisier, "%d", size);

	Persoana* persoane = (Persoana*)malloc(sizeof(Persoana) * (*size));
	for (int i = 0; i < *size; i++) {
		preluarePersoanaDinFiser(fisier, &(persoane[i]));
	}

	fclose(fisier);

	return persoane;
}

int main() {
	//persoana.txt:
	//Dan 20 1.75
	FILE* fisier = fopen("persoana.txt", "r");
	if (!fisier)
	{
		printf("Eroare la deschiderea fisierului!\n");
	}

	Persoana persoana;
	preluarePersoanaDinFiser(fisier, &persoana);

	afisarePersoana(persoana);

	free(persoana.nume);
	fclose(fisier);
	int dim;
	//persoane.txt:
	//3
	//Dan 20 1.75
	//Maria 21 1.70
	//Andrei 22 1.76
	Persoana* vectorPersoane = preluarePersoaneDinFisier("persoane.txt", &dim);

	if (!vectorPersoane) {
		afisarePersoane(vectorPersoane, dim);
	}

	return 0;
}