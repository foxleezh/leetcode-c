#include "include/env.h"

extern void solution3(void);

int main() {
	//_CrtSetBreakAlloc(81);
	solution3();
	_CrtDumpMemoryLeaks();
	int i = 0;
	scanf("%d",&i);
	return i;
}

