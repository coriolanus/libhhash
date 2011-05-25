#include <stdlib.h>
#include <9unit.h>
#include <hhash.h>
#include <hhset.h>

int
main(void)
{
	uint n = 16;
	uint m = 0;
	HHSet *S = hhsetnew(n,NULL,NULL);
	for(uint i = 0; i < 30; ++i){
		uint x = rand()+1;
		if(!hhsetget(S,x)){
			test(hhsetput(S,x));
			++m;
		}
	}
	test(S->T->m == m);
	hhsetfree(S);
	return 0;
}
