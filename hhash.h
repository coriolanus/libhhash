#ifndef LIBHHASH_H
#define LIBHHASH_H

typedef unsigned long ulong;
typedef struct HHash HHash;

struct HHash {
  ulong k, m, n;
  ulong *H;
  ulong *V;
};

#define hhashget(hhash, x, i) ((hhash)->V[((x) + (i)) % (hhash)->n])

HHash *hhashnew(ulong);
void hhashfree(HHash *);
int hhashput(HHash *, ulong, ulong);
void hhashdel(HHash *, ulong, ulong);
int hhashsucc(HHash *, ulong, ulong);

#endif
