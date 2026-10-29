#include <stdio.h>
#include <stdlib.h>
#include "finjeu.h"  
#include "initialisationjeu.h"  
#include "save.h"  // Pour sauvegardescore()
#include "liberationpersonnage.h"  // Pour liberationtourelles(), liberationennemis()


int testjeu(Jeu* jeu){
	if (jeu->etudiants==NULL){
		printf("VICTOIREEE\n");
		return 0;//pour pouvoir arreter la boucle while dans deroulementjeu()
	}
	Etudiant* ennemi=jeu->etudiants;
	while(ennemi!=NULL){
		if(ennemi->position==0){// un ennemi est arrivé dans l'université
			printf("DEFAITE...\n");
			jeu->score=0;
			return 0;
		}	
		ennemi=ennemi->next;
	}
	return 1;//continue le jeu
}


void findujeu(Jeu* jeu){//appelée en fin du jeu pour liberer tout avant de finir le jeu
	if(jeu->score>0)//si jamais la partie est gagné
		sauvegardescore(jeu);
	liberationtourelles(jeu);
	liberationennemis(jeu);
	free(jeu);
	remove("sauvegarde.txt");//on efface le fichier qui sauvegardait le jeu car la partie est terminée
}


void pausedujeu(Jeu* jeu){
	liberationtourelles(jeu);
	liberationennemis(jeu);
	free(jeu);
}

