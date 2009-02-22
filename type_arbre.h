/*$Id$*/

#ifndef TYPE_ARBRE_H_INCLUDED
#define TYPE_ARBRE_H_INCLUDED

#define MAX_CAR 100

typedef struct NODE *ARBRE;
typedef struct COUPLE COUPLE;

/*!
\enum TYPE_NODE
Définit le type du noeud de l'arbre : s'il s'agit d'une feuille ou d'un noeud interne
\li Feuille : Pas de fils (initialisés à NULL), le champs carac de la structure NODE est accessible
\li Noeud : Deux fils, initialisés par construction de l'arbre, seul le champs poids est accessible
*/
enum TYPE_NODE {feuille, noeud};

/*!
\struct COUPLE
Permet de stocker une lettre et son poids.
*/
struct COUPLE {
  int poids;
  char carac;
};

/*!
\struct NODE
Définit un noeud, dont le type est donné par TYPE_NODE, et les données sont stockées dans un COUPLE
*/
struct NODE {
  /* Les fils droits et gauche */
  ARBRE fg;
  ARBRE fd;
  /* Le type de noeud */
  enum TYPE_NODE type;
  /* Le caractère stocké et le poids */
  COUPLE data;
};


#endif // TYPE_ARBRE_H_INCLUDED
