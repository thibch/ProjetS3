#include <SDL.h>
#include "fonction.h"
#include <math.h>
#include "constant.h"

void calc_vie_tombe(character *a, int *yMomTomDeb, int *faitCalc, int *touche){
  int degatChute = 0;
  if(a->yMonde <= *yMomTomDeb - DISTCHUTEMPV && *touche == 1){
  	degatChute = (int)(0.08*(*yMomTomDeb - a->yMonde));
  	*yMomTomDeb = -1000;
  }
  if(degatChute%10 != 0 && degatChute%5 != 0){
    int vers10;
    int vers5;
    int valeur = degatChute;
    vers10 = valeur;
    vers5 = valeur;
    while((vers10%10 != 0 || vers10%5 != 0) && (vers5%10 != 0 || vers5%5 != 0)){
      vers10 += 1;
      vers5 -= 1;
    }
    if(vers10%10 == 0 || vers10%5 == 0){
     degatChute = vers10;
    }else{
     degatChute = vers5;
    }
  }
  if(a->PV > 0){
    a->PV -= degatChute;
  }
  if(a->PV < 0){
   a->PV = 0;
  }
  *faitCalc = 1;
}
