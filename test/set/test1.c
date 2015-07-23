#include <stdlib.h>
#include <hhash.h>
#include <hhset.h>
#include "test.h"

static ulong fill(HHSet *S) {
  ulong m = 0;
  for (ulong i = 0; i < 128; ++i) {
    ulong x = rand() + 1;
    if (!hhsetget(S, x)) {
      test(hhsetput(S, x));
      ++m;
    }
  }
  return m;
}

static ulong rnd(HHSet *S) {
  HHash *T = S->T;
  ulong h = rand() % T->n;
  while (T->V[h] == 0) h = (h + 1) % T->n;
  return T->V[h];
}

static ulong strip(HHSet *S) {
  ulong m = 0;
  for (; m < 64; ++m) {
    ulong x = rnd(S);
    hhsetdel(S, x);
    test(!hhsetget(S, x));
  }
  return m;
}

int main(void) {
  ulong n = 256;
  HHSet *S = hhsetnew(n, NULL, NULL);
  ulong m = fill(S);
  test(m == S->T->m);
  m -= strip(S);
  test(m == S->T->m);
  hhsetfree(S);
  return 0;
}
