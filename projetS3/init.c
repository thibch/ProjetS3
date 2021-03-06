#include <SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "init.h"
#include "fonction.h"
#include "creator.h"
#include "constant.h"

SDL_Surface* initialisation_SDL(){
  /* initialise SDL */
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Init(SDL_INIT_AUDIO);
  Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
  TTF_Init();

  SDL_WM_SetCaption("StarBund", "StarBund");

  /* create window */
  SDL_Surface *screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
  /* set keyboard repeat */
  SDL_EnableKeyRepeat(10, 10);

  return screen;
}


void initialisation_Jeu(monde *monde, character *joueur, input *input, monstre tabMon[NBMONSTRE], int freq, atlas *atlasJeu, char* arg1){
  //Creation du joueur, du monde, et des touches claviers et souris
  creer_joueur(joueur);
  creer_monde(monde);
  creer_input(input);

  //On génère le monde avec l'algorithme de perlin si on a pas mis l'argument LOADSAVE
  if(!(arg1 == NULL)){
    if(strcmp(arg1, "LOADSAVE")){
      monde->grilleChar = allouer_tab_2D_char(TMONDE, TMONDE);
      gen_monde(monde, freq);
    }else{
      monde->grilleChar = lire_fichier("saves/MondeTest.txt");
      tab_char2int(monde->grilleChar, monde->grilleInt, TMONDE, TMONDE);
    }
  }else{
    monde->grilleChar = allouer_tab_2D_char(TMONDE, TMONDE);
    gen_monde(monde, freq);
  }



  //apparition du joueur en fonction du monde
  apparition_joueur(joueur, *monde);
  for(int i=0;i<NBMONSTRE;i++){
    //création puis apparition du monstre
    creer_monstre(&tabMon[i], atlasJeu, *monde);
  }
}

void compteur_fps(){
  //Compteur d'images par secondes
  static int actualTime = 0, lastTime = 0;
  actualTime = SDL_GetTicks();
  float dt = (actualTime - lastTime);
  if(dt < 1000.0 / 100.0 ){
    SDL_Delay((1000.0 / 100.0) - dt); //On limite les images par secondes en faisant des pauses entre chaque image
  }
  lastTime = SDL_GetTicks();
}
