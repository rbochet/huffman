/*$Id$*/

#ifndef COEFFICIENTS_H_INCLUDED
#define COEFFICIENTS_H_INCLUDED

/* Ces fonctions affichent la table des caractères de l'arbre */
int afficheTable(ARBRE);
int afficheTableRec(ARBRE, ARBRE);

/* Ces fonctins servent a afficher un caractère */
int afficheCoeffCarRec(ARBRE, char, char *ret);
int afficheCoeffCar(ARBRE, char);

/* Ces fonctions permettent de renvoyer un char* qui contient le car */
int coeffCarRec(ARBRE, char, char *ret);
int coeffCar(ARBRE, char, char **ret);

/* Cette fonction sert a afficher des stats sur le codage effectué */
int stats(ARBRE, FILE *);
float  tauxCompression(ARBRE racine, FILE *entree, int *size);

#endif
