/** @file
 * Filtre Super Pixel
 **/

#include "image.hpp"

/// BEGIN EnsemblePoints

/** Structure de donnee representant un point dans l'espace
    spacio colorimetrique **/
typedef vector<double> Point;

/** Structure de donnee representant un ensemble de points dans l'espace
    spacio colorimetrique **/
typedef vector<Point> EnsemblePoints;
/// END EnsemblePoints

/// BEGIN distancePoints

/** Renvoie la distance Euclidienne entre deux points
 * @param p un point
 * @param c un point
 * @return la distance entre p et c
 **/
/**
*Auteur : Julie Fabre
* Degré de confiance : plutôt élevé, la fonction passe les tests, est utilisé tout au long de cette partie et me semble correct mathématiquement. 
**/
double distancePoints(Point p, Point c);
/// END distancePoints

/// BEGIN distanceAEnsemble

/** Renvoie la distance Euclidienne d'un point a un ensemble de points
 * @param p un point
 * @param C un ensemble de points
 * @return la distance
 **/
/**
*Auteur : Julie Fabre
* Degré de confiance : plutôt élevé, c'est un algorithme de recherche de minimum assez classique. 
**/
double distanceAEnsemble(Point p, EnsemblePoints C);
/// END distanceAEnsemble

/// BEGIN plusProcheVoisin

/** Renvoie le plus proche voisin d'un point p dans un ensemble C
 * @param p un point
 * @param C un ensemble de points
 * @return l'index du plus proche voisin
 **/
/**
*Auteur : Julie Fabre
* Degré de confiance : peu élevé, Même si la fonction semble marcher, et son implémentation semble logique, elle est possiblement la cause de certaines imprécisions qu'on trouve la fonction superPixel() et est également la potentielle cause de la relative lenteur de cette même fonction, même si certains problèmes d'optimisations ont déjà été corrigé. 
**/
int plusProcheVoisin(Point p, EnsemblePoints C);
/// END plusProcheVoisin

/// BEGIN sousEnsemble

/** Renvoie les points p de P tels que C[k] est le plus proche voisin de p dans C
 * @param P un ensemble de points
 * @param C un ensemble de points
 * @param k un entier
 * @return un sous ensemble des points de P
 **/
/**
*Auteur : Julie Fabre
* Degré de confiance : plutôt élevé, les tests de K-Moyenne() fonctionnent, K-moyenne() qui utilise des sous ensembles. De plus cette fonction a été réalisée en suivant les instructions de la partie Indication de l'exercice 6.4
**/
EnsemblePoints sousEnsemble(EnsemblePoints P, EnsemblePoints C,int k);
/// END sousEnsemble

/// BEGIN barycentre

/** Renvoie le barycentre d'un ensemble de points
 * @param Q un ensemble de points
 * @return c le barycentre de Q
 **/
/**
*Auteur : Julie Fabre
* Degré de confiance : moyennement élevé, la fonction me semble logique mathématiquement, avec elle K-moyenne() passe les tests, mais elle est potentiellement la cause des imprécisions de la fonction superPixel() 
**/
Point barycentre(EnsemblePoints Q);
/// END barycentre

/// BEGIN kMoyenne

/** Renvoie la K-moyenne de deux ensembles de points
 * @param P un ensemble de points
 * @param C un ensemble de points
 * @param nbAmeliorations:entier le nombre de fois ou l'amelioration va etre effectuee
 * @return C un ensemble de points les positions finales de points pilotes
 **/
/**
*Auteur : Julie Fabre
* Degré de confiance : plutôt élevé, la fonction passe les tests et me semble logique dans son fonctionnement.
**/
EnsemblePoints KMoyenne(EnsemblePoints P, EnsemblePoints C, int nbAmeliorations);
/// END kMoyenne

/// BEGIN FASTkMoyenne

/** Implantation optimisee de K-moyenne
 * @param P un ensemble de points
 * @param C un ensemble de points
 * @param nbAmeliorations:entier le nombre de fois ou l'amelioration va etre effectuee
 * @return C un ensemble de points les positions finales de points pilotes
 **/
EnsemblePoints FAST_KMoyenne(EnsemblePoints P, EnsemblePoints C, int nbAmeliorations);
/// END FASTkMoyenne

/// BEGIN pivotSuperPixel

/** Renvoie un ensemble de points (espace spatio colorimetrique)
 *  regulierement espaces dans une image
 * @param img une image
 * @param lambda un double
 * @param mu un entier
 * @return un ensemble de points dans l'espace spatio colorimetrique
 **/
/**
*Auteur : Julie Fabre
* Degré de confiance : plutôt élevé, la fonction a été réalisée selon les indications de l'exercice 6.7 et permet à superPixel() de passer les tests. 
**/
EnsemblePoints pivotSuperPixel (Image img, double lambda, int mu);
/// END pivotSuperPixel

/// BEGIN superPixels

/** Renvoie les superpixels d'une image dans l'espace spatio colorimetrique
 * @param img une image en teintes de gris
 * @param lambda un double
 * @param mu un entier
 * @param nbAmeliorations un entier
 * @return un ensemble de points, les superpixels
 **/
/**
*Auteur : Julie Fabre
* Degré de confiance : plutôt élevé, les tests passent et le fonctionnement de la fonction en elle même est très simple. 
**/
EnsemblePoints superPixels(Image img, double lambda, int mu, int nbAmeliorations);
/// END superPixels

/// BEGIN SuperPixel

/** Filtre SuperPixel
 * @param img une image
 * @param lambda un double
 * @param mu un entier
 * @param nbAmeliorations
 * @return l'image associee aux superpixels d'une image
 **/
/**
*Auteur : Julie Fabre
* Degré de confiance : moyennement élevé, la fonction passe les tests, mais sur certaines images on obtient de légères imprécisions qui sont pour certaines probablement des erreurs d'arrondis, pour d'autre on a un résultat un tout petit peu plus dfférent, et d'autres encore sont conformes à la correction.
**/
Image superPixel(Image img, double lambda, int mu, int nbAmeliorations);
/// END SuperPixel



// Ecrire votre code ici
/** Renvoie une version de l'image avec les contours bleus aux  frontières des superpixels
* @param img une image qui a été traité avec SuperPixel
* @return la version de l'image avec les contours bleus
**/
/**
*Auteur : Julie Fabre
* Degré de confiance : moyennement élevé, les résultats fonctionnent, mais il est possible que la fonction soit légèrement imprécise étant donné qu'elle ne vérifie que 4 pixels voisins, peut-être qu'en vérifiant les pixels diagonaux il est possible d'obtenir des résultats plus précis.  
**/
Image superPixelAvecBleu(Image img);

