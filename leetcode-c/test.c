#include "include/env.h"

extern void solution7(void);

int main() {
	//_CrtSetBreakAlloc(81);
	solution7();
	_CrtDumpMemoryLeaks();
	int i = 0;
	scanf("%d",&i);
	return i;
}

