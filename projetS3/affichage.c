#include <SDL.h>
#include <SDL/SDL_ttf.h>
#include "fonction.h"
#include "creator.h"

void affichage_monde(monde monde, character joueur1, atlas* atlasJeu, SDL_Surface *screen){
  int xAffichageStart = joueur1.xMonde/TAILLE_BLOCS;
  int yAffichageStart = TMONDE - joueur1.yMonde/TAILLE_BLOCS - NBBLOCS_FENETREY;
  int decalageX = -joueur1.xMonde%TAILLE_BLOCS;
  int decalageY = joueur1.yMonde%TAILLE_BLOCS;
  int i = 0;
  int j = 0;
  for(i=0;i<NBBLOCS_FENETREY;i++ )
    {
      for(j=0;j<NBBLOCS_FENETREX;j++)
	{
	  monde.affichage[i][j] = monde.grilleInt[i+yAffichageStart][j+xAffichageStart];
	  monde.posB[i][j] = TAILLE_BLOCS*(j+xAffichageStart);
	  monde.posBY[i][j] = TAILLE_BLOCS*(joueur1.yMonde/TAILLE_BLOCS + NB_BLOCS_AU_DESSUS_JOUEUR - i);
	  SDL_Rect posGrille;
	  posGrille.x = j*TAILLE_BLOCS + decalageX;
	  posGrille.y = i*TAILLE_BLOCS + decalageY;
	  if(monde.affichage[i][j] == TOPARB){
		posGrille.x = j*TAILLE_BLOCS + decalageX - 33;
		posGrille.y = i*TAILLE_BLOCS + decalageY - 64;
	    SDL_BlitSurface(atlasJeu->tabIm[TOPARBIM]->surface, NULL, screen, &posGrille);
	  }else if(monde.affichage[i][j] == TERRE){
	    SDL_BlitSurface(atlasJeu->tabIm[TERREIM]->surface, NULL, screen, &posGrille);
	  }else if(monde.affichage[i][j] == CASQUE){
	    if(monde.affichage[i-(i>0)][j] == FONDGROTTE){
	      SDL_BlitSurface(atlasJeu->tabIm[FONDGROTTEIM]->surface, &atlasJeu->tabIm[FONDGROTTEIM]->anim, screen, &posGrille);
	      posGrille.x += TAILLE_BLOCS;
	      SDL_BlitSurface(atlasJeu->tabIm[FONDGROTTEIM]->surface, &atlasJeu->tabIm[FONDGROTTEIM]->anim, screen, &posGrille);
	      posGrille.x -= TAILLE_BLOCS;
	    }
	    posGrille.y = i*TAILLE_BLOCS + decalageY - 7;
	    SDL_BlitSurface(atlasJeu->tabIm[CASQUEIM]->surface, NULL, screen, &posGrille);
	  }else if(monde.affichage[i][j] == ARMURE){
	    if(monde.affichage[i-(i>0)][j] == FONDGROTTE){
	      SDL_BlitSurface(atlasJeu->tabIm[FONDGROTTEIM]->surface, &atlasJeu->tabIm[FONDGROTTEIM]->anim, screen, &posGrille);
	      posGrille.x += TAILLE_BLOCS;
	      SDL_BlitSurface(atlasJeu->tabIm[FONDGROTTEIM]->surface, &atlasJeu->tabIm[FONDGROTTEIM]->anim, screen, &posGrille);
	      posGrille.x -= TAILLE_BLOCS;
	    }
	    posGrille.y = i*TAILLE_BLOCS + decalageY - 7;
	    SDL_BlitSurface(atlasJeu->tabIm[ARMUREIM]->surface, NULL, screen, &posGrille);
	  }else if(monde.affichage[i][j] == ARBRE){
	    SDL_BlitSurface(atlasJeu->tabIm[TRONCIM]->surface, NULL, screen, &posGrille);
	  }else if(monde.affichage[i][j] == ABG){
	    SDL_BlitSurface(atlasJeu->tabIm[ABGIM]->surface, NULL, screen, &posGrille);
	  }else if(monde.affichage[i][j] == ABD){
	    SDL_BlitSurface(atlasJeu->tabIm[ABDIM]->surface, NULL, screen, &posGrille);
	  }else if(monde.affichage[i][j] == BASARB){
	    SDL_BlitSurface(atlasJeu->tabIm[BASARBIM]->surface, NULL, screen, &posGrille);
	  }else if(monde.affichage[i][j] == FONDGROTTE  && monde.affichage[i][j-(int)(j>0)] != ARMURE && monde.affichage[i][j-(int)(j>0)] != CASQUE){
	    SDL_BlitSurface(atlasJeu->tabIm[FONDGROTTEIM]->surface,&atlasJeu->tabIm[FONDGROTTEIM]->anim, screen, &posGrille);
	  }
	}
  }
}

