#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "Classe.h"
#include "Salle.h"
#include "Reservation.h"
#include "Utils.h"
/*----------------------------------------------------------------------------------------*/
bool existance_jour(int j,int m, int an )
{
    if (m == 1 || m==3 || m==5 || m==7 || m==8 || m==10 ||m==12)
    {
        if(j>0 || j<=31)
        {
            return true;
        } 
        return false;
    }
    if (m==4 || m==6 || m==9 || m==11)
    {
        if(j>0 || j<=30)
        {
            return true;
        } 
        return false;
    }  
    if (m==2 && an % 4 == 0)
    {
        if(j>0 || j<=29)
        {
            return true;
        } 

        return false;
    }   
    else if (m==2)
    {
        if(j>0 || j<=28)
        {
            return true;
        } 

        return false;
    }   
}
/*----------------------------------------------------------------------------------------*/
bool sauvauch_t_il(Reservation a_verifiier )
{
    Reservation verifie;
    FILE *file = fopen("reservation.bin","rb+");
    while (fread(&verifie,sizeof(Reservation),1,file) ==1 )
    {
        if (verifie.Heure_de_debut == a_verifiier.Heure_de_debut && verifie.Heure_de_fin == a_verifiier.Heure_de_fin && verifie.date_de_reserv.jour == a_verifiier.date_de_reserv.jour && verifie.date_de_reserv.mois == a_verifiier.date_de_reserv.mois && verifie.date_de_reserv.annee == a_verifiier.date_de_reserv.annee )
        {
            fclose(file);
            return true;
        }
        else if (verifie.Heure_de_debut < a_verifiier.Heure_de_debut && verifie.Heure_de_fin > a_verifiier.Heure_de_debut && verifie.date_de_reserv.jour == a_verifiier.date_de_reserv.jour && verifie.date_de_reserv.mois == a_verifiier.date_de_reserv.mois && verifie.date_de_reserv.annee == a_verifiier.date_de_reserv.annee )
        {
            fclose(file);
            return true;
        }
        else if (verifie.Heure_de_debut < a_verifiier.Heure_de_fin && verifie.Heure_de_fin > a_verifiier.Heure_de_fin && verifie.date_de_reserv.jour == a_verifiier.date_de_reserv.jour && verifie.date_de_reserv.mois == a_verifiier.date_de_reserv.mois && verifie.date_de_reserv.annee == a_verifiier.date_de_reserv.annee )
        {
            fclose(file);
            return true;
        }
        else if(a_verifiier.Heure_de_debut > a_verifiier.Heure_de_fin)
        {
            fclose(file);
            return true;
        }
        fclose(file);
        return false;
    }
    /*Ce fonction permet de vérifier si la reservation n'as pas encore été choisi*/
}
/*----------------------------------------------------------------------------------------*/
void add_reserv(void)
{
    FILE *file1 = fopen("classe.bin","rb+");
    FILE *file2 = fopen("salle.bin","rb+");
    Reservation new_reserv;
    FILE *file = fopen("reservation.bin","ab+");
    CLASSE one_classe;
    Salle one_salle;
    char rep;
    srand(time(NULL));
    if (file == NULL)
    {
        fprintf(stderr,"Erreur d'ouverture, Veillez ressayer plustard");
        exit(EXIT_FAILURE);
    }
    if (file1 == NULL) {
        fprintf(stderr,"Ressayer plus tard");
        exit(EXIT_FAILURE);
    }
    if (file2 == NULL) {
        fprintf(stderr,"Ressayer plus tard");
        exit(EXIT_FAILURE);
    }
    new_reserv.Num_reserv = (rand() % 1000) + 1; /*Le numéro de réservation elle est donné 
    aléatoirement avec la fonction rand()*/
    printf("Veillez saisir le code de votre classe: ");
    scanf("%s",new_reserv.code_classe_reserv);
    while(code_classe_exist(new_reserv.code_classe_reserv))/*Le code de la classe permet de voir
    si la classe que vous voudrais réservé existe*/
    {
        printf("Le code que vous avez saisi n'existe pas\nveillez la resaisir: ");
        scanf("%s",new_reserv.code_classe_reserv);   
    }
/*Le bout de code suivant permet de saisir une salle cependant on doit vérifier si la capacité de 
la salle saisie est capable de recevoir l'effectif de la classe pour cela on lit la classe dans
un variable et la salle dans un variable puis on compare l'effectif de la classe et la capacité de 
la salle cependant pour éviter la repetition du code et l'utilisation du boucle while ou do..while
j'ai préferer utiliser la fonction goto*/
    Revenir_ici_pour_retaper_la_salle_de_clase:
    printf("Veillez saisir le code de votre salle: ");
    scanf("%s",new_reserv.code_salle_reserv);
    while (code_salle_exist(new_reserv.code_salle_reserv));
    {
        printf("Le code que vous avez saisi n'existe pas\nveillez la resaisir: ");
        scanf("%s",new_reserv.code_salle_reserv);       
    }
    while (fread(&one_classe,sizeof(CLASSE),1,file1) == 1)
    {
        if (strcmp(one_classe.code_unique,new_reserv.code_classe_reserv)==0)
        {
            break;
        }
    }
    while (fread(&one_salle,sizeof(Salle),1,file2)==1)
    {
        if (strcmp(one_salle.code_salle,new_reserv.code_salle_reserv)==0)
        {
         break;
        }   
    }
    if (one_salle.salle_capacity < one_classe.class_effectif)
    {
        printf("La salle n'est pas assez grand pour contenir l'effectif de la classe, Veuillez choisir une autre salle\n");
        goto Revenir_ici_pour_retaper_la_salle_de_clase;
    } 
    fclose(file1);
    fclose(file2);
    /*Le bout de code suivant nous permet de gerer la date de la reservation en donnant le jour 
    et la date en format JJ/MM/AAAA eet on vérifie si le années n'est bissextile et le nombre de 
    mois et exact et que le jour choisie en fonction du mois est-elle correct*/
    Rechoisir_une_date_de_reservation:
    printf("Saisie de la date JJ/MM/AAAA\n");
    printf("AAAA: ");
    scanf("%d",&new_reserv.date_de_reserv.annee);
    while (new_reserv.date_de_reserv.annee < ANNNES_COURANT)
    {
        printf("L'annes que vous avez saisie n'est pas bon veillez la resaisir: ");
        scanf("%d",&new_reserv.date_de_reserv.annee);
    }
    printf("MM: ");
    scanf("%d",&new_reserv.date_de_reserv.mois);
    while (new_reserv.date_de_reserv.mois < MOIS)
    {
        printf("L'annes que vous avez saisie n'est pas bon veillez la resaisir: ");
        scanf("%d",&new_reserv.date_de_reserv.mois);
    }

    printf("JJ : ");
    scanf("%d",&new_reserv.date_de_reserv.jour);
    while (!existance_jour(new_reserv.date_de_reserv.jour,new_reserv.date_de_reserv.mois,new_reserv.date_de_reserv.annee))
    {
        printf("Le jour que vous avez saisie n'est bon veillez la resaisir: ");
        scanf("%d",&new_reserv.date_de_reserv.jour);
    }
    printf("Veillez saisr l'heure de debut : ");
    scanf("%d",&new_reserv.Heure_de_debut);
    while (new_reserv.Heure_de_debut < 8 || new_reserv.Heure_de_debut > 19);
    {
        printf("Veillez la resaisir c'est pas bon : ");
        scanf("%d",&new_reserv.Heure_de_debut);
    }
    printf("Veillez saisr l'heure de fin : ");
    scanf("%d",&new_reserv.Heure_de_fin);
    while (new_reserv.Heure_de_fin < 8 || new_reserv.Heure_de_fin > 19);
    {
        printf("Veillez la resaisir c'est pas bon : ");
        scanf("%d",&new_reserv.Heure_de_fin);
    }
    /*Cependant il faut vérifier si deux classe ne sont pas reserve dans une même salle
    le même jour et la même heure*/
    if(sauvauch_t_il(new_reserv))
    {
        printf("Votre reservation sauvauche avec une autre reservation\n");
        printf("Voudrais vous choisir une nouvelle date tapez O ou si vous voulez le mettre en attente tapez N");
        scanf("%c",&rep);
        if(rep == 'O' || rep == 'o'){
            goto Rechoisir_une_date_de_reservation;
        }
        else if(rep == 'N' || rep == 'n'){
            new_reserv.etat_reserv = EN_ATTENTE;
        }
    }
    else
    {
        new_reserv.etat_reserv = VALIDE;
    }
    printf("Veillez saisir le motif de votre reservation: ");
    scanf("%s",new_reserv.motif);
    fwrite(&new_reserv,sizeof(Reservation),1,file);
    fclose(file);
}

