#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbre.h"
#include "huffman.h"
#define T_MAX 10000

void compress(char *file_in, char *file_out)
{
    arbre a;
    dico d;
    int n , len, i;
    int occ[256] = {0};
    entree table[256] = {0};
    unsigned char *serial =malloc (sizeof (char)*256) ;
    unsigned char c ;
    entree e;

    Bin_file *in = (Bin_file *)malloc(sizeof(Bin_file));
    open_file_read(in, file_in);
    // N=nb de char diff
    n = countCharInFile(occ, in->file);
    a = stringToHuffman(occ);
    //print_arbre(a);
    len = ser(a, serial, 0);
    d = get_table(a , n, table);

   /* i = 0;
    for (i = 0; i < n; i++) {
        printEntree(d[i]);
    }*/

    Bin_file *out = (Bin_file *)malloc(sizeof(Bin_file));
    open_file_write(out, file_out);

    fprintf(out->file, "%d\n", a->poids);
    fprintf(out->file, "%d\n", len);
    fprintf(out->file, "%s\n", serial);

    open_file_read(in, file_in);
    fscanf(in->file, "%c", &c) ;
    while (!feof(in->file)) {
        e = code(c, d) ;
        for (i = 0; i < e.len; i++) {
            ecrire_2(out, e.seqBits[i]) ;
        }
        fscanf(in->file, "%c", &c) ;
    }
    while (out->i_octet > 0) {
        ecrire_2(out, 0) ;
    }

    close_file(in);
    close_file(out);
    printf("Compression effectuee\n");
}

void extract(char *file_in, char *file_out){
    arbre a;
    int n , i , j , len;
    unsigned char s[T_MAX];
    unsigned char c;

    Bin_file *in = (Bin_file *)malloc(sizeof(Bin_file));
    Bin_file *out = (Bin_file *)malloc(sizeof(Bin_file));
    in->i_record = 0;
    in->record_length = 0;

    open_file_read(in,file_in);
    open_file_write(out,file_out);
    fscanf(in->file , "%d\n" , &n);

    fscanf(in->file, "%d\n", &len);

    j=0;
    while (j < len){
        fscanf(in->file, "%c", &c);
        s[j++] = c;
    }
    s[j] = 0;
    fscanf(in->file, "%c", &c);
    a = deserialisation_sup(s);

    for (i=0 ; i<n ; i++ ){
        c = findChar(a, in);
        fprintf(out->file , "%c", c);
    }
    close_file(in);
    close_file(out);
    printf("Extraction effectuee\n");
}

    int main(int argc, char *argv[])
{
    char c;
    char source[100], sortie[100] ;

    printf("Voulez-vous compresser ou décompresser (c ou d) ?\n");
    scanf("%c", &c) ;
    if (c == 'c') {
        printf("Entrer un fichier source à compresser :\n");
        scanf("%s", source) ;
        printf("Entrer un fichier de sortie :\n");
        scanf("%s", sortie) ;
        compress(source, sortie);
    } else if (c == 'd') {
        printf("Entrer un fichier source à décompresser:\n");
        scanf("%s", source) ;
        printf("Entrer un fichier de sortie :\n");
        scanf("%s", sortie) ;
        extract(source , sortie);
    } else {
        printf ("Erreur\n") ;
    }

    return 0;
}