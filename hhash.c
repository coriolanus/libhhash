#include <stdlib.h>
#include "hhash.h"
#include "mach.c"

HHash*
hhashnew(uint n)
{
	HHash *T = malloc(sizeof(HHash));
	T->m = 0;
	T->n = n;
	T->k = fls(n-1);
	T->V = malloc(n*sizeof(uint));
	T->H = malloc(n*sizeof(uint));
	for(int i = 0; i < n; ++i){
		T->H[i] = 0;
		T->V[i] = 0;
	}
	return T;
}

void
hhashfree(HHash *T)
{
	free(T->V);
	free(T->H);
	free(T);
}

static int
next(HHash *T, uint h, int i)
{
	uint H = T->H[h]&(~0<<i);
	if(H == 0)
		return -1;
	return ffs(H);
}

int
hhashsucc(HHash *T, uint h, uint i)
{
	h %= T->n;
	if(get(T->H[h],i))
	    return i;
	return next(T,h,i);
}

static void
move(HHash *T, uint h, uint i, uint j)
{
	h %= T->n;
	unset(T->H[h],i);
	set(T->H[h],j);
	uint hi = (h+i)%T->n;
	uint v = T->V[hi];
	T->V[hi] = 0;
	T->V[(h+j)%T->n] = v;
}

void
hhashdel(HHash *T, uint h, uint i)
{
	h %= T->n;
	uint j = (h+i)%T->n;
	if(T->V[j] == 0 || !get(T->H[h],i))
		return;
	T->V[j] = 0;
	unset(T->H[h],i);
	--T->m;
}

static uint
probe(HHash *T, uint h, uint i)
{
	for(;; ++i)
		if(T->V[(h+i)%T->n] == 0)
			return i;
}

static uint
seek(HHash *T, uint h)
{
	uint i = T->k-1;
	for(; i > 0; --i){
		uint hi = (T->n+h-i)%T->n;
		if(T->H[hi] == 0 && ffs(T->H[hi]) < i)
			return i;
	}
	return 0;
}

int
hhashput(HHash *T, uint h, uint v)
{
	if(T->m == T->n || v == 0)
		return 0;
	h %= T->n;
	uint d = probe(T,h,0);
	while(d >= T->k){
		uint hd = (h+d)%T->n;
		uint z = seek(T,hd);
		if (z == 0)
			return 0;
		z = (T->n+hd-z)%T->n;
		uint i = hhashsucc(T,z,0);
		uint j = (T->n+hd-z)%T->n;
		move(T,z,i,j);
		d = (T->n+z+i-h)%T->n;
	}
	uint hd = (h+d)%T->n;
	T->V[hd] = v;
	set(T->H[h],d);
	++T->m;
	return 1;
}
