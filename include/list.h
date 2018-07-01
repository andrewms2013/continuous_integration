//
// Created by andrewms on 26.06.18.
//
#ifndef COUNTINUOUS_INTEGRATION_LIST_H
#define COUNTINUOUS_INTEGRATION_LIST_H

#include <stdlib.h>

typedef struct __List List;

List * List_new();
void List_free(List * self);

void List_insert(List * self, void * value, size_t index);
void List_add(List * self, void * value);
void * List_at(List * self, size_t index);
void * List_removeAt(List * self, size_t index);
size_t List_count(List * self);

#endif //COUNTINUOUS_INTEGRATION_LIST_H
