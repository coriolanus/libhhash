CFILES=${shell find . -name "*.c"}

TESTS=${CFILES:%.c=%}

CFLAGS+=-I.. -I.
LDFLAGS+=-L.. -lhhash

default: test

test: $(TESTS)
	for f in $(TESTS);\
	do\
	  echo $$f; \
	done;

clean:
	rm -f $(TESTS) $(TESTSC:%.c=%.o)
