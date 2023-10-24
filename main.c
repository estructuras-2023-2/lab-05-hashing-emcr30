#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10

struct Node {
    int value;
    struct Node* next;
};

struct HashTable {
    int n;
    struct Node* bucket[SIZE];
};

struct HashTable* initHashTable(int n) {
    struct HashTable* ht = (struct HashTable*)malloc(sizeof(struct HashTable));
    ht->n = n;
    for (int i = 0; i < SIZE; i++) {
        ht->bucket[i] = NULL;
    }
    return ht;
}

int hashFunction(int x, int n) {
    return x % n;
}

void insert(struct HashTable* ht, int x) {
    int index = hashFunction(x, ht->n);
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->value = x;
    newNode->next = ht->bucket[index];
    ht->bucket[index] = newNode;
}

int delete(struct HashTable* ht, int x) {
    int index = hashFunction(x, ht->n);
    struct Node* current = ht->bucket[index];
    struct Node* prev = NULL;

    while (current != NULL) {
        if (current->value == x) {
            if (prev != NULL) {
                prev->next = current->next;
            } else {
                ht->bucket[index] = current->next;
            }
            int deleted = current->value;
            free(current);
            return deleted;
        }
        prev = current;
        current = current->next;
    }
    return -1;
}

int find(struct HashTable* ht, int x) {
    int index = hashFunction(x, ht->n);
    struct Node* current = ht->bucket[index];

    while (current != NULL) {
        if (current->value == x) {
            return current->value;
        }
        current = current->next;
    }
    return -1;
}

void printTable(struct HashTable* ht) {
    printf("Elementos en la tabla hash: ");
    for (int i = 0; i < SIZE; i++) {
        struct Node* current = ht->bucket[i];
        while (current != NULL) {
            printf("%d ", current->value);
            current = current->next;
        }
    }
    printf("\n");
}

int main() {
    srand(time(NULL));

    struct HashTable* ht = initHashTable(SIZE);

    printf("Ingrese elementos para insertar en la tabla hash (ingrese -1 para finalizar):\n");
    int elemento;
    while (1) {
        printf("Elemento: ");
        scanf("%d", &elemento);
        if (elemento == -1) {
            break;
        }
        insert(ht, elemento);
    }

    // Realizar búsquedas y eliminaciones según sea necesario.
    printf("Ingrese un elemento para buscar: ");
    scanf("%d", &elemento);
    int encontrado = find(ht, elemento);
    if (encontrado != -1) {
        printf("Elemento encontrado en la tabla hash: %d\n", encontrado);
    } else {
        printf("Elemento no encontrado en la tabla hash.\n");
    }

    printf("Ingrese un elemento para eliminar: ");
    scanf("%d", &elemento);
    int eliminado = delete(ht, elemento);
    if (eliminado != -1) {
        printf("Elemento eliminado de la tabla hash: %d\n", eliminado);
    } else {
        printf("Elemento no encontrado en la tabla hash para eliminar.\n");
    }

    // Mostrar los elementos restantes en la tabla hash.
    printTable(ht);

    return 0;
}

