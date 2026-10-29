#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // Nécessaire pour strcpy()
#include "save.h"  
#include "initialisationjeu.h"  




void sauvegardescore(Jeu* jeu) {
    FILE* scorefichier=NULL;//initialisation du ficher pour le score
    char niveautxt[20]; // Stocke le nom du fichier

    // Déterminer le fichier en fonction du niveau
    switch (jeu->niveau) {//on a un fichier score par niveau
        case 1: 
        	strcpy(niveautxt, "scoreniveau1.txt"); //copie du fichier dans niveautxt
        	break;
        case 2: 
        	strcpy(niveautxt, "scoreniveau2.txt"); 
        	break;
        case 3: 
        	strcpy(niveautxt, "scoreniveau3.txt"); 
        	break;
        case 4: 
        	strcpy(niveautxt, "scoreniveau4.txt"); 
        	break;
        case 5: 
        	strcpy(niveautxt, "scoreniveau5.txt"); 
        	break;
        default:
            printf("Ce niveau est inconnu.\n");
            return;
    }
	
    scorefichier=fopen(niveautxt, "r");
    if(scorefichier==NULL)//on regarde si le fichier pour le score était vide 
        printf("Premiere fois que vous réussissez ce niveau !\n");
    

    Score scores[11]; //on met 11 au depart pour inclure le score du joueur actuel(si jamais il y a deja 10 scores enregistrés)
    int cpt=0;

    // Tout d'abord on va lire les scores deja effectués sur ce niveau
    while (scorefichier!=NULL && fscanf(scorefichier, "%s %d", scores[cpt].nom, &scores[cpt].score)==2 && cpt<10) {
        cpt++;
    }
    if(scorefichier) fclose(scorefichier); // ferme après lecture

    // on demande le nom du joueur
    printf("Entrez votre pseudo :");
    scanf("%29s", scores[cpt].nom); // on limite à 29 caractères

    // ajoute le score du joueur actuel
    scores[cpt].score=jeu->score;
    cpt++;

    // Trier les scores par ordre décroissant
    int i;
    for(i=0; i<cpt-1; i++) {
        for (int j=i+1; j<cpt; j++) {
            if (scores[i].score < scores[j].score) { // on échange l'ordre dans la liste score si le score du joueur est plus haut
                Score mem=scores[i];
                scores[i]=scores[j];
                scores[j]=mem;
            }
        }
    }

    // limite de 10 scores par niveaux
    if(cpt>10) cpt=10;

    // sauvegarde des scores triés
    scorefichier=fopen(niveautxt, "w");
    if(scorefichier==NULL) {//on s'assure que le scorefichier existe bien
        printf("Erreur : impossible d'ouvrir le fichier des scores en écriture.\n");
        return;
    }
    int j;
    for(j=0; j<cpt; j++) {
        fprintf(scorefichier, "%s %d\n", scores[j].nom, scores[j].score);
    }
    fclose(scorefichier);

    printf("Score sauvegardé avec succès !\n");
}




void sauvegarde(Jeu *jeu){
	//on ouvre un fichier
	FILE* partie=fopen("sauvegarde.txt", "w");
	
	//on enregistre le tour 
	fprintf(partie, "%d\n", jeu->tour);
	// on enregsitre les depenses(pas besoin d'enregsitrer la cagnotte car c'est que les depenses qui seront importantes)
	fprintf(partie, "%d\n", jeu->depense);
	//on enregistre le score en cours
	fprintf(partie, "%d\n", jeu->score);
	
	
	// on enregistre le placement des tourelles encore en vie 
 	Tourelle* tourelle=jeu->tourelles;
	while(tourelle!=NULL){
		fprintf(partie," %d %d %d %d\n", tourelle->ligne, tourelle->position, tourelle->pointDeVie, tourelle->type);
		tourelle=tourelle->next;
	}
	fprintf(partie,"8\n");//pour voir qu'on a plus de tourelles et quon peut passer aux ennemis
	
	//on enregitre le placement des ennemis encore en vie:
	Etudiant* ennemi=jeu->etudiants;
	while(ennemi!=NULL){
		fprintf(partie, "%d %d %d %d %d %d\n", ennemi->ligne, ennemi->position, ennemi->pointsDeVie, ennemi->type, ennemi->vitesse, ennemi->tour);
		ennemi=ennemi->next;
	}
	fprintf(partie,"8\n"); //la meme chose que pour les tourelles
	
	
	fclose(partie);
	
}

void chargement(Jeu* jeu){
	printf("debut du chargement\n");
	FILE* partie=fopen("sauvegarde.txt", "r");
	//Tour
	fscanf(partie, "%d", &jeu->tour);
	//Depense
	fscanf(partie, "%d", &jeu->depense);
	//Score
	fscanf(partie,"%d", &jeu->score);
	
	//premiere tourelle enregistrée
	int ligne;
	Tourelle* tourelle=malloc(sizeof(Tourelle));

	while(1){ // On fait une boucle infinie et on sort avec break
    	fscanf(partie, "%d", &ligne);
    
    	if (ligne==8) break; // On sort AVANT d'allouer une nouvelle tourelle

    	tourelle=malloc(sizeof(Tourelle));
    	
    	tourelle->ligne=ligne;
    	fscanf(partie, "%d %d %d", &tourelle->position, &tourelle->pointDeVie, &tourelle->type);
    	
    	tourelle->next=NULL;
	
    	if (jeu->tourelles==NULL) {
       		jeu->tourelles=tourelle;
    	} 
    	else{
        	Tourelle* mem=jeu->tourelles;
        	while (mem->next!=NULL) {
            	mem=mem->next;
        	}
        	mem->next=tourelle;
    	}
    
	}
	

	
	Etudiant* premiersurligne[7]={NULL};//pour le chainage des prev_line et next_line

	
	//premier etudiant enregistré
	Etudiant* ennemi=malloc(sizeof(Etudiant));
	//on fait tout les ennemis et ca sarrete quand on a scan le 8
	while(1){
		fscanf(partie, "%d", &ligne);
		

		if (ligne==8) break; // On sort AVANT d'allouer une nouvelle tourelle
		
		ennemi=malloc(sizeof(Etudiant));
		ennemi->ligne=ligne;
		fscanf(partie, "%d %d %d %d %d", &ennemi->position, &ennemi->pointsDeVie, &ennemi->type, &ennemi->vitesse, &ennemi->tour);
		
		
		//pour le gros chainage des ennemis	
		ennemi->next=NULL;
		if(jeu->etudiants==NULL){
			jeu->etudiants=ennemi;
		}
		else{
			Etudiant* mem=jeu->etudiants;
			while(mem->next!=NULL){
				mem=mem->next;
			}
			mem->next=ennemi;
		}
		
		
		//pour gerer la liste chainée par rapport aux lignes
		
		if(premiersurligne[ennemi->ligne-1]==NULL){
			premiersurligne[ennemi->ligne-1]=ennemi;
		}
		else{//sinon on parcourt la liste pour atteindre le dernier etudiant sur la ligne
			Etudiant* test2=premiersurligne[ennemi->ligne-1];//premier ennemi de la ligne
			while(test2->next_line!=NULL){
				test2=test2->next_line;
			}
			test2->next_line=ennemi;//nouveau ennemi lié avec le dernier de la ligne
			ennemi->prev_line=test2;
		}
		
		
				
	}
	
	printf("chargement terminé");
	fclose(partie);
}

