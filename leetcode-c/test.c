#include "include/env.h"

extern void solution14(void);

int main() {
	//_CrtSetBreakAlloc(81);
	solution14();
	_CrtDumpMemoryLeaks();
	int i = 0;
	scanf("%d",&i);
	return i;
}

