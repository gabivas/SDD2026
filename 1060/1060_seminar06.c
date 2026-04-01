#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Nod Nod;
typedef struct HashTable HashTable;

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

struct HashTable
{
	Nod** vector;
	int dim;
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

void dezalocare(Nod** cap) {
	while ((*cap) != NULL) {
		free((*cap)->info.nume);
		Nod* aux = *cap;
		*cap = (*cap)->next;
		free(aux);
	}
}

HashTable initHashTable(int size) {
	HashTable tabela;
	tabela.dim = size;
	tabela.vector = (Nod**)malloc(size * sizeof(Nod*));
	for (int i = 0; i < size; i++)
	{
		tabela.vector[i] = NULL;
	}

	return tabela;
}

int hash(int varsta, int dimensiue) {
	return varsta % dimensiue;
}

void inserareInHashTable(HashTable tabela, Persoana p) {
	if (tabela.dim > 0) {
		int pozitie = hash(p.varsta, tabela.dim);
		if (pozitie >= 0 && pozitie < tabela.dim) {
			inserareLaSfarsit(&(tabela.vector[pozitie]), p);
		}
	}
}

void dezalocareHashTable(HashTable tabela) {
	for (int i = 0; i < tabela.dim; i++)
	{
		dezalocare(&(tabela.vector[i]));
	}
}

void traversareHashTable(HashTable tabela) {
	for (int i = 0; i < tabela.dim; i++)
	{
		printf("Pozitie: %d\n", i);
		afisareLista(tabela.vector[i]);
	}
}

float calculInaltimeMedieDupaVarsta(HashTable tabela, int varsta) {
	int pozitie = hash(varsta, tabela.dim);
	float sumaH = 0;
	int nrPersoane = 0;

	Nod* cap = tabela.vector[pozitie];
	while (cap != NULL) {
		if (cap->info.varsta == varsta) {
			sumaH += cap->info.inaltime;
			nrPersoane++;
		}
		cap = cap->next;
	}
	return sumaH / nrPersoane;
}

int main() {
	HashTable tabela = initHashTable(5);
	inserareInHashTable(tabela, initPersoana("Mihai", 26, 1.76));
	inserareInHashTable(tabela, initPersoana("Andreea", 27, 1.68));
	inserareInHashTable(tabela, initPersoana("Andrei", 27, 1.74));
	inserareInHashTable(tabela, initPersoana("Maria", 22, 1.64));

	traversareHashTable(tabela);

	printf("Inaltimea medie pentru persoanele cu varsta de 27 ani este: %.2f metri!", calculInaltimeMedieDupaVarsta(tabela, 27)); //1.71

	dezalocareHashTable(tabela);
	free(tabela.vector);
	tabela.dim = 0;
	tabela.vector = NULL;

	return 0;
}