#include <stdlib.h>
#include <9unit.h>
#include <hash/hhash.h>

uint
fill(HHash *T)
{
	uint m = 0;
	for(uint i = 0; i < 100; ++i){
		uint x = rand()%T->n;
		if(hhashsucc(T,x,0) < 0)
			if(hhashput(T,x,x))
				++m;
	}
	return m;
}

uint
count(HHash *T)
{
	uint m = 0;
	uint h = 0;
	while(h < T->n){
		int i = hhashsucc(T,h,0);
		while(i >= 0){
			++m;
			i = hhashsucc(T,h,i+1);
		}
		++h;
	}
	return m;
}

int
main(void)
{
	uint n = 256;
	HHash *T = hhashnew(n);
	uint m = fill(T);
	test(m == T->m);
	test(m == count(T));
	hhashfree(T);
	return 0;
}
