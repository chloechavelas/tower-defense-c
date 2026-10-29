
# Tower Defense – Projet en C

**Projet universitaire – L2 MIDO | Université Paris-Dauphine PSL | 2025**

**Auteurs :** Chloé Chavelas et Yasmine Mlika  
**Langage :** C  
**Environnement :** Terminal, GCC

## Présentation

Développement d'un jeu de stratégie de type Tower Defense en langage C.

Le joueur doit défendre une université contre des vagues successives d'ennemis en plaçant des tourelles et en gérant ses ressources.

Le jeu se déroule dans le terminal et propose cinq niveaux de difficulté.

## Fonctionnalités

- Menu principal interactif
- Sélection de cinq niveaux
- Chargement des ennemis et des tourelles
- Placement stratégique des tourelles
- Système de combats au tour par tour
- Gestion des points de vie et des ressources
- Sauvegarde et reprise d'une partie
- Gestion des scores

## Aspects techniques

- Programmation modulaire en C
- Utilisation de structures et de pointeurs
- Manipulation de listes chaînées
- Allocation et libération dynamique de la mémoire
- Lecture et écriture dans des fichiers
- Gestion des interactions dans le terminal

## Compilation et exécution

### Prérequis

Un compilateur C, tel que GCC.

### Compilation

Depuis le dossier contenant les fichiers source :

```bash
gcc -Wall main.c save.c actionpartour.c affichage.c chargementjeu.c finjeu.c initialisationjeu.c liberationpersonnages.c typeennemis.c typetourelles.c -o tower-defense
```

### Exécution

Sur macOS ou Linux :

```bash
./tower-defense
```

Les cinq fichiers `Niveau1.txt` à `Niveau5.txt` doivent rester dans le même dossier que celui depuis lequel le jeu est exécuté.

## Documentation

- [Guide de compilation et d'exécution](README.pdf)
- [Document de développement](dev.pdf)

## Compétences mobilisées

Programmation en C, structures de données, gestion de la mémoire, algorithmique, lecture de fichiers et développement collaboratif.
  
