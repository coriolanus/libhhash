#include <stdlib.h>
#include <hhash.h>
#include "test.h"

ulong fill(HHash *T) {
  ulong m = 0;
  for (ulong i = 0; i < 100; ++i) {
    ulong x = rand() % T->n;
    if (hhashsucc(T, x, 0) < 0)
      if (hhashput(T, x, x)) ++m;
  }
  return m;
}

ulong count(HHash *T) {
  ulong m = 0;
  ulong h = 0;
  while (h < T->n) {
    int i = hhashsucc(T, h, 0);
    while (i >= 0) {
      ++m;
      i = hhashsucc(T, h, i + 1);
    }
    ++h;
  }
  return m;
}

int main(void) {
  ulong n = 256;
  HHash *T = hhashnew(n);
  ulong m = fill(T);
  test(m == T->m);
  test(m == count(T));
  hhashfree(T);
  return 0;
}
