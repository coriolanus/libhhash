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

phony: format
format: $(CFILES) $(HFILES)
	clang-format -i $^

libhhash.a: $(OFILES)
	ar rcs $@ $^

clean:
	rm -f $(OFILES) libhhash.a
