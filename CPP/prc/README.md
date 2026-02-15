### PROJET TUTORE 
## Gestion des réservations de salles de la section informatique
### Pour mener à bien notre projet nous auront besoin :
+ De definir des structures avec leur prototypes de fonction
+ De définier des fonctions d'inter-dépendance
+ De créer des biblithéques .h pour ne pas emcombrer notre projet
#### Classe :
    Une classes est caractérisé par:
        code unique
        Nom
        Niveau
        Effectif
    Les prototypes de notre classe:
        add_class()
        edit_class()
        delete_class()
        search_class()
        show_class()
#### Salle:
    Une salles est caractérisé par:
        code unique
        Nom
        capacité
        disponibilité des machines
    Les prototypes de notre salles:
        add_salle()
        edit_salle()
        delete_salle()
        search_salle()
        show_salle()
#### Réservations:
    Une réservation est caractérisé par:
        Numéro unique
        ${code d'une salle}
        ${code d'une classe}
        La date
        Heure de début
        Heure de fin
        motif
        etat
    Les prototype de notre réservation:
        add_reserv()
        edit_reserv()
        delete_reserv()
        search_reserv()
        show_reserv()
        search_reserv_classe()
        search_reserv_salle()
        planing_class()
        planing_salle()
        Most_use_salle()
#### Fonctions Supplémentaire:
    Gestion_des_classe()
    Gestion_des_salles()
    Gestion_des_reserv()
    menu()


