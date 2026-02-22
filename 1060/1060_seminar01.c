#include<stdio.h>
#include<malloc.h>

void interschimbare(int* a, int* b) {
	//dereferentiere
	int aux = *a;
	*a = *b;
	*b = aux;
}

void main() {
	int varsta = 20;
	float salariuMediu = 6000.5;
	char caracter = 'A';

	printf("Varsta: %d, salariuMediu: %.2f, caracter: %c, caracter decimal: %d.", varsta, salariuMediu, caracter, caracter);

	char nume[4];
	nume[0] = 65;
	nume[1] = 110;
	nume[2] = 97;
	nume[3] = '\0';

	printf("\nNume: %s.", nume);

	char* numeDinamic = (char*)malloc(sizeof(char) * (strlen("Ana") + 1));
	strcpy(numeDinamic, "Ana");

	printf("\nNume dinamic: %s.", numeDinamic);

	int a = 7, b = 8;
	interschimbare(&a, &b);
	printf("\na = %d, b = %d.", a, b);

	//dezalocare
	free(numeDinamic);
}