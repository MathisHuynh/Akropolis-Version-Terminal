#pragma once
#include "Partie.h"
#include <optional>

class JoueurHumain;

class IllustreArchitecte;

class Vue {
protected:
	std::unique_ptr<Partie> partie;

	virtual void tour(JoueurHumain& joueur) = 0;

	void coup(Joueur& joueur, size_t choix, Coord pos = {0,0});

	TuilePtr& selectTuile(size_t idx) {
		TuilePtr& res = partie->getChantier()[idx];
		return res;
	}

	void retirerTuile(size_t idx) { partie->retirerTuile(idx); }
	void setCentre(size_t idx, Coord pivot) { partie->getChantier()[idx]->setCentre(pivot); }

	friend void JoueurHumain::jouerTour(Vue& vue);
	friend void IllustreArchitecte::jouerTour(Vue& vue);

	bool chantierVide() const { return partie->getChantierRead().empty(); }
	size_t tailleChantier() const { return partie->getChantierRead().size(); }
	const std::vector<TuilePtr>& getChantierRead() const { return partie->getChantierRead(); }
	const std::vector<JoueurPtr>& getJoueursRead() const { return partie->getJoueursRead(); }
};



//=========================================================================================================================
//										VUE TERMINAL
//=========================================================================================================================

class VueTerminal : public Vue
{
	friend void IllustreArchitecte::jouerTour(Vue& p);
	friend void JoueurHumain::jouerTour(Vue& p);

	void tour(JoueurHumain& joueur);

	//void coup(Joueur& joueur, size_t choix, Coord pos = {0,0});

	bool choixCase(const JoueurHumain& joueur, Coord& pos, size_t index, Coord pivot);
	bool choixRotation(const JoueurHumain& joueur, Coord pos, size_t index, Coord pivot);
	bool choixPivot(const JoueurHumain& joueur, size_t index, Coord& pivot);
	size_t choixTuile(const JoueurHumain& joueur) const;
	
	std::vector<JoueurPtr> creerJoueurs(const std::string& couleur = RESET, const std::string& contraste = FONDBn);
	std::vector<ReglePtr> creerRegles(const std::string& couleur = RESET, const std::string& contraste = FONDBn);

	//void jouerTour();
	void jouer();

public:

	void afficher(const Cite& c, Coord pos) const;
	void afficher(const Cite& c, const std::map<Coord, const Hex*>& overlay = {}, int rayon = 0) const;

	void afficher(const std::vector<TuilePtr>& c) const;

	void afficherChantier(const std::vector<TuilePtr>& c) const;
	void afficherChantier(const std::vector<TuilePtr>& c, size_t index, Coord pivot) const;

	void afficherIllustreArchitecte(const IllustreArchitecte& j) const;

	void afficherInfos(const JoueurHumain& joueur) const;

	VueTerminal(const std::string& couleur = RESET, const std::string& contraste = FONDBn);

	VueTerminal(const VueTerminal&) = delete;
	VueTerminal& operator=(const VueTerminal&) = delete;
};





void explications(const std::string& couleur = RESET);
void menuPrincipalTerminal(const std::string& couleur = RESET, const std::string& contraste = FONDBn);

void nouvellePartie(const std::string& couleur=RESET, const std::string& contraste=FONDBn);

void afficherCentre(const std::string& text, const std::string& couleur = RESET);

char entreeAttendue(std::vector<char> list);
bool entreeNumerique(std::string entree, int max = 0, int min = 0);
std::optional<std::string> lireNombreAvecEchap(size_t max);
std::optional<std::string> lireTexteAvecEchap(size_t max = 999);

size_t visibleLength(const std::string& s);