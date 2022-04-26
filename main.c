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

const unsigned MIN = 1000, MAX = 30000;
#define MSG_UTILISATEUR "Entrez le nombre de billes [%u - %u] :",MIN, MAX

void viderBuffer(void);

int main(void) {
   //---------Solution 1 : si 1000a est considéré comme entrée valide
//   unsigned nbBilles;
//   printf(MSG_UTILISATEUR);
//   while (scanf("%u", &nbBilles) != 1 || nbBilles < MIN || nbBilles > MAX) {
//      viderBuffer();
//      printf("%s\n", "Saisie incorrecte. Veuillez SVP recommencer.");
//      printf(MSG_UTILISATEUR);
//   }
//   viderBuffer();

//---------Solution 2 : si 1000a est considéré comme entrée invalide
//   long nbBilles;
//   char buffer[1024];
//   int lectureOk;
//   do{
//      printf(MSG_UTILISATEUR);
//      if (!fgets(buffer, 7, stdin))
//         return EXIT_FAILURE;
//      char *endptr;
//      errno = 0; // reset error number
//      nbBilles = strtol(buffer, &endptr, 10);
//      if(endptr != buffer && errno == 0 && (*endptr == '\n'))
//         lectureOk = 1;
//      else
//         printf("%s\n", "Saisie incorrecte. Veuillez SVP recommencer.");
//   } while (!lectureOk); // repeat until we got a valid number

   return 0;
}
void viderBuffer(void) {
   int c;
   while ((c = getchar()) != '\n' && c != EOF);
}
