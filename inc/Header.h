#pragma once
#include <iostream>
#include <memory>
#include <map>
#include <algorithm>
#include <cmath>
#include <array>
#include <set>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <string> 

#define PADDING 17

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

#define ECHAP 27
#define ENTREE 13

const std::string ROUGE = "\033[31m";
const std::string BLEU = "\033[34m";
const std::string JAUNE = "\033[33m";
const std::string VERT = "\033[32m";
const std::string VIOLET = "\033[35m";
const std::string BLANC = "\033[37m";
const std::string RESET = "\033[0m";

const std::string FOND = "\033[0;100m"; //Fond noir

const std::string FONDV = "\033[42m"; //Fond vert
const std::string FONDBn = "\033[30;47m";//Fond blanc texte noir

const std::string CLEAR ="\033[2J\033[1;1H";

//Classe Erreur
class JeuException {
	std::string info;
public:
	JeuException(const std::string& i) : info(i) {}
	std::string getInfo() { return info; }
};

//Caract�ristiques
enum class Couleur { bleu, rouge, vert, jaune, violet, blanc };


//Conversion en str
std::string toColor(Couleur c);
std::string toString(Couleur c);

//Listes
extern std::initializer_list<Couleur> Couleurs;
extern std::vector<Couleur> vCouleurs;

std::string toFond(int h); // 0<=h<=23

// �criture d'une caract�ristique sur un flux ostream
std::ostream& operator<<(std::ostream& f, Couleur c);



//---------------------------------------------------------------------------------------------------CLASSES---------------------------------------------------------------------------------------------------


//Classe coordonn�es
using Coord = std::pair<int, int>;
