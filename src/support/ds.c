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

bool queueInit(Queue *queue_list, int initial_capacity, int value_size)
{
    if (initial_capacity <= 0 || value_size <= 0) {
        printf("INIT: Invalid capacity or size\n");
        return false;
    }

    queue_list->data = malloc(initial_capacity * value_size);
    if (!queue_list->data) {
        printf("INIT: Allocating Failed\n");
        return false;
    }

    queue_list->value_size = value_size;
    queue_list->capacity = initial_capacity;
    queue_list->count = 0;
    queue_list->front = 0;
    queue_list->rear = 0;
    return true;
}

bool queueAppend(Queue *queue_list, void *value)
{
    if (!queue_list && !queue_list->data) {
        return false;
    }

    if (queue_list->count >= queue_list->capacity) {
        int new_capacity = queue_list->capacity * 2;
        void *new_data = malloc(new_capacity * queue_list->value_size);

        if (!new_data) {
            printf("APPEND: Reallocating Failed\n");
            return false;
        }

        char *src = (char *)queue_list->data;
        char *dest = (char *)new_data;

        for (int i = 0; i < queue_list->count; i++) {
            int src_index = (queue_list->front + i) % queue_list->capacity;
            memcpy(dest + (i * queue_list->value_size), src + (src_index * queue_list->value_size), queue_list->value_size);
        }

        free(queue_list->data);
        queue_list->data = new_data;
        queue_list->capacity = new_capacity;
        queue_list->front = 0;
        queue_list->rear = queue_list->count;

        queue_list->capacity = new_capacity;
    }

    char *data_ptr = (char *)queue_list->data;
    memcpy(data_ptr + (queue_list->rear * queue_list->value_size), value, queue_list->value_size);

    queue_list->rear = (queue_list->rear + 1) % queue_list->capacity;
    queue_list->count++;
    return true;
}

bool queueIsEmpty(Queue *queue_list) { return (queue_list->data == NULL) || (queue_list->count == 0); }

bool queuePop(Queue *queue_list, void *dest)
{
    if (!queue_list || !dest || queueIsEmpty(queue_list)) {
        return false;
    }

    char *data_ptr = (char *)queue_list->data;
    memcpy(dest, data_ptr + (queue_list->front * queue_list->value_size), queue_list->value_size);

    queue_list->front = (queue_list->front + 1) % queue_list->capacity;
    queue_list->count--;

    return true;
}

bool queueFree(Queue *queue_list)
{
    if (!queue_list && !queue_list->data) {
        return false;
    }
    free(queue_list->data);
    queue_list->data = NULL;
    queue_list->value_size = 0;
    queue_list->capacity = 0;
    queue_list->count = 0;
    queue_list->front = 0;
    queue_list->rear = 0;
    return true;
}

// Example usage
/*
#include <stdio.h>

int main() {
    Queue q;

    // Initialize queue for integers
    if (!queueInit(&q, 4, sizeof(int))) {
        printf("Failed to initialize queue\n");
        return 1;
    }

    // Add some values
    for (int i = 1; i <= 6; i++) {  // This will trigger expansion
        if (queueAppend(&q, &i)) {
            printf("Added: %d\n", i);
        }
    }

    // Pop values
    int value;
    while (!queueIsEmpty(&q)) {
        if (queuePop(&q, &value)) {
            printf("Popped: %d\n", value);
        }
    }

    queueFree(&q);
    return 0;
}
*/
