#include <stdlib.h>
#include <hhash.h>
#include <hhset.h>
#include "test.h"

int x;

static ulong fill(HHSet *S) {
  ulong m = 0;
  for (ulong i = 0; i < 128; ++i) {
    ulong y = rand() + 1;
    if (!hhsetget(S, y)) {
      test(hhsetput(S, y));
      ++m;
    }
    test(hhsetget(S, x));
  }
  return m;
}

int main(void) {
  ulong n = 256;
  srand(13948824);
  HHSet *S = hhsetnew(n, NULL, NULL);
  x = rand();
  hhsetput(S, x);
  fill(S);
  hhsetfree(S);
  return 0;
}
