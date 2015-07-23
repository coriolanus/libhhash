#include <stdlib.h>
#include "hhash.h"
#include "mach.c"

#define mod(x, n) ((x) < (n) ? (x) : (x) - (n))

HHash *hhashnew(ulong n) {
  HHash *T = malloc(sizeof(HHash));
  T->m = 0;
  T->n = n;
  T->k = fls(n - 1);
  T->V = malloc(n * sizeof(ulong));
  T->H = malloc(n * sizeof(ulong));
  for (int i = 0; i < n; ++i) {
    T->H[i] = 0;
    T->V[i] = 0;
  }
  return T;
}

void hhashfree(HHash *T) {
  free(T->V);
  free(T->H);
  free(T);
}

static int next(HHash *T, ulong h, int i) {
  ulong H = T->H[h] & (~0 << i);
  if (H == 0) return -1;
  return ffs(H);
}

static int succ(HHash *T, ulong h, ulong i) {
  if (get(T->H[h], i)) return i;
  return next(T, h, i);
}

int hhashsucc(HHash *T, ulong h, ulong i) {
  h %= T->n;
  return succ(T, h, i);
}

static void move(HHash *T, ulong h, ulong i, ulong j) {
  unset(T->H[h], i);
  set(T->H[h], j);
  i = mod(h + i, T->n);
  j = mod(h + j, T->n);
  ulong v = T->V[i];
  T->V[i] = 0;
  T->V[j] = v;
}

void hhashdel(HHash *T, ulong h, ulong i) {
  h %= T->n;
  ulong j = mod(h + i, T->n);
  if (T->V[j] == 0 || !get(T->H[h], i)) return;
  T->V[j] = 0;
  unset(T->H[h], i);
  --T->m;
}

static ulong probe(HHash *T, ulong h) {
  int i = 0;
  for (; h + i < T->n; ++i)
    if (T->V[h + i] == 0) return i;
  ulong j = 0;
  for (; T->V[j] != 0; ++j)
    ;
  return i + j;
}

static ulong seek(HHash *T, ulong h) {
  for (ulong i = T->k - 1; i > 0; --i) {
    ulong hi = mod(T->n + h - i, T->n);
    if (T->H[hi] != 0 && ffs(T->H[hi]) < i) return i;
  }
  return 0;
}

int hhashput(HHash *T, ulong h, ulong v) {
  if (T->m == T->n || v == 0) return 0;
  h %= T->n;
  ulong d = probe(T, h);
  while (d >= T->k) {
    ulong hd = mod(h + d, T->n);
    ulong z = seek(T, hd);
    if (z == 0) return 0;
    ulong j = z;
    z = mod(T->n + hd - z, T->n);
    ulong i = succ(T, z, 0);
    move(T, z, i, j);
    d = mod(T->n + z + i - h, T->n);
  }
  ulong hd = mod(h + d, T->n);
  T->V[hd] = v;
  set(T->H[h], d);
  ++T->m;
  return 1;
}
