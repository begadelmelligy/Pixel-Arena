#ifndef DS_H
#define DS_H

typedef struct DictEntry {
    int key;
    void *value;
} DictEntry;

typedef struct Dict {
    DictEntry *entries;
    int value_size;
    int count;
    int capacity;
} Dict;

void dictInit(Dict *dict, int capacity, int value_size);
void dictAdd(Dict *dict, const int key, void *value);
void dictUpdateValue(Dict *dict, const int key, void *value);
void *dictGet(Dict *dict, const int key);
void dictRemove(Dict *dict, const int key);
void dictFree(Dict *dict);

#endif
