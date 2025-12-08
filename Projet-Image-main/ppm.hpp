/** @file
 * Lecture et ecriture de fichiers au format PPM
 **/

#include <string>
#include "image.hpp"

/// BEGIN ppmh

/** Lit une image au format PPM, retourne un tableau de Couleur
 * @param source vers une image .ppm
 * @return une image
 **/
/**
*Auteur : Julie Fabre
* Degré de confiance : plutôt élevé, la fonction est très similaire dans son fonctionnement à lirePGM, elle passe les tests de ppm-test et elle est utilisiée sans problème plus tard dans le projet dans la partie 6 
**/
Image lirePPM(string source);

/**  Écrit une image dans un fichier PPM
 * @param img une image
 * @param cible le nom d'un fichier PPM
 **/
/**
*Auteur : Julie Fabre
* Degré de confiance : plutôt élevé, même principe que pourn lirePPM, elle est très similaire dans son fonctionnement à ecrirePGM, elle passe les tests de ppm-test et est utilisé sans problème plus tard la partie 6. 
**/
void  ecrirePPM(Image img, string cible);

/// END ppmh

