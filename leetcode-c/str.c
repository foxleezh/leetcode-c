#include <malloc.h>
#include "include/str.h"

void byte_free(Bytes *b) {
	free(b->content);
	free(b);
}


int str_split(List *dst, const char* str, const char* spl_s) {
	size_t size = strlen(str) + 1;
	size_t spli_size = strlen(spl_s) + 1;
	char* alloc_origin = (char*)malloc(size);
	strncpy(alloc_origin, str, size);
	char* alloc_tmp = (char*)malloc(spli_size);
	alloc_tmp[spli_size - 1] = '\0';
	int start = 0;
	int tmp_len = 0;
	int count = 0;
	for (size_t i = 0; i < size;)
	{
		strncpy(alloc_tmp, alloc_origin + i, spli_size - 1);
		if (!strcmp(alloc_tmp, spl_s) || i == (size - 1)) {
			tmp_len = i - start;
			if (tmp_len == 0) {
				i += (spli_size - 1);
				start = i;
				continue;
			}
			char* sp = malloc(tmp_len + 1);
			sp[tmp_len] = '\0';
			strncpy(sp, alloc_origin + start, tmp_len);
			list_add(dst, sp);
			count++;
			i += (spli_size - 1);
			start = i;
		}
		else {
			i++;
		}
	}
	free(alloc_origin);
	free(alloc_tmp);
	return 0;
}


char* str_replace(const char* strBase, char* strSrc, char* strDes)
{
	size_t size = strlen(strBase) + 1;
	size_t spli_size = strlen(strSrc) + 1;
	size_t desLen = strlen(strDes);
	char* alloc_origin = (char*)malloc(size);
	strncpy(alloc_origin, strBase, size);
	char* alloc_tmp = (char*)malloc(spli_size);
	alloc_tmp[spli_size - 1] = '\0';
	int start = 0;
	int tmp_len = 0;
	int count = 0;
	int result_size = size;
	if (desLen > spli_size) {
		result_size = (size - 1) / (spli_size - 1)*desLen;
	}
	char* alloc_result = malloc(result_size + 1);
	for (size_t i = 0; i < size;)
	{
		strncpy(alloc_tmp, alloc_origin + i, spli_size - 1);
		if (!strcmp(alloc_tmp, strSrc) || i == (size - 1)) {
			tmp_len = i - start;
			if (tmp_len == 0) {
				if (i != size - 1) {
					strncpy(alloc_result + count, strDes, desLen);
					count += desLen;
				}
				i += (spli_size - 1);
				start = i;
				continue;
			}
			strncpy(alloc_result + count, alloc_origin + start, tmp_len);
			count += tmp_len;
			if (i != size - 1) {
				strncpy(alloc_result + count, strDes, desLen);
				count += desLen;
			}
			i += (spli_size - 1);
			start = i;
		}
		else {
			i++;
		}
	}
	alloc_result[count] = '\0';
	free(alloc_origin);
	free(alloc_tmp);
	return alloc_result;
}