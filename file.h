#ifndef FILE_H
#define FILE_H

#include <stdlib.h>
#include <stdio.h>
#include "arbre.h"

#define BLOCK_SIZE 4096

typedef struct {
    FILE * file;
    char mode;
    unsigned char record [BLOCK_SIZE];
    int record_length;
    int i_record;
    char octet[8];
    int i_octet;
    int nb_octets;
} Bin_file;

typedef struct entree_t
{
    unsigned char c;
    unsigned char *seqBits;
    int len;
} entree ;

typedef entree *dico;

void close_file(Bin_file * input);
void open_file_read(Bin_file *input, char *name);
void open_file_write(Bin_file * input, char * name);
char lecture(Bin_file * input);
void chartobin(Bin_file * input, int c);


// Transforme une chaine de 8 car en char
unsigned char bitToCar(unsigned char *tab);

// Compresse in dans out par l'arbre a
void ecriture(Bin_file *in, Bin_file *out, dico d);

// Compresse inshallah in dans out par l'arbre a
void ecrire_2(Bin_file *output, char bit);


#endif