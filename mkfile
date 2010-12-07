MKSHELL=$PLAN9/bin/rc

<$PLAN9/src/mkhdr

<mkconfig

LIB=$PREFIX/lib/libhhash.a

CFLAGS='-std=c99'

OFILES=\
	hhash.$O\

CFILES=\
	hhash.c\
	mach.c\

HFILES=\
	hhash.h\

DIRS=map set

<$PLAN9/src/mkdirs

<$PLAN9/src/mklib

install:QV:	$HFILES
	for (t in $HFILES)
    	cp $t $PREFIX/include
