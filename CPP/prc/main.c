#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <locale.h>
#include "Classe.h"
#include "Salle.h"
#include "Reservation.h"
#include "gestion.h"



int main(int argc, char **argv)
{
    setlocale(LC_ALL,"French");
    menu();
    return 0;
}