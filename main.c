/*
-----------------------------------------------------------------------------------
Nom du fichier : main.cpp
Nom du labo    : Laboratoire no. 1
Auteur(s)      : Patrick Furrer Timothée Van Hove
Date creation  : 25 avril 2022
But            : Générer une planche de Galton et afficher un histogramme
                 représentant la répartition

Remarque(s)    : <à compléter>

Compilateur    : Mingw-w64 gcc 11.2.0
-----------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <time.h>
#include <string.h>

const unsigned MIN_BILLE = 1000, MAX_BILLE = 30000, MIN_RANGEE = 10, MAX_RANGEE = 20,
   RES_HISTOGRAMME = 15;
const char *MSG_BILLES = "Entrez le nombre de billes";
const char *MSG_RANGEES = "Entrez le nombre de rangees de compteurs";
const unsigned TAILLE_BUFFER = 128;

void viderBuffer(void);

/*
 * Calcul le nombre de clous sur la planche
 */
unsigned nbClous(unsigned nbEtage);

unsigned lectureEntree(const char *msg, unsigned min, unsigned max);

/*
 * Incremente les compteurs en fonction du parcours de la bille
 */
void parcoursBille(unsigned *tab, unsigned nbEtage);

/*
 * Affiche la planche de galton : les compteurs de chaque clous
 */
void imprimerCompteurs(const unsigned tabCompteur[], unsigned nbEtages);

void imprimerHistogramme(const unsigned tabCompteur[], unsigned nbEtages);

/*
 * Retourne le nombre de chiffre dans un nombre non signe
 */
unsigned nbChiffre(unsigned nombre);

/*
 * Donne la valeur max dans un tableau (ou une partie)
 */
unsigned valeurMax(const unsigned tab[], size_t taille);

int main(void) {
   //Amorcer le generateur aleatoire
   srand((unsigned) time(NULL));

   //Entrees utilisateur
   unsigned nbBilles = lectureEntree(MSG_BILLES, MIN_BILLE, MAX_BILLE);
   unsigned nbEtages = lectureEntree(MSG_RANGEES, MIN_RANGEE, MAX_RANGEE);

   //Allocation du tableau des compteurs
   unsigned *tabCompteur = calloc(nbClous(nbEtages), sizeof(unsigned));
   if (tabCompteur == NULL) {
      printf("Plus de memoire disponible\n Arret du programme");
      return EXIT_FAILURE;
   }
   //Simulation du parcours de la bille
   if (tabCompteur != NULL) {
      for (unsigned bille = 0; bille < nbBilles; ++bille) {
         parcoursBille(tabCompteur, nbEtages);
      }
   }

   imprimerCompteurs(tabCompteur, nbEtages);
   printf("\n");
   imprimerHistogramme(tabCompteur, nbEtages);

   //Liberer la memoire allouee
   free(tabCompteur);
   getchar();
   return EXIT_SUCCESS;
}

void viderBuffer(void) {
   int c;
   while ((c = getchar()) != '\n' && c != EOF);
}

unsigned lectureEntree(const char *msg, unsigned min, unsigned max) {
   int succes;
   unsigned entree = 0;
   do {
      printf("%s [%u - %u] :", msg, min, max);
      //Creer 2 buffers de 128 Bytes pour avoir de la marge et les initialiser à 0
      char bufferTemp[TAILLE_BUFFER], bufferComp[TAILLE_BUFFER];
      memset(bufferTemp, 0, TAILLE_BUFFER);
      memset(bufferComp, 0, TAILLE_BUFFER);
      //Stocker la valeur dans le buffer #1
      scanf("%s", bufferTemp);
      viderBuffer();
      //Recuperer la valeur au format unsigned depuis le buffer #1
      sscanf(bufferTemp, "%u", &entree);
      //stocker la valeur au format char* dans le buffer #2
      sprintf(bufferComp, "%u", entree);
      //Comparer les 2 buffer, recommencer s'ils ont différents
      succes = memcmp(bufferTemp, bufferComp, TAILLE_BUFFER);
      if (succes || entree < min || entree > max) {
         printf("%s\n", "Saisie incorrecte. Veuillez SVP recommencer.");
         succes = 1;
      }
   } while (succes);
   return entree;
}

void imprimerCompteurs(const unsigned tabCompteur[], unsigned nbEtages) {
   unsigned nbChiffreMax = nbChiffre(tabCompteur[0]);
   for (unsigned etage = 0, index = 0; etage < nbEtages; ++etage) {
      //Calcul du décalage pour un nombre de chiffres de billes impair
      unsigned decalage = ((nbChiffreMax + 1) % 2) * (nbEtages - etage) / 2;
      printf("%*s ", ((nbEtages - etage - 1) * 3) - decalage, "");
      for (unsigned colonne = 0; colonne <= etage; ++colonne, ++index) {
         printf("%*u ", nbChiffreMax, tabCompteur[index]);
      }
      printf("\n");
   }
}

void imprimerHistogramme(const unsigned tabCompteur[], unsigned nbEtages) {
   //Recuperer l'index du dernier etage du tableau
   unsigned indexDernierEtage = nbClous(nbEtages) - nbEtages;

   //Recuperer la valeur maximum de tous les compteurs du dernier etage
   unsigned valMax = valeurMax(tabCompteur + indexDernierEtage, nbEtages);
   unsigned nbChiffreMax = nbChiffre(tabCompteur[0]);
   for (unsigned i = RES_HISTOGRAMME; i > 0; --i) {
      for (unsigned j = 0; j < nbEtages; ++j) {
         char c = ' ';
         unsigned valeurCompteur = tabCompteur[indexDernierEtage + j];

         //Calcul de la hauteur de l'histogramme pour ce compteur entre 0 et 15
         double hauteur = round(valeurCompteur * (double) RES_HISTOGRAMME / valMax);

         //Imprimer '*' ou ' '
         if (hauteur >= i)
            c = '*';
         printf(" %*c", nbChiffreMax, c);
      }
      printf("\n");
   }
}

unsigned valeurMax(const unsigned tab[], size_t taille) {
   unsigned max = 0;
   for (size_t i = 0; i < taille; ++i) {
      if (tab[i] > max)
         max = tab[i];
   }
   return max;
}

void parcoursBille(unsigned *tab, unsigned nbEtages) {
   unsigned pos = 0;
   for (unsigned etage = 1; etage <= nbEtages; ++etage) {
      ++tab[pos];
      if (rand() % 2)
         ++pos;
      pos += etage;
   }
}

unsigned nbClous(unsigned nbEtages) {
   return nbEtages * (nbEtages + 1) / 2;
}

unsigned nbChiffre(unsigned nombre) {
   if (nombre == 0)
      return 1;
   return (unsigned) log10(nombre) + 1;
}
