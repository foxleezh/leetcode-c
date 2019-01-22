#include "include/list.h"
#include "stdlib.h"

int list_tostring(List *list) {
	for (size_t i = 0; i < list->size; i++)
	{
		ALog("[%d]=%s",i,list->list[i]);
	}
	return 0;
}

int list_add(List* list, void* item) {
	if (list->size == 0) {
		list->list = malloc(sizeof(void*));
	}else{
		list->list = realloc(list->list, sizeof(void*)*(list->size + 1));
	}
	list->list[list->size] = item;
	(list->size)++;
	return 0;
}

int list_free(List* list) {
	for (size_t i = 0; i < list->size; i++)
	{
		free(list->list[i]);
	}
	free(list->list);
	free(list);
	return 0;
}