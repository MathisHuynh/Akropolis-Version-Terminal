#include "Header.h"

std::initializer_list<Couleur> Couleurs = { Couleur::bleu, Couleur::rouge, Couleur::vert, Couleur::jaune, Couleur::violet , Couleur::blanc };

std::vector<Couleur> vCouleurs(Couleurs);

std::string toColor(Couleur c) {
	switch (c) {
	case Couleur::bleu: return BLEU;
	case Couleur::rouge: return ROUGE;
	case Couleur::vert: return VERT;
	case Couleur::jaune: return JAUNE;
	case Couleur::violet: return VIOLET;
	case Couleur::blanc: return BLANC;
	default: throw JeuException("Couleur inconnue");
	}
}

std::string toString(Couleur c) {
	switch (c) {
	case Couleur::bleu: return "Habitation";
	case Couleur::rouge: return "Caserne";
	case Couleur::vert: return "Jardin";
	case Couleur::jaune: return "Marche";
	case Couleur::violet: return "Temple";
	case Couleur::blanc: return "Carriere";
	default: throw JeuException("Couleur inconnue");
	}
}

std::string toFond(int h) { //jusqu'à 11 hauteurs -> changer l'indice à 1 pour 23 hauteurs
	int gris = 230 + h*2;
	if (gris > 255) gris = 255;
	return "\033[48;5;" + std::to_string(gris) + "m";
}

std::ostream& operator<<(std::ostream& f, Couleur c) { f << toString(c); return f; };