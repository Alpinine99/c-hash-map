#pragma once

#include <stdint.h>
#include <stdlib.h>

typedef struct HashTable HashTable;

// create a new hash table
HashTable *dict_create(size_t size);

// set or update a table value
void dict_set(HashTable *table, const char *key, const char *value);

// get a table value
char* dict_get(HashTable *table, const char *key);

// delete table value
void dict_delete(HashTable *table, const char *key);

// free dict
void dict_free(HashTable *table);

