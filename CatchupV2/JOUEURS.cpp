#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>

#define ROWMAX 6
#define COLMAX 7

#include "JOUEURS.hpp"
#include "GAME.hpp"

using namespace std;

char EMPTY = ' ';

Joueur::Joueur(std::string nom, char symbole, int choixPerso) : m_nom(nom), m_symbole(symbole), m_choixPerso(choixPerso), m_choixCol(-1), mistake(0), forfait(false)
{}
Joueur::~Joueur()
{}

bool Joueur::getForfait() const
{
    return forfait;
}

int Joueur::getChoixPerso() const
{
    return m_choixPerso;
}

char Joueur::getSymbol() const
{
    return m_symbole;
}

int Joueur::getCol() const
{
    return m_choixCol;
}

int Joueur::lastplay(const Joueur& joueurAdverse)
{
    return joueurAdverse.m_choixCol;
}

string Joueur::getName() const
{
    return m_nom;
}

Joueurhumain::Joueurhumain(std::string nom, char symbole, int choixPerso) : Joueur(nom, symbole, choixPerso)
{}

void Joueurhumain::choisirCoup(Game& tableau) // l'utilisateur joue
{
    mistake = 0;
    forfait = false;

    cout << "C'est a " << m_nom << " de jouer" << endl;
    cout << "Veuillez choisir une colonne: " << endl;
    cin >> m_choixCol; // Saisi par l'utilisateur
    cin.ignore();

    m_choixCol--; // Indice ajusté aux valeurs du tableau
    while(!tableau.checkMove(m_choixCol) && mistake < 2)// on appelle la méthode de la classe Jeu
    {
        mistake++;
        cout << mistake << " erreurs sur 3" << endl;
        cout << "Coup non jouable, veuillez choisir un coup valide: " << endl;
        cin >> m_choixCol; // Saisi par l'utilisateur
        cin.ignore();
        m_choixCol--; // Indice ajusté aux valeurs du tableau
    }
    if(mistake==2)
        forfait = true;
}

Joueurhumain::~Joueurhumain()
{}

JoueurStupide::JoueurStupide(std::string nom, char symbole, int choixPerso): Joueur(nom, symbole, choixPerso)
{}

void JoueurStupide::choisirCoup(Game& tableau) // colonne au hasard entre 1 et 10
{
    mistake = 0;
    forfait = false;

    srand(time(0)); //initalisation de la graine pour les nombres aléatoires
    while(!tableau.checkMove(m_choixCol) && mistake < 2)
    {
        mistake++; // On incrémente le nombre d'erreurs
        cout << mistake << "erreurs sur 3" << endl;
        m_choixCol = rand()%10+1; // colonne aléatoire entre 0 et 6
    }
    if(mistake==2)
        forfait = true; // On capitule

}

JoueurStupide::~JoueurStupide()
{}


JoueurAleatoire::JoueurAleatoire(std::string nom, char symbole, int choixPerso): Joueur(nom, symbole, choixPerso)
{}

void JoueurAleatoire::choisirCoup(Game& tableau) // joue un coup en prenant comtpte des dimensions du jeu
{
    srand(time(0)); //initalisation de la graine pour les nombres aléatoires
    do
    {
        m_choixCol = rand()%COLMAX; // colonne aléatoire entre 0 et 6
    }while(!tableau.checkMove(m_choixCol));
}
JoueurAleatoire::~JoueurAleatoire()
{}


JoueurMime::JoueurMime(std::string nom, char symbole, int choixPerso): Joueur(nom, symbole, choixPerso)
{}

void JoueurMime::choisirCoup(Game& tableau) // joue le même coup que son adversaire
{
    m_choixCol = tableau.getlastCol(); // On copie le coup adverse
    tableau.checkMove(m_choixCol); // on vérifie le coup
}
JoueurMime::~JoueurMime()
{}


JoueurBloqueur::JoueurBloqueur(std::string nom, char symbole, int choixPerso): Joueur(nom, symbole, choixPerso)
{}

