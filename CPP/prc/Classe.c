#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Classe.h"
#include "Salle.h"
#include "gestion.h"

char *Niv[] = {"Licence", "Master" , "Doctorat"};
/*---------------------------------------------------------------------------------*/

/*Fonction qui permet de vérifier si le code de la classe est unique*/
bool code_classe_exist(char code[])
 {
    FILE *file = fopen("classe.bin","rb+");
    CLASSE verifi_classe;
    while (fread(&verifi_classe,sizeof(CLASSE),1,file) ==1)
    {
        if (strcmp(code,verifi_classe.code_unique)==0)
        {
            return true;
        }
        
    }
    return false;
}
/*---------------------------------------------------------------------------------*/
void add_class()
{
    CLASSE new_class;
    int option;
    FILE *file = fopen("classe.bin","ab+");
    if (file == NULL) {
        fprintf(stderr,"Ressayer plus tard");
        exit(EXIT_FAILURE);
    }
    printf("Veillez saisir le code de votre classe: ");
    scanf("%s",new_class.code_unique);
    while (code_classe_exist(new_class.code_unique))
    {
        printf("Le code que vous avez saisie exite déja veiller en saisir une autre : ");
        scanf("%s",new_class.code_unique);
    }
    
    printf("Veillez saisir le nom de votre classe: ");
    scanf("%s",new_class.class_name);
    printf("Veillez saisr l'effectif de votre classe:");
    scanf("%d",&new_class.class_effectif);
    while (new_class.class_effectif <0) {
        printf("L'effectif de la classe ne peut pas être inférieur à O\n");
        printf("Veillez resaisir l'effectif de la classe: ");
        scanf("%d",&new_class.class_effectif);
    }
    printf("1.%s\n2.%s\n3.%s\nVeillez choisir le niveau de votre classe: ",Niv[0],Niv[1],Niv[2]);
    scanf("%d",&option);
    while (option<=0 || option>3)
    {
        printf("Veillez choisir sur les trois niveaux s'ils vous plait \n1.%s\n2.%s\n3.%s",Niv[0],Niv[1],Niv[2]);
        scanf("%d",&option); 
    }
    strcpy(new_class.class_niveau,Niv[option-1]);
    fwrite(&new_class,sizeof(CLASSE),1,file);
    printf("La classe %s de code %s de niveau %s et d'effectif %d a été bien enregistrée\n",new_class.class_name,new_class.code_unique,new_class.class_niveau,new_class.class_effectif);

    fclose(file);
    gestion_classe();
}

/*---------------------------------------------------------------------------------*/
void edit_class(void)
{
    FILE *file = fopen("classe.bin","rb+");
    FILE *temp = fopen("temp.bin","ab+");
    char codemodif[codecaractere];
    CLASSE edit_clas;
    CLASSE edit_classe;
    int option;
    bool mofier = false;
    if (file == NULL) {
        fprintf(stderr,"Ressayer plus tard");
        exit(EXIT_FAILURE);
    }
    if (temp == NULL) {
        fprintf(stderr,"Ressayer plus tard");
        exit(EXIT_FAILURE);
    }
    printf("Veillez saisir le code de la classe a modifier: ");
    scanf("%s",codemodif);
    while (fread(&edit_classe,sizeof(CLASSE),1,file)==1)
    {
        if (strcmp(edit_classe.code_unique,codemodif)==0)
        {
            printf("Nouveau nom:");
            scanf("%s",edit_clas.class_name);
            printf("Nouveau effectif:");
            scanf("%d",&edit_clas.class_effectif);
            while (edit_clas.class_effectif <0) {
                printf("Veillez resaisir l'effectif de la classe: ");
                printf("L'effectif de la classe ne peut pas être inférieur à O\n");
                scanf("%d",&edit_clas.class_effectif);
            }
            printf("Veillez choisir le niveau de votre classe \n1.%s\n2.%s\n3.%s",Niv[0],Niv[1],Niv[2]);
            scanf("%d",&option);
            while (option<=0 || option>3)
            {
                printf("Veillez choisir sur les trois niveaux s'il vous plait \n1.%s\n2.%s\n3.%s",Niv[0],Niv[1],Niv[2]);
                scanf("%d",&option);
            }
            strcpy(edit_clas.class_niveau,Niv[option-1]);  
            fwrite(&edit_clas,sizeof(CLASSE),1,temp);
            mofier = true;
            continue;
        }
        fwrite(&edit_classe,sizeof(CLASSE),1,temp);
    }
    fclose(temp);
    fclose(file);
    if (mofier)
    {
        printf("Classe modifier avec succes\n");
        remove("classe.bin");
        rename("temp.bin","classe.bin");
    }
    else
    {
        printf("Le code que vous avez saisie n'existe pas encore\n");
        remove("temp.bin");
    }
    gestion_classe();
}

