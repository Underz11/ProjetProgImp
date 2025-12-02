#include <stdexcept>
/** @file
 * Lecture et ecriture d'images binaires au format PBM
 **/
#include <iostream>
#include <fstream>
#include <vector>
#include "image.hpp"
using namespace std;

/// BEGIN lirePBM

/** Construire une image binaire depuis un fichier PBM
 * @param source le nom d'un fichier PBM
 * @return une image binaire (0/1)
 **/
ImageNB lirePBM(string source) {
    ifstream flux;
    flux.open(source);
    if (!flux) throw runtime_error("Fichier non trouve: "+source);
    
    string data;
    flux >> data;

    int sizeL;
    int sizel;
    flux >> sizeL;
    flux >> sizel;
    
    int car;

    auto imageBin = ImageNB (sizeL);
    for ( int i = 0 ; i < sizeL ; i++ ) imageBin[i] = vector<int> (sizel) ;
    
    for (int L = 0 ; L < sizeL ; L++ ){
        for ( int l = 0 ; l < sizel ; l++){
            flux >> car;
            imageBin[L][l] = car;
        }
    }
    flux.close();
    return imageBin;
}

/// BEGIN ecrirePBM

/** Ecrit une image binaire dans un fichier PBM
 * @param img une image binaire (0/1)
 * @param cible le nom d'un fichier PBM
 **/
void ecrirePBM(ImageNB img, string cible) {
    ofstream flux;
    flux.open(cible);
    if (!flux) throw runtime_error("Fichier non trouve: "+cible);

    flux << "P1";
    flux << ' ' << img.size();
    flux << ' ' << img[0].size();
    
    for ( auto ligne : img ) for (auto car : ligne ) flux << ' ' << car;

    flux.close();
    
}


/// BEGIN affichePBM

/** Affiche une image binaire PBM à l'écran avec ' ' pour 0 et '@' pour 1
 * @param img une image binaire (0/1)
 **/
void affichePBM(ImageNB img) {
    string v;
    for ( auto ligne : img){
       for ( auto car : ligne ){
           if (car == 1) v = '@';
           else if (car == 0) v = ' ';
           cout << v << ' ';
       }
       cout << endl;
    }
}

/// BEGIN inversePBM

/** Echange le noir et le blanc dans une image PBM
 * @param img une image binaire (0/1)
 * @return l'image où le blanc et le noir ont été inversés
 **/
ImageNB inversePBM(ImageNB img) {
    ImageNB imgInverse = img;
    for ( int i = 0 ; i < img.size() ; i++ ) for ( int j = 0 ; j < img[i].size() ; j++ ) imgInverse[i][j] = (img[i][j] + 1 ) % 2;
    return imgInverse;
}

void testLirePBM(){
    cout << "Vérifier que les images obtenues dans 'pbm/' sont semblables à celles fournies dans 'pbm/correction/'" << endl;
    ecrirePBM(lirePBM("images/smiley.pbm"),  "pbm/smiley.pbm");
    ecrirePBM(lirePBM("images/cercle.pbm"),  "pbm/cercle.pbm");
    ecrirePBM(lirePBM("images/code.pbm"), "pbm/code.pbm");
    ecrirePBM(lirePBM("images/damier.pbm"), "pbm/damier.pbm");
}

int main(){
    testLirePBM();

    affichePBM(lirePBM("images/smiley.pbm"));
    cout << endl;
    affichePBM(inversePBM(lirePBM("images/smiley.pbm")));

    return 0;
}


