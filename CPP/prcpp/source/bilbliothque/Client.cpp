#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include "Client.hpp"

Client::Client(string n, string p, vector <comptebanque> L, string m)
{
    nom = n;
    prenom = p;
    ListeComptes = L;
    motDepass = m;
}
void Client::ajouterCompte(comptebanque compte)
{
    ListeComptes.push_back(compte);
}
void Client::afficherInfosClient()
{
    cout << "Nom :" <<nom <<endl;
    cout <<"Prenom : "<<prenom << endl;
    cout << "Nombre de compte : "<<ListeComptes.size()<<endl;
}
void Client::afficherTousCoumpte()
{
    for(int i{0}; i< ListeComptes.size();i++)
    {
        cout << "Compte N° "<<i+1<<endl;
        ListeComptes[i].afficherInfosCompte();
    }
}
bool Client::authentifier(string passkey)
{
    for(int i=0;i<motDepass.length();i++)
    {
        if(passkey[i]!=motDepass[i])
        {
            return false;
        }
    }
    return true;
}
