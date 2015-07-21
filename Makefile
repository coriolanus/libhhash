OFILES=\
	hhash.o\
	hhset.o\
	hhmap.o\

CFILES=\
	hhash.c\
	mach.c\
	hhset.c\
	hhmap.c\

HFILES=\
	hhash.h\
	hhset.h\
	hhmap.h\

default: $(OFILES)

$(OFILES): $(CFILES) $(HFILES)

CFLAGS+=-std=c99 -O3

.PHONY: format
format: $(CFILES) $(HFILES)
	clang-format -i $^

libhhash.a: $(OFILES)
	ar rcs $@ $^

.PHONY: clean
clean:
	rm -f $(OFILES) libhhash.a
