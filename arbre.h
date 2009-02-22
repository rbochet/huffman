/*$Id$*/

#ifndef ARBRE_H_INCLUDED
#define ARBRE_H_INCLUDED

int remplitNodeOccurences(COUPLE occ[MAX_CAR], ARBRE nocc[MAX_CAR]);
int creeArbre(ARBRE *racine, ARBRE nocc[MAX_CAR], unsigned short len);
int trieNoeuds(ARBRE tab[MAX_CAR], int longueur);
int afficherNode(ARBRE root);
int freeArbre(ARBRE root);

#endif
