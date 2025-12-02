#include <stdexcept>
/** @file
 * Lecture et ecriture d'images en niveau de gris au format PGM
 **/
#include <iostream>
#include <fstream>
#include <vector>
#include "image.hpp"
using namespace std;


/// BEGIN lirePGM

/** Construire une image en teintes de gris depuis un fichier PGM
 * @param source le nom d'un fichier PGM
 * @return une image en teintes de gris
 **/
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

/// BEGIN ecrirePGM

/** Ecrit une image en teintes de gris dans un fichier PGM
 * @param img une image en teintes de gris
 * @param cible le nom d'un fichier PGM
 **/
void ecrirePGM(ImageGris img, string cible) {
    ofstream flux;
    flux.open(cible);
    if (!flux) throw runtime_error("Fichier non trouve: "+cible);

    flux << "P2";
    flux << ' ' << img.size();
    flux << ' ' << img[0].size();
    flux << ' ' << "255";
    
    for ( auto ligne : img ) for (auto car : ligne ) flux << ' ' << car;

    flux.close();
}

/** Construit une image cliché d'une image en niveau de gris
 * @param img une image en niveau de gris
 * @return l'image cliché qui inverse les niveaux de gris
 **/
ImageGris inversePGM(ImageGris img) {
    ImageGris imgInverse = img;
    for ( int i = 0 ; i < img.size() ; i++ ) for ( int j = 0 ; j < img[i].size() ; j++ ) imgInverse[i][j] = 255 - img[i][j];
    return imgInverse;
}

void lirePGMTest(){
    cout << "Vérifier que les images obtenues dans 'pgm/' sont semblables à celles fournies dans 'pgm/correction/'" << endl;
    ecrirePGM(lirePGM("images/brain.pgm"),  "pgm/brain.pgm");
    ecrirePGM(lirePGM("images/illusion.pgm"),  "pgm/illusion.pgm");
}

void inversePGMTest() {
    ImageGris imageOriginale;
    cout << "Vérifier que les images obtenues dans 'pgm/' sont semblables à celles fournies dans 'pgm/correction/'" << endl;
    imageOriginale = lirePGM("images/brain.pgm");
    ecrirePGM(inversePGM(imageOriginale),  "pgm/brain-inverse.pgm");
    imageOriginale = lirePGM("images/illusion.pgm");
    ecrirePGM(inversePGM(imageOriginale),  "pgm/illusion-inverse.pgm");
}

int main() {
    lirePGMTest();
    inversePGMTest();
    return 0;
}

