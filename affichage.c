#include <stdio.h>
#include <stdlib.h>


#include "affichage.h"  
#include "initialisationjeu.h"
#include "chargementjeu.h"  // Pour chargerNiveau(), placerTourelle()
#include "actionpartour.h"  // Pour deroulementjeu()



// fonction pour nettoyer l'écran
void clearScreen() {
    printf("\033[2J");   // efface tout l'écran pour permettre un affichage propre
    printf("\033[0;0H"); // replace le curseur en haut à gauche
}


//fonctions pour les couleurs

void couleurRouge() {
    printf("\033[1;31m"); //couleur rouge pour l'affichage du texte
}


void couleurVerte() {
    printf("\033[1;32m"); //couleur verte pour l'affichage du texte
}


void reinitialisercouleur() {
    printf("\033[0m"); // Réinitialise la couleur du texte à la valeur par défaut
}


void affichervagues(Jeu* jeu){
	printf("Vagues :\n");
	char plateau[7][15];// tableau pour representer les lignes et les colonnes
	int i,j;
	for (i=0; i< 7; i++){
		for(j=0; j<15; j++){
			plateau[i][j]= '.'; //Initialise tout le plateau avec des points
		}
	}
	Etudiant* ennemi=jeu->etudiants;
	while(ennemi!=NULL){
		plateau[ennemi->ligne-1][ennemi->tour-1]=ennemi->type;//rempli le tableau (à la ligne et à la colonne correspondante) avec  le type des ennemis
		ennemi=ennemi->next;
	}
	int k,l;
    for(k=0; k<7; k++){
    	printf("%d|",k+1); //pour afficher
        for(l=0; l<15; l++){
            printf(" %c ", plateau[k][l]);
        }
        printf("\n");
    }
	
	
}



void afficherjeu(Jeu* jeu){
    if (jeu==NULL) {//on s'assure que le jeu existe bien
        printf("Erreur le jeu n'existe pas.\n");
        return;
    }

    char typeEnnemis[7][15];  // initialisation plateau comme dans afficher vagues
    int pvennemis[7][15]; // stockage des pv de chaque ennemi
    int pvtourelles[7][15];//stockage des pv de chaque tourelle
    char typeTourelles[7][15]; //pareil initialisation du plateau 
    int i,j;

    for (i=0; i<7; i++) {
        for (j=0; j<15; j++) {
            typeEnnemis[i][j]='.';  // Case vide(pas d'ennemis pour l'instant)
            pvennemis[i][j]=-1; //on initialise pv a -1 et si ca ne change pas alors ca veut dire qu'il n'y a pas d'ennemi sur cette case
        	pvtourelles[i][j] = -1;// on initialise pv à -1 et si ca ne change pas alors ça veut dire qu'il n'y a pas de tourelle sur cette case
        	typeTourelles[i][j] = '.';//case vide(pas dee tourelles pour l'instant)
        }
    }

    // On commence par placer les tourelles sur le plateau associées à leurs pv 
	Tourelle* tourelle=jeu->tourelles;
	while (tourelle != NULL) {
        if (tourelle->ligne>=1 && tourelle->ligne<=7 && tourelle->position>=1 && tourelle->position<=15) {
            typeTourelles[tourelle->ligne-1][tourelle->position-1]=tourelle->type;
            pvtourelles[tourelle->ligne-1][tourelle->position-1]=tourelle->pointDeVie;
            
            
        } 
        else {
            printf("Erreur : tu as placé une tourelle hors du plateau!!(Ligne: %d, Position: %d)\n", tourelle->ligne, tourelle->position);
        }
        tourelle=tourelle->next;
    }

    //on place maintenant les ennemis avec leur pv à gauche et leur type à droite
    Etudiant* ennemi = jeu->etudiants;
    while (ennemi!=NULL && ennemi->tour<=jeu->tour){
    	if(ennemi->position>0){//si l'ennemi n'a pas passé la ligne d'arrivée
    		if(ennemi->prev_line==NULL || ennemi->prev_line->position!=15){// soit l'ennemi n'a personne devant lui sur la même ligne soit il n'existe pas d'ennemi sur la même ligne en position 15
    			
        	    typeEnnemis[ennemi->ligne - 1][ennemi->position - 1]=ennemi->type;
        	    pvennemis[ennemi->ligne - 1][ennemi->position - 1]=ennemi->pointsDeVie;
        	}
        	
        }
        ennemi=ennemi->next;
    }
    
  
    // Affichage du plateau 
    printf("\nPlateau de jeu :\n");
    printf("Tour %d\n", jeu->tour);
    
    for (i=0; i<7; i++) {
        printf("%d|", i + 1);
        for (j=0; j<15; j++) {
            if (pvennemis[i][j]!=-1 && pvennemis[i][j]!=-2) {
            	couleurRouge();//rouge pour les ennemis
                printf("%2d%c ", pvennemis[i][j], typeEnnemis[i][j]);// Affiche les ennemis avec leurs pv a gauche et leurs type à droite
            	reinitialisercouleur();
            }else if(pvtourelles[i][j] != -1){
            	couleurVerte();// vert pour les tourelles
            	printf("%2d%c ", pvtourelles[i][j], typeTourelles[i][j]);//affiche les tourelles
            	reinitialisercouleur();
            }else 
                printf(" .  ");// le reste affiche avec un point 
            
        }
        printf("\n");
    }
    printf("\n");
    printf("SCORE : %d\n", jeu->score); // affiche le score a chaque tour
    
    
}