void affichage_items_inv(input input, atlas* atlasJeu, SDL_Surface *screen){
  if(input.data.numItemInvX != -1 && input.data.rien == 0)
    {
      if(input.data.typeMemoire == 1)
	{
	  SDL_BlitSurface(atlasJeu->tabIm[CASQUEIM]->surface, NULL, screen, &input.data.posImage);
	}
      else if(input.data.typeMemoire == 2)
	{
	  SDL_BlitSurface(atlasJeu->tabIm[ARMUREIM]->surface, NULL, screen, &input.data.posImage);
	}
      else if(input.data.typeMemoire == 3){
	  SDL_BlitSurface(atlasJeu->tabIm[TERREIM]->surface, NULL, screen, &input.data.posImage);
      }
    }
}

void affichage_personnage(character joueur1, atlas* atlasJeu, SDL_Surface *screen){
  if(joueur1.dir == 2)
    {
      SDL_BlitSurface(atlasJeu->tabIm[JOUEURDIM]->surface,&atlasJeu->tabIm[JOUEURDIM]->anim, screen, &joueur1.pos);
    }
  else if(joueur1.dir == 1)
    {
      SDL_BlitSurface(atlasJeu->tabIm[JOUEURIM]->surface, &atlasJeu->tabIm[JOUEURIM]->anim, screen, &joueur1.pos);
    }
}

void affichage_vie_personnage(character *a, atlas* atlasJeu, SDL_Surface *screen){
  int i;
  if(a->PV%10 == 0){
   for(i = 0; i < a->PV/10; i++){
    setPosX(atlasJeu->tabIm[VIEENTIM],i*30 + 1);
    setPosY(atlasJeu->tabIm[VIEENTIM], 2);
    SDL_BlitSurface(atlasJeu->tabIm[VIEENTIM]->surface, NULL, screen, &atlasJeu->tabIm[VIEENTIM]->pos);
   }
    for(i = a->PV/10; i < 10;i++){
     setPosX(atlasJeu->tabIm[NOVIEIM],i*30 + 1);
     setPosY(atlasJeu->tabIm[NOVIEIM], 2);
     SDL_BlitSurface(atlasJeu->tabIm[NOVIEIM]->surface, NULL, screen, &atlasJeu->tabIm[NOVIEIM]->pos);
    }
  }
  if(a->PV%5 == 0 && a->PV%10 != 0){
    for(i = 0;i<= (a->PV - 5)/10;i++){
      setPosX(atlasJeu->tabIm[VIEENTIM], i*30 + 1);
      setPosY(atlasJeu->tabIm[VIEENTIM], 2);
      SDL_BlitSurface(atlasJeu->tabIm[VIEENTIM]->surface, NULL, screen, &atlasJeu->tabIm[VIEENTIM]->pos);
    }
    SDL_BlitSurface(atlasJeu->tabIm[MIVIEIM]->surface, NULL, screen, &atlasJeu->tabIm[VIEENTIM]->pos);
    for(i = (a->PV + 5)/10; i < 10;i++){
      setPosX(atlasJeu->tabIm[MIVIEIM],i*30 + 1);
      setPosY(atlasJeu->tabIm[MIVIEIM], 2);
      SDL_BlitSurface(atlasJeu->tabIm[NOVIEIM]->surface, NULL, screen, &atlasJeu->tabIm[MIVIEIM]->pos);
    }
  }
}

