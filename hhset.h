#ifndef LIBHHSET_H
#define LIBHHSET_H

typedef struct HHSet HHSet;

struct HHSet
{
	HHash *T;
	uint (*hash)(uint);
	int (*cmp)(uint, uint);
};

HHSet* hhsetnew(uint,void*,void*);
void hhsetfree(HHSet*);
int hhsetcopy(HHSet*,HHSet*);
int hhsetput(HHSet*,uint);
uint hhsetget(HHSet*,uint);
uint hhsetdel(HHSet*,uint);

#endif
