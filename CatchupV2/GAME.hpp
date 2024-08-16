#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED
#include <vector>
#include <string>

class Game
{
public:
    Game();
    void display() const; // affiche l'état actuel de la partie
    bool checkMove(int column) const; // vérifie si le coup est jouable
    void makeMove(char symbol, int column); // modifie le tableau avec l'ajout d'un symbole
    void undoMove(); // Annule le coup
    bool checkWin(char symbol, bool forfait); // vérifie si le coup joué mène à une victoire
    bool checkTieGame(const int nbcoups) const; // vérifie s'il y a match nul
    const std::vector<std::vector<char>>& getGrid() const;
    const std::vector<std::vector<char>>& SetGrid(Game& grid);
    int getlastRow() const;
    int getlastCol() const;
    Game* retournerPtr();

private:
    std::vector<std::vector<char>> m_grid; // le tableau
    int last_row;
    int last_col;
};

#endif // GAME_HPP_INCLUDED
