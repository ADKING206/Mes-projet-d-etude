#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Reservation.h"
#include "Salle.h"
#include "Classe.h"
#include "gestion.h"

Salle getNameSalle(char code[codeslcaractere])
{
    Salle une_salle;
    FILE *file = fopen("salle.bin","rb+");
    while (fread(&une_salle,sizeof(Salle),1,file)==1)
    {
        if (une_salle.code_salle == code)
        {
            return une_salle;
        }
        
    }
    
}

CLASSE getNameClasse(char code[codecaractere])
{
    CLASSE une_classe;
    FILE *file = fopen("salle.bin","rb+");
    while (fread(&une_classe,sizeof(CLASSE),1,file)==1)
    {
        if (une_classe.code_unique == code)
        {
            return une_classe;
        }
        
    }  
}
void getEtatReservation(Reservation une_reserv)
{
    switch (une_reserv.etat_reserv) {
    case VALIDE: printf("État : VALIDE\n"); break;
    case EN_ATTENTE: printf("État : EN ATTENTE\n"); break;
    case ANNULER: printf("État : ANNULÉE\n"); break;
}

}