/*----------------------------------------------------------------------------*/
void edit_reserv()
{
    Reservation edit_reserve;
    FILE *file = fopen("reservation.bin","rb+");
    FILE *temp = fopen("temp.bin","ab+");
    FILE *file1 = fopen("classe.bin","rb+");
    FILE *file2 = fopen("salle.bin","rb+");
    CLASSE one_classe;
    int numero_modif;
    Salle one_salle;
    char rep;
    bool trouver = false;
    if (temp == NULL)
    {
        fprintf(stderr,"Erreur d'ouverture, Veillez ressayer plustard");
        exit(EXIT_FAILURE);
    }
    if (file == NULL)
    {
        fprintf(stderr,"Erreur d'ouverture, Veillez ressayer plustard");
        exit(EXIT_FAILURE);
    }
    if (file1 == NULL) {
        fprintf(stderr,"Ressayer plus tard");
        exit(EXIT_FAILURE);
    }
    if (file2 == NULL) {
        fprintf(stderr,"Ressayer plus tard");
        exit(EXIT_FAILURE);
    }
    printf("Veillez saisir le numéro du reservation que vous voudrais modifier:");
    scanf("%d",&numero_modif);
    while(fread(&edit_reserve,sizeof(Reservation),1,file)==1)
    {
        if(edit_reserve.Num_reserv == numero_modif)
        {
            trouver = true;
            printf("Nouvelle classe: ");
            scanf("%s",edit_reserve.code_classe_reserv);
            while(code_classe_exist(edit_reserve.code_classe_reserv))
            {
                printf("Le code que vous avez saisi n'existe pas\nveillez la resaisir: ");
                scanf("%s",edit_reserve.code_classe_reserv);   
            }
            Revenir_ici_pour_retaper_la_salle_de_clase:
            printf("Nouvelle salle: ");
            scanf("%s",edit_reserve.code_salle_reserv);
            while (code_salle_exist(edit_reserve.code_salle_reserv));
            {
                printf("Le code que vous avez saisi n'existe pas\nveillez la resaisir: ");
                scanf("%s",edit_reserve.code_salle_reserv);       
            }
            while (fread(&one_classe,sizeof(CLASSE),1,file1) == 1)
            {
                if (strcmp(one_classe.code_unique,edit_reserve.code_classe_reserv)==0)
                {
                    break;
                }
            }
            while (fread(&one_salle,sizeof(Salle),1,file2)==1)
            {
                if (strcmp(one_salle.code_salle,edit_reserve.code_salle_reserv)==0)
                {
                 break;
                }   
            }
            if (one_salle.salle_capacity < one_classe.class_effectif)
            {
                printf("La salle n'est pas assez grand pour contenir l'effectif de la classe, Veuillez choisir une autre salle\n");
                goto Revenir_ici_pour_retaper_la_salle_de_clase;
            } 
            fclose(file1);
            fclose(file2);
            Rechoisir_une_date_de_reservation:
            printf("Nouvelle date JJ/MM/AAAA\n");
            printf("AAAA: ");
            scanf("%d",&edit_reserve.date_de_reserv.annee);
            while (edit_reserve.date_de_reserv.annee < ANNNES_COURANT)
            {
                printf("L'annes que vous avez saisie n'est pas bon veillez la resaisir: ");
                scanf("%d",&edit_reserve.date_de_reserv.annee);
            }
            printf("MM: ");
            scanf("%d",&edit_reserve.date_de_reserv.mois);
            while (edit_reserve.date_de_reserv.mois < MOIS)
            {
                printf("L'annes que vous avez saisie n'est pas bon veillez la resaisir: ");
                scanf("%d",&edit_reserve.date_de_reserv.mois);
            }
        
            printf("JJ : ");
            scanf("%d",&edit_reserve.date_de_reserv.jour);
            while (!existance_jour(edit_reserve.date_de_reserv.jour,edit_reserve.date_de_reserv.mois,edit_reserve.date_de_reserv.annee))
            {
                printf("Le jour que vous avez saisie n'est bon veillez la resaisir: ");
                scanf("%d",&edit_reserve.date_de_reserv.jour);
            }
            printf("Nouvelle heure de debut : ");
            scanf("%d",&edit_reserve.Heure_de_debut);
            while (edit_reserve.Heure_de_debut < 8 || edit_reserve.Heure_de_debut > 19);
            {
                printf("Veillez la resaisir c'est pas bon : ");
                scanf("%d",&edit_reserve.Heure_de_debut);
            }
            printf("Nouvelle heure de fin : ");
            scanf("%d",&edit_reserve.Heure_de_fin);
            while (edit_reserve.Heure_de_fin < 8 || edit_reserve.Heure_de_fin > 19);
            {
                printf("Veillez la resaisir c'est pas bon : ");
                scanf("%d",&edit_reserve.Heure_de_fin);
            }
            if(sauvauch_t_il(edit_reserve))
            {
                printf("Cette date et heure de reservation a deja ete choisie\n");
                printf("Voudrais vous annule la reservation tapez O ou bien si vous voulez changer la date de reservation tapez N:");
                scanf("%c",&rep);
                while (!(rep == 'O' || rep =='o'||rep == 'N' || rep =='n'))
                {
                    printf("Veillez choisir entre ces deux lettre s'ils vous plait:");
                    scanf("%c",&rep);
                }
                
                if(rep == 'O' || rep =='o'){
                    edit_reserve.etat_reserv = ANNULER;
                }
                else{
                    printf("Vous devez choisir une nouvelle date.\n");
                    goto Rechoisir_une_date_de_reservation;
                }
            }
            else 
            {
                edit_reserve.etat_reserv = VALIDE;
            }
            printf("Nouvelle le motif de votre reservation: ");
            scanf("%s",edit_reserve.motif);
            fwrite(&edit_class,sizeof(Reservation),1,temp);
            continue;
        }
        fwrite(&edit_class,sizeof(Reservation),1,temp);
    }

    fclose(file);
    fclose(temp);
    if(trouver)
    {
        printf("Classe modifier avec succes\n");
        remove("reservation.bin");
        rename("temp.bin", "reservation.bin");
    }
    else
    {
        printf("Le numero de reservation n'as pas ete retrouver\n");
        remove("temp.bin");
    }

}
/*--------------------------------------------------------------------------*/
void search_reserv()
{
    Reservation rech_reser;
    int num_rech_reser;
    FILE *file = fopen("reservation.bin","rb+");
    if (file == NULL)
    {
        fprintf(stderr,"Erreur d'ouverture, Veillez ressayer plustard");
        exit(EXIT_FAILURE);
    }
    printf("Veillez saisir le numero de reservation rechercher: ");
    scanf("%d",&num_rech_reser);
    while (fread(&rech_reser,sizeof(Reservation),1,file)==1)
    {
        if (num_rech_reser == rech_reser.Num_reserv)
        {
            printf("Numero de reservation : %d\t",rech_reser.Num_reserv);
            printf("Nom de la classe: %s\t",getNameClasse(rech_reser.code_classe_reserv).class_name);
            printf("Nom de la salle:%s\t",getNameSalle(rech_reser.code_salle_reserv).salle_name);
            printf("Date : %d/%d/%d\t",rech_reser.date_de_reserv.jour,rech_reser.date_de_reserv.mois,rech_reser.date_de_reserv.annee);
            printf("Heure de debut:%d\t",rech_reser.Heure_de_debut);
            printf("Heure de fin:%d\t",rech_reser.Heure_de_fin);
            printf("Duree:%d\t",(rech_reser.Heure_de_fin - rech_reser.Heure_de_debut));
            printf("Motif:%s\t",rech_reser.motif);
            getEtatReservation(rech_reser);
            printf("Reservation trouver avec succes\n");
            break;
        }
    
    }

    fclose(file);
}
/*--------------------------------------------------------------------------*/
void show_reserv()
{
    Reservation rech_reser;
    FILE *file = fopen("reservation.bin","rb+");
    if (file == NULL)
    {
        fprintf(stderr,"Erreur d'ouverture, Veillez ressayer plustard");
        exit(EXIT_FAILURE);
    }
    printf("Voici la liste de tous les reservations\n");
    while (fread(&rech_reser,sizeof(Reservation),1,file)==1)
    {
        printf("=====================================\n");
        printf("Numero de reservation : %d\t",rech_reser.Num_reserv);
        printf("Nom de la classe: %s\t",getNameClasse(rech_reser.code_classe_reserv).class_name);
        printf("Nom de la salle:%s\t",getNameSalle(rech_reser.code_salle_reserv).salle_name);
        printf("Date : %d/%d/%d\t",rech_reser.date_de_reserv.jour,rech_reser.date_de_reserv.mois,rech_reser.date_de_reserv.annee);
        printf("Heure de debut:%d\t",rech_reser.Heure_de_debut);
        printf("Heure de fin:%d\t",rech_reser.Heure_de_fin);
        printf("Duree:%d\t",(rech_reser.Heure_de_fin - rech_reser.Heure_de_debut));
        printf("Motif:%s\t",rech_reser.motif);
        getEtatReservation(rech_reser);
        printf("=====================================\n");
    }
    fclose(file);
}
void search_reser_class()
{
    Reservation une_reserv;
    FILE *file = fopen("reservation.bin","rb+");
    char codec[codecaractere];
    if (file == NULL)
    {
        fprintf(stderr,"Erreur d'ouverture, Veillez ressayer plus tard");
        exit(EXIT_FAILURE);
    }
    printf("Veillez saisir le code votre classe: ");
    scanf("%s",codec);
    while (fread(&une_reserv,sizeof(Reservation),1,file)==1)
    {
        if (strcmp(getNameClasse(codec).code_unique,une_reserv.code_classe_reserv)==0)
        {
            printf("=====================================\n");
            printf("Numero de reservation : %d\n",une_reserv.Num_reserv);
            printf("Nom de la classe: %s\t",getNameClasse(une_reserv.code_classe_reserv).class_name);
            printf("Nom de la salle:%s\t",getNameSalle(une_reserv.code_salle_reserv).salle_name);
            printf("Date : %d/%d/%d\t",une_reserv.date_de_reserv.jour,une_reserv.date_de_reserv.mois,une_reserv.date_de_reserv.annee);
            printf("Heure de debut:%d\t",une_reserv.Heure_de_debut);
            printf("Heure de fin:%d\t",une_reserv.Heure_de_fin);
            printf("Duree:%d\t",(une_reserv.Heure_de_fin - une_reserv.Heure_de_debut));
            printf("Motif:%s\t",une_reserv.motif);
            getEtatReservation(une_reserv);
            printf("=====================================\n");
        }
        
    }
    fclose(file);
    
}

