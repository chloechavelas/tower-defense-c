#ifndef TYPEENNEMIS_H
#define TYPEENNEMIS_H

#include "initialisationjeu.h"  
#include "liberationpersonnage.h"  // Pour `tourelletuée`


int ennemivitesse(Etudiant* ennemi);
void Zetsu(Jeu* jeu, Etudiant* zetsu);
void Orochimaru(Jeu* jeu, Etudiant* orochimaru);
void DeidaraExplosion(Jeu* jeu, Tourelle* tourelle, Etudiant* deidara);
void Hidan(Jeu* jeu, Etudiant* hidan);
void Kisame(Jeu* jeu, Etudiant* kisame, int degats,Tourelle* tourelle);

#endif