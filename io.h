/*$Id$*/

#ifndef IO_H_INCLUDED
#define IO_H_INCLUDED

#include "type_arbre.h"

int remplitOccurences(COUPLE tab[MAX_CAR], FILE *fd);
int trieOccurences(COUPLE tab[MAX_CAR]);
int afficheOccurences(COUPLE tab[MAX_CAR]);
unsigned short lenUtile(COUPLE tab[MAX_CAR]);
int compresseTexteCar(ARBRE racine, FILE *entree, FILE *sortie);
inline char carAffichable(char c);

#endif