void search_reser_salle()
{
    Reservation une_reserv;
    FILE *file = fopen("reservation.bin","rb+");
    char codec[codeslcaractere];
    if (file == NULL)
    {
        fprintf(stderr,"Erreur d'ouverture, Veillez ressayer plus tard");
        exit(EXIT_FAILURE);
    }
    printf("Veillez saisir le code votre salle: ");
    scanf("%s",codec);
    while (fread(&une_reserv,sizeof(Reservation),1,file)==1)
    {
        if (strcmp(getNameSalle(codec).code_salle,une_reserv.code_salle_reserv)==0)
        {
            printf("=====================================\n");
            printf("Numero de reservation : %d\n",une_reserv.Num_reserv);
            printf("Nom de la classe: %s\t",getNameClasse(une_reserv.code_classe_reserv).class_name);
            printf("Nom de la salle:%s\t",getNameSalle(une_reserv.code_salle_reserv).salle_name);
            printf("Date : %d/%d/%d\t",une_reserv.date_de_reserv.jour,une_reserv.date_de_reserv.mois,une_reserv.date_de_reserv.annee);
            printf("Heure de debut:%d\t",une_reserv.Heure_de_debut);
            printf("Heure de fin:%d\t",une_reserv.Heure_de_fin);
            printf("Duree:%d\t",(une_reserv.Heure_de_fin - une_reserv.Heure_de_debut));
            printf("Motif:%s\t",une_reserv.motif);
            getEtatReservation(une_reserv);
            printf("=====================================\n");
        }
        
    }
    fclose(file);
    
}

