#ifndef JOUEURS_HPP_INCLUDED
#define JOUEURS_HPP_INCLUDED

#include "GAME.hpp"
#include <string>

class Joueur // classe mère abstraite
{
public:
    Joueur(std::string nom, char symbol, int choixPerso); // constructeur surchargé
    virtual ~Joueur(); // destructeur virtuel car on utilise le polymorphisme
    virtual void choisirCoup(Game& tableau) = 0; // méthode virtuelle pure qui va être redéfinie dans les classes filles
    char getSymbol() const;
    int getCol() const;
    int lastplay(const Joueur& joueurAdverse);
    std::string getName() const;
    virtual int getChoixPerso() const;
    bool getForfait() const;

protected:
    std::string m_nom;
    char m_symbole;
    int m_choixCol;
    Game* m_game; // référence sur le tableau de jeu
    int m_choixPerso;
    int mistake;
    bool forfait;
    int m_coupRecommande;
};

class Joueurhumain : public Joueur // classe héritière
{
public:
    Joueurhumain(std::string nom, char symbole, int choixPerso);
    virtual ~Joueurhumain();
    void choisirCoup(Game& tableau) override;
};

class JoueurStupide : public Joueur // classe héritière
{
public:
    JoueurStupide(std::string nom, char symbole, int choixPerso);
    virtual ~JoueurStupide();
    void choisirCoup(Game& tableau) override;
};

class JoueurAleatoire : public Joueur // classe héritière
{
public:
    JoueurAleatoire(std::string nom, char symbole, int choixPerso);
    virtual ~JoueurAleatoire();
    void choisirCoup(Game& tableau) override;
};

class JoueurMime : public Joueur // classe héritière
{
public:
    JoueurMime(std::string nom, char symbole, int choixPerso);
    virtual ~JoueurMime();
    void choisirCoup(Game& tableau) override;
};

class JoueurBloqueur : public Joueur // classe héritière
{
public:
    JoueurBloqueur(std::string nom, char symbole, int choixPerso);
    virtual ~JoueurBloqueur();
    void choisirCoup(Game& tableau) override;
};

class JoueurAleasmart : public Joueur // classe héritière
{
public:
    JoueurAleasmart(std::string nom, char symbole, int choixPerso);
    virtual ~JoueurAleasmart();
    void choisirCoup(Game& tableau) override;
};

class JoueurExpert : public Joueur // Classe héritière
{
public:
    JoueurExpert(std::string nom, char symbole, int choixPerso);
    virtual ~JoueurExpert();
    void choisirCoup(Game& tableau);
};

class JoueurHumain : public Joueur // classe héritière
{
public:
    JoueurHumain(std::string nom, char symbole, int choixPerso);
    virtual ~JoueurHumain();
    void choisirCoup(Game& tableau) override;
private:
    Joueur* JoueurAdverse; // Pointeur sur l'adversaire
};

class JoueurHUMAIN : public Joueur // classe héritière
{
public:
    JoueurHUMAIN(std::string nom, char symbole, int choixPerso);
    virtual ~JoueurHUMAIN();
    void choisirCoup(Game& tableau) override;
};


class JoueurLisseur : public Joueur
{
public:
    JoueurLisseur(std::string nom, char symbole, int choixPerso);
    virtual ~JoueurLisseur();
    void choisirCoup(Game& tableau) override;
};
#endif // JOUEURS_HPP_INCLUDED
