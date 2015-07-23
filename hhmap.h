#ifndef LIBHHMAP_H
#define LIBHHMAP_H

typedef unsigned int uint;

HHSet *hhmapnew(ulong n, ulong (*)(ulong), int (*)(ulong, ulong));
int hhmapput(HHSet *, uint, uint);
uint hhmapget(HHSet *, uint);
uint hhmapdel(HHSet *, uint);

#endif
