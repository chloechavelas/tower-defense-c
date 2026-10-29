#ifndef ACTIONPARTOUR_H
#define ACTIONPARTOUR_H

#include "initialisationjeu.h"
#include "affichage.h" //clearScreen()
#include "typeennemis.h"//Orochimaru(),Zetsu(),Hidan()
#include "typetourelles.h" // NarutoKakashi(),  soinSakura(), attaqueShikamaru(), attaqueSasuke()
#include "finjeu.h" //testjeu(), findujeu(), pausedujeu()

void ennemistour(Jeu* jeu);

void attaquedesennemis(Jeu* jeu);

void attaquedestourelles(Jeu* jeu);

void deroulementjeu(Jeu* jeu);

#endif