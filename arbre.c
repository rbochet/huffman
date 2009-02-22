/*$Id$*/

#include <stdlib.h>
#include <stdio.h>

#include "type_arbre.h"
#include "arbre.h"
#include "io.h"


/*!
\brief Remplit un tableau de feuilles correspondant au tableau des occurences
\param occ Le tableau TRIÉ des occurences sous forme de couple
\param nocc Le tableau dans lequel on range les noeuds
*/
int remplitNodeOccurences(COUPLE occ[MAX_CAR], ARBRE nocc[MAX_CAR])
{
  unsigned short i;

  /* On traduit en ptr vers des feuilles */
  for(i = 0 ; i < lenUtile(occ) ; i++)
  {
    nocc[i] = (ARBRE)malloc(sizeof(struct NODE));
    /* On veut juste des feuilles */
    nocc[i]->fg = NULL;
    nocc[i]->fd = NULL;
    nocc[i]->type = feuille;
    /* Dont la donnée est le contenu data*/
    nocc[i]->data = occ[i];
  }

  return lenUtile(occ);
}


/*!
\brief Construit l'arbre à partir du tableau de des noeuds
\param racine L'arbre sera construit dans racine
\param nocc le tableau des noeuds
\param len Le nombre de noeuds non nuls du tableau
\warning Le tableau des noeuds doit être trié !
*/
int creeArbre(ARBRE *racine, ARBRE nocc[MAX_CAR], unsigned short len)
{
  ARBRE trac;
  len--;
  /* Tant qu'on a pas épuisé le tableau */
  while(len != 0)
  {
    /*
    printf("DEBUT\n");
    for(i=0;i<len;i++)
      afficherNode(nocc[i]);
    printf("FIN\n");
    */

    /* Invariant de boucle : le tableau est trié */
    trac = (ARBRE)malloc(sizeof(struct NODE));
    /* On met ensemble les deux noeuds de plus petits poids */
    trac->fd = nocc[len];
    trac->fg = nocc[len-1];
    /* Le poids est la somme des deux autres poids */
    trac->data.poids = nocc[len]->data.poids + nocc[len-1]->data.poids;
    /* Il s'agit d'un noeud, pas d'une feuille */
    trac->type = noeud;

    /* On stocke dans l'arbre, puis on diminue d'un la longueur */
    nocc[len-1] = trac;

    /*
    On trie l'arbre : dans ce cas, un tri a bulle est spéciallement adapté
    car un seul élément bouge dans le pire des cas
    */
    trieNoeuds(nocc, len);
    len--;

  }
  /* len =0  => il ne reste qu'un elt, c'est la racine  */
  *racine = nocc[len];
  return 0;
}

/*!
\brief Trie le tablea des noeuds
\param tab Le tableau à trier
\param longueur La longeur sur laquelle on doit trier le tableau
*/
int trieNoeuds(ARBRE tab[MAX_CAR], int longueur)
{
  short i, inversion;
  ARBRE swap;

  /* Tri a bulle optimisé */
  do
  {
    inversion=0;
    for(i=0;i<longueur-1;i++)
    {
       if (tab[i]->data.poids < tab[i+1]->data.poids)
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

/*!
\brief Libère la mémoire occupée par un arbre
\param root Arbre à libérer
*/
int freeArbre(ARBRE root)
{
  /* Suppression des deux sous arbres */
  if(root->fg !=NULL)
    freeArbre(root->fg);
  if(root->fd !=NULL)
    freeArbre(root->fd);
  /* Suppression de la structure principale */
  free(root);
  return 0;
}

/*!
\brief Affiche les infos du node en question (type, poids, éventuellement caractère)
*/
int afficherNode(ARBRE root)
{
  printf("Type : %d\tPoids : %d", root->type, root->data.poids);
  if(root->type == feuille)
    printf("\tCaractère : %c\n", root->data.carac);
  else
    printf("\n");
  return 0;
}