void JoueurBloqueur::choisirCoup(Game& tableau)
{
    const int MAX_MENACE_RANGE = 3;
    const int MAX_MENACES_REQUISES = 2;

    int bestCol = -1; // on va chercher la colonne à jouer pour bloquer l'adversaire
    int compteur;
    int colpointee = -1;

    const std::vector<std::vector<char>>& grid = tableau.getGrid(); // on déclare une référence sur le tableau
    char symboleAdverse = tableau.getGrid()[tableau.getlastRow()][tableau.getlastCol()]; // On récupère le symbole du joueur adverse

    int colAdverse = tableau.getlastCol();
    int ligneAdverse = tableau.getlastRow();

    /*--------------Recherche des menaces potentielles autour du dernier coup adverse--------------*/

    /*--------------Recherche des menaces potentielles vers le bas--------------*/

    compteur = 0;
    for(int i=ligneAdverse; i<ligneAdverse+MAX_MENACE_RANGE; i++)
    {
        if(grid[i][colAdverse]==symboleAdverse)
        {
            compteur++;
        }
    }
    if(compteur==MAX_MENACES_REQUISES && tableau.checkMove(colAdverse)) // si il y a menace et qu'on peut jouer sur cette même colonne
        bestCol = colAdverse; // Cette colonne doit être défendue

    /*--------------Recherche des menaces potentielles de chaque côté(...xxx...)--------------*/
    compteur = 0;
    for(int i=colAdverse-1; i<=colAdverse+1; i++)
    {
        if(grid[ligneAdverse][i]==symboleAdverse)
            compteur++;
    }
    if(compteur==MAX_MENACES_REQUISES)
    {
        if(ligneAdverse == ROWMAX-1) // si on se trouve sur la ligne du bas
        {
            if(grid[ligneAdverse][colAdverse+2]==EMPTY) // si on peut bloquer à droite
                bestCol = colAdverse+2;
            else if(grid[ligneAdverse][colAdverse-2]==EMPTY) // Sinon si on peut bloquer à gauche
                bestCol = colAdverse-2;
        }
        else if(grid[ligneAdverse+1][colAdverse+2]!=EMPTY && grid[ligneAdverse][colAdverse+2]==EMPTY) // Si on ne se trouve pas sur la ligne du bas mais qu'on peut bloquer à droite
        {
            if(tableau.checkMove(colAdverse+2))
                bestCol = colAdverse+2;
        }
        else if(grid[ligneAdverse+1][colAdverse-2]!=EMPTY && grid[ligneAdverse][colAdverse-2]!=EMPTY) // si on peut bloquer à gauche
        {
            if(tableau.checkMove(colAdverse-2))
                bestCol = colAdverse-2;
        }
    }


    /*--------------Recherche des menaces potentielles vers la droite--------------*/

    compteur = 0;
    for(int i=colAdverse; i<=colAdverse+MAX_MENACE_RANGE; i++) // On parcourt les colonnes à droite du dernier coup
    {
        if(grid[ligneAdverse][i]==symboleAdverse) // On vérifie chaque symbole
            compteur++;
        else colpointee = i;

        if(compteur==MAX_MENACES_REQUISES && colpointee!=-1) // Si menace
        {
            if(ligneAdverse==ROWMAX-1) // et si on se trouve en ligne du bas
            {
                if(grid[ligneAdverse][colpointee]==EMPTY) // si la colonne pointée est vide alors on peut bloquer
                    bestCol = colpointee;
            }
            else if(grid[ligneAdverse+1][colpointee]!=EMPTY && grid[ligneAdverse][colpointee]==EMPTY) // Si on ne se trouve pas sur la ligne du bas mais qu'on peut bloquer à droite
            {
                bestCol = colpointee;
            }
        }
    }


    /*--------------Recherche des menaces potentielles vers la gauche--------------*/

    compteur = 0;
    colpointee = -1;
    for(int i=colAdverse-MAX_MENACE_RANGE; i<colAdverse; i++) // On parcourt les colonnes à gauche du dernier coup
    {
        if(grid[ligneAdverse][i]==symboleAdverse) // On vérifie chaque symbole
            compteur++;
        else colpointee = i;

        if(compteur==MAX_MENACES_REQUISES && colpointee!=-1) // Si menace
        {
            if(ligneAdverse==ROWMAX-1) // et si on se trouve en ligne du bas
            {
                if(grid[ligneAdverse][colpointee]==EMPTY) // si la colonne pointée est vide alors on peut bloquer
                    bestCol = colpointee;
            }
            else if(grid[ligneAdverse+1][colpointee]!=EMPTY && grid[ligneAdverse][colpointee]==EMPTY) // Si on ne se trouve pas sur la ligne du bas mais qu'on peut bloquer à droite
            {
                bestCol = colpointee;
            }
        }
    }

    /*--------------Recherche des menaces potentielles sur la diagonale centrale en bas (°\)--------------*/

    compteur = 0;
    for(int i = ligneAdverse, j = colAdverse; i < ligneAdverse + MAX_MENACE_RANGE; i++, j++) // on parcourt les pions
    {
        if(i >= 0 && i < ROWMAX && j >= 0 && j < COLMAX && grid[i][j] == symboleAdverse) // On vérifie les symboles
        {
            compteur++;
        }
    }

    if(compteur == MAX_MENACES_REQUISES && tableau.checkMove(colAdverse + MAX_MENACE_RANGE)) // Si il y a menace
    {
        bestCol = colAdverse + MAX_MENACE_RANGE; // on place le pion à droite
    }

    /*--------------vérification diagonale en bas à gauche (/°)--------------*/

    compteur = 0;
    for(int i = ligneAdverse, j = colAdverse; i < ligneAdverse + MAX_MENACE_RANGE; i++, j--)
    {
        if(i >= 0 && i < ROWMAX && j >= 0 && j < COLMAX && grid[i][j] == symboleAdverse)
        {
            compteur++;
        }
    }
    if(compteur == MAX_MENACES_REQUISES && tableau.checkMove(colAdverse - MAX_MENACE_RANGE))
    {
        bestCol = colAdverse - MAX_MENACE_RANGE;
    }

    /*--------------On joue le meilleur coup bloqueur--------------*/

    if(bestCol!=-1)
    {
        m_choixCol = bestCol;
    }

    else if (bestCol == -1)
    {
        srand(time(0));
        do{
            bestCol = rand() % COLMAX;
        }while(!tableau.checkMove(bestCol));
        m_choixCol = bestCol;
    }
}

