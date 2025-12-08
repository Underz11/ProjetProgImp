/** @file
 * Filtres de conversion couleur <-> teintes de gris
 **/

#include "image.hpp"

/// BEGIN griscouleurh

/** Transforme une image couleur en une image en teintes de gris
 * @param img une image
 * @return une image en teintes de gris
 **/
/**
*Auteur : Julie Fabre
* Degré de confiance : plutôt élevé, la fonction passe les tests de gris-couleurs-test, et elle a été testée dans la partie "Aller plus loin" avec quelques images prisent au hasard sur mon ordinateur.
**/
ImageGris CouleurAuGris(Image img);

/** Transforme une image en teintes de gris en une image en couleurs (mais grise)
 * @param img une image en teintes de gris
 * @return une image
 **/
/**
*Auteur : Julie Fabre
* Degré de confiance : moyennement élevée, la fonction passe les tests, l'implémentation me semble plutôt logique, mais je n'ai pas fait de tests supplémentaire sur la fonction pour confirmer son efficacité 
**/
Image GrisACouleur(ImageGris img);

/// END griscouleurh

