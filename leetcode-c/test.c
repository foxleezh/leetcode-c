#include "include/env.h"

extern void solution21(void);

int main() {
	//_CrtSetBreakAlloc(79);
	solution21();
	_CrtDumpMemoryLeaks();
	int i = 0;
	scanf("%d",&i);
	return i;
}