void planing_salle()
{
    Reservation une_reserv;
    FILE *file = fopen("reservation.bin","rb+");
    char codec[codeslcaractere];
    if (file == NULL)
    {
        fprintf(stderr,"Erreur d'ouverture, Veillez ressayer plus tard");
        exit(EXIT_FAILURE);
    }
    printf("Veillez saisir le code votre salle: ");
    scanf("%s",codec);
    while (fread(&une_reserv,sizeof(Reservation),1,file)==1)
    {
        if (strcmp(getNameSalle(codec).code_salle,une_reserv.code_salle_reserv)==0)
        {
            if(une_reserv.etat_reserv != VALIDE)
            {
                continue;
            }
            printf("=====================================\n");
            printf("Numero de reservation : %d\n",une_reserv.Num_reserv);
            printf("Nom de la classe: %s\t",getNameClasse(une_reserv.code_classe_reserv).class_name);
            printf("Nom de la salle:%s\t",getNameSalle(une_reserv.code_salle_reserv).salle_name);
            printf("Date : %d/%d/%d\t",une_reserv.date_de_reserv.jour,une_reserv.date_de_reserv.mois,une_reserv.date_de_reserv.annee);
            printf("Heure de debut:%d\t",une_reserv.Heure_de_debut);
            printf("Heure de fin:%d\t",une_reserv.Heure_de_fin);
            printf("Duree:%d\t",(une_reserv.Heure_de_fin - une_reserv.Heure_de_debut));
            printf("Motif:%s\t",une_reserv.motif);
            getEtatReservation(une_reserv);
            printf("=====================================\n");
        }
        
    }
    fclose(file);
     
}