void affichage_barre_inv (input *input,int *choixAct, atlas* atlasJeu, SDL_Surface *screen){
	int i;
	SDL_Rect posBarInv;
	SDL_Rect posBarItInv;
	SDL_Rect ActInv;
	SDL_Rect posTexte;
	SDL_Surface *nomItem;
	TTF_Font *police = NULL;
	police = TTF_OpenFont("Polices/angelina.ttf", 35);
	SDL_Color couleurNoire = {0, 0, 0};
	for(i=0;i<10;i++){
	posBarInv.x = 2 + (31*i);
	posBarInv.y = 33;
	SDL_BlitSurface(atlasJeu->tabIm[INVIMIM]->surface, NULL, screen, &posBarInv);
	posBarItInv.x = 2 + (31 * i) + 2;
	posBarItInv.y = 37;
		  if(input->data.inv[0][i].type == 1)
		    {
		      SDL_BlitSurface(atlasJeu->tabIm[CASQUEIM]->surface, NULL, screen, &posBarItInv);
		    }
		  else if(input->data.inv[0][i].type == 2)
		    {
		      SDL_BlitSurface(atlasJeu->tabIm[ARMUREIM]->surface, NULL, screen, &posBarItInv);
		    }
		  else if(input->data.inv[0][i].type == 3){
		    SDL_BlitSurface(atlasJeu->tabIm[TERREIM]->surface, NULL, screen, &posBarItInv);
		  }
	}
	if(input->data.e == 0){
	  	ActInv.x = ((input->data.clavier - 1)*31) + 2;
		ActInv.y = 33;
		posTexte.x = ((input->data.clavier - 1)*31) + 2;
		posTexte.y = 64;
		nomItem = TTF_RenderText_Solid (police,input->data.inv[0][input->data.clavier-1].nomItem, couleurNoire);
		*choixAct = input->data.inv[0][input->data.clavier-1].type;
		SDL_BlitSurface(nomItem, NULL, screen, &posTexte);
		SDL_BlitSurface(atlasJeu->tabIm[ACTUELINVIM]->surface, NULL, screen, &ActInv);
	}
	TTF_CloseFont(police);
}

void affichage_crack(monde *monde, int *incAnim, atlas* atlasJeu, int minaX, int minaY, character *a, SDL_Surface *screen) {
  int StartFen = TMONDE - a->yMonde/TAILLE_BLOCS - NBBLOCS_FENETREY;
  setPosX(atlasJeu->tabIm[CRACKIM], minaX*TAILLE_BLOCS - a->xMonde);
  setPosY(atlasJeu->tabIm[CRACKIM], (minaY - StartFen)*16 - 2);
  if(*incAnim > 15 && *incAnim < 30){
    setAnimY(atlasJeu->tabIm[CRACKIM], 15);
    SDL_BlitSurface(atlasJeu->tabIm[CRACKIM]->surface, &atlasJeu->tabIm[CRACKIM]->anim, screen, &atlasJeu->tabIm[CRACKIM]->pos);
  }
  else if(*incAnim > 30 && *incAnim < 45){
    setAnimY(atlasJeu->tabIm[CRACKIM], 30);
    SDL_BlitSurface(atlasJeu->tabIm[CRACKIM]->surface, &atlasJeu->tabIm[CRACKIM]->anim, screen, &atlasJeu->tabIm[CRACKIM]->pos);
  }
  else if(*incAnim >= 45 && *incAnim < 60){
    setAnimY(atlasJeu->tabIm[CRACKIM], 45);
    SDL_BlitSurface(atlasJeu->tabIm[CRACKIM]->surface, &atlasJeu->tabIm[CRACKIM]->anim, screen, &atlasJeu->tabIm[CRACKIM]->pos);
  }
}

void affichage_monstre(monstre *monstre, atlas* atlasJeu, SDL_Surface *screen, character joueur){
  if(monstre->x > joueur.xMonde && monstre->x < joueur.xMonde + SCREEN_WIDTH && monstre->y > joueur.yMonde && monstre->y < joueur.yMonde + SCREEN_HEIGHT){
    setPosX(atlasJeu->tabIm[SLIMEIM], monstre->x - joueur.xMonde);
    setPosY(atlasJeu->tabIm[SLIMEIM], NBBLOCS_FENETREY*TAILLE_BLOCS - (monstre->y - joueur.yMonde));
    SDL_BlitSurface(atlasJeu->tabIm[SLIMEIM]->surface, &atlasJeu->tabIm[SLIMEIM]->anim, screen, &atlasJeu->tabIm[SLIMEIM]->pos);
  }
}
