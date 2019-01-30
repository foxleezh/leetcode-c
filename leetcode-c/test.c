#include "include/env.h"

extern void solution10(void);

int main() {
	//_CrtSetBreakAlloc(81);
	solution10();
	_CrtDumpMemoryLeaks();
	int i = 0;
	scanf("%d",&i);
	return i;
}

