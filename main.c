/*
-----------------------------------------------------------------------------------
Nom du fichier : main.cpp
Nom du labo    : Laboratoire no. 1
Auteur(s)      : Patrick Furrer Timothée Van Hove
Date creation  : 25 avril 2022
But            : Génréer une planche de Galton et afficher un histograme
                 représentant la répartition

Remarque(s)    : <à compléter>

Compilateur    : Mingw-w64 gcc 11.2.0
-----------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const unsigned MIN_BILLE = 1000, MAX_BILLE = 30000, MIN_RANGEE = 10, MAX_RANGEE = 20;
const char *MSG_ERREUR = "Saisie incorrecte. Veuillez SVP recommencer.";
const char *MSG_BILLES = "Entrez le nombre de billes";
const char *MSG_RANGEES = "Entrez le nombre de rangees de compteurs";

void viderBuffer(void);

unsigned entreeUtilisateur(const char *msg, const char *msgErreur, unsigned min,
                           unsigned max);

int main(void) {
   entreeUtilisateur(MSG_BILLES, MSG_ERREUR, MIN_BILLE, MAX_BILLE);
   entreeUtilisateur(MSG_RANGEES, MSG_ERREUR, MIN_RANGEE, MAX_RANGEE);

   return 0;
}

void viderBuffer(void) {
   int c;
   while ((c = getchar()) != '\n' && c != EOF);
}

unsigned entreeUtilisateur(const char *msg, const char *msgErreur, unsigned min,
                           unsigned max) {
   printf("%s [%u - %u] :", msg, min, max);
   unsigned resultat = 0;
   while (scanf("%u", &resultat) != 1 || resultat < min || resultat > max) {
      viderBuffer();
      printf("%s\n", msgErreur);
      printf("%s [%u - %u] :", msg, min, max);
   }
   viderBuffer();
}
