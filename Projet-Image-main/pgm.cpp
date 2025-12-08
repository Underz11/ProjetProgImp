#include <stdexcept>
/** @file
 * Lecture et ecriture d'images en niveau de gris au format PGM
 **/

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
#include "pgm.hpp"


ImageGris lirePGM(string source) {
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
    
    double car;

    auto image = ImageGris (sizeL);
    for ( int i = 0 ; i < sizeL ; i++ ) image[i] = vector<double> (sizel) ;
    
    for (int L = 0 ; L < sizeL ; L++ ){
        for ( int l = 0 ; l < sizel ; l++){
            flux >> car;
            image[L][l] = car;
        }
    }
    flux.close();
    return image;
}

void ecrirePGM(ImageGris img, string cible) {
    ofstream flux;
    flux.open(cible);
    if (!flux) throw runtime_error("Fichier non trouve: "+cible);

    flux << "P2";
    flux << ' ' << img.size();
    flux << ' ' << img[0].size();
    flux << ' ' << "255";
    
    for ( auto ligne : img ) for (auto car : ligne ) flux << ' ' << ((int)car);

    flux.close();
}



bool ImageGrisEgal(ImageGris a, ImageGris b, float precision) {
    if (a.size() != b.size()) return false ;
    if (a[0].size() != b[0].size()) return false;
    for ( int i = 0 ; i < a.size() ; i++){
        if (a[i].size() != b[i].size() ) return false;
        for (int j = 0 ; j < a[i].size() ; j++) if (abs(a[i][j]-b[i][j]) > precision) return false;
    }
    return true;
}

ImageGris inversePGM(ImageGris img) {
    ImageGris imgInverse = img;
    for ( int i = 0 ; i < img.size() ; i++ ) for ( int j = 0 ; j < img[i].size() ; j++ ) imgInverse[i][j] = 255 - img[i][j];
    return imgInverse;
}

