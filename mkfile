MKSHELL=$PLAN9/bin/rc

<$PLAN9/src/mkhdr

<mkconfig

LIB=$PREFIX/lib/libhhash.a

CFLAGS='-std=c99'

OFILES=\
	hhash.$O\
	hhset.$O\
	hhmap.$O\

CFILES=\
	hhash.c\
	mach.c\
	hhset.c\
	hhmap.c\

HFILES=\
	hhash.h\
	hhset.h\
	hhmap.h\

<$PLAN9/src/mklib

hhset.$O:	hhash.$O

hhmap.$O:	hhset.$O

install:QV:	$HFILES
	for (t in $HFILES)
    	cp $t $PREFIX/include
