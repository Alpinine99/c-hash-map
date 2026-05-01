#include <stdio.h>
#include <hashmap.h>


int main() {
    HashTable *dict = dict_create(100);
    dict_set(dict, "name", "andreas");
    dict_set(dict, "age", "23");
    dict_set(dict, "gender", "male");

    char* name = dict_get(dict, "name");
    char* age = dict_get(dict, "age");
    char* gender = dict_get(dict, "gender");
    printf("name: %s, age: %s, gender: %s\n", name, age, gender);

    dict_set(dict, "age", "19"); // affects the original one
    dict_delete(dict, "gender"); // doesn't affect original
    gender = dict_get(dict, "gender");
    printf("name: %s, age: %s, gender: %s\n", name, age, gender);
    dict_free(dict);
    return 0;
}