int afficherMenuPrincipal() {
    int choix;
    printf("\033[1;36m"); // couleur bleu
    printf("\nBienvenue dans notre jeu inspiré de Naruto 🌟\n");
    printf("\033[0m"); // réinitialise la couleur à blanc
    couleurRouge(); 
    printf("\n=== MENU PRINCIPAL ===\n");
    reinitialisercouleur();
    printf("\033[1;36m");
    printf("1. Explication du jeu\n");
    printf("2. Commencer\n");
    printf("3. Quitter\n");
    printf("Votre choix : ");
    printf("\033[0m");
    scanf("%d", &choix);
    return choix; 
}


void afficherPresentationTourelles() {
	couleurRouge();
    printf("\n  PRÉSENTATION DES SHINOBIS  \n");
    reinitialisercouleur();
    printf("\033[1;33m");
    printf("\nL'Université est en danger ! Fais appel aux plus grands ninjas pour la défendre :\n");
    printf("🔥 Naruto Uzumaki (N) : 150 crédits, 10 PV, en mode Senin, il lance un Rasengan dévastateur (5 dégâts/tour)\n");
    printf("🌪️ Gaara du Désert (G) : 80 crédits, 25 PV, son Mur de Sable est une forteresse impénétrable (1 dégât/tour)\n");
    printf("⚡ Kakashi Hatake (K) : 60 crédits, 5 PV, son légendaire Chidori transperce l’ennemi (2 dégâts/tour)\n");
    printf("💖 Sakura Haruno (S) : 40 crédits, 8 PV, disciple de Tsunade, elle soigne les tourelles voisines jusqu'à atteindre 10PV (+2 PV/tour)\n");
    printf("🕶️ Shikamaru Nara (H) : 50 crédits, 4 PV, avec son Jutsu des Ombres, il paralyse les ennemis (1 tour sur 2)\n");
    printf("⚡ Sasuke Uchiha (U) : 100 crédits, 6 PV, invoque le Kirin, un éclair dévastateur (2 dégâts sur toute la ligne)\n");
    printf("🌀 Stratégie, chakra et courage : à toi de jouer, shinobi !\n\n");
    printf("\033[0m");
}

