#define WORD (8 * sizeof(ulong))

#define clz(x) __builtin_clzl(x)

#define fls(x) (WORD - clz(x))

#define ffs(x) (__builtin_ctzl(x))

#define get(x, i) ((x) & (1 << (i)))

#define set(x, i) (x = (x) | (1 << (i)))

#define unset(x, i) (x = (x) & ~(1 << (i)))
