#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

typedef struct Nod Nod;

typedef struct Carte {
	char* titlu;
	int nrPagini;
	float pret;
} Carte;

struct Nod {
	Carte info;
	Nod* next;
};

void push(Nod** varf, Carte c) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c; //shallow copy util
	nou->next = *varf;
	*varf = nou;
}

void put(Nod** prim, Carte c) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c; //shallow copy util
	nou->next = NULL;
	if ((*prim) == NULL) {
		*prim = nou;
	}
	else {
		Nod* aux = *prim;
		while (aux->next != NULL) {
			aux = aux->next;
		}
		aux->next = nou;
	}
}

Carte initCarte(const char* titlu, int nrPagini,
float pret) {
	Carte c;
	c.nrPagini = nrPagini;
	c.pret = pret;
	c.titlu = (char*)malloc(sizeof(char) * (strlen(titlu) + 1));
	strcpy(c.titlu, titlu);

	return c;
}

void afisareCarte(Carte carte) {
	printf("\nTitlu: %s, nrPagini: %d, pret: %.2f.", carte.titlu, carte.nrPagini, carte.pret);
}

Carte pop(Nod** stiva) {
	if (*stiva == NULL) {
		return initCarte(NULL, 0, 0);
	}
	Carte c = (*stiva)->info;
	//deep copy: Carte c = initCarte((*stiva)->info.titlu, (*stiva)->info.nrPagini...);
	Nod* copie = *stiva;
	*stiva = (*stiva)->next;
	free(copie);
	return c;
}

void conversieDinCoadaInVector(Nod** coada, Carte** vectorCarti, int nrCarti) {
	*vectorCarti = (Carte*)malloc(sizeof(Carte) * nrCarti);
	int i = 0;
	while (*coada != NULL) {
		(*vectorCarti)[i] = pop(coada);
		i++;
	}
}

int main() {
	Nod* stiva = NULL;
	push(&stiva, initCarte("Don Quijote", 250, 45));
	push(&stiva, initCarte("Macbeth", 320, 62.5));
	push(&stiva, initCarte("Mandrie si prejudecata", 170, 50));
	push(&stiva, initCarte("Frankenstein", 225, 61));

	printf("\nTraversare stiva:");
	Carte c;
	while (stiva != NULL) {
		c = pop(&stiva);
		afisareCarte(c);
		free(c.titlu);
	}

	Nod* coada = NULL;
	put(&coada, initCarte("Don Quijote", 250, 45));
	put(&coada, initCarte("Macbeth", 320, 62.5));
	put(&coada, initCarte("Mandrie si prejudecata", 170, 50));
	put(&coada, initCarte("Frankenstein", 225, 61));

	//printf("\nTraversare coada:");
	//while (coada != NULL) {
	//	c = pop(&coada); // get este pop
	//	afisareCarte(c);
	//	free(c.titlu);
	//}
	Carte* vectorCarti = NULL;
	int nrCarti = 4;
	conversieDinCoadaInVector(&coada, &vectorCarti, nrCarti);
	if (vectorCarti != NULL) {
		printf("\nTraversare vector:");
		for (int i = 0; i < nrCarti; i++) {
			afisareCarte(vectorCarti[i]);
			free(vectorCarti[i].titlu);
		}

		free(vectorCarti);
	}	

	return 0;
}