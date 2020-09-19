// Projet C
// KERNEVES Théo, DELOLME Antonin, SANTOS Aurelien, LAVEDRINE Aymeric
// Module Huffman

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"

void printEntree(entree e){
    printf("char : %c - codage : %s - longueur : %d\n", e.c, e.seqBits, e.len);
}

// parcours en profondeur
void parcours_profondeur(arbre a, int indice, entree table[], unsigned char *tab)
{
    unsigned char *tab2 ;
    static int j = 0 ;
    if(!est_arbre_vide(a)){
        if(!est_feuille(a)){
            //printf("%c\n", carac(a)) ;
            tab[indice] = '0';
            parcours_profondeur(gauche(a), indice+1, table , tab) ;
            tab[indice] = '1';
            parcours_profondeur(droit(a), indice+1, table , tab) ;
        }else{
            entree e;
            e.len=indice;
            e.c=carac(a);
            tab[indice] = 0 ;
            tab2 = malloc(sizeof(indice + 1));
            memcpy(tab2 , tab , indice + 1);
            e.seqBits = tab2 ;
            memcpy(&(table[j]) , &e , sizeof(entree));

            //table[j]->len=indice ;
            //table[j]->c=carac(a);
            table[j]=e;
            j++;
        }
    }
    return;
}

entree code(unsigned char c, dico d)
{
    while ((d)->c != c) d++;

    return *d;
}

dico get_table (arbre a , int size, entree t[]){

    entree table [256];
    dico d;
    d = &(table[0]);

    unsigned char *tab = malloc(hauteur(a) + 1);
    parcours_profondeur(a, 0, table, tab);
    return d;
}

int countCharInFile (int T[], FILE *f) {
    unsigned char c;
    int n , ic;

    n = 0 ;
    while (fscanf(f, "%c", &c) != EOF) {
        ic = (int)c;
        if (T[ic] == 0) n++ ;
        T[ic] = T[ic] + 1 ;
    }

    rewind(f);
    return n ;
}

arbre charToLeaf (unsigned char c, int poids) {
    return creer_feuille (c, poids) ;
}

arbre stringToHuffman (int T[]) {
    int i ;
    arbre tmp, a1, a2 ;
    Liste l ;

    l = creer_liste_vide();
    for (i = 0 ; i < 256; i++) {
        if (T[i] != 0) {
            tmp = charToLeaf (i, T[i]) ;
            l = insertNode (l, tmp) ;
        }
    }

    while (!est_liste_vide(queue((l)))) {
        l = removeNode (l, &a1) ;
        l = removeNode (l, &a2) ;

        tmp = creer_arbre_complet ('.', poids(a1) + poids(a2), a1, a2) ;
        l = insertNode (l, tmp) ;   
    }

    return tete(l) ;
}

unsigned char findChar(arbre huffman, Bin_file *input)
{
    arbre tmp;
    unsigned char bit;

    tmp = huffman;
    while (!est_feuille(tmp))
    {
        bit = lecture(input);
        
        if (bit == 1)
        {
            tmp = tmp->droit;
        }
        else if (bit == 0)
        {
            tmp = tmp->gauche;
        }
    }
    return carac(tmp);
}