default: all

include make.inc

all: library bin

library:
	(cd lib; make)

bin:
	(cd lib; make bin)

clean:
	(cd lib; make clean)

purge:
	(cd lib; make purge)
