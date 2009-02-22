#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include "type_arbre.h"
#include "coefficients.h"
#include "io.h"

/*!
\brief Parcours de manière récursive l'arbre pour trouver le code d'un caractère
\param racine Racine de l'arbre de Huffman
\param c Caractère à trouver
\param ret Ou écrire le chemin parcouru
\warning Cette fonction ne peut être utilisée que par coeffCar
*/
int coeffCarRec(ARBRE racine, char c, char *ret)
{
  /* Invariant : On écrit tjrs au début de la chaine, décalage de pointeur */
  if(racine->type == feuille)
  {
    if(c == racine->data.carac) return 1;
    else return 0;
  }
  else
  {
    int retd, retg;
    retd = coeffCarRec(racine->fd, c, ret+1);
    retg = coeffCarRec(racine->fg, c, ret+1);
    if(retd)
    {
      *ret = '1';
      return 1;
    }
    else if(retg)
    {
      *ret = '0';
      return 1;
    }
    /* Si on a rien trouvé, on écrit rien et on remonte un zéro */
    return 0;
  }

}

/*!
\brief Affiche la correspondance binaire d'un caractère
\param racine L'arbre de Huffman
\param c Le caractère qu'on recherche
*/
int afficheCoeffCar(ARBRE racine, char c)
{
  char *ret;
  /* On récupère le coeff */
  coeffCar(racine, c, &ret);
  printf("Code du caractère '%c' (0x%02x) : %s\n", carAffichable(c), c, ret);
  free(ret);
  return 0;
}

/*!
\brief Affiche la table de tous les symboles de l'arbre et de leur code correspondant
\param racine L'arbre à analyser
*/
int afficheTable(ARBRE racine)
{
  printf("Affichage de la table des caractères : \n");
  /* On lance la fonction récursive */
  afficheTableRec(racine, racine);
  printf("Fin de la table\n");
  return 0;
}

/*!
\brief Affiche la table de tous les symboles de l'arbre et de leur code correspondant
\param racine L'arbre à analyser
\param noeudCourant Le sous arbre pointé
\warning Cette fonction ne peut être utilisée que par afficheTv
*/
int afficheTableRec(ARBRE racine, ARBRE noeudCourant)
{
  if(noeudCourant->type == feuille)
  {
    afficheCoeffCar(racine, noeudCourant->data.carac);
  }
  else
  {
    afficheTableRec(racine, noeudCourant->fg);
    afficheTableRec(racine, noeudCourant->fd);
  }
  return 0;
}

/*!
\brief Renvoie le code binaire d'un caractère dans *ret
\param racine Racine de l'arbre de Huffman
\param c Caractère à trouver
\param ret Contient une chaine optimisée pour le code binaire
\warning Cette fonction alloue de la mémoire, mais ne la libère pas, penser à libérer ret
*/
int coeffCar(ARBRE racine, char c, char **ret)
{
  /* Dans le cas le plus défavorable, on a MAX_CAR car de long */
  *ret = (char *)calloc(MAX_CAR, sizeof(char));
  coeffCarRec(racine, c, *ret);
  /* On corrige la longueur de la chaine*/
  *ret = (char *)realloc(*ret, (size_t)strlen(*ret)+2);
  return 0;
}

/*!
\brief Affiche des statistiques sur la compression
\param racine L'arbre de Huffman
\param entree Le fichier qui a été analysé
*/
int stats(ARBRE racine, FILE * entree)
{
  int size;
  float ratio;
  printf("Module de statistiques : \n");
  /* On relit le fichier depuis le début */
  fseek(entree, 0, SEEK_SET);
  ratio = tauxCompression(racine, entree, &size);

  printf("La taille des données compressée est : %d\n", size);
  printf("Le ratio de compression est de %f.\n", ratio);
  return 0;
}

/*!
\brief Calcule des infos sur la sortie de*
\param racine L'arbre de Huffman
\param entree Le fichier ananlysé
\param size Résultat : modifié pour contenir la taille des données une fois compressées
\return Le ratio de compression
*/
float  tauxCompression(ARBRE racine, FILE *entree, int *size)
{
  int longFichier, longCode;
  char c;
  char *code;

  /* Initialisations*/
  longCode = 0;
  longFichier = 0;

  /* On parcours le fichier */
  while((c = fgetc(entree)) != EOF){
    /* Un caractère ascii est codé sur 8 bits */
    longFichier += 8;
    /* On calcule la longueur du code */
    coeffCar(racine, c, &code);
    longCode += strlen(code);
    /* On se rappelle que coeffCar ne désalloue pas la mémoire */
    free(code);
  }
  /* On renvoit le rapport */
  *size = longCode;
  return (float)longCode/(float)longFichier;
}

