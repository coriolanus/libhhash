#define WORD \
	sizeof(uint)*8

#define clz(x) \
	__builtin_clz(x)

#define fls(x) \
	(WORD-clz(x))

#define ffs(x) \
	(__builtin_ctz(x))

#define get(x,i) \
	((x)&(1<<(i)))

#define set(x,i) \
	(x = (x)|(1<<(i)))

#define unset(x,i) \
	(x = (x)&~(1<<(i)))
