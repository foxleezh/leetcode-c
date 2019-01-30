#include "include/env.h"

extern void solution11(void);

int main() {
	//_CrtSetBreakAlloc(81);
	solution11();
	_CrtDumpMemoryLeaks();
	int i = 0;
	scanf("%d",&i);
	return i;
}

