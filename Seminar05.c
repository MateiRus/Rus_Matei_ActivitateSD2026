#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;
typedef struct listaDubla listaDubla;
typedef struct Nod Nod;

struct Nod {
	Masina info;
	Nod* next;
	Nod* prev;
};

struct listaDubla {
	Nod* prim;
	Nod* ultim;
};

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

void afisareInversaListaMasini(listaDubla lista) {
	//afiseaza toate elemente de tip masina din lista dublu inlantuita
	//prin apelarea functiei afisareMasina()
	Nod* p = lista.prim;
	while (p)
	{
		afisareMasina(p->info);
		p = p->next;
	}
}

void afisareListaMasini(listaDubla lista) {
	//afiseaza toate elemente de tip masina din lista dublu inlantuita
	//prin apelarea functiei afisareMasina()
	Nod* p = lista.ultim;
	while (p)
	{
		afisareMasina(p->info);
		p = p->prev;
	}
}

void adaugaMasinaInLista(listaDubla* ld, Masina masinaNoua) {

	Nod* nou = malloc(sizeof(Nod));
	nou->info = masinaNoua;
	nou->next = ld->prim;
	nou->prev = NULL;
	if (ld->prim)
	{
		ld->prim->prev = nou;
	}
	else
	{
		ld->ultim = nou;
	}
	ld->prim = nou;

}

void adaugaLaInceputInLista(/*lista dubla de masini*/ Masina masinaNoua) {
	//adauga la inceputul listei dublu inlantuite o noua masina pe care o primim ca parametru
}

listaDubla citireLDMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul

	FILE* f = fopen(numeFisier, "r");
	if (f) {
		listaDubla ld;
		ld.prim = ld.ultim = NULL;

		while (!feof(f))
		{
			adaugaMasinaInLista(&ld, citireMasinaDinFisier(f));
		}
		fclose(f);
		return ld;
	}

}

void dezalocareLDMasini(listaDubla* ld) {
	//sunt dezalocate toate masinile si lista dublu inlantuita de elemente

	while (ld->prim && ld->prim->next)
	{
		free(ld->prim->info.numeSofer);
		ld->prim = ld->prim->next;
		free(ld->prim->info.model);
		free(ld->prim->prev);
	}
	if (ld->prim)
	{
		free(ld->prim->info.numeSofer);
		free(ld->prim->info.model);
		free(ld->prim);
	}
	ld->prim = ld->ultim = NULL;
}

float calculeazaPretMediu(listaDubla ld) {
	//calculeaza pretul mediu al masinilor din lista.

	float pretMediu = 0;
	int nrMasini = 0;

	if (ld.prim == NULL)
		return 0;

	while (ld.prim)
	{
		pretMediu += ld.prim->info.pret;
		ld.prim = ld.prim->next;
		nrMasini++;
	}
	return pretMediu / nrMasini;
}

void stergeMasinaDupaID(listaDubla* ld, int id) {
	//sterge masina cu id-ul primit.
	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
	if (ld->prim && ld->prim->info.id == id) {
		free(ld->prim->info.model);
		free(ld->prim->info.numeSofer);
		ld->prim = ld->prim->next;
		if (ld->prim)
		{
			free(ld->prim->prev);
		}
		else
		{
			free(ld->ultim);
			ld->ultim = NULL;
		}
		return;
	}
	else {
		Nod* p = ld->prim;
		while (p && p->info.id != id) {
			p = p->next;
		}
		if (p)
		{
			if (p->prev) {
				p->prev->next = p->next;
			}
			if (p->next)
			{
				p->next->prev = p->prev;
			}
			else {
				p->prev->next = NULL;
				ld->ultim = p->prev;
			}
			free(p->info.model);
			free(p->info.numeSofer);
			free(p);
		}
	}

}

char* getNumeSoferMasinaScumpa(listaDubla ld) {
	//cauta masina cea mai scumpa si 
	//returneaza numele soferului acestei maasini.

	float pretMasina = -1;
	char* sofer = NULL;

	while (ld.prim)
	{
		if (ld.prim->info.pret > pretMasina) {

			pretMasina = ld.prim->info.pret;
			if (sofer != NULL) {
				free(sofer);
			}
			sofer = malloc(sizeof(char) * strlen(ld.prim->info.numeSofer) + 1);
			strcpy(sofer, ld.prim->info.numeSofer);

		}
		ld.prim = ld.prim->next;
	}
	return sofer;
}

int main() {

	listaDubla lista = citireLDMasiniDinFisier("masini.txt");
	afisareListaMasini(lista);
	printf("%f\n", calculeazaPretMediu(lista));
	printf("%s\n", getNumeSoferMasinaScumpa(lista));
	stergeMasinaDupaID(&lista, 1);
	printf("\nMasini dupa stergere:\n");
	afisareListaMasini(lista);
	return 0;
}