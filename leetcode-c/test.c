#include "include/env.h"

extern void solution18(void);

int main() {
	//_CrtSetBreakAlloc(80);
	solution18();
	_CrtDumpMemoryLeaks();
	int i = 0;
	scanf("%d",&i);
	return i;
}

