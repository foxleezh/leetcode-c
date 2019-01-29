#include "include/env.h"

extern void solution8(void);

int main() {
	//_CrtSetBreakAlloc(81);
	solution8();
	_CrtDumpMemoryLeaks();
	int i = 0;
	scanf("%d",&i);
	return i;
}

