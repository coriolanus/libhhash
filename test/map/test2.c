#include <stdlib.h>
#include <hhash.h>
#include <hhset.h>
#include <hhmap.h>
#include "test.h"

void fill(HHSet *S, ulong m) {
  for (uint i = 0; i < m; ++i) {
    uint x = rand();
    test(hhmapput(S, x, i + 1));
    test(hhmapget(S, x) == i + 1);
  }
}

int main(void) {
  ulong n = 256;
  ulong m = 150;
  HHSet *S = hhmapnew(n, NULL, NULL);
  fill(S, m);
  test(m == S->T->m);
  hhsetfree(S);
  return 0;
}
