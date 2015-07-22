#include <stdlib.h>
#include <hhash.h>
#include <hhset.h>
#include "test.h"

static uint fill(HHSet *S) {
  uint m = 0;
  for (uint i = 0; i < 128; ++i) {
    uint x = rand() + 1;
    if (!hhsetget(S, x)) {
      test(hhsetput(S, x));
      ++m;
    }
  }
  return m;
}

static uint rnd(HHSet *S) {
  HHash *T = S->T;
  uint h = rand() % T->n;
  while (T->V[h] == 0) h = (h + 1) % T->n;
  return T->V[h];
}

static uint strip(HHSet *S) {
  uint m = 0;
  for (; m < 64; ++m) {
    uint x = rnd(S);
    hhsetdel(S, x);
    test(!hhsetget(S, x));
  }
  return m;
}

int main(void) {
  uint n = 256;
  HHSet *S = hhsetnew(n, NULL, NULL);
  uint m = fill(S);
  test(m == S->T->m);
  m -= strip(S);
  test(m == S->T->m);
  hhsetfree(S);
  return 0;
}
