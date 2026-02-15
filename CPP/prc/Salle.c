#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Salle.h"
#include "Classe.h"
#include "gestion.h"


/*----------------------------------------------------------------------------------------------------------------*/

/*Fonction qui permet de vérifier si le code de la salle est unique*/
bool code_salle_exist(char code[])
 {
    FILE *file = fopen("salle.bin","rb+");
    Salle verifi_classe;
    while (fread(&verifi_classe,sizeof(Salle),1,file)==1)
    {
        if (strcmp(code,verifi_classe.code_salle)==0)
        {
            return true;
        }
        
    }
    return false;
}

/*----------------------------------------------------------------------------------------------------------------*/
void add_salle()
{
    Salle new_salle;
    int option;
    FILE *file = fopen("salle.bin","ab+");
    if (file == NULL) {
        fprintf(stderr,"Ressayer plus tard");
        exit(EXIT_FAILURE);
    }
    printf("Veillez saisir le code de votre salle: ");
    scanf("%s",new_salle.code_salle);
    while (code_classe_exist(new_salle.code_salle))
    {
        printf("Le code que vous avez saisie exite déja veiller en saisir une autre : ");
        scanf("%s",new_salle.code_salle);
    }
    
    printf("Veillez saisir le nom de votre salle: ");
    scanf("%s",new_salle.salle_name);
    printf("Veillez saisr la capacité de votre salle:");
    scanf("%d",&new_salle.salle_capacity);
    while (new_salle.salle_capacity <0) {
        printf("La capacité de la salle ne peut pas être inférieur à O\n");
        printf("Veillez resaisir la capacité de votre salle: ");
        scanf("%d",&new_salle.salle_capacity);
    }
    printf("1.OUI\n2.NON\nVotre salle dispose t-elle des machine: ");
    scanf("%d",&option);
    while (option<=0 || option>2)
    {
        printf("Veillez choisir entre 1(OUI) et 2(NON)");
        scanf("%d",&option); 
    } 
    if(option==1)
        strcpy(new_salle.dispo_machine,"OUI");
    else
        strcpy(new_salle.dispo_machine,"NON");
    fwrite(&new_salle,sizeof(Salle),1,file);
    printf("La salle %s de code %s de capacité %d et de disposition des machines %s a été bien enregistrée\n",new_salle.salle_name,new_salle.code_salle,new_salle.salle_capacity,new_salle.dispo_machine);

    fclose(file);
    gestion_salle();
}

/*----------------------------------------------------------------------------------------------------------------*/

void edit_salle(void)
{
    FILE *file = fopen("salle.bin","rb+");
    FILE *temp = fopen("temp.bin","ab+");
    char codemodif[codeslcaractere];
    Salle edit_sal;
    Salle edit_sall;
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
    while (fread(&edit_sall,sizeof(Salle),1,file)==1)
    {
        if (strcmp(edit_sall.code_salle,codemodif)==0)
        {
            printf("Nouveau nom:");
            scanf("%s",edit_sal.salle_name);
            printf("Nouveau capacité:");
            scanf("%d",&edit_sal.salle_capacity);
            while (edit_sal.salle_capacity <0) {
                printf("Veillez resaisir l'effectif de la classe: ");
                printf("L'effectif de la classe ne peut pas être inférieur à O\n");
                scanf("%d",&edit_sal.salle_capacity);
            }
            printf("1.OUI\n2.NON\nVotre salle dispose t-elle des machine: ");
            scanf("%d",&option);
            while (option<=0 || option>2)
            {
                printf("Veillez choisir entre 1(OUI) et 2(NON)");
                scanf("%d",&option); 
            } 
            if(option==1)
                strcpy(edit_sal.dispo_machine,"OUI");
            else
                strcpy(edit_sal.dispo_machine,"NON");
            fwrite(&edit_sal,sizeof(Salle),1,temp);
            mofier = true;
            continue;
        }
        fwrite(&edit_sall,sizeof(Salle),1,temp);
    }
    fclose(temp);
    fclose(file);
    if (mofier)
    {
        printf("Salle modifier avec succes\n");
        remove("salle.bin");
        rename("temp.bin","salle.bin");
    }
    else
    {
        printf("Le code que vous avez saisie n'existe pas encore\n");
        remove("temp.bin");
    }
    gestion_salle();
}

/*----------------------------------------------------------------------------------------------------------------*/
void search_salle(void)
{
    FILE *file = fopen("salle.bin","rb");
    Salle sch_salle;
    char sc_code[codeslcaractere];
    bool trouver=false;
    if (file == NULL) {
        fprintf(stderr,"Ressayer plus tard");
        exit(EXIT_FAILURE);
    }
    printf("Veillez saisir le code de votre classe: ");
    scanf("%s",sc_code);
    while (fread(&sch_salle,sizeof(Salle),1,file)==1)
    {
        if (strcmp(sc_code,sch_salle.code_salle)==0)
        {
            printf("NOM : %s\n",sch_salle.salle_name);
            printf("CODE : %s\n",sch_salle.code_salle);
            printf("CAPACITE : %d\n",sch_salle.salle_capacity);
            printf("DISPONIBILITE DES MACHINES : %s\n",sch_salle.dispo_machine);
            trouver=true;
            break;
        }
        
    }
    fclose(file);
    if (trouver)
    {
        printf("Salle trouvé avec succées");
    }
    else
    {
        printf("Il n'existe pas encore de salle avec cette code");
    }
    
    gestion_salle();
}
/*----------------------------------------------------------------------------------------------------------------*/
void show_salle(void)
{
    FILE *file = fopen("salle.bin","rb");
    Salle sch_salle;
    if (file == NULL) {
        fprintf(stderr,"Ressayer plus tard");
        exit(EXIT_FAILURE);
    }
    while (fread(&sch_salle,sizeof(Salle),1,file)==1)
    {
        printf("==================\n");
        printf("NOM : %s\n",sch_salle.salle_name);
        printf("CODE : %s\n",sch_salle.code_salle);
        printf("CAPACITE : %d\n",sch_salle.salle_capacity);
        printf("DISPONIBILITE DES MACHINES : %s\n",sch_salle.dispo_machine);
        printf("==================\n");
    }
    fclose(file);
    gestion_salle();
}

/*----------------------------------------------------------------------------------------------------------------*/
void delete_salle(void)
{
    FILE *file = fopen("salle.bin","rb+");
    FILE *temp = fopen("temp.bin","ab+");
    char codesuppr[codeslcaractere];
    Salle sup_salle;
    bool supprimer=false;
    if (file == NULL) {
        fprintf(stderr,"Ressayer plus tard");
        exit(EXIT_FAILURE);
    }
    if (temp == NULL) {
        fprintf(stderr,"Ressayer plus tard");
        exit(EXIT_FAILURE);
    }
    printf("Veillez saisir le code de la salle a supprimer: ");
    scanf("%s",codesuppr);
    while (fread(&sup_salle,sizeof(Salle),1,file)==1)
    {
        if (strcmp(sup_salle.code_salle,codesuppr)==0)
        {
            supprimer=true;
            continue;
        }
        fwrite(&sup_salle,sizeof(Salle),1,temp);
    }
    fclose(temp);
    fclose(file);
    if (supprimer)
    {
        printf("Salle supprimer avec succes\n");
        remove("salle.bin");
        rename("temp.bin","salle.bin");
    }
    else
    {
        printf("Le code que vous avez saisie n'existe pas encore\n");
        remove("temp.bin");
    }
    gestion_salle();
}