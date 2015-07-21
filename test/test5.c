#include <stdlib.h>
#include <hhash.h>
#include "test.h"

int
find(HHash *T, uint x)
{
	uint h = x%T->n;
	int i = hhashsucc(T,h,0);
	while(i >= 0){
		uint y = hhashget(T,h,i);
		if(x == y)
			return 1;
		i = hhashsucc(T,h,i+1);
	}
	return 0;
}

int
main(void)
{
	uint n = 256;
	HHash *T = hhashnew(n);
	test(hhashput(T,0x04,0x04));
	test(hhashput(T,0x09,0x09));
	test(hhashput(T,0x11,0x11));
	test(hhashput(T,0x24,0x24));
	test(hhashput(T,0x25,0x25));
	test(hhashput(T,0x32,0x32));
	test(hhashput(T,0x39,0x39));
	test(hhashput(T,0x3c,0x3c));
	test(hhashput(T,0x40,0x40));
	test(hhashput(T,0x4b,0x4b));
	test(hhashput(T,0x56,0x56));
	test(hhashput(T,0x67,0x67));
	test(hhashput(T,0x71,0x71));
	test(find(T,0x04));
	test(find(T,0x09));
	test(find(T,0x11));
	test(find(T,0x24));
	test(find(T,0x25));
	test(find(T,0x32));
	test(find(T,0x39));
	test(find(T,0x3c));
	test(find(T,0x40));
	test(find(T,0x4b));
	test(find(T,0x56));
	test(find(T,0x67));
	test(find(T,0x71));
	hhashfree(T);
	return 0;
}
