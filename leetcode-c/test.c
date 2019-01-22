#include "include/env.h"

extern void solution1(void);

int main() {
	//_CrtSetBreakAlloc(76);
	solution1();
	_CrtDumpMemoryLeaks();
	int i = 0;
	scanf("%d",&i);
	return i;
}

