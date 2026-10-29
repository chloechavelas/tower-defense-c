#include <stdio.h>
#include <stdlib.h>
 
#include "initialisationjeu.h"  
#include "chargementjeu.h"  // Pour chargerNiveu(), placerTourelle()
#include "affichage.h"  // Pour afficherMenuPrincipal(), afficherExplicationJeu(), affichervagues(), afficherPresentationTourelles(), afficherPresentationVillains()
#include "actionpartour.h"  // Pour deroulementjeu()
#include "finjeu.h"  // Pour findujeu()
#include "save.h" //pour sauvegarde() et chargement()


int main() {
    Jeu* jeu=malloc(sizeof(Jeu));
    debutjeu(jeu); // Initialise le jeu
    int choix;
    int jeuEnCours=1;//pour l'instant oui le jeu est en cours

    FILE* partie=fopen("sauvegarde.txt", "r");
    if(partie!=NULL){
    	fclose(partie);
    	char c;
    	printf("Veux-tu reprendre la partie commencé ? (O/N)\n");
    	scanf(" %c", &c);
    	if(c=='O'){
    		printf("chargement en cours\n");
    		chargement(jeu);
    		printf("Chargement de l'ancienne partie reussi, tu peux reprendre la partie, BONNE CHANCE!!\n");
    		deroulementjeu(jeu);
    		jeuEnCours=0;//le jeu est arrété
    		
    	}
    	else{
    		printf("Nouvelle partie ! Bonne chance !!\n");
    		remove("sauvegarde.txt");//on supprime le fichier qui sauvegarde la partie d'avant qui n'etait pas terminée
    	}
    }
    
    
    do {
    	if (!jeuEnCours) {
            break; // Quitte complètement après une partie
        }
        
        choix = afficherMenuPrincipal(); // Appel de la fonction de menu principal
        switch (choix) {
            case 1:
                afficherExplicationJeu(jeu); // Affiche l'explication du jeu
                break;

            case 2:
            	printf("\033[1;31m"); // couleur rouge 
            	printf("\nPrépares toi pour l'aventure !\n");
            	printf("\033[0m"); // réinitialise la couleur par défaut
        		afficherPresentationTourelles();
        		printf("\033[1;36m"); // couleur bleu 
        		printf("\nChoisis ton niveau, entre : 1  2  3  4  5 \n");
        		printf("\033[0m"); 
        		scanf("%d", &jeu->niveau);

        		char* niveaux[] = {"Niveau1.txt", "Niveau2.txt", "Niveau3.txt", "Niveau4.txt", "Niveau5.txt"};
        		if (jeu->niveau>=1 && jeu->niveau<=5) {
            		if (chargerNiveau(jeu, niveaux[jeu->niveau-1])) {
                		affichervagues(jeu); // Affiche les vagues d'ennemis
                		afficherPresentationVillains();
                		printf("Tu dois maintenant placer tes tourelles de défense !\n");
                		placerTourelle(jeu);

                		printf("\n=== LISTE DES TOURELLES PLACÉES ===\n");
                		Tourelle* mem=jeu->tourelles;
                		if (mem==NULL){
                    		printf("Aucune tourelle placée.\n");
                		}
                		while (mem!=NULL) {
                    		printf("Ligne: %d, Position: %d, Type: %c, PV: %d, Prix: %d\n",
                           		mem->ligne, mem->position, mem->type, mem->pointDeVie, mem->prix);
                    		mem=mem->next;
                		}
                		deroulementjeu(jeu); 
                		jeuEnCours = 0;
            		} 
            		else {
                		printf("Erreur : impossible de charger le niveau.\n");
            		}
        		} 
        		else {
            		printf("Niveau invalide.\n");
        		}
                break;

            case 3:
                printf("\nAu plaisir de te revoir bientôt !\n");
                jeuEnCours=0;
                findujeu(jeu);
                break;

            default:
                printf("\nChoix invalide. Veuillez réessayer.\n");
                break;
        }
    } while (jeuEnCours); 
	
    return 0;
}
