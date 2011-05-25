#ifndef LIBHHMAP_H
#define LIBHHMAP_H

typedef unsigned short ushort;

HHSet* hhmapnew(uint,void*,void*);
int hhmapput(HHSet*,ushort,ushort);
ushort hhmapget(HHSet*,ushort);
ushort hhmapdel(HHSet*,ushort);

#endif
