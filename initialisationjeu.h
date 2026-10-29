#ifndef INITIALISATIONJEU_H
#define INITIALISATIONJEU_H


typedef struct tourelle{
	int type;
	int pointDeVie;
	int ligne;
	int position;
	int prix;
	struct tourelle* next;
}Tourelle;

typedef struct etudiant{
	int type; 
	int pointsDeVie;
	int ligne;
	int position;
	int vitesse;
	int tour;
	struct etudiant* next;
	struct etudiant* next_line;
	struct etudiant* prev_line;
}Etudiant;

typedef struct{
	Tourelle* tourelles;
	Etudiant* etudiants;
	int cagnotte;
	int tour;
	int score;//rajouté pour afficher le score
	int depense;//rajouté pour que le score diminue à la fin de la partie en fonction des dépenses effectuées au debut avec l'achat des tourelles
	int niveau;// rajouté pour savoir quel niveau nous sommes quand on stoppe une partie en plein milieu
} Jeu;

typedef struct {
    char nom[30]; // on stocke le nom du joueur(on imagine que ce ne sera pas plus de 30 caractères)
    int score;    // on stocke le score du joueur
} Score;

void debutjeu(Jeu* jeu);

#endif
