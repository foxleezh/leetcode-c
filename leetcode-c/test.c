#include "include/env.h"

/*
 * Ҫ�������solution��������ָ�Ϊ��Ӧ����Ŀ
 */

extern void solution28(void);

int main() {
	//_CrtSetBreakAlloc(76);
	solution28();
	_CrtDumpMemoryLeaks();
	int i = 0;
	scanf("%d",&i);
	return i;
}

