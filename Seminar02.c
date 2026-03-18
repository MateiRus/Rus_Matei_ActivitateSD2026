//#include<stdio.h>
//#include<malloc.h>
//
//struct Telefon {
//	int id;
//	int RAM;
//	char* producator;
//	float pret;
//	char serie;
//};
//struct Telefon initializare(int id, int RAM, char* producator, float pret, char serie) {
//	struct Telefon t;
//	t.id = id;
//	t.RAM = RAM;
//	t.producator = (char*)malloc((strlen(producator) + 1) * sizeof(char));
//	strcpy(t.producator, producator);
//	t.pret = pret;
//	t.serie = serie;
//
//	return t;
//}
//
//struct Telefon copiazaTelefon(struct Telefon t) {
//
//	struct Telefon telefon = initializare(t.id, t.RAM, t.producator, t.pret, t.serie);
//	return telefon;
//
//}
//
//void afisare(struct Telefon t) {
//
//	printf("ID: %d\nRAM: %d\nProducator: %s\nPret: %f\nSerie: %x\n\n", t.id, t.RAM, t.producator, t.pret, t.serie);
//
//}
//
//void afisareVector(struct Telefon* vector, int nrElemente) {
//	for (int i = 0;i < nrElemente;i++)
//		afisare(vector[i]);
//}
//
//struct Telefon* copiazaPrimeleNElemente(struct Telefon* vector, int nrElemente, int nrElementeCopiate) {
//
//	if (nrElementeCopiate > nrElemente)
//		nrElementeCopiate = nrElemente;
//
//	struct Telefon* vectorNou = (struct Telefon*)malloc(sizeof(struct Telefon) * nrElementeCopiate);
//
//	for (int i = 0;i < nrElemente;i++)
//	{
//		vectorNou[i] = copiazaTelefon(vector[i]);
//	}
//	return vectorNou;
//}
//
//void dezalocare(struct Telefon** vector, int* nrElemente) {
//
//	for (int i = 0; i < *nrElemente;i++) {
//
//		free((*vector)[i].producator);
//		(*vector)[i].producator = NULL;
//	}
//	*vector = NULL;
//	*nrElemente = 0;
//
//}
//
//void copiazaTelefoaneScumpe(struct Telefon* vector, char nrElemente, float pret_min, struct Telefon** vectorNou, int* dimensiune) {
//
//	*dimensiune = 0;
//	for (int i = 0; i < nrElemente;i++)
//	{
//		if (vector[i].pret >= pret_min)
//			*dimensiune++;
//	}
//
//	*vectorNou = malloc(*dimensiune * sizeof(struct Telefon));
//
//
//	for (int i = 0, k = 0; i < nrElemente;i++) {
//
//		if (vector[i].pret >= pret_min)
//		{
//
//			(*vectorNou)[k] = copiazaTelefon(vector[i]);
//			k++;
//		}
//
//
//	}
//
//
//
//}
//
//struct Telefon getPrimulElementConditionat(struct Telefon* vector, int nrElemente, const char* conditie) {
//	//trebuie cautat elementul care indeplineste o conditie
//	//dupa atributul de tip char*. Acesta este returnat.
//	struct Telefon s;
//	s.id = 1;
//
//	return s;
//}
//
//
//
//int main() {
//
//	struct Telefon t;
//	t = initializare(3, 4, "Samsung", 1500.00, 'A');
//	int nrTelefoane = 3;
//	int nrElementeCopiate = 2;
//	struct Telefon* telefoane = (struct Telefon*)malloc(sizeof(struct Telefon) * nrTelefoane);
//	telefoane[0] = initializare(1, 2, "Xiaomi", 925.00, 'X');
//	telefoane[1] = initializare(2, 6, "Apple", 2200.50, 'B');
//	telefoane[2] = t;
//	afisareVector(telefoane, nrTelefoane);
//
//	struct Telefon* telefoaneCopiate = copiazaPrimeleNElemente(telefoane, nrTelefoane, nrElementeCopiate);
//
//	afisareVector(telefoaneCopiate, nrElementeCopiate);
//
//	dezalocare(&telefoaneCopiate, &nrElementeCopiate);
//
//	printf("Telefoane Scumpe.\n");
//
//	afisareVector(telefoane, nrTelefoane);
//
//	struct Telefon* vectorNou;
//	int dimensiune;
//	float pret_minim = 1000.00;
//	copiazaTelefoaneScumpe(telefoane, nrTelefoane, pret_minim, &vectorNou, &dimensiune);
//
//	afisareVector(vectorNou, dimensiune);
//
//	return 0;
//}