#include "Partie.h"
#include "Joueur.h"


Partie::Partie(std::vector<JoueurPtr>& j, std::vector<ReglePtr>& r,bool longue) :scoring(std::unique_ptr<ScoreStrategy>(new ScoreStrategy)), joueurs(std::move(j)) {
	if(longue) pioche = std::unique_ptr<Pioche>(new Pioche(61));
	else pioche = std::unique_ptr<Pioche>(new Pioche(joueurs.size()+2 + (joueurs.size() + 1) * 11));
	scoring->regles = std::move(r);
	remplirChantier();
}

void Partie::remplirChantier() {
	while (!pioche->estVide() && chantier.size() < joueurs.size() + 2) chantier.emplace_back(pioche->piocher());
}

void Partie::retirerTuile(size_t index) {
	chantier.erase(chantier.begin() + index);
}

void Partie::rafraichirScore() {
	for (auto& joueur : joueurs) {
		joueur->score = joueur->scoreHorsCite();
		joueur->score+=scoring->calculerScore(joueur->getCite());
	}
}

void Partie::jouerTour(Vue& vue) {
	for (auto& joueur : getJoueurs()) {
		joueur->jouerTour(vue);
		if (chantier.size() <= 1) remplirChantier();
	}
	tour++;
	rafraichirScore();
}