JoueurBloqueur::~JoueurBloqueur()
{}


JoueurAleasmart::JoueurAleasmart(std::string nom, char symbole, int choixPerso): Joueur(nom, symbole, choixPerso)
{}

void JoueurAleasmart::choisirCoup(Game& tableau)
{
    forfait = false;

/*--------------Vérification d'un coup menant à la victoire--------------*/

    Game jeuTest;
    jeuTest.SetGrid(tableau); // Recopie
    char symbol = getSymbol(); // Le symbole du joueur
    // Vérifier si on peut gagner immédiatement
    for (int col = 0; col < COLMAX; col++) {
        if (jeuTest.checkMove(col)) {
            jeuTest.makeMove(symbol, col); // Simuler un coup
            if (jeuTest.checkWin(symbol, forfait)) {
                jeuTest.undoMove(); // On annule le coup
                m_choixCol = col; // Choisir cette colonne pour gagner
                return;
            }
        }
    }


    /*--------------Coup au hasard--------------*/

    srand(time(0)); //initalisation de la graine pour les nombres aléatoires
    int maxTries = 50;
    int tries = 0;
    do
    {
        m_choixCol = rand()%COLMAX; // colonne aléatoire entre 0 et 6
        tries++;
    }while(!tableau.checkMove(m_choixCol) && tries<maxTries);
}

JoueurAleasmart::~JoueurAleasmart()
{}


JoueurExpert::JoueurExpert(std::string nom, char symbole, int choixPerso): Joueur(nom, symbole, choixPerso)
{}

void JoueurExpert::choisirCoup(Game& tableau)
{
    forfait = false;
    int cas = 0;

    m_choixCol = -1;
    m_coupRecommande = -1;

    /*--------------Vérification d'un coup menant à la victoire--------------*/

    Game jeuTest;
    jeuTest.SetGrid(tableau); // Recopie
    char symbol = getSymbol(); // Le symbole du joueur
    // Vérifier si on peut gagner immédiatement
    for (int col = 0; col < COLMAX; col++) {
        if (jeuTest.checkMove(col)) {
            jeuTest.makeMove(symbol, col); // Simuler un coup
            if (jeuTest.checkWin(symbol, forfait)) {
                jeuTest.undoMove(); // On annule le coup
                m_choixCol = col; // Choisir cette colonne pour gagner
                m_coupRecommande = m_choixCol; // Pour le JoueurHUMAIN
                return;
            } else jeuTest.undoMove();
        }
    }

    /*--------------Vérifier si l'adversaire peut gagner au prochain coup et bloquer--------------*/
    if(m_choixCol==-1)
    {
        char opponentSymbol = tableau.getGrid()[tableau.getlastRow()][tableau.getlastCol()];
        cout << "le symbole de l'adversaire: "<<opponentSymbol << endl;
        for (int col = 0; col < COLMAX; col++)
        {
            if (jeuTest.checkMove(col))
            {
                jeuTest.makeMove(opponentSymbol, col); // Simuler un coup de l'adversaire
                if (jeuTest.checkWin(opponentSymbol, forfait))
                {
                    jeuTest.undoMove();
                    m_choixCol = col; // Choisir cette colonne pour bloquer
                    return;
                }else jeuTest.undoMove();
            }
        }
    }

    if(m_choixCol==-1)
    {
        srand(time(0));
        do
        {
            m_choixCol = rand() % COLMAX;
        }
        while(!tableau.checkMove(m_choixCol));
    }

}

