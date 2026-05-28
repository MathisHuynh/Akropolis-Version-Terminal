#include "Pioche.h"


// 61 Tuiles au total (on ne les connait pas)

// taille de la pioche = nbJoueur + 2 + (nbJoueur+1) * 11

Pioche::Pioche(size_t taille) : tuiles(std::vector<TuilePtr>()){
	srand(time(NULL));
	for (int i = 0; i < taille; i++) tuiles.push_back(std::move(TuileFactory::tuileStandardAleatoire()));
}

TuilePtr Pioche::piocher() {
    if (tuiles.size() == 0) throw JeuException("Pioche vide");
    int x = rand() % tuiles.size();
    TuilePtr t = std::move(tuiles[x]);
    tuiles.erase(tuiles.begin() + x);
    return t;
}