#include <stdio.h>
#include <stdlib.h>
#include "initialisationjeu.h"


void debutjeu(Jeu* jeu){//on initialise le jeu au debut avant de rentrer les informations sur la partie
	jeu->tourelles=NULL;
	jeu->etudiants=NULL;
	jeu->cagnotte=0;
	jeu->tour=0;
	jeu->score=0;
	jeu->depense=0;
	jeu->niveau=0;
}





