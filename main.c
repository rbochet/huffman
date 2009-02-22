/*$Id$*/

#include <stdio.h>
#include <stdlib.h>

#include "type_arbre.h"
#include "arbre.h"
#include "io.h"
#include "coefficients.h"

int main(int argc, char **argv)
{
  /* Les variables les plus globales */
  COUPLE occ[MAX_CAR];
  ARBRE nocc[MAX_CAR];
  ARBRE racine;
  unsigned short len;

  FILE *fd;

  /* Test des arguments */
  if(argc < 2)
  {
    fprintf(stderr, "Usage : %s entrée\n", argv[0]);
    fprintf(stderr, "Ce programme ne gère que l'ASCII (man ascii)\n");
    exit(EXIT_FAILURE);
  }

  /* Enchainement des fonctions */
  fd = fopen(argv[1], "r");

  /* On remplit les occurences */
  remplitOccurences(occ, fd);
  trieOccurences(occ);
  /*afficheOccurences(occ); */

  /* On génère l'arbre */
  len = remplitNodeOccurences(occ, nocc);
  creeArbre(&racine, nocc, len);

  /* On affiche les coeffs des lettres présentes */
  afficheTable(racine);

  /* On recommence au début du fichier */
  fseek(fd, 0, SEEK_SET);

  /* On affiche le texte en binaire */
  printf("Le texte compressé est : \n");
  compresseTexteCar(racine, fd, stdout);

  /* On écrit les statistiques de compression */
  stats(racine, fd);

  /* Fermeture propre du programme */
  fclose(fd);
  freeArbre(racine);

  return 0;
}
