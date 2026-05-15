//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//struct StructuraMasina {
//    int id;
//    int nrUsi;
//    float pret;
//    char* model;
//    char* numeSofer;
//    unsigned char serie;
//};
//typedef struct StructuraMasina Masina;
//
//typedef struct Nod Nod;
//struct Nod {
//    Masina masina;
//    Nod* next;
//};
//
//typedef struct NodDublu NodDublu;
//struct NodDublu {
//    Masina info;
//    NodDublu* next;
//    NodDublu* prev;
//};
//
//typedef struct ListaDubla ListaDubla;
//struct ListaDubla {
//    NodDublu* first;
//    NodDublu* last;
//};
//
//Masina citireMasinaDinFisier(FILE* file) {
//    char buffer[100];
//    char sep[3] = ",\n";
//    fgets(buffer, 100, file);
//    char* aux;
//    Masina m1;
//    aux = strtok(buffer, sep);
//    m1.id = atoi(aux);
//    m1.nrUsi = atoi(strtok(NULL, sep));
//    m1.pret = atof(strtok(NULL, sep));
//    aux = strtok(NULL, sep);
//    m1.model = malloc(strlen(aux) + 1);
//    strcpy_s(m1.model, strlen(aux) + 1, aux);
//    aux = strtok(NULL, sep);
//    m1.numeSofer = malloc(strlen(aux) + 1);
//    strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);
//    m1.serie = *strtok(NULL, sep);
//    return m1;
//}
//
//void afisareMasina(Masina masina) {
//    printf("Id: %d\n", masina.id);
//    printf("Nr. usi : %d\n", masina.nrUsi);
//    printf("Pret: %.2f\n", masina.pret);
//    printf("Model: %s\n", masina.model);
//    printf("Nume sofer: %s\n", masina.numeSofer);
//    printf("Serie: %c\n\n", masina.serie);
//}
//
//
//void pushStack(Nod** stiva, Masina masina) {
//    Nod* temp = (Nod*)malloc(sizeof(Nod));
//    temp->masina = masina;
//    temp->next = *stiva;
//    *stiva = temp;
//}
//
//Masina popStack(Nod** stiva) {
//    if (*stiva == NULL) {
//        Masina rezultat;
//        rezultat.id = -1;
//        return rezultat;
//    }
//    Masina rezultat = (*stiva)->masina;
//    Nod* temp = (*stiva)->next;
//    free(*stiva);
//    *stiva = temp;
//    return rezultat;
//}
//
//char isEmptyStack(Nod* stiva) {
//    return stiva == NULL;
//}
//
//Nod* citireStackMasiniDinFisier(const char* numeFisier) {
//    FILE* file = fopen(numeFisier, "r");
//    if (!file) return NULL;
//    Nod* stiva = NULL;
//    while (!feof(file)) {
//        Masina masina = citireMasinaDinFisier(file);
//        pushStack(&stiva, masina);
//    }
//    fclose(file);
//    return stiva;
//}
//
//void dezalocareStivaDeMasini(Nod** stiva) {
//    while (*stiva) {
//        free((*stiva)->masina.model);
//        free((*stiva)->masina.numeSofer);
//        Nod* temp = *stiva;
//        *stiva = (*stiva)->next;
//        free(temp);
//    }
//}
//
//int sizeStack(Nod* stiva) {
//    int cnt = 0;
//    Nod* p = stiva;
//    while (p) {
//        cnt++;
//        p = p->next;
//    }
//    return cnt;
//}
//
//
//void enqueue(ListaDubla* coada, Masina masina) {
//    NodDublu* nou = (NodDublu*)malloc(sizeof(NodDublu));
//    nou->info = masina;
//    nou->next = NULL;
//    nou->prev = coada->last;
//    if (coada->last)
//        coada->last->next = nou;
//    else
//        coada->first = nou;
//    coada->last = nou;
//}
//
//Masina dequeue(ListaDubla* coada) {
//    Masina rezultat;
//    rezultat.id = -1;
//    if (coada->first) {
//        rezultat = coada->first->info;
//        NodDublu* temp = coada->first;
//        coada->first = temp->next;
//        if (coada->first)
//            coada->first->prev = NULL;
//        else
//            coada->last = NULL;
//        free(temp);
//    }
//    return rezultat;
//}
//
//ListaDubla citireCoadaDeMasiniDinFisier(const char* numeFisier) {
//    ListaDubla coada;
//    coada.first = coada.last = NULL;
//    FILE* f = fopen(numeFisier, "r");
//    if (f) {
//        while (!feof(f)) {
//            enqueue(&coada, citireMasinaDinFisier(f));
//        }
//        fclose(f);
//    }
//    return coada;
//}
//
//void dezalocareCoadaDeMasini(ListaDubla* coada) {
//    NodDublu* p = coada->first;
//    while (p) {
//        free(p->info.model);
//        free(p->info.numeSofer);
//        NodDublu* temp = p;
//        p = p->next;
//        free(temp);
//    }
//    coada->first = coada->last = NULL;
//}
//
//Masina getMasinaByID(Nod** stiva, int id) {
//    Masina rezultat;
//    rezultat.id = -1;
//    Nod* stivaNoua = NULL;
//    while (*stiva) {
//        Masina m = popStack(stiva);
//        if (m.id == id) {
//            rezultat = m;
//            
//            pushStack(&stivaNoua, m);
//            break;
//        }
//        pushStack(&stivaNoua, m);
//    }
//    while (stivaNoua) {
//        pushStack(stiva, popStack(&stivaNoua));
//    }
//    return rezultat;
//}
//
//float calculeazaPretTotalStiva(Nod* stiva) {
//    float total = 0;
//    Nod* p = stiva;
//    while (p) {
//        total += p->masina.pret;
//        p = p->next;
//    }
//    return total;
//}
//
//float calculeazaPretTotalCoada(ListaDubla coada) {
//    float total = 0;
//    NodDublu* p = coada.first;
//    while (p) {
//        total += p->info.pret;
//        p = p->next;
//    }
//    return total;
//}
//
//int main() {
//    Nod* stiva = citireStackMasiniDinFisier("masini.txt");
//
//    printf("Pret total stiva: %.2f\n", calculeazaPretTotalStiva(stiva));
//    printf("Size stiva: %d\n\n", sizeStack(stiva));
//
//    afisareMasina(popStack(&stiva));
//    afisareMasina(popStack(&stiva));
//
//    Masina gasita = getMasinaByID(&stiva, 4);
//    if (gasita.id != -1) afisareMasina(gasita);
//
//    dezalocareStivaDeMasini(&stiva);
//
//    printf("COADA\n");
//    ListaDubla coada = citireCoadaDeMasiniDinFisier("masini.txt");
//    afisareMasina(dequeue(&coada));
//    afisareMasina(dequeue(&coada));
//    dezalocareCoadaDeMasini(&coada);
//
//    return 0;
//}