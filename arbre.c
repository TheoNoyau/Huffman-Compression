#include <stdlib.h>
#include <stdio.h>
#include "arbre.h"
#define T_MAX 100

int est_arbre_vide(arbre a){
    return (a==NULL) ;
}

arbre gauche (arbre a){
    return a->gauche;
}

arbre droit (arbre a){
    return a->droit;
}

int poids(arbre a){
    return a->poids;
}

unsigned char carac(arbre a){
    return a->carac;
}

arbre creer_arbre(void){
    return malloc(sizeof(noeud));
}

arbre ajoute_gauche(arbre a){
    a->gauche = creer_arbre() ;
    return gauche(a);
}

arbre ajoute_droit(arbre a){
    a->droit = creer_arbre();
    return droit(a);
}

void set_poids (arbre a , int pds){
    a->poids = pds ;
}

void set_carac(arbre a, unsigned char c){
    a->carac = c ;
}

arbre creer_arbre_complet(unsigned char e, int poids, arbre fg, arbre fd) {
    arbre a ;
    a = creer_arbre();
    set_poids(a, poids) ;
    set_carac(a, e) ;
    a->gauche = fg ;
    a->droit = fd ;

    return a;
}

arbre creer_feuille(unsigned char e, int poids) {
    return creer_arbre_complet(e, poids, NULL, NULL);
}

int est_feuille (arbre a) {
    if (est_arbre_vide(a))
        return 0 ;
    return (est_arbre_vide(a->gauche) && est_arbre_vide(a->droit)) ;
}

// calcule la hauteur d'un arbre
int hauteur(arbre a){
    if(est_arbre_vide(a)) return 0 ;
    else {
        return 1 + max(hauteur(a->gauche), hauteur(a->droit)) ;
    }
}

void print_arbre_aux(arbre a)
{
  if (est_arbre_vide(a))
    printf(".") ;
  else
  {
    printf("%c (", a->carac) ;
    print_arbre_aux(a->gauche) ;
    printf(") (");
    print_arbre_aux(a->droit) ;
    printf(")") ;
  }
}

void print_arbre(arbre a) // Notation préfixe
{
  print_arbre_aux(a) ;
  printf("\n") ;
  printf ("%d\n", poids(a));
  printf("\n");
}

int ser (arbre a, unsigned char *s, int i) {
 
  if (est_arbre_vide (a)) {
    s[i] = '0' ;
    s[i+1] = 0;
    return ++i ;
  }
  else {
    s[i++] = '1' ;
    s[i++] = carac(a) ;
    s[i+1] =0;
    i = ser (a->gauche, s, i) ;
    i = ser (a->droit, s, i) ;
 
    return i ;
  }
}

arbre deserialisation_sup(unsigned char *chaine){
    int i;
    i=0;
    return deserialisation(chaine,&i);
}

arbre deserialisation (unsigned char* chaine, int*i){
    arbre pointeur ;
    if (chaine[*i]=='0'){
        (*i)++;
        pointeur = NULL;
    } else if (chaine[*i]=='1'){
        (*i)++;
        pointeur = creer_arbre_complet(chaine[*i] , 0 , NULL , NULL);
        (*i)++;
        pointeur->gauche = (deserialisation(chaine,i));
        pointeur->droit = (deserialisation(chaine,i));
        //return pointeur;
    }
    return pointeur;
}