void planing_class()
{
    Reservation une_reserv;
    FILE *file = fopen("reservation.bin","rb+");
    char codec[codecaractere];
    if (file == NULL)
    {
        fprintf(stderr,"Erreur d'ouverture, Veillez ressayer plus tard");
        exit(EXIT_FAILURE);
    }
    printf("Veillez saisir le code votre classe: ");
    scanf("%s",codec);
    while (fread(&une_reserv,sizeof(Reservation),1,file)==1)
    {
        if (strcmp(getNameClasse(codec).code_unique,une_reserv.code_classe_reserv)==0)
        {
            if(une_reserv.etat_reserv != VALIDE)
            {
                continue;
            }
            printf("=====================================\n");
            printf("Numero de reservation : %d\t",une_reserv.Num_reserv);
            printf("Nom de la classe: %s\t",getNameClasse(une_reserv.code_classe_reserv).class_name);
            printf("Nom de la salle:%s\t",getNameSalle(une_reserv.code_salle_reserv).salle_name);
            printf("Date : %d/%d/%d\t",une_reserv.date_de_reserv.jour,une_reserv.date_de_reserv.mois,une_reserv.date_de_reserv.annee);
            printf("Heure de debut:%d\t",une_reserv.Heure_de_debut);
            printf("Heure de fin:%d\t",une_reserv.Heure_de_fin);
            printf("Duree:%d\t",(une_reserv.Heure_de_fin - une_reserv.Heure_de_debut));
            printf("Motif:%s\t",une_reserv.motif);
            getEtatReservation(une_reserv);
            printf("=====================================\n");
        }
        
    }
    fclose(file);
       
}


