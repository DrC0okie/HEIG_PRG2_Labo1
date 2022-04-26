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

const unsigned MIN = 11000, MAX = 30000;
#define MSG_UTILISATEUR "Entrez le nombre de billes [%u - %u] :",MIN, MAX

void viderBuffer(void);

int main(void) {
   unsigned nbBilles;
   printf(MSG_UTILISATEUR);
   while (scanf("%u", &nbBilles) != 1 || nbBilles < MIN || nbBilles > MAX) {
      printf("%s\n", "Saisie incorrecte. Veuillez SVP recommencer.");
      viderBuffer();
      printf(MSG_UTILISATEUR);
   }
   viderBuffer();


   return 0;
}

void viderBuffer(void) {
   int c;
   do {
      c = getchar();
   } while (c != '\n' && c != EOF);
}
