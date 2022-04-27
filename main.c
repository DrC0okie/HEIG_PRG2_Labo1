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

#define NB_CLOUS(ETAGE) ((ETAGE)*((ETAGE)+1)/2)
#define ENFANT_GAUCHE(ETAGE, PARENT) ((PARENT) + (ETAGE))
#define ENFANT_DROITE(ETAGE, PARENT) ((PARENT) + (ETAGE) + 1)

const unsigned MIN_BILLE = 1000, MAX_BILLE = 30000, MIN_RANGEE = 10, MAX_RANGEE = 20;
const char *MSG_ERREUR = "Saisie incorrecte. Veuillez SVP recommencer.";
const char *MSG_BILLES = "Entrez le nombre de billes";
const char *MSG_RANGEES = "Entrez le nombre de rangees de compteurs";

void viderBuffer(void);

unsigned entreeUtilisateur(const char *msg, const char *msgErreur, unsigned min,
                           unsigned max);
void imprimerCompteurs(unsigned* tableau, unsigned nbRangees);
void imprimerLigneCompteurs(unsigned* tableau, unsigned numLigne);

unsigned separerGauche(unsigned valeur);

int main(void) {
    unsigned nbBilles =entreeUtilisateur(MSG_BILLES, MSG_ERREUR, MIN_BILLE, MAX_BILLE);
    unsigned nbEtage = entreeUtilisateur(MSG_RANGEES, MSG_ERREUR, MIN_RANGEE, MAX_RANGEE);
   nbEtage = 10;
    nbBilles = 30000;
   unsigned* tabCompteur = calloc(NB_CLOUS(nbEtage) , sizeof(unsigned));
    tabCompteur[0] = nbBilles;
    int i = 0;
    // Parcours du tableau
    for( unsigned etage = 0, index = 0; etage < nbEtage; ++etage) {
        for (unsigned colonne =0; colonne < etage; ++colonne, ++index) {
            unsigned valeurGauche = separerGauche(tabCompteur[index]);
            tabCompteur[ENFANT_GAUCHE(etage, index)] += valeurGauche;
            tabCompteur[ENFANT_DROITE(etage, index)] += tabCompteur[index] - valeurGauche;
        }

        printf("\n");
    }
    for( unsigned etage = 0, index = 0; etage <= nbEtage; ++etage) {
        for (unsigned colonne =0; colonne < etage; ++colonne, ++index) {
            printf("valeur %d ", tabCompteur[index]);
        }
        printf("\n");
    }
    //nettoyage de la mémoire
    free(tabCompteur);
   return EXIT_SUCCESS;
}

void viderBuffer(void) {
   int c;
   while ((c = getchar()) != '\n' && c != EOF);
}

unsigned entreeUtilisateur(const char *msg, const char *msgErreur, unsigned min,
                           unsigned max) {
   printf("%s [%u - %u] :", msg, min, max);
   unsigned entree = 0;
   while (scanf("%u", &entree) != 1 || entree < min || entree > max) {
      viderBuffer();
      printf("%s\n", msgErreur);
      printf("%s [%u - %u] :", msg, min, max);
   }
   viderBuffer();
   return entree;
}


unsigned separerGauche(unsigned valeur) {
    unsigned valeurGauche = 0;
    for(unsigned i = 0; i < valeur; ++i) {
        if(rand() % 2) {
            ++valeurGauche;
        }
    }
    return valeurGauche;
}
void imprimerCompteurs(unsigned* tableau, unsigned nbRangees)
{
   for (unsigned i = 1; i <= nbRangees; ++i) {
      imprimerLigneCompteurs(tableau, i);
   }
}

void imprimerLigneCompteurs(unsigned* tableau, unsigned numLigne)
{
   for (unsigned i = 1; i <= numLigne; ++i) {
      printf("%u ", tableau[(numLigne-1) + (i-1)]);
   }
   printf("\n");
}
