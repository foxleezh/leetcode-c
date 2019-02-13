#include "include/env.h"

extern void solution19(void);

int main() {
	//_CrtSetBreakAlloc(79);
	solution19();
	_CrtDumpMemoryLeaks();
	int i = 0;
	scanf("%d",&i);
	return i;
}

