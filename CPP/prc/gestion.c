#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Classe.h"
#include "Salle.h"
#include "Reservation.h"
#include "gestion.h"

/*---------------------------------------------------------------------------------------------*/
void menu(void)
{
    int a;
    printf("1.Gestion des classes\n");
    printf("2.Gestion des salles\n");
    printf("3.Gestion des réservation\n");
    printf("4.Quitter le programme\n");
    printf("\n   Veillez choisir une option: ");
    scanf("%d",&a);
    switch (a)
    {
    case 1 : gestion_classe();
        break;
    case 2 : gestion_salle();
        break;
    case 4 : exit(EXIT_SUCCESS);
        break;
    default: printf("Veillez choisir sur les option possible s'il vous plait\n");
            scanf("%d",&a);
        break;
    }
}
/*---------------------------------------------------------------------------------------------*/
void gestion_classe(void)
{
    int a;
    printf("1.Ajouter une classe\n");
    printf("2.Mofier une classe\n");
    printf("3.Rechercher une classe\n");
    printf("4.Afficher toutes les classes\n");
    printf("5.Supprimer une classe\n");
    printf("6.Retour\n");
    printf("\n   Veillez choisir une option: ");
    scanf("%d",&a);
    switch (a)
    {
    case 1 : add_class();
        break;
    case 2 : edit_class();
        break;
    case 3 : search_class();
        break;
    case 4 : show_class();
        break;
    case 5 : delete_class();
        break;
    case 6 : menu();
        break;
    default: printf("Veillez choisir sur les option possible s'il vous plait\n");
            scanf("%d",&a);
        break;
    }

}

/*---------------------------------------------------------------------------------------------*/
void gestion_salle(void)
{
    int a;
    printf("1.Ajouter une salle\n");
    printf("2.Modifier une salle\n");
    printf("3.Rechercher une salle\n");
    printf("4.Afficher les salles\n");
    printf("5.Supprimer une salle\n");
    printf("6.Retour\n");
    printf("\n  Veillez choisir une option: ");
    scanf("%d",&a);
    switch (a)
    {
    case 1:add_salle();
        break;
    case 2 : edit_salle();
        break;
    case 3 :search_salle();
        break;
    case 4 : show_salle();
        break;
    case 5 : delete_salle();
        break;
    case 6 : menu();
        break;
    default: printf("Veillez choisir sur les options disponible: ");
            scanf("%d",&a);
        break;
    }
}
