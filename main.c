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

const unsigned MIN_BILLE = 1000, MAX_BILLE = 30000, MIN_RANGEE = 10, MAX_RANGEE = 20,
   RES_HISTOGRAMME = 15;
const char *MSG_BILLES = "Entrez le nombre de billes";
const char *MSG_RANGEES = "Entrez le nombre de rangees de compteurs";

void viderBuffer(void);

unsigned nbClous(unsigned nbEtage);

unsigned entreeUtilisateur(const char *msg, unsigned min, unsigned max);

void parcoursBille(unsigned *tab, unsigned nbEtage);

void imprimerCompteurs(const unsigned tabCompteur[], unsigned nbEtages);

void imprimerHistogramme(const unsigned tabCompteur[], unsigned nbEtages);

unsigned nbChiffre(unsigned nombre);

unsigned valeurMax(const unsigned tab[], size_t taille);

int main(void) {
   //Amorcer le generateur aleatoire
   srand((unsigned) time(NULL));

   //Entrees utilisateur
   unsigned nbBilles = entreeUtilisateur(MSG_BILLES, MIN_BILLE, MAX_BILLE);
   unsigned nbEtages = entreeUtilisateur(MSG_RANGEES, MIN_RANGEE, MAX_RANGEE);



   //Allocation du tableau des compteurs
   unsigned *tabCompteur = calloc(nbClous(nbEtages), sizeof(unsigned));

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

unsigned entreeUtilisateur(const char *msg, unsigned min, unsigned max) {
   printf("%s [%u - %u] :", msg, min, max);
   unsigned entree = 0;
   while (scanf("%u", &entree) != 1 || entree < min || entree > max) {
      viderBuffer();
      printf("%s\n", "Saisie incorrecte. Veuillez SVP recommencer.");
      printf("%s [%u - %u] :", msg, min, max);
   }
   viderBuffer();
   return entree;
}

void imprimerCompteurs(const unsigned tabCompteur[], unsigned nbEtages) {
   for (unsigned etage = 0, index = 0; etage < nbEtages; ++etage) {
      printf("%*s ", (nbEtages - etage - 1) * 3, "");
      for (unsigned colonne = 0; colonne <= etage; ++colonne, ++index) {
         printf("%*u ", nbChiffre(tabCompteur[0]), tabCompteur[index]);
      }
      printf("\n");
   }
}

void imprimerHistogramme(const unsigned tabCompteur[], unsigned nbEtages) {
   //Recuperer l'index du dernier etage du tableau
   unsigned indexDernierEtage = nbClous(nbEtages) - nbEtages;

   //Recuperer la valeur maximum de tous les compteurs du dernier etage
   unsigned valMax = valeurMax(tabCompteur + indexDernierEtage, nbEtages);

   for (unsigned i = RES_HISTOGRAMME; i > 0; --i) {
      for (unsigned j = 0; j < nbEtages; ++j) {
         char c = ' ';
         unsigned valeurCompteur = tabCompteur[indexDernierEtage + j];

         //Calcul de la hauteur de l'histogramme pour ce compteur entre 0 et 15
         double hauteur = round(valeurCompteur * (double)RES_HISTOGRAMME / valMax);

         //Imprimer '*' ou ' '
         if(hauteur >= i)
            c = '*';
         printf(" %*c", nbChiffre(tabCompteur[0]), c);
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
    return (unsigned) log10(nombre) + 1;
}