void afficherPresentationVillains() {
	couleurRouge();
    printf("\n  PRÉSENTATION DE L'AKATSUKI  \n");
    reinitialisercouleur();
    printf("\033[1;33m");
    printf("Les pires criminels du monde shinobi attaquent l’Université !\n");
    printf("🌱 Zetsu (Z) : 5 PV, un espion perfide, il frappe discrètement lorsque l'ennemi est face à lui (1 dégât)\n");
    printf("🐍 Orochimaru (O) : 10 PV, invoque ses serpents maudits (2 dégâts en haut/bas/face)\n");
    printf("💥 Deidara (D) : 6 PV, l’art est une explosion ! Il explose à sa mort et blesse celui qui l'a tué (4 dégâts)\n");
    printf("🩸 Hidan (H) : 15 PV, adepte de Jashin, il maudit ses adversaires (enlève 1 PV, régénère 2 PV)\n");
    printf("🦈 Kisame (K) : 20 PV, le Bijuu sans queue, son épée Samehada absorbe les attaques (réduit les dégâts subis de moitié)\n");
    printf("⚔️ Que ton Nindo te guide... la bataille peut commencer !\n\n");
    printf("\033[0m");
}



void afficherExplicationJeu(Jeu* jeu){
    int choixbis;
    couleurRouge();
    printf("\n   EXPLICATION DU JEU   \n");
    reinitialisercouleur();
    printf("\033[1;33m");
    printf("\n🌟 Naruto, Sasuke, Kakashi... Les plus grands ninjas t’attendent ! 🌟\n");
    printf("\nL’Akatsuki prépare une attaque contre l’Université et seul un véritable stratège shinobi peut les arrêter. 🔥\n");
    printf("\n📜 Règles du jeu :\n");
    printf(" Une vague de vilains redoutables va bientôt surgir.\n");
    printf(" Place judicieusement tes tourelles pour protéger l’Université.\n");
    printf(" Chaque tourelle a une capacité unique, utilise-les intelligemment !\n");
    printf(" À la fin de la partie, tu entreras ton pseudo, et un fichier contenant tes 10 meilleurs scores pour chaque niveau sera créé !");
    printf("\n Si tu es prêt à te lancer dans l'aventure, entre 2, sinon entre 0 : ");
    printf("\033[0m");
    scanf("%d", &choixbis);

    if (choixbis==2) {
    	couleurRouge();
        printf("\nPrépares toi pour l'aventure !\n");
        reinitialisercouleur();
        afficherPresentationTourelles();
        printf("\033[1;36m");
        printf("\nChoisis ton niveau, entre : 1  2  3  4  5 \n");
        printf("\033[0m");
        scanf("%d", &jeu->niveau);

        char* niveaux[]={"Niveau1.txt", "Niveau2.txt", "Niveau3.txt", "Niveau4.txt", "Niveau5.txt"};
        if (jeu->niveau>=1 && jeu->niveau<=5) {
            if (chargerNiveau(jeu, niveaux[jeu->niveau-1])) {
                affichervagues(jeu);
                afficherPresentationVillains();
                printf("Tu dois maintenant placer tes tourelles de défense !\n");
                placerTourelle(jeu);

                printf("\n=== LISTE DES TOURELLES PLACÉES ===\n");
                Tourelle* mem=jeu->tourelles;
                if (mem==NULL) {
                    printf("Aucune tourelle placée.\n");
                }
                while (mem!=NULL) {
                    printf("Ligne: %d, Position: %d, Type: %c, PV: %d, Prix: %d\n",
                           mem->ligne, mem->position, mem->type, mem->pointDeVie, mem->prix);
                    mem=mem->next;
                }
                deroulementjeu(jeu); 
            } 
            else {
                printf("Erreur : impossible de charger le niveau.\n");
            }
        } 
        else {
            printf("Niveau invalide.\n");
        }
    }
    printf("\nAu plaisir de te revoir !\n");
}


