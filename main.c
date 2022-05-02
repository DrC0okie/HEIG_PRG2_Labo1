/*-----------------------------------------------------------------------------------
Nom du fichier :  main.cpp
Nom du labo    :  Laboratoire no. 1
Auteur(s)      :  Patrick Furrer Timothee Van Hove
Date creation  :  25 avril 2022
But            :  Generer une planche de Galton et simuler le passage de chaque
                  bille au travers. Afficher le representation de la planche de
                  galton avec des compteurs qui s'incrementent au passage de
                  chaque bille. Afficher un histogramme representant la
                  distribution des billes dans les derniers compteurs

Remarque(s)    :  - Toutes les saisies utilisateur sont controlees. L'utilisateur
                  doit entrer (valeur numerique) un nombre de billes  entre
                  [1000, 30000], et un nombre d'etages entre [10, 20].
                  - Le programme se termine automatiquement apres l'affichage de
                  l'histogramme

Compilateur    : mingw-w64 gcc 11.2.0
-----------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <inttypes.h>

const uint32_t MIN_BILLE = 1000, MAX_BILLE = 30000, MIN_RANGEE = 10, MAX_RANGEE = 20,
   RESOLUTION_HISTO = 15, TAILLE_BUFFER = 128;
const char* MSG_BILLES = "Entrez le nombre de billes";
const char* MSG_RANGEES = "Entrez le nombre de rangees de compteurs";

//Vide le buffer stdin
void viderStdin(void);

//Calcul le nombre de nbCompteurs sur la planche
uint32_t nbCompteurs(uint32_t nbEtage);

//Lis l'entree utilisateur et renvoie la valeur lue si l'entree est valide si non,
//invite l'utilisateur a recommencer avec un message d'erreur
uint32_t lectureEntree(const char* msg, uint32_t min, uint32_t max);

//Incremente les compteurs en fonction du parcours de la bille
void parcoursBille(uint32_t* tab, uint32_t nbEtage);

//Affiche les compteurs de la planche de Galton (chaque compteurs). Fait varier
//l'espace avant les compteurs de 1 (1 ligne / 2) si nbBilles a une nombre de
// chiffres pair
void imprimerCompteurs(const uint32_t* tabCompteur, uint32_t nbEtages);

//Affiche l'histogramme de la distribution du nbre de billes dans les
//compteurs du dernier etage
void imprimerHistogramme(const uint32_t* tabCompteur, uint32_t nbEtages);

//Retourne le nombre de chiffre dans un nombre non signe
uint32_t longueurNbre(uint32_t nombre);

//Retourne 1 si le nombre est pair, si non 0
uint32_t estPair(uint32_t nombre);

//Donne la valeur max dans un tableau (ou une partie)
uint32_t valeurMax(const uint32_t* tab, size_t taille);

int main(void) {
   //Amorcer le generateur aleatoire (distribution differente a chaque execution)
   srand((uint32_t) time(NULL));

   //Entrees utilisateur
   uint32_t nbBilles = lectureEntree(MSG_BILLES, MIN_BILLE, MAX_BILLE);
   uint32_t nbEtages = lectureEntree(MSG_RANGEES, MIN_RANGEE, MAX_RANGEE);

   //Allocation du tableau des compteurs
   uint32_t *tabCompteur = calloc(nbCompteurs(nbEtages), sizeof(uint32_t));
   if (tabCompteur == NULL) {
      printf("Plus de memoire disponible\n Arret du programme");
      return EXIT_FAILURE;
   }
   //Simulation du parcours de la bille
   for (uint32_t bille = 0; bille < nbBilles; ++bille) {
      parcoursBille(tabCompteur, nbEtages);
   }

   //Affichage des compteurs et de l'histogramme
   imprimerCompteurs(tabCompteur, nbEtages);
   printf("\n");
   imprimerHistogramme(tabCompteur, nbEtages);

   //Liberer la memoire allouee
   free(tabCompteur);
   getchar();
   return EXIT_SUCCESS;
}

void viderStdin(void) {
   int c;
   while ((c = getchar()) != '\n' && c != EOF);
}

uint32_t lectureEntree(const char* msg, uint32_t min, uint32_t max) {
   int echec;
   uint32_t entree = 0;
   do {
      echec = 0;
      printf("%s [%u - %u] :", msg, min, max);
      //Creer 2 buffers de 128 Bytes pour avoir de la marge et les initialiser a 0
      char bufferTemp[TAILLE_BUFFER], bufferComp[TAILLE_BUFFER];
      memset(bufferTemp, 0, TAILLE_BUFFER);
      memset(bufferComp, 0, TAILLE_BUFFER);
      //Stocker la valeur dans le buffer #1
      scanf("%s", bufferTemp);
      viderStdin();
      //Recuperer la valeur au format uint32_t depuis le buffer #1
      sscanf(bufferTemp, "%"PRIu32, &entree);
      //Stocker la valeur au format char* dans le buffer #2
      sprintf(bufferComp, "%"PRIu32, entree);
      //Comparer les 2 buffers, recommencer s'ils sont differents
      if (strcmp(bufferTemp, bufferComp) || entree < min || entree > max) {
         printf("%s\n", "Saisie incorrecte. Veuillez SVP recommencer.");
         echec = 1;
      }
   } while (echec);
   return entree;
}

void imprimerCompteurs(const uint32_t* tabCompteur, uint32_t nbEtages) {
   uint32_t nbChiffres = longueurNbre(tabCompteur[0]);
   //Calcul du centre de l'affichage sur la base du dernier etage de compteurs
   uint32_t nbEspaces = (nbChiffres + 1) * nbEtages / 2;
   //Calcul du centre du nombre pour centrer le compteur
   uint32_t centreCompteur = (nbChiffres + 1) / 2;
   for (uint32_t etage = 0, index = 0; etage < nbEtages; ++etage) {
      //Decrement du nbEspaces avant le compteur pour avoir un affichage symetrique
      //Si nbChiffres de billes est impair, pas besoin de faire varier 1 ligne sur 2
      nbEspaces -= (estPair(nbChiffres) && estPair(etage + 1)) + centreCompteur;
      printf("%*s ", nbEspaces, "");
      for (uint32_t colonne = 0; colonne <= etage; ++colonne, ++index) {
         printf("%*u ", nbChiffres, tabCompteur[index]);
      }
      printf("\n");
   }
}

void imprimerHistogramme(const uint32_t* tabCompteur, uint32_t nbEtages) {
   //Recuperer l'index du dernier etage du tableau
   uint32_t indexDernierEtage = nbCompteurs(nbEtages) - nbEtages;
   //Recuperer la valeur maximum de tous les compteurs du dernier etage
   uint32_t valMax = valeurMax(tabCompteur + indexDernierEtage, nbEtages);
   uint32_t nbChiffres = longueurNbre(tabCompteur[0]);
   for (uint32_t i = RESOLUTION_HISTO; i > 0; --i) {
      for (uint32_t j = 0; j < nbEtages; ++j) {
         char c = ' ';
         uint32_t valeurCompteur = tabCompteur[indexDernierEtage + j];
         //Calcul de la hauteur de l'histogramme pour ce compteur entre 0 et 15
         double hauteur = round(valeurCompteur * (double) RESOLUTION_HISTO / valMax);
         //Imprimer '*' ou ' '
         if (hauteur >= i)
            c = '*';
         printf(" %*c", nbChiffres, c);
      }
      printf("\n");
   }
}

uint32_t valeurMax(const uint32_t* tab, size_t taille) {
   uint32_t max = 0;
   for (size_t i = 0; i < taille; ++i) {
      if (tab[i] > max)
         max = tab[i];
   }
   return max;
}

void parcoursBille(uint32_t* tab, uint32_t nbEtages) {
   uint32_t pos = 0;
   for (uint32_t etage = 1; etage <= nbEtages; ++etage) {
      ++tab[pos];
      if (rand() % 2)
         ++pos;
      pos += etage;
   }
}

uint32_t nbCompteurs(uint32_t nbEtages) {
   return nbEtages * (nbEtages + 1) / 2;
}

uint32_t longueurNbre(uint32_t nombre) {
   if (nombre == 0)
      return 1;
   return (uint32_t) log10(nombre) + 1;
}

uint32_t estPair(uint32_t nombre) {
   return (nombre + 1) % 2;
}