/*---------------------------------------------------------------------------------*/
void search_class(void)
{
    FILE *file = fopen("classe.bin","rb");
    CLASSE sch_classe;
    char sc_code[codecaractere];
    bool trouver=false;
    if (file == NULL) {
        fprintf(stderr,"Ressayer plus tard");
        exit(EXIT_FAILURE);
    }
    printf("Veillez saisir le code de votre classe: ");
    scanf("%s",sc_code);
    while (fread(&sch_classe,sizeof(CLASSE),1,file)==1)
    {
        if (strcmp(sc_code,sch_classe.code_unique)==0)
        {
            printf("NOM : %s\n",sch_classe.class_name);
            printf("CODE : %s\n",sch_classe.code_unique);
            printf("EFFECTIF : %d\n",sch_classe.class_effectif);
            printf("NIVEAU : %s\n",sch_classe.class_niveau);
            trouver=true;
            break;
        }
        
    }
    fclose(file);
    if (trouver)
    {
        printf("Classe trouvé avec succées");
    }
    else
    {
        printf("Il n'existe pas encore de classe avec cette code");
    }
    
    gestion_classe();
}

/*---------------------------------------------------------------------------------*/
void show_class(void)
{
    FILE *file = fopen("classe.bin","rb");
    CLASSE sch_classe;
    if (file == NULL) {
        fprintf(stderr,"Ressayer plus tard");
        exit(EXIT_FAILURE);
    }
    while (fread(&sch_classe,sizeof(CLASSE),1,file)==1)
    {
        printf("==================\n");
        printf("NOM : %s\n",sch_classe.class_name);
        printf("CODE : %s\n",sch_classe.code_unique);
        printf("EFFECTIF : %d\n",sch_classe.class_effectif);
        printf("NIVEAU : %s\n",sch_classe.class_niveau);
        printf("==================\n");
    }
    fclose(file);
    gestion_classe();
}
/*---------------------------------------------------------------------------------*/
void delete_class(void)
{
    FILE *file = fopen("classe.bin","rb+");
    FILE *temp = fopen("temp.bin","ab+");
    char codesuppr[codecaractere];
    CLASSE sup_classe;
    bool supprimer=false;
    if (file == NULL) {
        fprintf(stderr,"Ressayer plus tard");
        exit(EXIT_FAILURE);
    }
    if (temp == NULL) {
        fprintf(stderr,"Ressayer plus tard");
        exit(EXIT_FAILURE);
    }
    printf("Veillez saisir le code de la classe a supprimer: ");
    scanf("%s",codesuppr);
    while (fread(&sup_classe,sizeof(CLASSE),1,file)==1)
    {
        if (strcmp(sup_classe.code_unique,codesuppr)==0)
        {
            supprimer=true;
            continue;
        }
        fwrite(&sup_classe,sizeof(CLASSE),1,temp);
    }
    fclose(temp);
    fclose(file);
    if (supprimer)
    {
        printf("Classe supprimer avec succes\n");
        remove("classe.bin");
        rename("temp.bin","classe.bin");
    }
    else
    {
        printf("Le code que vous avez saisie n'existe pas encore\n");
        remove("temp.bin");
    }
    gestion_classe();
}