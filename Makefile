
all: libcxml.a

libcxml.a: cxml.o cxml_types.o
	ar rcs libcxml.a cxml.o cxml_types.o

cxml.o: cxml.c cxml.h
	gcc -O -c cxml.c -I.

cxml_types.o: cxml_types.c cxml_types.h
	gcc -O -c cxml_types.c -I.

clean:
	rm -f *.o *.a *.gch