#include <stdexcept>
/** @file
 * Lecture et écriture d'images au format PPM
 **/


#include <iostream>
#include <fstream>
#include "ppm.hpp"

Image lirePPM(string source) {
    // Remplacez cette ligne et la suivante par le code adéquat

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
    for ( int i = 0 ; i < sizeL ; i++ ) image[i] = vector<Couleur> (sizel) ;
    
    for (int L = 0 ; L < sizeL ; L++ ){
        for ( int l = 0 ; l < sizel ; l++){
            flux >> col1;
            flux >> col2;
            flux >> col3;
            struct Couleur col = {col1, col2, col3};
            image[L][l] = col;
        }
    }
    flux.close();
    return image;

}

void ecrirePPM(Image img, string cible) {
    ofstream flux;
    flux.open(cible);
    if (!flux) throw runtime_error("Fichier non trouve: "+cible);

    flux << "P3";
    flux << ' ' << img.size();
    flux << ' ' << img[0].size();
    flux << ' ' << "255";
    
    for ( auto ligne : img ) {
      for (auto car : ligne) {
          
      }
    }flux << ' ' << car;

    flux.close(); 
}

