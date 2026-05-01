#include <hashmap.h>


typedef struct HashEntry {
    char *key;
    char *value;
    struct HashEntry *next;
} HashEntry;

struct HashTable {
    HashEntry **buckets;
    size_t size;
};

// bjb2 hash function
static size_t bjb2_hash(const char* key, size_t size) {
    size_t _hash = 5381;
    int c;
    while ((c = *key++))
        _hash = ((_hash << 5) + _hash) + c;
    return _hash % size;
}


struct HashTable *dict_create(size_t size) {
    struct HashTable *table = malloc(sizeof(struct HashTable));
    table->buckets = calloc(size, sizeof(struct HashTable*));
    table->size = size;
    return table;
}

void dict_set(struct HashTable *table, const char *key, const char *value) {
    size_t index = bjb2_hash(key, table->size);
    HashEntry *entry = table->buckets[index];

    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            // update existing element
            free(entry->value);
            entry->value = strdup(value);
            return;
        }
        entry = entry->next;
    }

    // create new element
    HashEntry *new_entry = malloc(sizeof(HashEntry));
    new_entry->key = strdup(key);
    new_entry->value = strdup(value);
    new_entry->next = table->buckets[index]; // point to old head
    table->buckets[index] = new_entry;       // new head
}

char *dict_get(struct HashTable *table, const char *key) {
    size_t index = bjb2_hash(key, table->size);
    HashEntry *entry = table->buckets[index];

    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0)
            return entry->value;
        entry = entry->next;
    }
    return NULL;
}

void dict_delete(struct HashTable *table, const char *key) {
    size_t index = bjb2_hash(key, table->size);
    HashEntry *entry = table->buckets[index];
    HashEntry *prev = NULL;

    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            if (prev == NULL) // this is the head
                table->buckets[index] = entry->next;
            else
                prev->next = entry->next;

            free(entry->key);
            free(entry->value);
            free(entry);
            return;
        }
        prev = entry;
        entry = entry->next;
    }
}

void dict_free(struct HashTable *table) {
    for (size_t i=0; i<table->size; i++) {
        HashEntry *entry = table->buckets[i];
        while (entry != NULL) {
            HashEntry *temp = entry->next;
            free(entry->key);
            free(entry->value);
            free(entry);
            entry = temp;
        }
    }
    free(table->buckets);
    free(table);
}