JoueurExpert::~JoueurExpert()
{}


JoueurHumain::JoueurHumain(std::string nom, char symbole, int choixPerso): Joueur(nom, symbole, choixPerso)
{}

void JoueurHumain::choisirCoup(Game& tableau)
{
    forfait = false;

    /*--------------Vérification d'un coup menant à la victoire--------------*/

    int conseil = 0;

    Game jeuTest;
    jeuTest.SetGrid(tableau); // Recopie
    char symbol = getSymbol(); // Le symbole du joueur
    // Vérifier si on peut gagner immédiatement
    for (int col = 0; col < COLMAX; col++) {
        if (jeuTest.checkMove(col)) {
            jeuTest.makeMove(symbol, col); // Simuler un coup
            if (jeuTest.checkWin(symbol, forfait)) {
                jeuTest.undoMove(); // On annule le coup
                conseil = col; // Choisir cette colonne pour gagner
                cout << "Tu peux gagner en jouant la colonne " << conseil+1 << endl;
                return;
            } else jeuTest.undoMove();
        }
    }

    mistake = 0;

    tableau.display();
    cout << "C'est a " << m_nom << " de jouer" << endl;
    cout << "Veuillez choisir une colonne: " << endl;
    cin >> m_choixCol; // Saisi par l'utilisateur
    cin.ignore();

    m_choixCol--; // Indice ajusté aux valeurs du tableau
    while(!tableau.checkMove(m_choixCol) && mistake < 2)// on appelle la méthode de la classe Jeu
    {
        mistake++;
        cout << mistake << " erreurs sur 3" << endl;
        cout << "Coup non jouable, veuillez choisir un coup valide: " << endl;
        cin >> m_choixCol; // Saisi par l'utilisateur
        cin.ignore();
        m_choixCol--; // Indice ajusté aux valeurs du tableau
    }
    if(mistake==2)
        forfait = true;
}

JoueurHumain::~JoueurHumain()
{}


JoueurHUMAIN::JoueurHUMAIN(std::string nom, char symbole, int choixPerso): Joueur(nom, symbole, choixPerso)
{}

void JoueurHUMAIN::choisirCoup(Game& tableau)
{
    m_coupRecommande = -1;
    JoueurExpert Roger("Advisor", '&', 7);
    Roger.choisirCoup(tableau);

    if(m_coupRecommande!=-1) // Si on peut gagner au prochain coup
    {
        cout << "Le joueur Expert vous conseille de jouer la colonne " << m_coupRecommande << endl;
    }

    mistake = 0;

    tableau.display();
    cout << "C'est a " << m_nom << " de jouer" << endl;
    cout << "Veuillez choisir une colonne: " << endl;
    cin >> m_choixCol; // Saisi par l'utilisateur
    cin.ignore();

    m_choixCol--; // Indice ajusté aux valeurs du tableau
    while(!tableau.checkMove(m_choixCol) && mistake < 2)// on appelle la méthode de la classe Jeu
    {
        mistake++;
        cout << mistake << " erreurs sur 3" << endl;
        cout << "Coup non jouable, veuillez choisir un coup valide: " << endl;
        cin >> m_choixCol; // Saisi par l'utilisateur
        cin.ignore();
        m_choixCol--; // Indice ajusté aux valeurs du tableau
    }
    if(mistake==2)
        forfait = true;

}

JoueurHUMAIN::~JoueurHUMAIN()
{}

JoueurLisseur::JoueurLisseur(std::string nom, char symbole, int choixPerso): Joueur(nom, symbole, choixPerso)
{}

void JoueurLisseur::choisirCoup(Game& tableau)
{
    int rows = ROWMAX-1;
    int nbSBL[COLMAX-1];
    m_choixCol = 0;

    for(int j=0; j<COLMAX; j++)
    {
        nbSBL[j] = 0;
    }

    for(int i=0; i<=COLMAX-1; i++)
    {
        while(tableau.getGrid()[rows][i]!=EMPTY && rows>=0) // si la case est déjà jouée, on regarde celle du dessus
        {
            rows--;
            nbSBL[i]++;
        }
    }
    for(int p=1; p<COLMAX; p++)
    {
        if(nbSBL[p]<nbSBL[p-1])
        {
            m_choixCol = nbSBL[p];
        }
    }
}

JoueurLisseur::~JoueurLisseur()
{}
