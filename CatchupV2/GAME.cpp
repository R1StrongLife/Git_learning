#include "GAME.hpp"
#include "JOUEURS.hpp"

#include <iostream>
#include <string>
#include <vector>

#define ROWMAX 6
#define COLMAX 7

using namespace std;

char VIDE = ' ';

Game* Game::retournerPtr()
{
    return this;
}

Game::Game(): last_col(-1), last_row(-1)
{
    m_grid.resize(ROWMAX, std::vector<char>(COLMAX, VIDE)); // On initialise le tableau avec ROWMAX lignes et COLMAX colonnes
}

void Game::display() const
{
    /*--------------Affichage du numéro des colonnes--------------*/

    for(int col = 0; col<COLMAX; col++)
    {
        cout << ' ' << col+1 << "  ";
    }
    cout << endl;

    /*--------------Affichage du tableau--------------*/

    for (int row = 0; row < ROWMAX; ++row)
    {
        for (int col = 0; col < COLMAX; ++col) // affichage des lignes et des symboles
        {
            cout << "| " << m_grid[row][col] << " ";
        }
        cout << "|" << endl;

        for(int col = 0; col < COLMAX; ++col) // affichage des lignes séparatrices
        {
            cout << "+---";
        }
        cout << "+" << endl;
    }
}

bool Game::checkMove(int column) const
{
    if(column<0 || column > COLMAX)
    {
        cout << "Veuillez choisir une colonne valide" << endl;
        return false;
    }
    else if(m_grid[0][column]!= VIDE) // la dérnière case est-elle dispo?
    {
        cout << "Cette colonne est pleine!" << endl;
    }
    else
    {
        return true;
    }
}

void Game::makeMove(char symbol, int column)
{
    int rows = ROWMAX-1; // on a vérifie que le symbole peut être placé, on cherche la bonne case
    while(m_grid[rows][column]!=VIDE && rows>=0) // si la case est déjà jouée, on regarde celle du dessus
    {
        rows--;
    }
    if(rows>=0) // la case est vide
    {
        m_grid[rows][column] = symbol; // sinon on place le symbole à l'emplacement voulu
        last_row = rows;
        last_col = column;
    }
}
void Game::undoMove()
{
    m_grid[last_row][last_col] = VIDE;
}

