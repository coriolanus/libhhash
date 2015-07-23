#include <stdlib.h>
#include <hhash.h>
#include "test.h"

int main(void) {
  ulong n = 16;
  HHash *T = hhashnew(n);
  ulong x = 15;
  test(hhashput(T, x, 1));
  test(hhashsucc(T, x, 0) == 0);
  test(hhashput(T, x, 1));
  test(hhashsucc(T, x, 1) == 1);
  test(hhashput(T, x, 1));
  test(hhashsucc(T, x, 2) == 2);
  test(T->m == 3);
  x = 14;
  test(hhashput(T, x, 1));
  test(hhashsucc(T, x, 0) == 0);
  test(hhashput(T, x, 1));
  test(hhashsucc(T, x, 1) == 1);
  test(!hhashput(T, x, 1));
  hhashfree(T);
  return 0;
}
