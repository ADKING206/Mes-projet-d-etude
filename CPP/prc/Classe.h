#ifndef _CLASSE_H_
#define _CLASSE_H_

#define codecaractere 6
/*Défintion d'une classe*/

typedef struct CLASSE 
{
    char code_unique[codecaractere];
    char class_name[26];
    char class_niveau[10];
    int class_effectif ;
}CLASSE;

/*Prototype de notre classe*/

void add_class(void);
void edit_class(void);
void delete_class(void);
void search_class(void);
void show_class(void);


bool code_classe_exist(char code[]);
#endif