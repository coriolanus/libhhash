#include <stdlib.h>
#include "hhash.h"
#include "hhset.h"
#include "hhmap.h"

#define HALF \
	(8*sizeof(ushort))

static uint
id(uint x)
{
	return (ushort)x;
}

static int
neq(uint x, uint y)
{
	return (ushort)x != (ushort)y;
}

HHSet *
hhmapnew(uint n, void *hash, void *cmp)
{
	HHSet *S = malloc(sizeof(HHSet));
	S->T = hhashnew(n);
	S->hash = (hash != NULL) ? hash : id;
	S->cmp = (cmp != NULL) ? cmp : neq;
	return S;
}

int
hhmapput(HHSet *S, ushort k, ushort v)
{
	if(v == 0)
		return 0;
	uint x = (((uint)v)<<HALF)|k;
	return hhsetput(S,x);
}

ushort
hhmapget(HHSet *S, ushort k)
{
	return (ushort)(hhsetget(S,k)>>HALF);
}

ushort
hhmapdel(HHSet *S, ushort k)
{
	return (ushort)(hhsetdel(S,k)>>HALF);
}
