#include <stdio.h>
#include <stdlib.h>
#include "typetourelles.h"  
#include "initialisationjeu.h"  
#include "liberationpersonnage.h"  // ennemitué()
#include "typeennemis.h" //kisame()


void score(Jeu* jeu, Etudiant* ennemi){//fonction pour ajouter des points au score lorsque un ennemi est tué
	 switch(ennemi->position){//plus l'ennemi est tué au debut du plateau plus le joueur remporte des points
	 	case 1:
	 		jeu->score+=1;
	 		break;
		case 2:
	 		jeu->score+=2;
	 		break;
	 	case 3:
	 		jeu->score+=4;
	 		break;
	 	case 4:
	 		jeu->score+=8;
	 		break;
	 	case 5:
	 		jeu->score+=16;
	 		break;
	 	case 6:
	 		jeu->score+=32;
	 		break;
	 	case 7:
	 		jeu->score+=64;
	 		break;
	 	case 8:
	 		jeu->score+=128;
	 		break;
	 	case 9:
	 		jeu->score+=256;
	 		break;
	 	case 10:
	 		jeu->score+=512;
	 		break;
	 	case 11:
	 		jeu->score+=1024;
	 		break;
	 	case 12:
	 		jeu->score+=2048;
	 		break;
	 	case 13:
	 		jeu->score+=4096;
	 		break;
	 	case 14:
	 		jeu->score+=8192;
	 		break;
	 	case 15:
	 		jeu->score+=16384;
	 		break; 		
	 		
	}
}


void NarutoKakashi(Jeu* jeu, Tourelle* tourelle, int degats){
	if(tourelle==NULL) return;//pour eviter des erreurs d'appel de tourelle qui n'existe plus
	Etudiant* ennemi=jeu->etudiants;
	while(ennemi!=NULL){
	
			if(ennemi->ligne==tourelle->ligne && ennemi->tour<jeu->tour+1 && ennemi->prev_line==NULL){//l'ennemi est touché si c'est le premier sur sa ligne 
				
				if(tourelle==NULL) return;//pour éviter des erreurs d'appel de tourelle qui n'existe plus(éviter les erreurs)
				
				if(ennemi->prev_line==NULL || ennemi->prev_line->position!=15){
					if(ennemi->type=='K')//verification si l'ennemi touche est kisame, on appelle la fonction kisame()pour qu'il reduise de moitié les degats sur lui
						Kisame(jeu, ennemi, degats, tourelle);
					
					else ennemi->pointsDeVie-=degats;
					if(ennemi->pointsDeVie<=0){
						score(jeu, ennemi);//augmenter le score 
						Etudiant* mem=ennemi->next;//on memorise le prochain ennemi
						ennemitué(jeu, tourelle, ennemi);
						ennemi=mem;//on associe ennemi->next a ennemi sans ecrire ennemi->next car 'ennemi' a été libéré dans la fonction ennemitué
						if(jeu->tourelles==NULL || tourelle==NULL){//pour eviter les erreurs on verifie que la tourelle n'a pas été tué pendant les attaques
                					printf("la tourelle a ete supprimé pendant l'attaque !\n");
                					return;
              					}
						
					}
					else ennemi=ennemi->next;
				}
			
				
			}
			else ennemi=ennemi->next;
	}
}

void attaqueSasuke(Jeu* jeu, Tourelle* tourelle) {
   
    Etudiant* ennemi=jeu->etudiants;

    while (ennemi!=NULL && tourelle!=NULL) {

    
        if (tourelle->ligne==ennemi->ligne && ennemi->position<=14) { // C'est pr que ennemi s'affiche en 15e position
        	if(ennemi->type=='K')
        		Kisame(jeu, ennemi, 2, tourelle);
            else ennemi->pointsDeVie-=2;
            if (ennemi->pointsDeVie<=0) {//exactement la meme chose que pour NarutoKakashi()
            	score(jeu,ennemi);
            	Etudiant* mem=ennemi->next;
                ennemitué(jeu, tourelle, ennemi);
                ennemi=mem;
                if(jeu->tourelles==NULL || tourelle==NULL){
                	printf("la tourelle a ete supprimé pendant l'attaque !\n");
                	return;
                }
            } 
            else 
               	ennemi=ennemi->next;
            
        } 
        
        else ennemi=ennemi->next;
    }
}


void attaqueShikamaru(Jeu* jeu, Tourelle* tourelle) {  //tourelle qui immobilise les ennemis de sa ligne un tour sur deux
    Etudiant* ennemi=jeu->etudiants;
	while (ennemi!=NULL) {
		if(jeu->tour%2!=0){
        	if (ennemi->ligne==tourelle->ligne) {
        		ennemi->vitesse=0; // Immobilisé
        	}
        }
    	else ennemi->vitesse=ennemivitesse(ennemi);//appel de la fonction ennemivitesse pour retablir la vitesse à chaque ennemi lorsque c'est le tour où ils peuvent avancer
        
      	ennemi = ennemi->next;
	}
}

void soinSakura(Jeu* jeu, Tourelle* tourelle) {// tourelle qui peut soigner les tourelles situées une position avant ou une position après(sur la même ligjne)
    
    Tourelle* autreTourelle=jeu->tourelles;
    while (autreTourelle!=NULL) {
        if (autreTourelle->ligne==tourelle->ligne && (autreTourelle->position==tourelle->position-1 || autreTourelle->position==tourelle->position+1)) {
            if (autreTourelle->pointDeVie<10) {  // soigner uniquement si les PV sont inférieurs à 10
                autreTourelle->pointDeVie += 2;
                if (autreTourelle->pointDeVie>10) {  // limite les PV à 10
                    autreTourelle->pointDeVie=10;// on ramene les pv de la tourelle à 10 (le max)
                }
                
            } 
            else {
                printf("La tourelle en (%d, %d) est déjà à pleine santé.\n",
                       autreTourelle->ligne, autreTourelle->position);
            }
        }
        autreTourelle=autreTourelle->next;
    }
}

