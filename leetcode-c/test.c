#include "include/env.h"

extern void solution20(void);

int main() {
	//_CrtSetBreakAlloc(79);
	solution20();
	_CrtDumpMemoryLeaks();
	int i = 0;
	scanf("%d",&i);
	return i;
}

