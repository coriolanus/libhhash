#include <stdlib.h>
#include <limits.h>
#include <hhash.h>
#include <hhset.h>
#include <hhmap.h>
#include "test.h"

ulong hash(ulong x) {
  ulong k = (uint)x;
  return k * 0x9e3779b1;
}

void fill(HHSet *S, ulong m) {
  for (uint i = 0; i < m; ++i) {
    uint x = rand() % (USHRT_MAX - 1) + 1;
    test(!hhmapget(S, i));
    test(hhmapput(S, i, x));
    test(hhmapget(S, i) == x);
  }
}

int main(void) {
  ulong n = 256;
  ulong m = 150;
  HHSet *S = hhmapnew(n, hash, NULL);
  fill(S, m);
  test(m == S->T->m);
  hhsetfree(S);
  return 0;
}
