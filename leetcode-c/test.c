#include "include/env.h"

/*
 * 要测试请把solution后面的数字改为对应的题目
 */

extern void solution22(void);

int main() {
	//_CrtSetBreakAlloc(76);
	solution22();
	_CrtDumpMemoryLeaks();
	int i = 0;
	scanf("%d",&i);
	return i;
}

