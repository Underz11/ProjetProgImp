#include <stdexcept>
/** @file
 * Filtres de conversion couleur <-> teintes de gris
 **/
#include "gris-couleurs.hpp"
//La partie rapport se trouve dans gris-couleurs.hpp
ImageGris CouleurAuGris( Image img ) {
    //On crée une image grise qui a les mêmes dimensions que l'image donnée en argument. C'est cette image qui sera renvoyée à la fin de la fonction
    auto newImgGris = ImageGris(img.size());
    for ( int i = 0 ; i < img.size() ; i++ ) newImgGris[i] = vector<double> (img[0].size()) ;
    //On parcourt l'image et on construit l'image grise en faisant la moyenne pondérée des composantes r/g/b de l'élément correspondant de l'image.
    for (int i = 0; i < img.size(); i++) {
        for (int j=0; j < img[i].size(); j++) {
            newImgGris[i][j] = 0.2126*img[i][j].r + 0.7152*img[i][j].g + 0.0722*img[i][j].b;
        }
    
    }
    //On renvoie l'image grise obtenue.
    return newImgGris;
    
    
}

Image GrisACouleur( ImageGris img ) {
    //On crée une image qui a les mêmes dimensions que l'image grise donnée en argument. C'est cette image qui sera renvoyée à la fin de la fonction
    auto newImgCol = Image(img.size());
    for ( int i = 0 ; i < img.size() ; i++ ) newImgCol[i] = vector<Couleur> (img[0].size());
    //On parcourt l'image grise et à partir de chaque niveau de gris on construit l'image en associant chaque élément de l'image grise avec un niveau de gris c à la couleur {c,c,c}
    for (int i = 0; i < img.size(); i++) {
        for (int j=0; j < img[0].size(); j++) {
            newImgCol[i][j] = Couleur({img[i][j], img[i][j], img[i][j]});
        } 
        
}
    //On renvoie l'image obtenue
    return newImgCol;
}
