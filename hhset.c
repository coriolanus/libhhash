#include <stdlib.h>
#include "hhash.h"
#include "hhset.h"

static uint id(uint x) { return x - 1; }

static int neq(uint x, uint y) { return x != y; }

HHSet *hhsetnew(uint n, uint (*hash)(uint), int (*cmp)(uint, uint)) {
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
    uint x = S->T->V[i];
    if (x) {
      uint h = T->hash(x);
      if (!hhashput(T->T, h, x)) return 0;
    }
  }
  return 1;
}

static uint hunt(HHSet *S, uint h, uint k, int kill) {
  int i = hhashsucc(S->T, h, 0);
  while (i >= 0) {
    uint x = hhashget(S->T, h, i);
    if (S->cmp(k, x) == 0) {
      if (kill) hhashdel(S->T, h, i);
      return x;
    }
    i = hhashsucc(S->T, h, i + 1);
  }
  return 0;
}

uint hhsetget(HHSet *S, uint k) { return hunt(S, S->hash(k), k, 0); }

uint hhsetdel(HHSet *S, uint k) { return hunt(S, S->hash(k), k, 1); }

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

int hhsetput(HHSet *S, uint x) {
  if (x == 0) return 0;
  uint h = S->hash(x);
  if (hunt(S, h, x, 0)) return 0;
  if (hhashput(S->T, h, x)) return 1;
  if (!resize(S)) return 0;
  return hhashput(S->T, h, x);
}
