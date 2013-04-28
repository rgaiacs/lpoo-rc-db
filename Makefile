default: all

include make.inc

all: library


library:
	(cd lib; make)

clean:
	(cd lib; make clean)

purge:
	(cd lib; make purge)
