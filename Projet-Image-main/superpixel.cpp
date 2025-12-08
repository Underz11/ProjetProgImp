#include <stdexcept>
/** @file
 * Filtre Super Pixel
 **/
#include <cmath>
#include "superpixel.hpp"
//La partie rapport se trouve dans superpixel.hpp
double distancePoints(Point p, Point c) {
    double somme = 0;
    //Formule de la distance Euclidienne, c'est à dire sqrt(Σ(pi-ci)^2)
    for (int i = 0; i < p.size(); i++) {
        somme += (p[i]-c[i])*(p[i]-c[i]);
    }
    return sqrt(somme);
}

double distanceAEnsemble(Point p, EnsemblePoints C) {
    //On initialise le minimum avec la distance entre p et le premier point de C
    double minDist = distancePoints(p, C[0]);
    //On regarde chaque point de C, et on regarde si la distance entre ce point et p est inférieur au minimum, si c'est le cas, cette distance devient le nouveau minimum et ainsi de suite.
    for (auto point:C) {
        double current_distance = distancePoints(p, point); 
        if ( current_distance < minDist) minDist = current_distance;
    }
    //On renvoie la valeur du minimum qu'on a déterminé
    return minDist;
}

int plusProcheVoisin(Point p, EnsemblePoints C) {
    //On calcul la distance minimum qui sera utilisée pour déterminer à quel point correspond cette distance. 
    double distProche = distanceAEnsemble(p, C);
    //On parcourt chaque point de l'ensemble C en vérifiant si la distance entre p et ce point correspond à la distance minimum en prenant compte des imprécisions, si tel est le cas, on renvoit l'indice du point.
    for (int i = 0; i < C.size(); i++) {
        if (abs(distancePoints(p, C[i]) - distProche) < 0.0001 ) return i;
    }
}

EnsemblePoints sousEnsemble(EnsemblePoints P,EnsemblePoints C,int k) {
    //On crée un nouvel ensemble de points
    EnsemblePoints newEnsemble = {};
    //On parcourt les points de P, et on ajoute à l'ensemble créé précédemment les points de P tel que C[k] soit leur plus proche voisin dans C.
    for (auto p:P) {
        if (plusProcheVoisin(p, C) == k) newEnsemble.push_back(p);
        
    }
    //On renvoie l'ensemble créé.
    return newEnsemble;
}

Point barycentre(EnsemblePoints Q) {
    //On initialise le barycentre
    Point barycntre = {};
    //On applique la formule du barycentre, pour cela on fait la moyenne des x des points de Q pour avoir le x du barycentre, et ainsi de suite pour chaque paramètre des points de l'ensemble 
    for (int i = 0; i < Q[0].size(); i++) {
        double somme = 0;
        for (int j = 0; j < Q.size(); j++) {
            somme += Q[j][i];
        }
        barycntre.push_back(somme/Q.size());
    }
    //On renvoie le barycentre obtenue
    return barycntre;
    
}

EnsemblePoints KMoyenne(EnsemblePoints P,EnsemblePoints C, int nbAmeliorations) {
    //Pour chaque point pilote de l'ensemble C, on crée le sousEnsemble des points de P associé et on remplace ce point par le barycentre de l'ensemble obtenu. On répète l'opération autant de fois que le nombre d'amélioration spécifié.
    for (int i = 0; i < nbAmeliorations; i++) {
        for (int k = 0; k < C.size(); k++) {
            EnsemblePoints newEnsemble = sousEnsemble(P, C, k);
            C[k] = barycentre(newEnsemble);
        }
        
    }
    //On renvoie la liste finale des points pilotes.
    return C;
}

EnsemblePoints FAST_KMoyenne(EnsemblePoints P,EnsemblePoints C, int nbAmeliorations) {
    vector<int> label;
    label.resize(P.size());
    for(int n=0; n<nbAmeliorations; n++) {
        vector<int> clusterSize;
        clusterSize.resize(C.size(),0);
        for (int p=((int)P.size())-1; p>=0; p--) {
            double di = 0;
            int nn=0;
            for(int d=((int)P[0].size())-1; d>=0; d--)
                di+=(P[p][d]-C[0][d])*(P[p][d]-C[0][d]);
            for(int c=((int)C.size())-1; c>=1; c--) {
                double dt=0;
                for(int d=((int)P[0].size())-1; d>=0; d--)
                    dt+=(P[p][d]-C[c][d])*(P[p][d]-C[c][d]);
                if(dt<di) {
                    di=dt;
                    nn=c;
                }
            }
            label[p]=nn;
            clusterSize[nn]++;
        }
        for (int p=((int)P.size())-1; p>=0; p--)
            for(int d=((int)P[0].size())-1; d>=0; d--)
                C[label[p]][d]+=P[p][d];
        for(int c=((int)C.size())-1; c>=0; c--)
            if(clusterSize[c]!=0)
                for(int d=((int)P[0].size())-1; d>=0; d--)
                    C[c][d] = C[c][d]/(clusterSize[c]+1);
    }
    return C;
}

