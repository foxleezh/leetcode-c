#include "include/env.h"

extern void solution9(void);

int main() {
	//_CrtSetBreakAlloc(81);
	solution9();
	_CrtDumpMemoryLeaks();
	int i = 0;
	scanf("%d",&i);
	return i;
}

