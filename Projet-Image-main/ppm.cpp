#include <stdexcept>
/** @file
 * Lecture et écriture d'images au format PPM
 **/


#include <iostream>
#include <fstream>
#include "ppm.hpp"
//La partie rapport se trouve dans ppm.hpp
Image lirePPM(string source) {
    
//On ouvre la source en lecture en vérifiant qu'elle existe, on initialise les dimensions, le maximum des valeurs et l'image.
    ifstream flux;
    flux.open(source);
    if (!flux) throw runtime_error("Fichier non trouve: "+source);
    string data;
    flux >> data;
    int sizeL;
    int sizel;
    double max;
    flux >> sizeL;
    flux >> sizel;
    flux >> max;
    double col1;
    double col2;
    double col3;
    auto image = Image(sizeL);


    //On construit l'image en ajoutant des lignes (tableaux de couleurs)
    for ( int i = 0 ; i < sizeL ; i++ ) image[i] = vector<Couleur> (sizel) ;
    //On récupère les informations de couleurs trois par trois pour constituer un élément du tableau (une couleur)
    for (int L = 0 ; L < sizeL ; L++ ){
        for ( int l = 0 ; l < sizel ; l++){
            flux >> col1;
            flux >> col2;
            flux >> col3;
            struct Couleur col = {col1, col2, col3};
            image[L][l] = col;
        }
    }
    //On ferme la source et on renvoit l'image
    flux.close();
    return image;

}

void ecrirePPM(Image img, string cible) {
    ofstream flux;
    //On ouvre la cible en écriture en vérifiant si elle existe
    flux.open(cible);
    if (!flux) throw runtime_error("Fichier non trouve: "+cible);
    //On place les informations essentielles, le format les dimensions et le maximum des valeurs
    flux << "P3" <<endl;
    flux << img.size();
    flux << ' ' << img[0].size() << endl;
    flux << "255" << endl;
    //On parcourt l'image et on place individuellement chaque élément r/g/b de chaque élément couleur en tronquant pour obtenir des entiers
    for ( auto ligne : img ) {
      for (auto car : ligne) {
          flux  << ((int)car.r) << ' ';
          flux  << ((int)car.g) << ' ';
          flux  << ((int)car.b)<< ' ';
      }
    }
    //On ferme la cible
    flux.close(); 
}

