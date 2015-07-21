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
	test(hhashsucc(T,x,0) == 0);
	test(hhashput(T,x,1));
	test(hhashsucc(T,x,1) == 1);
	test(hhashput(T,x,1));
	test(hhashsucc(T,x,2) == 2);
	test(hhashput(T,x,1));
	test(hhashsucc(T,x,3) == 3);
	test(!hhashput(T,x,1));
	hhashfree(T);
	return 0;
}
