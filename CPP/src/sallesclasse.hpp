#ifndef _SALLESCLASSE_
    #define _SALLESCLASSE_
    #include <string>
    using namespace std;
    namespace SallesClasse
    {
        // Définitions de la classe
        class Classe
        {
            private:
               string id_classe;
               string name;
               string Level;
               int effectif;
            public:
               void add_new_code(string id_classe);
        };
    };
    
    








#endif