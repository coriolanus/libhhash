#ifndef LIBHHSET_H
#define LIBHHSET_H

typedef struct HHSet HHSet;

struct HHSet {
  HHash* T;
  ulong (*hash)(ulong);
  int (*cmp)(ulong, ulong);
};

HHSet* hhsetnew(ulong, ulong (*)(ulong), int (*)(ulong, ulong));
void hhsetfree(HHSet*);
int hhsetcopy(HHSet*, HHSet*);
int hhsetput(HHSet*, ulong);
ulong hhsetget(HHSet*, ulong);
ulong hhsetdel(HHSet*, ulong);

#endif
