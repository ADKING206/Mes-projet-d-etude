#ifndef _SALLE_H_
#define _SALLE_H_
#define codeslcaractere 8

/*Définition d'une salle*/
typedef struct Salle
{
    char code_salle[codeslcaractere];
    char salle_name[10];
    int salle_capacity;
    char dispo_machine[4];
}Salle;

/*Les prototypes de notre salles*/

void add_salle(void);
void edit_salle(void);
void delete_salle(void);
void search_salle(void);
void show_salle(void);

bool code_salle_exist(char code[]);
#endif