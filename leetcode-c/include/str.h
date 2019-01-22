#pragma once
#include "list.h"
#include "string.h"

typedef struct Byte_Class {
	int length;
	unsigned char* content;
}Bytes;

void byte_free(Bytes *b);

int str_split(List *list, const char* str, const char* split);

char* str_replace(const char* strBase, char* strSrc, char* strDes);

