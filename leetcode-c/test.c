#include "include/env.h"

extern void solution17(void);

int main() {
	//_CrtSetBreakAlloc(74);
	solution17();
	_CrtDumpMemoryLeaks();
	int i = 0;
	scanf("%d",&i);
	return i;
}

