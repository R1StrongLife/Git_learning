#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "GAME.hpp"
#include "JOUEURS.hpp"

using namespace std;

int main()
{
int choix1;
int choix2;
string nom_joueur;
char sbl1;
char sbl2;
int coupArbitraire = 1; // Argument à passer en paramètre pour appeler les méthodes
int nbcoups = 0;

int winJ1 = 0;
int winJ2 = 0;
int tiegame = 0;
int nombreParties = 0;

    srand(time(nullptr));

    /*--------------Choix du type du joueur 1--------------*/

    cout << "Veuillez choisir le type du joueur1 (entre 1 et 9):  " << endl;
    cout << "1: Joueurhumain; 2: JoueurStupide; 3: JoueurAleatoire; 4: JoueurMime;" << endl;
    cout << "5: JoueurBloqueur; 6:JoueurAleasmart; 7: JoueurExpert; 8: JoueurHumain" << endl;
    cout << "         9:JoueurHUMAIN              10:JoeurLisseur                   " << endl;
    cin >> choix1;
    while(choix1<1 || choix1>10 || choix1==4) // le joueur 1 ne peux pas être Mime
    {
        cout << "Choix non valide, veuillez recommencer: " << endl;
        cin >> choix1;
    }

    cin.ignore();

    cout << "Veuillez donner un nom au joueur: 'def' pour joueur par défaut:" << endl; // choix du nom
    getline(cin, nom_joueur); // Récupère toute la ligne écrite par l'utilisateur
    if(nom_joueur=="def")
    {
        nom_joueur = "joueur1";
    }
    cout << "Quel symbole lui attribuez-vous? " << endl; // choix du symbole
    cin >> sbl1;


    Joueur* joueur1; // pointeur sur le premier joueur

    switch(choix1)
    {
        case 1:
            joueur1 = new Joueurhumain(nom_joueur, sbl1, choix1); // le pointeur pointe sur un nouveau joueur
        break;
        case 2:
            joueur1 = new JoueurStupide(nom_joueur, sbl1, choix1);
        break;
        case 3:
            joueur1 = new JoueurAleatoire(nom_joueur, sbl1, choix1);
        break;
        case 4:
            joueur1 = new JoueurMime(nom_joueur, sbl1, choix1);
        break;
        case 5:
            joueur1 = new JoueurBloqueur(nom_joueur, sbl1, choix1);
        break;
        case 6:
            joueur1 = new JoueurAleasmart(nom_joueur, sbl1, choix1);
        break;
        case 7:
            joueur1 = new JoueurExpert(nom_joueur, sbl1, choix1);
        break;
        case 8:
            joueur1 = new JoueurHumain(nom_joueur, sbl1, choix1);
        break;
        case 9:
            joueur1 = new JoueurHUMAIN(nom_joueur, sbl1, choix1);
        break;
        case 10:
            joueur1 = new JoueurLisseur(nom_joueur, sbl2, choix2);
        break;
    }

   /*--------------Choix du type du joueur 2--------------*/

    cout << "Veuillez choisir le type du joueur2 (entre 1 et 9):  " << endl;
    cout << "1: Joueurhumain; 2: JoueurStupide; 3: JoueurAleatoire; 4: JoueurMime;" << endl;
    cout << "5: JoueurBloqueur; 6:JoueurAleasmart; 7: JoueurExpert; 8: JoueurHumain" << endl;
    cout << "         9:JoueurHUMAIN              10:JoeurLisseur                   " << endl;
    cin >> choix2;
    while(choix2<1 || choix2>10)
    {
        cout << "Choix non valide, veuillez recommencer: " << endl;
        cin >> choix2;
    }

    cin.ignore();

    cout << "Veuillez donner un nom au joueur: 'def' pour joueur par défaut:" << endl;
    getline(cin,nom_joueur);
    if(nom_joueur=="def")
    {
        nom_joueur = "joueur2";
    }
    cout << "Quel symbole lui attribuez-vous? " << endl; // choix du symbole
    cin >> sbl2;
    while(sbl2 == sbl1)
    {
        cout << "Symbole du premier joueur, choisissez-en un autre: " << endl;
        cin >> sbl2;
    }
    cin.ignore();

    Joueur* joueur2; // Pointeur sur le second joueur

    switch(choix2)
    {
        case 1:
            joueur2 = new Joueurhumain(nom_joueur, sbl2, choix2);
        break;
        case 2:
            joueur2 = new JoueurStupide(nom_joueur, sbl2, choix2);
        break;
        case 3:
            joueur2 = new JoueurAleatoire(nom_joueur, sbl2, choix2);
        break;
        case 4:
            joueur2 = new JoueurMime(nom_joueur, sbl2, choix2);
        break;
        case 5:
            joueur2 = new JoueurBloqueur(nom_joueur, sbl2, choix2);
        break;
        case 6:
            joueur2 = new JoueurAleasmart(nom_joueur, sbl2, choix2);
        break;
        case 7:
            joueur2 = new JoueurExpert(nom_joueur, sbl2, choix2);
        break;
        case 8:
            joueur2 = new JoueurHumain(nom_joueur, sbl2, choix2);
        break;
        case 9:
            joueur2 = new JoueurHUMAIN(nom_joueur, sbl2, choix2);
        break;
        case 10:
            joueur2 = new JoueurLisseur(nom_joueur, sbl2, choix2);
        break;
    }


    /*--------------Commencement du jeu--------------*/

    Joueur* JoueurEnCours = joueur1; // le joueur 1 commence la partie
    Joueur* JoueurEnAttente = joueur2;

    char reponse;
    do
    {
        Game puissance4;
//        JoueurEnCours->m_game = puissance4.retournerPtr();
//        JoueurEnAttente->m_game = puissance4.retournerPtr();
        do
        {
            puissance4.display(); //affichage du jeu
            if(JoueurEnCours->getChoixPerso()>1 && JoueurEnCours->getChoixPerso()<8)
            {
                for(long long p=0; p<900000000; p++) // Retard
                {

                }
            }
            JoueurEnCours->choisirCoup(puissance4); // Le premier joueur joue
            puissance4.makeMove(JoueurEnCours->getSymbol(), JoueurEnCours->getCol());
            //JoueurEnAttente->lastplay(*JoueurEnCours); // Au cas où joueur mime
            nbcoups++;

            if(JoueurEnCours == joueur1) // au tour du joueur2 de jouer
            {
                JoueurEnCours = joueur2;
                JoueurEnAttente = joueur1;
            }
            else if(JoueurEnCours == joueur2) // au tour du joueur1 de jouer
            {
                JoueurEnCours = joueur1;
                JoueurEnAttente = joueur2;
            }

        }
        while(!puissance4.checkWin(sbl1, joueur1->getForfait()) && !puissance4.checkWin(sbl2, joueur2->getForfait())
                && !puissance4.checkTieGame(nbcoups));

        /*--------------Fin du jeu--------------*/
        puissance4.display(); // on affiche le tableau final

        if(puissance4.checkWin(sbl1, joueur1->getForfait()))
        {
            cout << joueur1->getName() << " remporte la partie" << endl;
            winJ1++;
        }
        else if (puissance4.checkWin(sbl2, joueur2->getForfait()))
        {
            cout << joueur2->getName() << " remporte la partie" << endl;
            winJ2++;
        }
        else if(puissance4.checkTieGame(nbcoups))
        {
            cout << "Match nul" << endl;
            tiegame++;
        }
        else if(joueur1->getForfait())
        {
            cout << joueur2->getName() << " remporte la partie" << endl;
            winJ2++;
        }
        else if(joueur2->getForfait())
        {
            cout << joueur2->getName() << " remporte la partie" << endl;
            winJ1++;
        }

        //Demander à l'utilisateur s'il veut jouer une autre partie
        cout << "Voulez vous relancer une partie (o/n)?" << endl;
        cin >> reponse;

        //Incrémenter le noombre de parties
        nombreParties++;

    }
    while(reponse=='o' || reponse=='O');

    /*--------------Gestion du fichier--------------*/
    std::string monFichier = "resultat" + to_string(nombreParties) + ".txt";
    std::ofstream fichierResultat;

    //Ouverture du fichier en écriture
    fichierResultat.open(monFichier);

    // Ecriture des composantes dans le fichier
    if(fichierResultat.is_open())
    {
        fichierResultat << "Date et heure: " << __DATE__ << " " << __TIME__ << std::endl;
        fichierResultat << "Nombre de victoires pour le Joueur 1 : " << winJ1 << std::endl;
        fichierResultat << "Nombre de victoires pour le Joueur 2 : " << winJ2 << std::endl;
        fichierResultat << "Nombre de parties nulles : " << tiegame << std::endl;
        fichierResultat.close();
    }else{
        std::cout << "Impossible d'ouvrir le fichier de resultat." << std::endl;
    }

    delete joueur1; // suppression des instances
    delete joueur2;
    delete JoueurEnCours;
    delete JoueurEnAttente;

return 0;
}
