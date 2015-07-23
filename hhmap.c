#include <stdlib.h>
#include "hhash.h"
#include "hhset.h"
#include "hhmap.h"

#define HALF (8 * sizeof(uint))

static ulong id(ulong x) { return (uint)x; }

static int neq(ulong x, ulong y) { return (uint)x != (uint)y; }

HHSet *hhmapnew(ulong n, ulong (*hash)(ulong), int (*cmp)(ulong, ulong)) {
  HHSet *S = malloc(sizeof(HHSet));
  S->T = hhashnew(n);
  S->hash = (hash != NULL) ? hash : id;
  S->cmp = (cmp != NULL) ? cmp : neq;
  return S;
}

int hhmapput(HHSet *S, uint k, uint v) {
  if (v == 0) return 0;
  ulong x = (((ulong)v) << HALF) | k;
  return hhsetput(S, x);
}

uint hhmapget(HHSet *S, uint k) { return (uint)(hhsetget(S, k) >> HALF); }

uint hhmapdel(HHSet *S, uint k) { return (uint)(hhsetdel(S, k) >> HALF); }
