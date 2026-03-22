#include<stdio.h>
#include<malloc.h>

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

Persoana initPersoana(const char* nume,int varsta, float inaltime) {
	Persoana p;
	p.inaltime = inaltime;
	p.varsta = varsta;
	p.nume = (char*)malloc(strlen(nume) + 1);
	strcpy(p.nume, nume);

	return p;
}

void afisarePersoana(Persoana p) {
	printf("\nPersoana cu numele %s are inaltimea egala cu %.2f si varsta egala cu %d.", p.nume, p.inaltime, p.varsta);
}

void push(Nod** varf, Persoana p) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = p;
	nou->next = *varf;
	*varf = nou;
}

Persoana pop(Nod** varf) {
	if ((*varf) == NULL) {
		return initPersoana(NULL, 0, 0);
	}
	Persoana p;
	p = (*varf)->info;
	//deep copy: p = initPersoana((*varf)->info.nume, (*varf)->info.inaltime...)
	Nod* aux = *varf;
	*varf = (*varf)->next;
	free(aux);

	return p;
}

void put(Nod** coada, Persoana p) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->next = NULL;
	nou->info = p;

	if (*coada == NULL) {
		*coada = nou;
	}
	else {
		Nod* aux = *coada;
		while (aux->next != NULL) {
			aux = aux->next;
		}
		aux->next = nou;
	}
}

void conversieDeLaCoadaLaVector(Nod** coada, Persoana** vectorPersoane, int dim) {
	for (int i = 0; i < dim; i++) {
		(*vectorPersoane)[i] = pop(coada);
	}
}

int main() {
	Nod* stiva = NULL;
	push(&stiva, initPersoana("Andrei", 20, 1.72));
	push(&stiva, initPersoana("Maria", 21, 1.74));
	push(&stiva, initPersoana("Dan", 22, 1.76));

	printf("\nParcurgere stiva:");
	Persoana p;
	while (stiva != NULL) {
		p = pop(&stiva);
		afisarePersoana(p);
		free(p.nume);
	}

	Nod* coada = NULL;
	put(&coada, initPersoana("Andrei", 20, 1.72));
	put(&coada, initPersoana("Maria", 21, 1.74));
	put(&coada, initPersoana("Dan", 22, 1.76));

	//printf("\nParcurgere coada:");
	//while (coada != NULL) {
	//	p = pop(&coada); // get = pop
	//	afisarePersoana(p);
	//	free(p.nume);
	//}
	int dim = 3;
	Persoana* vectorPersoana = (Persoana*)malloc(sizeof(Persoana) * dim);
	conversieDeLaCoadaLaVector(&coada, &vectorPersoana, dim);
	printf("\nParcurgere vector:");
	for (int i = 0; i < dim; i++) {
		afisarePersoana(vectorPersoana[i]);
		vectorPersoana[i].nume;
	}

	free(vectorPersoana);

	return 0;
}