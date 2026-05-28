#pragma once
#include "Tuile.h"

struct Case {
	const Hex* hex{ nullptr };
	size_t h{ 1 };
	int id{ 0 };
};



using Grid = std::map<Coord, Case>;



class Cite {
	friend class Joueur;
	friend class JoueurHumain;

	Grid plateau;
	static const Coord adjacence[6];

	Cite()=default;
	void init();

	int placerHex(const Hex* h, const Coord& pos, int id = 0);
	int placerTuile(const TuilePtr& t, const Coord& pos);

public:

	const Grid& getPlateau() const{ return plateau; }

	bool caseVide(const Coord& pos) const;
	bool caseAdjacente(const Coord& pos) const;
	bool coupLegal(const TuilePtr& t, const Coord& pos) const;
	bool placementPossible(TuilePtr& t, const Coord& pos) const;

	//bool estCouleurIsole(const Coord& pos) const;
	bool estCouleurIsoleSaufPlace(const Coord& pos) const;
	//bool estPeripherique(const Coord& pos) const;
	bool estEntouree(const Coord& pos) const;
	bool adjacentAPlaceCouleur(const Coord& pos) const;
	bool adjacentALac(const Coord& pos) const;



	std::set<Coord> casesAdjacentes(const Coord& pos) const;
	std::set<Coord> groupe(const Coord& pos) const;
	std::set<Coord> groupeMax(const Couleur& c) const;

	std::set<Coord> casesAdjacentesVides() const;
	std::vector<std::set<Coord>> lacs() const;
	std::set<Coord> peripherie() const;
	std::set<Coord> peripherieHex() const;
	std::set<Coord> peripherieCouleur(const Couleur& c) const;
	std::set<Coord> hexIsoles(const Couleur& c) const;
	std::set<Coord> hexEntoures(const Couleur& c) const;
	std::set<Coord> quartiers(const Couleur& c) const;
	

	bool estDansGroupeMax(const Coord& pos) const;
	bool estExterieur(const Coord& c, int rayonMax) const;


	//void afficher() const;
	//void afficher(const std::map<Coord, const Hex*>& overlay) const;

	size_t getEtoiles(const Couleur& c) const;
};


int hex_distance(int x1, int y1, int x2, int y2);