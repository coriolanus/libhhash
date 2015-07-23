#include <stdlib.h>
#include <hhash.h>
#include <hhset.h>
#include "test.h"

int main(void) {
  ulong n = 16;
  ulong m = 0;
  HHSet *S = hhsetnew(n, NULL, NULL);
  for (ulong i = 0; i < 30; ++i) {
    ulong x = rand() + 1;
    if (!hhsetget(S, x)) {
      test(hhsetput(S, x));
      ++m;
    }
  }
  test(S->T->m == m);
  hhsetfree(S);
  return 0;
}