void Most_use_salle()
{
    Reservation une_reserv, autre_reserv;
    int *nbr_de_salle_reserve, nbr = 0, i =0,imin,tempt;
    char code[codeslcaractere];
    FILE *file = fopen("reservation.bin","rb+");
    FILE *temp = fopen("codesalle.bin","ab+");
    bool deja_vue = false;
    if (file == NULL)
    {
        fprintf(stderr,"Erreur d'ouverture, Veillez ressayer plus tard");
        exit(EXIT_FAILURE);
    }
    if (temp == NULL)
    {
        fprintf(stderr,"Erreur d'ouverture, Veillez ressayer plus tard");
        exit(EXIT_FAILURE);
    }
    nbr_de_salle_reserve = malloc(sizeof(int));
    while (fread(&une_reserv,sizeof(Reservation),1,file)==1)
    {
        while (fread(&code,sizeof(char[codeslcaractere]),1,file)==1)
        {
            if (strcmp(une_reserv.code_salle_reserv,code)==0)
            {
                deja_vue = true;
            }
            
        }
        if (deja_vue)
        {
            continue;
        }
        
        nbr =0;
        while (fread(&autre_reserv,sizeof(Reservation),1,file)==1)
        {
            if(strcmp(une_reserv.code_salle_reserv,autre_reserv.code_salle_reserv)==0)
            {
                nbr +=1;
            }
        }
        nbr_de_salle_reserve[i] = nbr;
        i++;
        nbr_de_salle_reserve = realloc(nbr_de_salle_reserve,sizeof(int));
        fwrite(&une_reserv.code_salle_reserv,sizeof(char[codeslcaractere]),1,temp);
    }
    for ( i = 0; i < nbr_de_salle_reserve-1; i++)
    {
        imin = i;
        for (int j = i+1; j < nbr_de_salle_reserve; j++)
        {
            if(nbr_de_salle_reserve[j]>nbr_de_salle_reserve[imin])
            {
                imin = j;
            }
        }
        tempt = nbr_de_salle_reserve[imin];
        nbr_de_salle_reserve[imin] = nbr_de_salle_reserve[i];
        nbr_de_salle_reserve[i] = tempt;
    }
    printf("Code        Rang        nombre\n");
    while (fread)
    {
        /* code */
    }
    
    
    fclose(temp);
    remove("temp.bin");
    free(nbr_de_salle_reserve);
    fclose(file);
}