#include "include/env.h"

extern void solution6(void);

int main() {
	//_CrtSetBreakAlloc(81);
	solution6();
	_CrtDumpMemoryLeaks();
	int i = 0;
	scanf("%d",&i);
	return i;
}

