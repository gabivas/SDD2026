#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Nod Nod;

typedef struct Persoana {
	char* nume;
	int varsta;
	float inaltime;
} Persoana;

struct Nod
{
	Persoana info;
	Nod* next;
};

Persoana preluarePersoanaDinFiser(FILE* fisier) {
	char buffer[20];
	Persoana p;
	fscanf(fisier, "%s %d %f", buffer, &p.varsta, &p.inaltime);

	p.nume = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
	strcpy(p.nume, buffer);

	return p;
}

void afisarePersoana(Persoana persoana) {
	printf("Nume: %s, varsta: %d, inaltime: %.2f.\n", persoana.nume, persoana.varsta, persoana.inaltime);
}

void afisareLista(Nod* cap) {
	while(cap!= NULL){
		afisarePersoana(cap->info);
		cap = cap->next;
	}
}

void inserareLaInceput(Nod** cap, Persoana p) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = p; // shallow copy util
	nou->next = *cap;
	*cap = nou;
}

void inserareLaSfarsit(Nod** cap, Persoana p) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = p; // shallow copy util
	nou->next = NULL;

	if ((*cap) == NULL) {
		*cap = nou;
	}
	else {
		Nod* aux = *cap;
		while (aux->next != NULL) {
			aux = aux->next;
		}
		aux->next = nou;
	}
}

Nod* preluareListaPersoaneDinFisier(const char* numeFisier) {
	FILE* fisier = fopen(numeFisier, "r");
	if (!fisier)
	{
		printf("Eroare la deschiderea fisierului!\n");
		return NULL;
	}
	Nod* cap = NULL;
	inserareLaSfarsit(&cap, preluarePersoanaDinFiser(fisier));
	inserareLaSfarsit(&cap, preluarePersoanaDinFiser(fisier));
	inserareLaSfarsit(&cap, preluarePersoanaDinFiser(fisier));

	fclose(fisier);

	return cap;
}

void dezalocare(Nod** cap){
	while ((*cap) != NULL) {
		free((*cap)->info.nume);
		Nod* aux = *cap;
		*cap = (*cap)->next;
		free(aux);
	}
}

float calculInaltimeMedie(Nod* cap) {
	float suma = 0;
	int nrPers = 0;
	while (cap != NULL) {
		suma += cap->info.inaltime;
		nrPers++;
		cap = cap->next;
	}

	return suma / nrPers;
}

int main() {
	Nod* cap = preluareListaPersoaneDinFisier("persoane.txt");

	afisareLista(cap);

	printf("\nInaltimea medie este de: %.2f metri!", calculInaltimeMedie(cap));

	dezalocare(&cap);

	return 0;
}