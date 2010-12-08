#include <stdlib.h>
#include <9unit.h>
#include <hhash.h>
#include <hhset.h>
#include <hhmap.h>

uint hash(uint x)
{
	uint k = (ushort)x;
	return k*0x9e3779b1;
}

void
fill(HHSet *S, uint m)
{
	for (ushort i = 0; i < m; ++i) {
		ushort x = rand();
		test(hhmapput(S,x,i+1));
		test(hhmapget(S,x) == i+1);
	}
}

int
main(void)
{
	uint n = 256;
	uint m = 150;
	HHSet *S = hhmapnew(n,hash,NULL);
	fill(S,m);
	test(m == S->T->m);
	hhsetfree(S);
	return 0;
}
