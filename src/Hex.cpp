#include "Hex.h"
#include "Joueur.h"

std::map<Couleur,size_t> Hex::Netoiles={
	{Couleur::bleu, 1},//bleu
	{Couleur::rouge, 2},//rouge
	{Couleur::vert, 3},//vert
	{Couleur::violet, 2},//violet
	{Couleur::jaune, 2},//jaune
	{Couleur::blanc, 0}//blanc
};

std::ostream& operator<<(std::ostream& f, const Hex& h) {
	f << toColor(h.getCouleur()) << h.getNbEtoile() << "*" << RESET;
	return f;
}

int Hex::recouvert() const{
	return 0;
}

int HexBlanc::recouvert() const{
	return 1;
}