#include <stdlib.h>
#include <9unit.h>
#include <hash/hhash.h>
#include <hash/hhset.h>
#include <hash/hhmap.h>

int
main(void)
{
	uint n = 256;
	HHSet *S = hhmapnew(n,NULL,NULL);
	test(hhmapput(S,5,15));
	test(hhmapget(S,5) == 15);
	test(hhmapput(S,7,17));
	test(hhmapget(S,7) == 17);
	test(hhmapput(S,3,13));
	test(hhmapget(S,3) == 13);
	test(hhmapdel(S,5) == 15);
	test(!hhmapget(S,5));
	test(hhmapdel(S,7) == 17);
	test(!hhmapget(S,7));
	test(hhmapdel(S,3) == 13);
	test(!hhmapget(S,3));
	hhsetfree(S);
	return 0;
}
