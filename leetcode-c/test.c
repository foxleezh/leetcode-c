#include "include/env.h"

extern void solution13(void);

int main() {
	//_CrtSetBreakAlloc(81);
	solution13();
	_CrtDumpMemoryLeaks();
	int i = 0;
	scanf("%d",&i);
	return i;
}

