#include "include/env.h"

/*
 * Ҫ�������solution��������ָ�Ϊ��Ӧ����Ŀ
 */

extern void solution23(void);

int main() {
	//_CrtSetBreakAlloc(76);
	solution23();
	_CrtDumpMemoryLeaks();
	int i = 0;
	scanf("%d",&i);
	return i;
}

