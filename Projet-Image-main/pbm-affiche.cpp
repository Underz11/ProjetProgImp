#include <stdexcept>
/** @file
 * Affichage d'une image PBM
 **/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/// BEGIN affichePBM

/** Affiche une image binaire PBM à l'écran avec ' ' pour 0 et '@' pour 1
 * @param source le nom d'un fichier PBM
 **/
void affichePBM(string source)  {
    ifstream flux;
    flux.open(source);

    string data;
    flux >> data;

    int sizeL;
    int sizel;
    flux >> sizeL;
    flux >> sizel;
    
    int car;
    string v;
    //cout << "debut" << endl;
    for (int L = 0 ; L < sizeL ; L++ ){
        for ( int l = 0 ; l < sizel ; l++){
        //cout << "tourne" << endl;
        flux >> car;
        if (car == 0) v = ' ';
        else if (car == 1) v = '@';
        cout << ' ' << v;
        }
        cout << endl;
    }

    flux.close();
    //cout << "fin" << endl;
}

/** Echange le noir et le blanc dans une image PBM
 * @param source le nom du fichier PBM à lire
 * @param cible le nom du nouveau fichier PMB créé
 **/
void inversePBM(string source, string cible) {
    ifstream f1;
    ofstream f2;

    f1.open(source);
    f2.open(cible);

    //cout << "debut" << endl;
    
    string data;
    f1 >> data;
    f2 << data;

    int val;
    
    for ( int i = 0 ; i < 2 ; i++ ){
        f1 >> val;
        f2 << ' ' << val;
    }
    
    while(f1 >> val){
        //cout << "tourne" << endl;
        f2 << ' ' << (val + 1) % 2;
    }
    f1.close();
    f2.close();
    //cout << "fin" << endl;
}


int main(){
    cout << "Affichage du smiley " << endl;
    affichePBM("./images/smiley.pbm");
    cout << "Fabrication du smiley inversé (vérifiez que le nouveau fichier a été créé dans le dossier pbm/smiley-inverse.pbm" << endl;
    inversePBM("images/smiley.pbm","pbm/smiley-inverse.pbm");
    cout << "Affichage du smiley inversé" << endl;
    affichePBM("./pbm/smiley-inverse.pbm");
    return 0;
}