bool Game::checkWin(char symbol, bool forfait) // le symbole sera le même passé en paramètre lors de l'appel de makeMove
{
    if(forfait)
    {
        return true;
    }

    int compteur = 0; // cette variable stockera le nombre de mêmes symboles
    int i;
    int j;

    /*--------------vérification horizontale à droite--------------*/

    for(i = last_col; i < last_col+4; i++) // on parcourt les 4 symboles
    {
        if(i>=0 && i<COLMAX && m_grid[last_row][i]==symbol) //on vérifie les limites de la grille
        {
            compteur++;
        }
    }
    if(compteur == 4)
        return true;

    /*--------------vérification horizontale à gauche--------------*/

    compteur = 0;

    for(i = last_col-4; i <= last_col; i++) // on parcourt les 4 symboles
    {
        if(i>=0 && i<COLMAX && m_grid[last_row][i]==symbol) //on vérifie les limites de la grille
        {
            compteur++;
        }
    }
    if(compteur == 4)
        return true;

    /*--------------vérification verticale en bas--------------*/

    compteur = 0;

    for(i = last_row; i < last_row+4; i++) // on va parcourir les lignes
    {
        if(i>=0 && i<ROWMAX && m_grid[i][last_col]==symbol) //on vérifie les limites de la grille
        {
            compteur++;
        }
    }
    if(compteur == 4)
        return true;

    /*--------------vérification diagonales en haut à droite (./)--------------*/

    i = last_row;
    j = last_col;

    compteur = 0;

    for(int k=0; k<4; k++)
    {
        if(i>=0 && i<ROWMAX && j>=0 && j<COLMAX && m_grid[i][j]==symbol) // vérification des limites de la grille
        {
            compteur++;
        }
        i--;
        j++;
    }
    if(compteur == 4)
        return true;

    /*--------------vérification diagonales en haut à gauche (\.)--------------*/

    i = last_row;
    j = last_col;

    compteur = 0;

    for(int k=0; k<4; k++)
    {
        if(i>=0 && i<ROWMAX && j>=0 && j<COLMAX) // vérification des limites de la grille
        {
            if(m_grid[i][j]==symbol)
            compteur++;
        }
        i--;
        j--;
    }
    if(compteur == 4)
        return true;


    /*--------------vérification diagonales en bas à droite (°\)--------------*/

    i = last_row;
    j = last_col;

    compteur = 0;

    for(int k=0; k<4; k++)
    {
        if(i>=0 && i<ROWMAX && j>=0 && j<COLMAX) // vérification des limites de la grille
        {
            if(m_grid[i][j]==symbol)
            compteur++;
        }
        i++;
        j++;
    }
    if(compteur == 4)
        return true;

    /*--------------vérification diagonales en bas à gauche (/°)--------------*/

    i = last_row;
    j = last_col;

    compteur = 0;

    for(int k=0; k<4; k++)
    {
        if(i>=0 && i<ROWMAX && j>=0 && j<COLMAX) // vérification des limites de la grille
        {
            if(m_grid[i][j]==symbol)
            compteur++;
        }
        i++;
        j--;
    }
    if(compteur == 4)
        return true;


    /*--------------vérification horizontale central droite--------------*/

    compteur = 0;
    if(last_col>=1 && last_col<=4) // On vérifie les limites
    {
        for(i = last_col-1; i < last_col+3; i++)
        {
            if(i>=0 && i<COLMAX && m_grid[last_row][i]==symbol)
            {
                compteur++;
            }
        }
        if(compteur==4)
            return true;
    }


    /*--------------vérification horizontale central gauche--------------*/

    compteur = 0;
    if(last_col <= 5 && last_col >= 2)
    {
        for(i = last_col-3; i < last_col+1; i++)
        {
            if(i>=0 && i<COLMAX && m_grid[last_row][i]==symbol)
            {
                compteur++;
            }
        }
        if(compteur==4)
            return true;
    }



    /*--------------vérification diagonales central haut à droite (./)--------------*/

    i = last_row+1;
    j = last_col-1;

    compteur = 0;

    if(last_col>=1 && last_col<=4 && last_row>=2 && last_row<=4)
    {
        for(int k=0; k<4; k++)
        {
            if(i>=0 && i<ROWMAX && j>=0 && j<COLMAX && m_grid[i][j]==symbol) // vérification des limites de la grille
            {
                compteur++;
            }
            i--;
            j++;
        }
        if(compteur == 4)
            return true;
    }



    /*--------------vérification diagonales central haut à gauche (\.)--------------*/

    i = last_row+1;
    j = last_col+1;

    compteur = 0;

    if(last_col>=2 && last_col<=5 && last_row>=2 && last_row<=4)
    {
        for(int k=0; k<4; k++)
        {
            if(i>=0 && i<ROWMAX && j>=0 && j<COLMAX) // vérification des limites de la grille
            {
                if(m_grid[i][j]==symbol)
                    compteur++;
            }
            i--;
            j--;
        }
        if(compteur == 4)
            return true;
    }



    /*--------------vérification diagonales central bas à droite (°\)--------------*/

    i = last_row-1;
    j = last_col-1;

    compteur = 0;

    if(last_col>=1 && last_col<=4 && last_row>=1 && last_row<=3)
    {
        for(int k=0; k<4; k++)
        {
            if(i>=0 && i<ROWMAX && j>=0 && j<COLMAX) // vérification des limites de la grille
            {
                if(m_grid[i][j]==symbol)
                    compteur++;
            }
            i++;
            j++;
        }
        if(compteur == 4)
            return true;
    }



    /*--------------vérification diagonales centrale bas à gauche (/°)--------------*/

    i = last_row-1;
    j = last_col+1;

    compteur = 0;

    if(last_col>=2 && last_col<=5 && last_row>=1 && last_row<=3)
    for(int k=0; k<4; k++)
    {
        if(i>=0 && i<ROWMAX && j>=0 && j<COLMAX) // vérification des limites de la grille
        {
            if(m_grid[i][j]==symbol)
            compteur++;
        }
        i++;
        j--;
    }
    if(compteur == 4)
        return true;


    /*--------------vérification globale--------------*/

    if(compteur!=4)
        return false;

    //    /*--------------vérification vertical central bas--------------*/
//
//    compteur = 0;
//    for(i = last_row-1; i < last_row+3; i++)
//    {
//        if(i>=0 && i<ROWMAX && m_grid[i][last_col]==symbol)
//        {
//            compteur++;
//        }
//    }
//    if(compteur==4)
//        return true;


//    /*--------------vérification vertical central haut--------------*/
//
//    compteur = 0;
//    for(i = last_row-3; i < last_row+1; i++)
//    {
//        if(i>=0 && i<ROWMAX && m_grid[i][last_col]==symbol)
//        {
//            compteur++;
//        }
//    }
//    if(compteur==4)
//        return true;

//    --------------vérification verticale en haut-------------/
//
//    compteur = 0;
//
//    for(i = last_row-4; i <= last_row; i++) // on va parcourir les lignes
//    {
//        if(i>=0 && i<ROWMAX && m_grid[i][last_col]==symbol) //on vérifie les limites de la grille
//        {
//            compteur++;
//        }
//    }
//    if(compteur == 4)
//        return true;
}

bool Game::checkTieGame(const int nbcoups) const
{
     return (nbcoups==42); // nombre maximum de coups faisable en une partie
}

int Game::getlastRow() const
{
    return last_row;
}

const vector<std::vector<char>>& Game::getGrid() const
{
    return m_grid;
}
const std::vector<std::vector<char>>& Game::SetGrid(Game& grid)
{
    m_grid = grid.getGrid();
}

int Game::getlastCol() const
{
    return last_col;
}
