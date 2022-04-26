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
