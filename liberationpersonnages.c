#include <stdio.h>
#include <stdlib.h>

#include "liberationpersonnage.h"  
#include "initialisationjeu.h"
#include "typeennemis.h" //deidarexplosion()

void tourelletuée(Jeu* jeu, Tourelle* tourelle){

	// verif si la tourelle est la premiere de la liste
	if(tourelle==jeu->tourelles)
		jeu->tourelles=tourelle->next;
		
	else{
		Tourelle* avant=jeu->tourelles;//on cherche le prev de la tourelle
		while( avant && avant->next != tourelle ){
			avant=avant->next;
		}
		if(tourelle->next && tourelle==avant->next)
			avant->next=tourelle->next;
		else avant->next=NULL;
	}
	
	free(tourelle);//on peut liberer la tourelle car on a bien gerer le chainage 
		
}


void ennemitué(Jeu* jeu,Tourelle* tourelle, Etudiant* ennemi){
	if (ennemi->type=='D')//on met cette condition car c'est lorsque deidara est tué qu'il fait son action(explosion)
		DeidaraExplosion(jeu, tourelle, ennemi);
		
	//verif si l'ennemi est le premier de la liste
	if(ennemi==jeu->etudiants)
		jeu->etudiants=ennemi->next;
	
	else{
		Etudiant* avant=jeu->etudiants;//on cherche le prev de l'ennemi
		while(avant->next!=ennemi){
			avant=avant->next;
		}
		if(ennemi==avant->next)
			avant->next=ennemi->next;
	}
	//on gere ensuite le chainage des ennemis sur la meme ligne afin de pouvoir liberer l'ennemi tué
	if(ennemi->next_line!=NULL)
		ennemi->next_line->prev_line=ennemi->prev_line;
		
	if(ennemi->prev_line!=NULL)
		ennemi->prev_line->next_line=ennemi->next_line;
	 
	free(ennemi);//on peut libérer l'ennemi car on a bien gerer le chainage principale et celui des lignes

}


void liberationtourelles(Jeu* jeu) {//foncion qui libere les tourelles a la fin du jeu
    if (jeu==NULL || jeu->tourelles==NULL) {
        return;  //Évite un crash si la liste est déjà vide
    }

    Tourelle* t = jeu->tourelles;
    while (t != NULL) {  //libere chaque tourelle encore en vie  
        Tourelle* mem = t;
        t = t->next;
        free(mem);
    }

    jeu->tourelles = NULL;  // pour éviter d’accéder à une mémoire déjà libérée(éviter les erreurs)
}



void liberationennemis(Jeu* jeu){
	if(jeu->etudiants==NULL || jeu==NULL)
		return;//évite un crash si la liste des ennemis et déja vide
	Etudiant* ennemis=jeu->etudiants;
	while(ennemis!=NULL){//libère chaque ennemie encore en vie 
		Etudiant* mem=ennemis;
		ennemis=ennemis->next;
		free(mem);
	}
	jeu->etudiants=NULL;
}
