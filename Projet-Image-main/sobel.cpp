#include <stdexcept>
/** @file
 * Filtres de Sobel
 **/
#include <cmath>
#include "sobel.hpp"

ImageGris intensiteH(ImageGris img) {
    auto nligne = vector<double> ( img[0].size() );
    for (int a = 0 ; a < nligne.size() ; a++) nligne[a] = 0;
    auto nimg = ImageGris ( img.size() );
    for ( int b = 0; b < nimg.size() ; b++) nimg[b] = nligne;
    for( int i = 1 ; i < img.size()-1 ; i++ ) for ( int j = 0 ; j < img[i].size()-1 ; j++)
        if (j!=0) nimg[i][j] = img[i-1][j-1] + 2*img[i][j-1] +
            img[i+1][j-1]- img[i-1][j+1] - 2*img[i][j+1] - img[i+1][j+1];
    return nimg;
}

ImageGris intensiteV(ImageGris img) {
    auto nligne = vector<double> ( img[0].size() );
    for (int a = 0 ; a < nligne.size() ; a++) nligne[a] = 0;
    auto nimg = ImageGris ( img.size() );
    for ( int b = 0; b < nimg.size() ; b++) nimg[b] = nligne;
    for( int i = 1 ; i < img.size()-1 ; i++ ) for ( int j = 0 ; j < img[i].size()-1 ; j++)
        if (j!=0) nimg[i][j] = img[i-1][j-1] + 2*img[i-1][j] + img[i-1][j+1] - img[i+1][j-1] - 2*img[i+1][j] - img[i+1][j+1];
    return nimg;
}

ImageGris intensite(ImageGris img) {
    auto nligne = vector<double> ( img[0].size() );
    for (int a = 0 ; a < nligne.size() ; a++) nligne[a] = 0;
    auto nimg = ImageGris ( img.size() );
    for ( int b = 0; b < nimg.size() ; b++) nimg[b] = nligne;
    for( int i = 1 ; i < img.size()-1 ; i++ ) for ( int j = 0 ; j < img[i].size()-1 ; j++)
        if (j!=0){
            double h = img[i-1][j-1] + 2*img[i][j-1] + img[i+1][j-1]- img[i-1][j+1] - 2*img[i][j+1] - img[i+1][j+1];
            double v = img[i-1][j-1] + 2*img[i-1][j] + img[i-1][j+1] - img[i+1][j-1] - 2*img[i+1][j] - img[i+1][j+1];
            nimg[i][j] = sqrt( h*h + v*v );
        }
    return nimg;
}
