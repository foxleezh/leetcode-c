#include "include/env.h"

extern void solution12(void);

int main() {
	//_CrtSetBreakAlloc(81);
	solution12();
	_CrtDumpMemoryLeaks();
	int i = 0;
	scanf("%d",&i);
	return i;
}

