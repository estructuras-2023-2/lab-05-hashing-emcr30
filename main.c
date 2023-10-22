#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TABLE_SIZE 10

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct HashTable {
    Node* table[TABLE_SIZE];
    int (*hash_function)(int);
} HashTable;

int mi_Mod(int x) {
    return x % TABLE_SIZE;
}

int randomFn(int x) {
    return rand() % TABLE_SIZE;
}

void initHashTable(HashTable* ht, int (*hash_function)(int)) {
    ht->hash_function = hash_function;
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->table[i] = NULL;
    }
}

void insert(HashTable* ht, int x) {
    int index = ht->hash_function(x);
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = x;
    new_node->next = ht->table[index];
    ht->table[index] = new_node;
}

Node* find(HashTable* ht, int x) {
    int index = ht->hash_function(x);
    Node* current = ht->table[index];
    while (current != NULL) {
        if (current->data == x) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

int main() {
    srand(time(NULL));

    HashTable ht1, ht2;
    initHashTable(&ht1, mi_Mod);
    initHashTable(&ht2, randomFn);

    insert(&ht1, 1234567);
    Node* found = find(&ht1, 1234567);
    if (found) {
        printf("Encontrado: %d\n", found->data);
    }

    insert(&ht2, 1234567);
    insert(&ht2, 76554334234);

    printf("Resultados random de Hash:\n");
    printf("%d\n", randomFn(52));
    printf("%d\n", randomFn(3235235));

    return 0;
}

