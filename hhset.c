#include <stdlib.h>
#include "hhash.h"
#include "hhset.h"

static ulong id(ulong x) { return x - 1; }

static int neq(ulong x, ulong y) { return x != y; }

HHSet *hhsetnew(ulong n, ulong (*hash)(ulong), int (*cmp)(ulong, ulong)) {
  HHSet *S = malloc(sizeof(HHSet));
  S->T = hhashnew(n);
  S->hash = (hash != NULL) ? hash : id;
  S->cmp = (cmp != NULL) ? cmp : neq;
  return S;
}

void hhsetfree(HHSet *S) {
  hhashfree(S->T);
  free(S);
}

int hhsetcopy(HHSet *S, HHSet *T) {
  for (int i = 0; i < S->T->n; ++i) {
    ulong x = S->T->V[i];
    if (x) {
      ulong h = T->hash(x);
      if (!hhashput(T->T, h, x)) return 0;
    }
  }
  return 1;
}

static ulong hunt(HHSet *S, ulong h, ulong k, int kill) {
  int i = hhashsucc(S->T, h, 0);
  while (i >= 0) {
    ulong x = hhashget(S->T, h, i);
    if (S->cmp(k, x) == 0) {
      if (kill) hhashdel(S->T, h, i);
      return x;
    }
    i = hhashsucc(S->T, h, i + 1);
  }
  return 0;
}

ulong hhsetget(HHSet *S, ulong k) { return hunt(S, S->hash(k), k, 0); }

ulong hhsetdel(HHSet *S, ulong k) { return hunt(S, S->hash(k), k, 1); }

static int resize(HHSet *R) {
  HHSet *S = hhsetnew(2 * R->T->n, R->hash, R->cmp);
  if (!hhsetcopy(R, S)) {
    hhsetfree(S);
    return 0;
  }
  HHash *T = R->T;
  R->T = S->T;
  S->T = T;
  hhsetfree(S);
  return 1;
}

int hhsetput(HHSet *S, ulong x) {
  if (x == 0) return 0;
  ulong h = S->hash(x);
  if (hunt(S, h, x, 0)) return 1;
  if (hhashput(S->T, h, x)) return 1;
  if (!resize(S)) return 0;
  return hhashput(S->T, h, x);
}
