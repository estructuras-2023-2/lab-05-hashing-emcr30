#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10

typedef struct HashTable {
    int n;
    int* bucket[SIZE];
    int (*h)(int, int);
} HashTable;

int mi_Mod(int x, int n) {
    return x % n;
}

void insert(HashTable* ht, int x) {
    int index = ht->h(x, ht->n);
    ht->bucket[index] = (int*)realloc(ht->bucket[index], (ht->bucket[index][0] + 2) * sizeof(int));
    ht->bucket[index][0] += 1;
    ht->bucket[index][ht->bucket[index][0]] = x;
}

int delete(HashTable* ht, int x) {
    int index = ht->h(x, ht->n);
    int* poss = ht->bucket[index];
    for (int i = 1; i <= poss[0]; i++) {
        if (poss[i] == x) {
            int deleted = poss[i];
            for (int j = i; j < poss[0]; j++) {
                poss[j] = poss[j + 1];
            }
            poss[0] -= 1;
            poss = (int*)realloc(poss, (poss[0] + 1) * sizeof(int));
            ht->bucket[index] = poss;
            return deleted;
        }
    }
    return -1;
}

int find(HashTable* ht, int x) {
    int index = ht->h(x, ht->n);
    int* poss = ht->bucket[index];
    for (int i = 1; i <= poss[0]; i++) {
        if (poss[i] == x) {
            return poss[i];
        }
    }
    return -1;
}

int randomFn(int x, int n) {
    return rand() % n;
}

int* RandomHashFun(int M, int n) {
    int* fnTable = (int*)malloc(M * sizeof(int));
    for (int x = 0; x < M; x++) {
        fnTable[x] = rand() % n;
    }
    return fnTable;
}

int main() {
    srand(time(NULL));

    HashTable ht1;
    ht1.n = SIZE;
    ht1.h = mi_Mod;
    for (int i = 0; i < SIZE; i++) {
        ht1.bucket[i] = (int*)malloc(sizeof(int));
        ht1.bucket[i][0] = 0;
    }

    int x = 1234567;
    long long int y = 76554334234;

    insert(&ht1, x);

    int result = find(&ht1, x);
    if (result != -1) {
        printf(" %d se encuentra en la tabla hash.\n", result);
    } else {
        printf(" %d no se encuentra en la tabla hash.\n", x);
    }

    int z = 42;
    insert(&ht1, z);

    result = find(&ht1, z);
    if (result != -1) {
        printf("%d se encuentra en la tabla hash.\n", result);
    } else {
        printf("%d no se encuentra en la tabla hash.\n", z);
    }

    result = delete(&ht1, x);
    if (result != -1) {
        printf("Se ha eliminado %d de la tabla hash.\n", result);
    } else {
        printf("No se encontró %d para eliminar en la tabla hash.\n", x);
    }

    int result2 = delete(&ht1, 999);
    if (result2 != -1) {
        printf("Se ha eliminado %d de la tabla hash.\n", result2);
    } else {
        printf("No se encontró el elemento para eliminar en la tabla hash.\n");
    }

    for (int i = 0; i < SIZE; i++) {
        free(ht1.bucket[i]);
    }

    return 0;
}

