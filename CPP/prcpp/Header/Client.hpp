#ifndef _CLIENT_
    #define _CLIENT_
    #include <string>
    #include <vector>
    #include "comptebancaire.hpp"
    using namespace std;
    class Client
    {
    private:
        string nom;
        string prenom;
        vector <comptebanque> ListeComptes;
        string motDepass;
    public:
        Client(string n, string p, vector <comptebanque> L, string m);
        void ajouterCompte(comptebanque compte);
        void afficherInfosClient();
        void afficherTousCoumpte();
        bool authentifier(string motDepass);
    }; 
#endif
