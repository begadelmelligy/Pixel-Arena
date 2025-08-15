#include "ds.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void dictInit(Dict *dict, int capacity, int value_size)
{
    dict->entries = malloc(sizeof(DictEntry) * capacity);
    dict->value_size = value_size;
    dict->capacity = capacity;
    dict->count = 0;
}

void dictAdd(Dict *dict, const int key, void *value)
{
    if (dict == NULL) {
        printf("Dict doesn't Exist\n");
        return;
    }

    if (dict->count >= dict->capacity) {
        printf("Dict is Full\n");
        return;
    }

    for (int i = 0; i < dict->count; i++) {
        if (dict->entries[i].key == key) {
            printf("Key already Exists\n");
            return;
        }
    }

    void *copy = malloc(dict->value_size);
    memcpy(copy, value, dict->value_size);

    dict->entries[dict->count].key = key;
    dict->entries[dict->count].value = copy;
    dict->count++;
}

void dictUpdateValue(Dict *dict, const int key, void *value)
{
    if (dict == NULL) {
        printf("Dict doesn't Exist\n");
        return;
    }

    for (int i = 0; i < dict->count; i++) {
        if (dict->entries[i].key == key) {
            memcpy(dict->entries[i].value, value, dict->value_size);
            return;
        }
    }
}

void *dictGet(Dict *dict, const int key)
{
    if (dict == NULL) {
        printf("Dict doesn't Exist\n");
        return NULL;
    }
    for (int i = 0; i < dict->count; i++) {
        if (dict->entries[i].key == key) {
            return dict->entries[i].value;
        }
    }

    printf("Key doesn't Exist\n");
    return NULL;
}

void dictRemove(Dict *dict, const int key)
{
    if (dict == NULL) {
        printf("Dict doesn't Exist\n");
        return;
    }
    for (int i = 0; i < dict->count; i++) {
        if (dict->entries[i].key == key) {
            free(dict->entries[i].value);
            // Shift remaining entries down
            for (int j = i; j < dict->count - 1; j++) {
                dict->entries[j] = dict->entries[j + 1];
            }
            dict->count--;
            return;
        }
    }
    printf("Key doesn't Exist\n");
}

void dictFree(Dict *dict)
{
    if (dict == NULL) {
        return;
    }

    for (int i = 0; i < dict->count; i++) {
        free(dict->entries[i].value);
        dict->entries[i].value = NULL;
    }
    free(dict->entries);
    dict->entries = NULL;

    dict->value_size = 0;
    dict->capacity = 0;
    dict->count = 0;
}
