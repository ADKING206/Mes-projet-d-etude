#include "comptebancaire.hpp"
#include <iostream>
#include <string>
using namespace std;
comptebanque::comptebanque(double s,string nu_c,string pro,string histo,float TA)
{
    _solde = s;
    _numeroCompte = nu_c;
    _proprietaire = pro;
    _historiquedoperation = histo;
    _tauxinteretannuel = TA;
    _estPremium = false;
}
void comptebanque::deposer(double montant)
{
    _solde +=montant;
}
void comptebanque::retirer(double montant)
{
    _solde -=montant;
}
void comptebanque::afficherSolde()
{
    cout << "Votre solde est de : "<<_solde<<endl;
}
void comptebanque::afficherInfosCompte()
{
    cout<< "Proprietaire: " << _proprietaire <<endl;
    cout << "Numero de compte: "<< _numeroCompte<<endl;
    cout << "votre solde: "<<_solde<<endl;
}
void comptebanque::ajouterOperationHistorique(string type, float montant ,Date _date )
{
    cout << "Type d'operation : "<<type<<endl;
    cout << "montant : "<<montant<<endl;
    cout <<"Date: "<<_date.jour<<"/"<<_date.mois<<"/"<<_date.annes<<endl;
}
float comptebanque::calculerInteretAnnuel()
{
     
}
