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

TESTC=${shell find test -name "*.c"}

TESTS=${TESTC:%.c=%}

default: $(OFILES) libhhash.a

$(OFILES): $(CFILES) $(HFILES)

CFLAGS+=-std=c99 -O3

.PHONY: format
format: $(CFILES) $(HFILES)
	clang-format -i $^

libhhash.a: $(OFILES)
	ar rcs $@ $^

.PHONY: clean
clean:
	rm -f $(OFILES) libhhash.a $(TESTS)

$(TESTS): $(TESTC) $(CFILES) $(HFILES)
	cc -L. -lhhash $(CFLAGS) -I. -Itest -o $@ $@.c

test: $(TESTS)
	for f in $(TESTS); \
	do \
	  echo $$f; \
	done;
