#include <stdlib.h>
#include <hhash.h>
#include <hhset.h>
#include "test.h"

int x;

static uint fill(HHSet *S) {
  uint m = 0;
  for (uint i = 0; i < 128; ++i) {
    uint y = rand() + 1;
    if (!hhsetget(S, y)) {
      test(hhsetput(S, y));
      ++m;
    }
    test(hhsetget(S, x));
  }
  return m;
}

int main(void) {
  uint n = 256;
  srand(13948824);
  HHSet *S = hhsetnew(n, NULL, NULL);
  x = rand();
  hhsetput(S, x);
  fill(S);
  hhsetfree(S);
  return 0;
}
