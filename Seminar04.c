//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//struct StructuraMasina {
//	int id;
//	int nrUsi;
//	float pret;
//	char* model;
//	char* numeSofer;
//	unsigned char serie;
//};
//typedef struct StructuraMasina Masina;
//
//
//struct Nod {
//	Masina info;
//	struct Nod* next;
//};
//typedef struct Nod Nod;
//Masina citireMasinaDinFisier(FILE* file) {
//	char buffer[100];
//	char sep[3] = ",\n";
//	fgets(buffer, 100, file);
//	char* aux;
//	Masina m1;
//	aux = strtok(buffer, sep);
//	m1.id = atoi(aux);
//	m1.nrUsi = atoi(strtok(NULL, sep));
//	m1.pret = atof(strtok(NULL, sep));
//	aux = strtok(NULL, sep);
//	m1.model = malloc(strlen(aux) + 1);
//	strcpy_s(m1.model, strlen(aux) + 1, aux);
//
//	aux = strtok(NULL, sep);
//	m1.numeSofer = malloc(strlen(aux) + 1);
//	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);
//
//	m1.serie = *strtok(NULL, sep);
//	return m1;
//}
//
//void afisareMasina(Masina masina) {
//	printf("Id: %d\n", masina.id);
//	printf("Nr. usi : %d\n", masina.nrUsi);
//	printf("Pret: %.2f\n", masina.pret);
//	printf("Model: %s\n", masina.model);
//	printf("Nume sofer: %s\n", masina.numeSofer);
//	printf("Serie: %c\n\n", masina.serie);
//}
//
//void afisareListaMasini(Nod* first) {
//
//	while (first) {
//		afisareMasina(first->info);
//		first = first->next;
//	}
//}
//
//void adaugaMasinaInLista(Nod** first, Masina masinaNoua) {
//
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->info = masinaNoua;
//	nou->next = NULL;
//	if (!(*first)) {
//		*first = nou;
//	}
//	else {
//		Nod* pointer = *first;
//		while (pointer->next) {
//			pointer = pointer->next;
//		}
//		pointer->next = nou;
//	}
//}
//
//void adaugaLaInceputInLista(Nod** first, Masina masinaNoua) {
//
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->next = *first;
//	nou->info = masinaNoua;
//	*first = nou;
//
//
//}
//
//void* citireListaMasiniDinFisier(const char* numeFisier) {
//	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
//	//prin apelul repetat al functiei citireMasinaDinFisier()
//	//ATENTIE - la final inchidem fisierul/stream-ul
//	FILE* file = fopen(numeFisier, "r");
//	Nod* first = NULL;
//	while (!feof(file)) {
//		adaugaMasinaInLista(&first, citireMasinaDinFisier(file));
//	}
//	fclose(file);
//	return first;
//}
//
//void dezalocareListaMasini(Nod** first) {
//	while (*first) {
//		free((*first)->info.numeSofer);
//		free((*first)->info.model);
//		Nod* temp = *first;
//		temp = (*first)->next;
//		free(*first);
//		*first = temp;
//	}
//
//}
//
//float calculeazaPretMediu(Nod* first) {
//
//	int nrMasini = 0;
//	float pretTotal = 0.0;
//	if (first) {
//		while (first)
//		{
//			nrMasini++;
//			pretTotal += first->info.pret;
//			first = first->next;
//
//		}
//		return pretTotal / nrMasini;
//	}
//	return 0;
//
//}
//
//void stergeMasiniDinSeria(Nod** first, char serieCautata) {
//	//sterge toate masinile din lista care au seria primita ca parametru.
//	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
//
//
//	while ((*first) && (*first)->info.serie == serieCautata)
//	{
//		Nod* temp = (*first);
//		(*first) = (*first)->next;
//
//		free(temp);
//	}
//
//	if (*first == NULL) {
//		return;
//	}
//
//	Nod* aux = (*first);
//	Nod* temp = (*first)->next;
//
//	while (temp)
//	{
//		if (temp->info.serie == serieCautata)
//		{
//			aux->next = temp->next;
//
//			free(temp);
//
//			temp = aux->next;
//		}
//		else
//		{
//			aux = temp;
//			temp = temp->next;
//		}
//	}
//
//}
//
//float calculeazaPretulMasinilorUnuiSofer(Nod* first, const char* numeSofer) {
//	//calculeaza pretul tuturor masinilor unui sofer.
//
//	float pretTotalMasini = 0;
//
//	while ((first)) {
//
//		if (strcmp(numeSofer, first->info.numeSofer) == 0)
//		{
//			pretTotalMasini += first->info.pret;
//		}
//		first = first->next;
//
//	}
//	return pretTotalMasini;
//}
//
//int main() {
//	Nod* first = citireListaMasiniDinFisier("masini.txt");
//	Masina masina = { 11, 2, 50000, "Audi", "Matei",'A' };
//	adaugaLaInceputInLista(&first, masina);
//	printf("%f", calculeazaPretMediu(first));
//	stergeMasiniDinSeria(&first, 'A');
//	afisareListaMasini(first);
//	printf("%f", calculeazaPretulMasinilorUnuiSofer(first, "Gigel"));
//
//	return 0;
//}