#ifndef _COMPEEBANCAIRE_
    #define _COMPEEBANCAIRE_
    #include <string>
    using namespace std;
        struct Date
        {
            int jour;
            int mois;
            int annes;
        }typedef Date;
        
        class comptebanque
        {
            protected:
                double _solde;
                string _numeroCompte;
                string _proprietaire;
                string _historiquedoperation;
                float _tauxinteretannuel;
                bool _estPremium;
            public:
                comptebanque(double s,string nu_c,string pro,string histo,float TA);
                void deposer(double montant);
                void retirer(double montant);
                void afficherSolde();
                void afficherInfosCompte();
                void ajouterOperationHistorique(string type, float montant ,Date _date );
                float calculerInteretAnnuel();
                bool authentifierUtilisateur(string motDepass);
        };
#endif