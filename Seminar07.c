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
//    Masina info;
//    Nod* next;
//};
//
//struct HashTable {
//    int dim;
//    Nod** vector;
//};
//typedef struct HashTable HashTable;
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
//void afisareListaMasini(Nod* lista) {
//    Nod* p = lista;
//    while (p) {
//        afisareMasina(p->info);
//        p = p->next;
//    }
//}
//
//void adaugaMasinaInLista(Nod** lista, Masina masinaNoua) {
//    Nod* nodNou = (Nod*)malloc(sizeof(Nod));
//    nodNou->info = masinaNoua;
//    nodNou->next = NULL;
//    if (*lista == NULL) {
//        *lista = nodNou;
//    }
//    else {
//        Nod* temp = *lista;
//        while (temp->next) {
//            temp = temp->next;
//        }
//        temp->next = nodNou;
//    }
//}
//
//HashTable initializareHashTable(int dimensiune) {
//    HashTable ht;
//    ht.dim = dimensiune;
//    ht.vector = malloc(dimensiune * sizeof(Nod*));
//    for (int i = 0; i < dimensiune; i++) {
//        ht.vector[i] = NULL;
//    }
//    return ht;
//}
//
//int calculeazaHash(int id, int dimensiune) {
//    return id * 7 % dimensiune;
//}
//
//void inserareMasinaInTabela(HashTable hash, Masina masina) {
//    int hashCode = calculeazaHash(masina.id, hash.dim);
//    adaugaMasinaInLista(&hash.vector[hashCode], masina);
//}
//
//HashTable citireMasiniDinFisier(const char* numeFisier) {
//    HashTable hash = initializareHashTable(5);
//    FILE* file = fopen(numeFisier, "r");
//    if (!file) {
//        printf("Eroare la deschiderea fisierului.\n");
//        return hash;
//    }
//    while (!feof(file)) {
//        Masina masinaCitita = citireMasinaDinFisier(file);
//        inserareMasinaInTabela(hash, masinaCitita);
//    }
//    fclose(file);
//    return hash;
//}
//
//void afisareTabelaDeMasini(HashTable ht) {
//    for (int i = 0; i < ht.dim; i++) {
//        if (ht.vector[i]) {
//            printf("Clusterul %d:\n", i + 1);
//            afisareListaMasini(ht.vector[i]);
//            printf("\n");
//        }
//    }
//}
//
//void dezalocareTabelaDeMasini(HashTable* ht) {
//    for (int i = 0; i < ht->dim; i++) {
//        Nod* p = ht->vector[i];
//        while (p) {
//            free(p->info.model);
//            free(p->info.numeSofer);
//            Nod* temp = p;
//            p = p->next;
//            free(temp);
//        }
//        ht->vector[i] = NULL;
//    }
//    free(ht->vector);
//    ht->vector = NULL;
//    ht->dim = 0;
//}
//
//float* calculeazaPreturiMediiPerClustere(HashTable ht, int* nrClustere) {
//    *nrClustere = 0;
//    for (int i = 0; i < ht.dim; i++) {
//        if (ht.vector[i] != NULL) (*nrClustere)++;
//    }
//    if (*nrClustere == 0) return NULL;
//
//    float* medii = malloc(sizeof(float) * (*nrClustere));
//    int k = 0;
//    for (int i = 0; i < ht.dim; i++) {
//        if (ht.vector[i] != NULL) {
//            float suma = 0;
//            int cnt = 0;
//            Nod* p = ht.vector[i];
//            while (p) {
//                suma += p->info.pret;
//                cnt++;
//                p = p->next;
//            }
//            medii[k++] = suma / cnt;
//        }
//    }
//    return medii;
//}
//
//Masina getMasinaDupaId(HashTable ht, int id) {
//    Masina m;
//    m.id = -1;
//    m.model = NULL;
//    m.numeSofer = NULL;
//
//    int hashCode = calculeazaHash(id, ht.dim);
//    Nod* cautare = ht.vector[hashCode];
//    while (cautare) {
//        if (cautare->info.id == id) {
//            m = cautare->info;
//            m.model = malloc(strlen(cautare->info.model) + 1);
//            strcpy(m.model, cautare->info.model);
//            m.numeSofer = malloc(strlen(cautare->info.numeSofer) + 1);
//            strcpy(m.numeSofer, cautare->info.numeSofer);
//            return m;
//        }
//        cautare = cautare->next;
//    }
//    return m;
//}
//
//int main() {
//    HashTable hash = citireMasiniDinFisier("masini.txt");
//    afisareTabelaDeMasini(hash);
//
//    Masina gasita = getMasinaDupaId(hash, 5);
//    if (gasita.id != -1) {
//        afisareMasina(gasita);
//        free(gasita.model);
//        free(gasita.numeSofer);
//    }
//    else {
//        printf("Nu s-a gasit masina cu id=5.\n");
//    }
//
//    int nrClustere = 0;
//    float* medii = calculeazaPreturiMediiPerClustere(hash, &nrClustere);
//    for (int i = 0; i < nrClustere; i++) {
//        printf("Cluster %d - pret mediu: %.2f\n", i, medii[i]);
//    }
//    free(medii);
//
//    dezalocareTabelaDeMasini(&hash);
//    return 0;
//}