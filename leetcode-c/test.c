#include "include/env.h"

extern void solution15(void);

int main() {
	//_CrtSetBreakAlloc(74);
	solution15();
	_CrtDumpMemoryLeaks();
	int i = 0;
	scanf("%d",&i);
	return i;
}

