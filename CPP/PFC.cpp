#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
using namespace std;

const char Piere = 'P';
const char Feuille = 'F';
const char Ciseau = 'C';

int main() {
    srand(time(NULL));  // Initialisation une seule fois

    char choix_machine[3] = {Piere, Feuille, Ciseau};
    char choix_joueur;
    char rejouer;

    do {
        int nbr = rand() % 3;

        cout << "Veuillez choisir une lettre P/F/C (Pierre/Feuille/Ciseau): ";
        cin >> choix_joueur;

        cout << "Vous: " << choix_joueur << " | Ordi: " << choix_machine[nbr] << "\n";

        if ((choix_joueur == Piere && choix_machine[nbr] == Ciseau) ||
            (choix_joueur == Ciseau && choix_machine[nbr] == Feuille) ||
            (choix_joueur == Feuille && choix_machine[nbr] == Piere))
            cout << "🎉 Vous avez gagné !" << endl;
        else if (choix_joueur == choix_machine[nbr])
            cout << "🤝 Match nul." << endl;
        else
            cout << "😞 Vous avez perdu." << endl;

        cout << "Voulez-vous rejouer ? (O/N): ";
        cin >> rejouer;

    } while (rejouer == 'O' || rejouer == 'o');

    cout << "Merci d’avoir joué !" << endl;
    return 0;
}
