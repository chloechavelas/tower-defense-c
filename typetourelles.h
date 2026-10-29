#ifndef TYPETOURELLES_H
#define TYPETOURELLES_H

#include "initialisationjeu.h" 
#include "liberationpersonnage.h"  // ennemitué()
#include "typeennemis.h" //kisame()

void score(Jeu* jeu, Etudiant* ennemi);
void NarutoKakashi(Jeu* jeu, Tourelle* tourelle, int degats);
void attaqueSasuke(Jeu* jeu, Tourelle* tourelle);
void attaqueShikamaru(Jeu* jeu, Tourelle* tourelle);
void soinSakura(Jeu* jeu, Tourelle* tourelle);

#endif 
