#pragma once
#include "Cite.h"

class VueTerminal;

//TEST
class Vue;
//TEST

using JoueurPtr = std::unique_ptr<Joueur>;

enum class NiveauDifficulte {
	Hippodamos,
	Metagenes,
	Callicrates
};

class Partie;

class Joueur {
protected:
	std::string nom;
	size_t pierres;
	size_t score{ 0 };
	Cite cite;

	friend class Partie;
	friend class Vue;
	friend class VueTerminal;

	Joueur(const std::string& n, size_t p): nom(n), pierres(p) {}

	virtual void poserTuile(TuilePtr& t, Coord pos) {};

	//TEST
	virtual void jouerTour(Vue& vue) = 0;
	//TEST

	//virtual void jouerTourTerminal(VueTerminal& p) {};
	virtual size_t scoreHorsCite() const { return 0; };

	// Gestion pierres
	void ajouterPierres(int n) {
		if (n > 0) pierres += n;
	}

	bool payerPierres(int n) {
		if (n < 0) return false;
		if (pierres < n) return false;
		pierres -= n;
		return true;
	}

	void initCite(){ cite.init(); };

public:
	virtual ~Joueur() = default;

	// Getters 
	const std::string& getNom() const { return nom; }
	size_t getScore() const { return score; }

	size_t getPierres() const { return pierres; }

	const Cite& getCite() const { return cite; }
};



class JoueurHumain :public Joueur {
	friend class Partie;
	friend class VueTerminal;
	friend class VueGUI;

	JoueurHumain(const std::string& n, size_t p): Joueur(n,p){}

	friend class Vue;
	void jouerTour(Vue& vue);

	void poserTuile(TuilePtr& t, Coord pos) { ajouterPierres(cite.placerTuile(t, pos)); }

	//void jouerTourTerminal(VueTerminal& p);

	size_t scoreHorsCite() const { return getPierres(); };
};



class IllustreArchitecte : public Joueur {
	NiveauDifficulte difficulte;
	std::vector<TuilePtr> tuiles;
	friend class Partie;
	friend class VueTerminal;
	friend class VueGUI;

	IllustreArchitecte(NiveauDifficulte diff) : Joueur("Illustre Architecte", 2), difficulte(diff) {}

	friend class Vue;
	void jouerTour(Vue& vue);

	// Tour IA
	void poserTuile(TuilePtr& t, Coord pos = { 0,0 });

	//void jouerTourTerminal(VueTerminal& p);
public:
	
	const std::vector<TuilePtr>& getTuiles() const { return tuiles; }
	
	size_t scoreHorsCite() const;
	size_t choisirIndexTuile(const std::vector<TuilePtr>& chantier) const;
};