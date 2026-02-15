### PROJET-C++
Ceci est un projet de gestion d'une banque en utilisant Le langage Orienté Objet C++
## 📌 Fiche de Conception : Gestion de Compte Bancaire (POO - C++)
## 🎯 Objectif général

Créer une application bancaire orientée objet permettant de gérer des comptes, des clients et la banque dans son ensemble, avec une architecture pensée pour l’évolution future.

## 🧱 Objets (Classes) nécessaires
# 1- CompteBancaire (classe de base)

 Représente un compte générique.
 
 ### Attributs (privés)
 
    solde : montant disponible
    
    numeroCompte : identifiant du compte
    
    proprietaire : nom du client
    
    historiqueOperations : liste des transactions (dépôts/retraits)
    
    tauxInteretAnnuel : pour calculer intérêts (optionnel, selon type de compte)
    
    estPremium : booléen pour comptes premium
 
### Méthodes (publiques)
 
    deposer(montant)
 
    retirer(montant)
 
    afficherSolde()
 
    afficherInfosCompte()
    
    ajouterOperationHistorique(type, montant, date)
    
    calculerInteretsAnnuel()
    
    authentifierUtilisateur(motDePasse)
    
        Règles:
    
            Empêcher les retraits si le solde est insuffisant
    
            Encapsulation stricte pour protéger les données sensibles
    
            Historique et intérêts prêts pour évolution

# 2- CompteCourant (hérite de CompteBancaire)

## Attributs spécifiques : 
    limiteDécouvert, fraisOperation

## Méthodes spécifiques :
     appliquerFrais(), autoriserDecouvert()

# 3- CompteEpargne (hérite de CompteBancaire)

## Attributs spécifiques : tauxInteret, dateDernierCalculInterets

    Méthodes spécifiques : calculerInterets(), ajouterInterets()

 Ici, on utilise héritage pour spécialiser les types de compte.

# 4- Client

Représente un utilisateur de la banque.

## Attributs

    nom, prenom

    listeComptes : std::vector de comptes

    motDePasse : pour authentification

## Méthodes

    ajouterCompte(compte)

    afficherInfosClient()

    afficherTousComptes()

    authentifier(motDePasse)

L’utilisation de std::vector permet de gérer dynamiquement plusieurs comptes.

# 5- Banque

Coordonne tous les clients et comptes.

## Attributs

    nomBanque

    listeClients : std::vector de clients

## Méthodes

    ajouterClient(client)

    rechercherClient(nomOuNumero)

    afficherTousClients()

    afficherTousComptes()

    calculerInteretsTousComptes()

Cette classe centralise la gestion et facilite les extensions futures.

# 🔄 Interactions entre objets
Émetteur	           Action	                       Cible
Client	             Possède et gère	  CompteBancaire (Courant ou Épargne)
Banque	             Gère et retrouve	  Clients et leurs comptes
CompteBancaire	   Suit les opérations	  Historique interne et calcul intérêts
## 🚦 Cas d’utilisation principaux

    Créer un client et l’authentifier

    Créer un compte courant ou épargne (standard ou premium)

    Déposer et retirer de l’argent

    Consulter le solde et les informations du compte

    Consulter l’historique des opérations

    Calculer et appliquer les intérêts annuels

    Afficher tous les clients et comptes

    Sécuriser les accès par mot de passe

Ces cas couvrent l’usage normal et la maintenance future.

## 💡 Évolutions futures / architecture durable

    Héritage : compte courant et compte épargne dérivent de compte générique

    Polymorphisme : opérations spécifiques aux types de comptes

    Encapsulation stricte : protège solde, mot de passe, historique

    Vectorisation : std::vector pour listes dynamiques de comptes et clients

    Comptes premium : fonctionnalités avancées (frais réduits, limites supérieures)

    Historique des opérations : prêt pour journalisation et audit

    Intérêts annuels : calcul automatique selon type de compte

    Authentification utilisateur : sécurité et contrôle d’acc