EnsemblePoints pivotSuperPixel(Image img, double lambda, int mu) {
    //On initialise la liste des points pivots
    EnsemblePoints listePivot = {};
    //On parcourt les points de l'image en incrémentant de mu en mu pour obtenir la position des points pivots, on ajoute ensuite les points pivots à la liste définie précédemment à partir de leur position, ainsi que de la couleur de l'image à la position en multipliant par le paramètre lambda
    for (int i = 0; i < img.size(); i += mu) {
        for (int j = 0; j < img[i].size(); j += mu) {
            listePivot.push_back({j,i,lambda*img[i][j].r,lambda*img[i][j].g,lambda*img[i][j].b});
        }
    }
    //On renvoie la liste des points pivots.
    return listePivot;
}

EnsemblePoints superPixels(Image img,double lambda, int mu, int nbAmeliorations) {
   //On initialise la liste des points pivots 
   EnsemblePoints pivot = pivotSuperPixel(img, lambda,mu);
    //On convertit chaque pixel de l'image en un point
   EnsemblePoints image = {};
   for (int i = 0; i < img.size(); i ++) {
       for (int j = 0; j < img[i].size(); j ++) {
           image.push_back({j,i,lambda*img[i][j].r,lambda*img[i][j].g,lambda*img[i][j].b});
       }
   }
    //On renvoie l'ensemble obtenue à partir de la K-Moyenne de l'image et de ses points pivots améliorée nbAmeliorations fois.
   return FAST_KMoyenne(image, pivot, nbAmeliorations);
    
}
Image superPixel(Image img, double lambda, int mu, int nbAmeliorations) {
    //On construit l'ensemble des superPixels de l'image
    EnsemblePoints sPixels = superPixels(img, lambda, mu, nbAmeliorations);
    //On parcourt les points de l'images, pour chaque point on cherche quel est le superpixel le plus proche, et on attribue la couleur du superpixel correspondant à ce point en la redivisant par lambda pour obtenir la couleur réelle.
    for (int i = 0; i < img.size(); i ++) {
       for (int j = 0; j < img[i].size(); j ++) {
          Point point_img = {j,i,lambda*img[i][j].r,lambda*img[i][j].g,lambda*img[i][j].b};
           int indiceSuperPixel = plusProcheVoisin(point_img, sPixels);
           img[i][j] = {sPixels[indiceSuperPixel][2]/lambda,sPixels[indiceSuperPixel][3]/lambda,sPixels[indiceSuperPixel][4]/lambda };

   }
    
    
    
}
    //On renvoie l'image obtenue
    return img;
}



// Ecrire votre code ici
Image superPixelAvecBleu(Image img) {
    //On crée une copie de l'image pour éviter d'avoir une image entièrement bleu.
    Image copie = img;
    //On parcourt l'image, on vérifie que le pixel n'est pas au bord de l'image, puis on regarde les pixels voisins en bas, en haut, à droite, et à gauche, si l'un d'entre eux est différent, on change la couleur du pixel correspondant dans copie en bleu
    for (int i = 0; i < img.size(); i++) {
        for (int j = 0; j < img[i].size(); j++) {
            if (i > 0 && j > 0 && i < img.size() - 1 && j < img[i].size() - 1) {
                if ((img[i-1][j].r != img[i][j].r || img[i+1][j].r != img[i][j].r || img[i][j-1].r != img[i][j].r || img[i][j+1].r != img[i][j].r)|| (img[i-1][j].g != img[i][j].g || img[i+1][j].g != img[i][j].g || img[i][j-1].g != img[i][j].g || img[i][j+1].g != img[i][j].g) || (img[i-1][j].b != img[i][j].b || img[i+1][j].b != img[i][j].b || img[i][j-1].b != img[i][j].b || img[i][j+1].b != img[i][j].b)) copie[i][j] = {0,0,255};
            }
        }
    }
    //On renvoie la copie de l'image avec les bords bleus.
    return copie;
}

