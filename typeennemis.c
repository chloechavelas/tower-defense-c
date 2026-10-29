#include <stdio.h>
#include <stdlib.h>
#include "typeennemis.h"  
#include "initialisationjeu.h"  
#include "liberationpersonnage.h"  // Pour tourelletuée()


int ennemivitesse(Etudiant* ennemi){ // fonction qui sert a retrouver la vitesse des ennemis (sert dans la fonction shikamaru(un tour sur deux) et pour retablir la vitesse lorsque la tourelle meurt)
	switch(ennemi->type){
			case 'Z'://Zetsu
				ennemi->vitesse=1;
				break;
			case 'O'://Ochimaru
				ennemi->vitesse=1;
				break;
			case 'D'://Deidara
				ennemi->vitesse=2;
				break;
			case 'H'://Hidan
				ennemi->vitesse=1;
				break;
			case 'S'://Sasori
				ennemi->vitesse=1;
				break;
			case 'K':
				ennemi->vitesse=1;
			case 'M'://Madara Uchiha
				ennemi->vitesse=1;
				break;
		
		}
		
	return ennemi->vitesse;
}







void Zetsu(Jeu* jeu, Etudiant* zetsu){//ennemi de base 
	
	Tourelle* tourelle=jeu->tourelles;
	while(tourelle!=NULL){
		if (tourelle->ligne==zetsu->ligne && tourelle->position==zetsu->position-1){
			tourelle->pointDeVie-=1;
			if(tourelle->pointDeVie<=0){
				if(tourelle->type=='H'){
					zetsu->vitesse=ennemivitesse(zetsu);// on retablit la vitesse a l'ennemi en tete sur sa ligne
					Etudiant* e=jeu->etudiants;// on va rétablir la vitesse a tous les ennemis de la ligne
					while(e!=NULL){ 
						if(e->ligne==zetsu->ligne)
							e->vitesse=ennemivitesse(e);
						e=e->next;
					}
				}
				Tourelle* mem=tourelle->next;
				tourelletuée(jeu,tourelle);
				tourelle=mem;
			}
			else tourelle=tourelle->next;
		}

		
		else tourelle=tourelle->next;
	}
}


void Orochimaru(Jeu* jeu, Etudiant* orochimaru){
	Tourelle* tourelle= jeu->tourelles;
	while(tourelle!=NULL){
		if(tourelle->position==orochimaru->position-1 && tourelle->ligne==orochimaru->ligne){//comme zetsu
			tourelle->pointDeVie-=2;

		}
		else{//ennemi qui peut toucher des tourelles sur la même position une ligne au dessus et en dessous
			if (orochimaru->ligne==1){
				if(tourelle->ligne==orochimaru->ligne+1 && tourelle->position==orochimaru->position){
					tourelle->pointDeVie-=2;
				}
			}
			else if(orochimaru->ligne==7){
				if(tourelle->ligne==orochimaru->ligne-1 && tourelle->position==orochimaru->position){
					tourelle->pointDeVie-=2;
				}
			}
			else{
				if(orochimaru->position==tourelle->position && (orochimaru->ligne-1==tourelle->ligne||orochimaru->ligne+1==tourelle->ligne)){
					tourelle->pointDeVie-=2;
				}
			}
		}
		
		if(tourelle->pointDeVie<=0){
			if(tourelle->type=='H'){
				orochimaru->vitesse=ennemivitesse(orochimaru);// on retablit la vitesse a l'ennemi en tete sur sa ligne
				Etudiant* e=jeu->etudiants;// on va rétablir la vitesse à tous les ennemis de la ligne
				while(e!=NULL){ 
					if(e->ligne==orochimaru->ligne)
						e->vitesse=ennemivitesse(e);
					e=e->next;
				}
			}
			Tourelle* mem=tourelle->next;
			tourelletuée(jeu, tourelle);
			tourelle=mem;
		}
		
		else tourelle=tourelle->next;	
		
		
		
	}
	
}


void DeidaraExplosion(Jeu* jeu, Tourelle* tourelle, Etudiant* deidara){
	if (tourelle==NULL) return;//on verifie que la tourelle qui a attaqué deidara n'est pas morte pendant l'attaque
	tourelle->pointDeVie-=4;
	if (tourelle->pointDeVie<=0){
		if(tourelle->type=='H'){
			Etudiant* e=jeu->etudiants;// on va rétablir la vitesse a tous les ennemis de la ligne
			while(e!=NULL){ 
				if(e->ligne==deidara->ligne)
					e->vitesse=ennemivitesse(e);
				e=e->next;
			}
		}
		
		tourelletuée(jeu, tourelle);

	}
}


void Hidan(Jeu* jeu, Etudiant* hidan){//ennemi qui gagne 2 pv en attaquant une tourelle
	Tourelle* tourelle=jeu->tourelles;
	while(tourelle!=NULL){
		if(tourelle->position==hidan->position-1 && tourelle->ligne==hidan->ligne){
			hidan->pointsDeVie+=2;
			tourelle->pointDeVie-=1;
			if (tourelle->pointDeVie<=0){
				if(tourelle->type=='H')
					hidan->vitesse=ennemivitesse(hidan);
				Tourelle* mem=tourelle->next;
				tourelletuée(jeu, tourelle);
				tourelle=mem;
				
			}
			else tourelle=tourelle->next;
		}
		else tourelle=tourelle->next;		
	}

}


void Kisame(Jeu* jeu, Etudiant* kisame, int degats,Tourelle* tourelle){//ennemi avec beaucoup de pv, difficile à abattre 
	kisame->pointsDeVie-=degats/2;//réduis les degats qui reçoient par deux
	if (tourelle->ligne==kisame->ligne && tourelle->position==kisame->position-1){
		tourelle->pointDeVie-=1;
		if(tourelle->pointDeVie<=0){
			if(tourelle->type=='H'){
				Etudiant* e=jeu->etudiants;
				while(e!=NULL){
					if(e->ligne==kisame->ligne)
						e->vitesse=ennemivitesse(e);
					e=e->next;
				}
			}
			tourelletuée(jeu,tourelle);
		}
	}
						
}