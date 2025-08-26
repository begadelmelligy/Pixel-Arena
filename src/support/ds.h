#ifndef DS_H
#define DS_H

#include "stdbool.h"

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

typedef struct Queue {
    void *data;
    int value_size;
    int count;
    int capacity;
    int front;
    int rear;
} Queue;

bool queueInit(Queue *queue_list, int initial_capacity, int value_size);
bool queueAppend(Queue *queue_list, void *value);
bool queueIsEmpty(Queue *queue_list);
bool queuePop(Queue *queue_list, void *dest);
bool queueFree(Queue *queue_list);

#endif
