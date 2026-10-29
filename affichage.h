#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "initialisationjeu.h" 
#include "chargementjeu.h"  // Pour `chargerNiveau()`, `placerTourelle()`
#include "actionpartour.h"  // Pour `deroulementjeu()`


void clearScreen();
void couleurRouge();
void couleurVerte();
void reinitialisercouleur();
void affichervagues(Jeu* jeu);
void afficherjeu(Jeu* jeu);
int afficherMenuPrincipal();
void afficherPresentationTourelles();
void afficherPresentationVillains();
void afficherExplicationJeu(Jeu* jeu);


#endif