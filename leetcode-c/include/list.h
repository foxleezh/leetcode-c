#pragma once
#include "env.h"

typedef struct List_Class {
	int size;
	void** list;
}List;


int list_tostring(List* list);

int list_add(List* list,void* item);

int list_free(List* list);