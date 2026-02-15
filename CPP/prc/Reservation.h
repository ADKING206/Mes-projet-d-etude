#ifndef _RESERVATION_H_
#define _RESERVATION_H
#define MOIS 11
#define ANNNES_COURANT 2025
typedef enum etat{
    VALIDE , EN_ATTENTE , ANNULER , TERMINER
}etat;
/*Définition d'une date*/
typedef struct Date
{
    int jour;
    int mois;
    int annee;
}Date;

/*Définition d'une réservation*/

typedef struct Reservation
{
    int Num_reserv;
    char code_classe_reserv[codecaractere];
    char code_salle_reserv[codeslcaractere];
    int Heure_de_debut;
    int Heure_de_fin;
    char motif[25];
    Date date_de_reserv;
    etat etat_reserv;
}Reservation;

/*Les prototypes de notre reservation*/
void add_reserv(void);
void edit_reserv(void);
void delete_reserv(void);
void search_reserv(void);
void show_reserv(void);
void search_reser_class(void);
void seach_reserv_salle(void);
void planing_salle(void);
void planing_class(void);
void Most_use_salle(void);


bool sauvauch_t_il(Reservation a_verifier);
bool existance_jour(int j,int m, int an );
#endif