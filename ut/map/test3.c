#include <stdlib.h>
#include <limits.h>
#include <9unit.h>
#include <hash/hhash.h>
#include <hash/hhset.h>
#include <hash/hhmap.h>

uint hash(uint x)
{
	uint k = (ushort)x;
	return k*0x9e3779b1;
}

void
fill(HHSet *S, uint m)
{
	for(ushort i = 0; i < m; ++i){
		ushort x = rand()%(USHRT_MAX-1)+1;
		test(!hhmapget(S,i));
		test(hhmapput(S,i,x));
		test(hhmapget(S,i) == x);
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
