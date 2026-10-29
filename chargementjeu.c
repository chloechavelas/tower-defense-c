#include <stdio.h>
#include <stdlib.h>

#include "chargementjeu.h"  


int chargerNiveau(Jeu* jeu, char* nomfichier){
	FILE* fichier=fopen(nomfichier,"r");
	if(fichier==NULL){
		printf("Erreur dans le chargement du fichier %s.(chargerNiveau)\n", nomfichier);
		return 0;
	}
		
	fscanf(fichier,"%d",&jeu->cagnotte); //enregistre le montant de l'argent que dispose le joueur pour se defendre 
	
	int numtour;
	int numligne;
	char typevilain;
	
	Etudiant* premiersurligne[7]={NULL};

	while(fscanf(fichier,"%d %d %c", &numtour, &numligne, &typevilain)==3){// condition pour verifier quand est ce qu'on a chargé tous les ennemis
		Etudiant* ennemi=malloc(sizeof(Etudiant));
		if(ennemi==NULL){
			printf("Erreur dans l'allocation memoire de l'ennemi. (chargerNiveau)\n");
			fclose(fichier);
			return 0;
		}
		ennemi->type=typevilain;
		ennemi->ligne=numligne;
		ennemi->position=15; //fin du plateau est le placement initial des etudiants jusqu'à ce qu'ils entrent dans la partie(donc s'affiche en position 15)
		ennemi->tour=numtour;
		ennemi->next=NULL;
		ennemi->next_line=NULL;
		ennemi->prev_line=NULL;
		
		// pour la liste chainée principale
		if(jeu->etudiants==NULL)
			jeu->etudiants=ennemi;//si c'est le premier ennemi enregistré
		
		else{//sinon on parcourt la liste pour atteindre le dernier ennemi
			
			Etudiant* test1=jeu->etudiants;
			while(test1->next!=NULL){
				test1=test1->next;
			}
			test1->next=ennemi;
		}
		
		
		//pour gerer la deuxieme liste chainée des etudiants, celle par rapport aux lignes(prev_line, next_line)
		if(premiersurligne[numligne-1]==NULL){// si il n'y a rien dans la case d'indice etudiant->ligne-1, cela veut dire que c'est le premier sur sa ligne
			premiersurligne[numligne-1]=ennemi;
		}
		else{//sinon on parcourt la liste pour atteindre le dernier etudiant sur la ligne
			Etudiant* test2=premiersurligne[numligne-1];//premier ennemi de la ligne
			while(test2->next_line!=NULL){
				test2=test2->next_line;
			}
			test2->next_line=ennemi;//nouvel ennemi lié avec le dernier de la ligne
			ennemi->prev_line=test2;
		}
		
		//pv et vitesse en/ fonction des differents ennemis
		switch(typevilain){
			case 'Z'://Zetsu
				ennemi->pointsDeVie=5;
				ennemi->vitesse=1;
				break;
			case 'O'://Ochimaru
				ennemi->pointsDeVie=10;
				ennemi->vitesse=1;
				break;
			case 'D'://Deidara
				ennemi->pointsDeVie=6;
				ennemi->vitesse=2;
				break;
			case 'H'://Hidan
				ennemi->pointsDeVie=15;
				ennemi->vitesse=1;
				break;
			case 'K':
				ennemi->pointsDeVie=20;
				ennemi->vitesse=1;
			default: 
				printf("Type d'ennemi invalide/n");
				continue;
		}
			
	}

	fclose(fichier);
	return 1; //nous avons réussi a charger le niveau
	
}

void placerTourelle(Jeu* jeu){
	int ligne,position;
	char type;
	int memcagnotte=jeu->cagnotte;// va servir pour le score (moins on depense plus on peut gagner de points)
	do {
		printf("Cagnotte disponible:%d\n", jeu->cagnotte);
		printf("Entre la ligne(1-7) ou 0 pour terminer: ");
		scanf("%d",&ligne);
		if(ligne==0){
			break;
		}
		if (ligne<1 || ligne>7) {
            printf("Erreur : ligne invalide. Tu peux entrer une valeur entre 1 et 7.\n");
            continue;
        }
		printf("Entre la position (1-14): ");
		scanf("%d",&position);
		if (position<1 || position>14) { //la tourelle ne peut pas etre sur la meme case qu'un ennemi, de ce fait elle ne peut pas etre en position 15
            printf("Erreur : position invalide. Tu peux entrer une valeur entre 1 et 14.\n");
            continue;
        }
		
		
		printf("Entre le type de tourelle (N, G, K, S, H, U): ");
        scanf(" %c", &type);

        int prix= 0;
        int pv= 0;

        switch (type) {
            case 'N': 
            	prix =150; 
            	pv=10; 
            	break; // Naruto Uzumaki
             case 'G': 
            	prix =90;  
            	pv=25;  
            	break; // Gaara du Désert
            case 'K': 
            	prix =60;  
            	pv=5;  
            	break; // Kakashi Hatake 
            case 'S': 
            	prix =40;  
            	pv=8;  
            	break; // Sakura Haruno
            case 'H': 
            	prix =50;  
            	pv=4;  
            	break; // Shikamaru Nara
            case 'U': 
            	prix =100; 
            	pv=6;  
            	break; // Sasuke Uchiha
            default:
                printf("Type de tourelle invalide.\n");
                continue;
        }
		
		Tourelle* tr=jeu->tourelles;
		int test=0;
		while(tr!=NULL){
			if(tr->position==position && tr->ligne==ligne){
				test=1;
				break;
			}
			tr=tr->next;
		}
		
		if(test){//pour verifier que il n'y a aucun personnage sur la case selectionné
			printf("ATTENTION : une tourelle est deja placé sur cette emplacement.\n");
			continue;
		}
			
		jeu->cagnotte-=prix;//on retire à la cagnotte le prix de la tourelle
		if(jeu->cagnotte<0){
			printf("Pas assez d'argent pour ce type de tourelles.\n");
			jeu->cagnotte+=prix;
			continue;
		}
		Tourelle* tourelle=malloc(sizeof(Tourelle));
		
		tourelle->type=type;
		tourelle->pointDeVie=pv;
		tourelle->ligne=ligne;
		tourelle->position=position;
		tourelle->prix=prix;
		tourelle->next=NULL;
		
		//gestion du chainage entre les tourelles(plus simple que pour les etudiants)
		if(jeu->tourelles==NULL){
			jeu->tourelles=tourelle;//si c'est la premiere tourelle
		}
		else{
			Tourelle* t=jeu->tourelles;
			while(t->next!=NULL)t=t->next;
			t->next=tourelle;
		}
		
		printf("Tourelle de type %c placee en ligne %d, position %d. \n", type, ligne, position);
	}while(jeu->cagnotte>=40); //40=prix minimal d'une tourelle 
		
	jeu->depense=memcagnotte-jeu->cagnotte;// enregistre combien on a depensé pour placer les tourelles;


}

