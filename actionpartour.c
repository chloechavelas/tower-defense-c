#include <stdio.h>
#include <stdlib.h>

#include "actionpartour.h" 
#include "initialisationjeu.h"
#include "affichage.h" //clearScreen()
#include "typeennemis.h"//Orochimaru(),Zetsu(),Hidan()
#include "typetourelles.h" // NarutoKakashi(),  soinSakura(), attaqueShikamaru(), attaqueSasuke()
#include "finjeu.h" //testjeu(), findujeu(), pausedujeu()

void ennemistour(Jeu* jeu){
	Etudiant* ennemi=jeu->etudiants;
	while(ennemi!=NULL && ennemi->tour<=jeu->tour){//la boucle tourne jusqu'a ce que, soit tous les ennemis aient avancé(s'ils sont tous sur le plateau) soit jusqu'a ce que ce soit pas le tour de l'apparition de l'ennemi
		//verification qu'il n'y a pas de tourelle devant l'ennemi
		Tourelle* tourelle=jeu->tourelles;
		int verif=1;// verif ajouté pour voir si la vitesse de l'ennemi sur ce tour va depasser la tourelle devant lui (ce qui est impossible dans les regles de notre jeu)
		while(tourelle!=NULL){
			if(tourelle->position>=(ennemi->position)-ennemi->vitesse && tourelle->ligne==ennemi->ligne && tourelle->pointDeVie>0){
				verif=0;
				if(ennemi->prev_line==NULL)
					ennemi->position=tourelle->position+1; // l'ennemi est donc positionné juste devant la tourelle(donc une position en plus de la position de la tourelle)
			}
			tourelle=tourelle->next;
		}
			
		//verification qu'il n'y a pas un autre ennemi sur le nouveau positionnement de l'ennemi
		if (verif){//si verif est bon c'est a dire que la vitesse de fait pas depasser l'ennemi de la tourelle en terme de position
			if(ennemi->position!=1){//test si l'ennemi est a la dernier position(juste avant d'entrer dans l'université)
				if(ennemi->prev_line==NULL||((ennemi->position)-(ennemi->vitesse))>(ennemi->prev_line->position) ){
					ennemi->position-=ennemi->vitesse; 
				}
				else
					ennemi->position=ennemi->prev_line->position+1;
			}
			else ennemi->position=0;// si il est a la dernière position il n'avance que de 1
		}
		
	
	ennemi=ennemi->next;
	}	
	
}



void attaquedesennemis(Jeu* jeu){
	Etudiant* ennemi=jeu->etudiants;
	//int degats=0;
	while(ennemi!=NULL && ennemi->tour<=jeu->tour){
		if(ennemi->prev_line!=NULL && ennemi->prev_line->position==15)//si cet ennemi est encore à la colonne 15 le notre ne peut pas attaquer car théoriquement il n'est pas rentre dans le jeu
				ennemi=ennemi->next;

		else{
			switch (ennemi->type){//chaque ennemi est associé a sa propre fonction d'attaque
				case 'O': Orochimaru(jeu, ennemi); break;
				case 'Z': Zetsu(jeu, ennemi); break;
				case 'H': Hidan(jeu, ennemi); break;
			}
			
			ennemi=ennemi->next;		
		}
	
	}			
	
}



void attaquedestourelles(Jeu* jeu){
	Tourelle* tourelle=jeu->tourelles;
	
	while (tourelle!=NULL && jeu->tour>0){
		int degats;
		
		
		if(tourelle==NULL) return;
		switch(tourelle->type){//on va donner a chaque tourelle : son nombre de degats et sa fonction d'attaque
            	case 'N': 
            		degats=5;
            		NarutoKakashi(jeu, tourelle, degats);
            		break; // Naruto Uzumaki
           	 case 'G': 
            		degats=1;
            		NarutoKakashi(jeu, tourelle, degats);
            		break; //Gaara
           	 case 'K':
            		degats=2;
            		NarutoKakashi(jeu, tourelle, degats); 
            		break; // Kakashi Hatake
            	case 'S': 
            		soinSakura(jeu, tourelle); 
            		break; // Sakura Haruno (ne fait pas de dégâts directs, soigne)
            	case 'H': 
            		attaqueShikamaru(jeu, tourelle); 
            		break; // Shikamaru Nara (ralentit uniquement)
           	 case 'U': 
           	 		attaqueSasuke(jeu, tourelle); 
            		break; // Gaara du Désert (protège)
           	 default: 
            		degats=0; 
            		break; 
			}
			
		if (jeu->tourelles==NULL || tourelle==NULL) {//rajouté pour évité de prendre en compte une tourelle tué apres son attaque si il a tué deidara
            	printf("Une tourelle a été supprimée pendant l’attaque, arrêt du tour.\n");
            	return;
        	}
		
		tourelle=tourelle->next;
	}
	
}


void deroulementjeu(Jeu* jeu){
	
    while(testjeu(jeu)){//on vérifie que le jeu est toujours en cours grace a lappel de la fonction testjeu  
    	clearScreen(); //pour un affichage plus propre, on affiche que le plateau du tour actuel
    	afficherjeu(jeu);
    	
        
        char pause;
       	printf("Appuies sur Entrée pour continuer...ou sur Q pour quitter\n");
        scanf("%c",&pause);//lorsque l'utilisateur tape une touche on peut passer a la suite, si il tape sur Q, cela va arreter la partie
        if(pause=='Q'){
        	printf("Sauvegarde de la partie en cours...");
        	sauvegarde(jeu);
        	printf("Partie sauvegardée !\n");

        	pausedujeu(jeu);

        	return;
        }
        ennemistour(jeu);
    	attaquedesennemis(jeu);
    	attaquedestourelles(jeu);
        jeu->tour++;
               
    }
    jeu->score-=10*jeu->depense;//à la fin du jeu le score du joueur est diminué en fonction des dépenses qu'il a effectué au debut de la partie
    if (jeu->score<0) jeu->score=0;//pour ramener le score à 0 si il est negatif.
    afficherjeu(jeu);//on affiche le jeu une dernière fois 
    findujeu(jeu);
}


