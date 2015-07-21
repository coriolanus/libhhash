#ifndef LIBHHASH_H
#define LIBHHASH_H

typedef unsigned int uint;
typedef struct HHash HHash;

struct HHash {
  uint k, m, n;
  uint *H;
  uint *V;
};

#define hhashget(hhash, x, i) ((hhash)->V[((x) + (i)) % (hhash)->n])

HHash *hhashnew(uint);
void hhashfree(HHash *);
int hhashput(HHash *, uint, uint);
void hhashdel(HHash *, uint, uint);
int hhashsucc(HHash *, uint, uint);

#endif
