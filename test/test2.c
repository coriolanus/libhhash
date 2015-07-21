#include <stdlib.h>
#include <hhash.h>
#include "test.h"

int
main(void)
{
	uint n = 16;
	HHash *T = hhashnew(n);
	uint x = rand()%n;
	test(hhashput(T,x,1));
	uint i = hhashsucc(T,x,0);
	test(i == 0);
	hhashdel(T,x,i);
	test(hhashsucc(T,x,0) < 0);
	hhashfree(T);
	return 0;
}
