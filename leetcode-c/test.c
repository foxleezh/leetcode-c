#include "include/env.h"

extern void solution5(void);

int main() {
	//_CrtSetBreakAlloc(81);
	solution5();
	_CrtDumpMemoryLeaks();
	int i = 0;
	scanf("%d",&i);
	return i;
}

