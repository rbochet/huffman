/*$Id$*/
#include <stdio.h>
#include <stdlib.h>

#include "type_arbre.h"
#include "io.h"
#include "coefficients.h"

/*! \author Romain BOCHET 
\brief Crée un tableau des occurences d'apparition d'un caractère dans un fichier
\param tab Le tableau à remplir
\param fd Le fichier à analyser
*/
int remplitOccurences(COUPLE tab[MAX_CAR], FILE* fd)
{
  char c, flag;
  unsigned short i;

  /* On définit un couple vide */
  COUPLE vide;
  vide.carac = 0;
  vide.poids = 0;

  /* On remplit avec rien */
  for(i = 0 ; i < MAX_CAR ; i++)
    tab[i] = vide;

  /* On parcours le tab */
  while((c = fgetc(fd)) != EOF){
    i = 0;
    flag = 0;
    while(tab[i].poids != 0)
    {
      if(tab[i].carac == c)
      {
        /* On vient de le rencontrer une fois de plus */
        tab[i].poids++;
        flag = 1;
      }
      i++;
    }
    if(!flag) /* On ne l'a pas trouvé ! */
    {
      /* On créée un nouvel enregistrement */
      tab[i].poids = 1;
      tab[i].carac = c;
    }
  }
  return 0;
}

/*! \author Romain BOCHET 
\brief Trie le tableau des occurences (les plus fréquentes au début)
\param tab Le tableau à trier
*/
int trieOccurences(COUPLE tab[MAX_CAR])
{
  unsigned short i, inversion, longueur;
  COUPLE swap;

  /* Calcul de la longueur utile */
  longueur = lenUtile(tab);

  /* Tri a bulle optimisé */
  do
   {
   inversion=0;

   for(i=0;i<longueur-1;i++)
      {
      if (tab[i].poids<tab[i+1].poids)
         {
         swap = tab[i];
         tab[i] = tab[i+1];
         tab[i+1] = swap;
         inversion=1;
         }
      }
   longueur--;
   }
  while(inversion);
  return 0;
}

/*! \author Romain BOCHET 
\brief Affiche un tableau d'occurences
\param tab Le tableau à afficher
*/
int afficheOccurences(COUPLE tab[MAX_CAR])
{
  unsigned short i;
  i= 0;
  printf("-- Affichage du tableau des occurences --\n");
  while(i < MAX_CAR && tab[i].poids != 0)
  {
    printf("| 0x%02x | %c | %2d |\n", tab[i].carac, carAffichable(tab[i].carac), tab[i].poids);
    i++;
  }
  printf("-- Fin affichage --\n");
  return 0;
}

/*! \author Romain BOCHET 
\brief Calcule la longueur utile dans le tableau (apparitions != 0)
\param tab Le tableau à trier
\return La longueur des données utiles
*/
unsigned short lenUtile(COUPLE tab[MAX_CAR])
{
  unsigned short longueur = 0;
  while(longueur < MAX_CAR && tab[longueur].poids != 0)
  {
    longueur++;
  }
  return longueur;
}

/*! \author Romain BOCHET 
\brief Ecrit dans un flux le contenu du fichier au format 'pseudo-binaire'
\param racine L'arbre de Huffman
\param entree Le flux d'entree
\param sortie Le flux de sortie
\warning Le flux d'entrée n'est lu qu'a partir de la valeur courante du pointeur, utiliser fseek avant
*/
int compresseTexteCar(ARBRE racine, FILE *entree, FILE *sortie)
{
  char c;
  char *code;
  /* On parcours le fichier */
  while((c = fgetc(entree)) != EOF){
    //afficheCoeffCar(racine, c);
    coeffCar(racine, c, &code);
    fprintf(sortie, "%s ", code);
    /* On se rappelle que coeffCar ne désalloue pas la mémoire */
    free(code);
  }
  fprintf(sortie, "\n");
  return 0;

}

/*! \author Romain BOCHET 
\brief Donne une valeur affichable d'un caractère (\n, ACK, ...)
\param c Le caractère
\return Le caractère si il appartient à [32, 126], ou un point '.'
*/
inline char carAffichable(char c)
{
  return (((c>=32)&&(c<=126))?c:'.');
}
