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
	Nod* prev;
};

Persoana initPersoana(const char* nume, int varsta, float inaltime) {
	Persoana p;
	p.varsta = varsta;
	p.inaltime = inaltime;
	p.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(p.nume, nume);

	return p;
}

void afisarePersoana(Persoana persoana) {
	printf("Nume: %s, varsta: %d, inaltime: %.2f.\n", persoana.nume, persoana.varsta, persoana.inaltime);
}

void afisareLista(Nod* cap) {
	while (cap != NULL) {
		afisarePersoana(cap->info);
		cap = cap->next;
	}
}

void afisareListaDreaptaStanga(Nod* coada) {
	while (coada != NULL) {
		afisarePersoana(coada->info);
		coada = coada->prev;
	}
}

void inserareLaInceput(Nod** cap, Nod** coada, Persoana p) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = p; // shallow copy util
	nou->next = *cap;
	nou->prev = NULL;

	if (*cap == NULL) {
		*cap = *coada = nou;
	}
	else {
		(*cap)->prev = nou;
		*cap = nou;
	}
}

void inserareLaSfarsit(Nod** cap, Nod** coada, Persoana p) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = p; // shallow copy util
	nou->next = NULL;
	nou->prev = *coada;

	if ((*cap) == NULL) {
		*cap = *coada = nou;
	}
	else {
		(*coada)->next = nou;
		*coada = nou;
	}
}

void dezalocare(Nod** cap, Nod** coada) {
	while ((*cap) != NULL) {
		free((*cap)->info.nume);
		Nod* aux = *cap;
		*cap = (*cap)->next;
		free(aux);
	}
	*coada = NULL;
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

void afisareLDICirculara(Nod* cap) {
	if (!cap) {
		return;
	}
	Nod* aux = cap;
	do
	{
		afisarePersoana(cap->info);
		cap = cap->next;

	} while (aux != cap);
}

void afisareLDICirculara2(Nod* cap) {
	if (!cap) {
		return;
	}
	Nod* aux = cap->prev;
	while (cap != aux) {
		afisarePersoana(cap->info);
		cap = cap->next;
	}
	afisarePersoana(cap->info);
}

float inaltimeMaxima(Nod* cap) {
	float maxx = 0;
	Nod* aux = cap;
	do 
	{
		if (cap->info.inaltime > maxx)
			maxx = cap->info.inaltime;
		cap = cap->next;
	} while (aux != cap);
	return maxx;
}

int main() {
	Nod* cap = NULL;
	Nod* coada = NULL;
	inserareLaSfarsit(&cap, &coada, initPersoana("Mihai", 26, 1.76));
	inserareLaSfarsit(&cap, &coada, initPersoana("Andreea", 24, 1.68));
	inserareLaSfarsit(&cap, &coada, initPersoana("Maria", 22, 1.64));

	afisareLista(cap);

	printf("\nInaltimea medie este de: %.2f metri!\n", calculInaltimeMedie(cap));

	//LDI circulara
	coada->next = cap;
	cap->prev = coada;

	printf("\nInaltimea max este de: %.2f metri!\n\n", inaltimeMaxima(cap));

	afisareLDICirculara(cap);

	//dezalocare(&cap, &coada);

	return 0;
}