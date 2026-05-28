#pragma once
#include "Pioche.h"
#include "Joueur.h"
#include "ScoreStrategy.h"


class Partie
{
	friend class Vue;
	friend class VueTerminal;
	friend class VueGUI;
	friend class GUIcontroler;

	std::unique_ptr<Pioche> pioche{nullptr};
	std::unique_ptr<ScoreStrategy> scoring{ nullptr };
	std::vector<JoueurPtr> joueurs;
	std::vector<TuilePtr> chantier;
	size_t tour{ 1 };

	Partie(const Partie& c) = delete;
	Partie(std::vector<JoueurPtr>& j, std::vector<ReglePtr>& r, bool longue = false);
	Partie& operator=(const Partie& c) = delete;

	void remplirChantier();
	void retirerTuile(size_t index);

	void rafraichirScore();

	std::vector<TuilePtr>& getChantier() { return chantier; }
	std::vector<JoueurPtr>& getJoueurs() { return joueurs; }

	void jouerTour(Vue& vue);

public:

	bool piocheVide() const { return pioche->estVide(); }
	size_t cartesRestantes() const { return pioche->getNbTuiles(); }
	size_t getNbJoueurs() const { return joueurs.size(); }

	const std::vector<JoueurPtr>& getJoueursRead() const { return joueurs; }
	const std::vector<TuilePtr>& getChantierRead() const { return chantier; }
	int  getTourCourant() const { return tour; }
};