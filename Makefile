CC = gcc
CCOPTS = -Wall

all: hoffman.exe

arbre.o: arbre.c arbre.h
	${CC} ${CCOPTS} -c arbre.c

liste_ext.o: liste_ext.c liste_ext.h listes.h
	${CC} ${CCOPTS} -c liste_ext.c

file.o: file.h arbre.h listes.h liste_ext.h huffman.h
	${CC} ${CCOPTS} -c file.c 

huffman.o: huffman.h arbre.h huffman.h file.h
	${CC} ${CCOPTS} -c huffman.c 

hoffman.exe: main_compression.c arbre.o liste_ext.o file.o huffman.o
	${CC} ${CCOPTS} main_compression.c  arbre.o liste_ext.o file.o huffman.o -o huffman.exe

clean: 
	rm *.o
	rm *.txt