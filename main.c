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
unsigned nbClous(unsigned nbEtage);
unsigned entreeUtilisateur(const char *msg, const char *msgErreur, unsigned min,
                           unsigned max);
void parcoursBille(unsigned* tab, unsigned nbEtage);
void imprimerCompteurs(unsigned *tableau, unsigned nbRangees);

void imprimerLigneCompteurs(unsigned *tableau, unsigned numLigne);


int main(void) {
    unsigned nbBilles = entreeUtilisateur(MSG_BILLES, MSG_ERREUR, MIN_BILLE, MAX_BILLE);
    unsigned nbEtage =  entreeUtilisateur(MSG_RANGEES, MSG_ERREUR, MIN_RANGEE, MAX_RANGEE);

    unsigned *tabCompteur = calloc(nbClous(nbEtage), sizeof(unsigned));


    for(unsigned bille = 0; bille < nbBilles; ++bille) {
        parcoursBille(tabCompteur, nbEtage);
    }
    //affichage tableau (pas beau)
    for (unsigned etage = 0, index = 0; etage <= nbEtage; ++etage) {
        for (unsigned colonne = 0; colonne < etage; ++colonne, ++index) {
            printf("valeur %d ", tabCompteur[index]);
        }
        printf("\n");
    }

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

void imprimerCompteurs(unsigned *tableau, unsigned nbRangees) {
    for (unsigned i = 1; i <= nbRangees; ++i) {
        imprimerLigneCompteurs(tableau, i);
    }
}

void imprimerLigneCompteurs(unsigned *tableau, unsigned numLigne) {
    for (unsigned i = 1; i <= numLigne; ++i) {
        printf("%u ", tableau[(numLigne - 1) + (i - 1)]);
    }
    printf("\n");
}


void parcoursBille(unsigned* tab, unsigned nbEtage) {
    unsigned pos = 0;
    for( unsigned etage = 1; etage <= nbEtage; ++etage) {
        ++tab[pos];
        if(rand() % 2) ++pos;

        pos += etage;
    }
}


unsigned nbClous(unsigned nbEtage) {
    return nbEtage * (nbEtage + 1) / 2;
}

/* Fonction de check temp
 *     for (unsigned etage = 0, index = 0; etage <= nbEtage; ++etage) {
        unsigned summ = 0;
        for (unsigned colonne = 0; colonne <= etage; ++colonne, ++index) {
            summ+= tabCompteur[index];
        }
        printf("Check summ %d \n", summ);
    }
    printf("Check 1st value %d \n", tabCompteur[0]);
    //nettoyage de la mémoire
    */