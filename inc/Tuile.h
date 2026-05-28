#pragma once
#include "Hex.h"

class Tuile {
	friend class TuileFactory;
protected:

	Tuile() = default;
	static int count;
	int id{ 0 };
	std::map<Coord, const Hex*> hexs;

public:

	//~Tuile() = default;

	int getId() const { return id; }
	std::map<Coord, const Hex*> getHexs() const { return hexs; }

	void rotation(bool horaire = true);

	void setCentre(const Coord& pos);
	std::map<Coord, const Hex*> getCoordPlateau(const Coord& ancrage) const;

	int rayon();
	//void afficher();

	std::vector<std::string> toLignes() const;
	std::vector<std::string> toLignes(Coord pivot) const;

	bool contientPlace() const;
};

std::ostream& operator<<(std::ostream& f, const Tuile& t);

using TuilePtr = std::unique_ptr<Tuile>;


//    X
//   X X

class TuileStandard : public Tuile {
	friend class TuileFactory;
	const std::vector<Coord> coords = {
		{0,0},
		{1,-1},
		{0,-1}
	};

	TuileStandard(const std::vector<const Hex*>& h) {
		if (h.size() != coords.size())
			throw JeuException("TuileStandard n�cessite exactement 3 hexagones");

		for (int i = 0; i < coords.size(); ++i) hexs[coords[i]] = h[i];
		id = count++;
	}
};

//       X
//    X X
//       X


class TuileDepart : public Tuile {
	friend class TuileFactory;
	friend class Cite;

	// static const std::vector<const Hex*> defaultlayout;

	const std::vector<Coord> coords = {
		{0,0},
		{0,1},
		{-1,0},
		{1,-1}
	};
	static const std::vector<const Hex*>& getDefaultLayout();

	TuileDepart(const std::vector<const Hex*>& h) {
    if (h.size() != 4) // coords.size() est 4
        throw JeuException("TuileDepart nécessite exactement 4 hexagones");

    for (int i = 0; i < coords.size(); i++) 
        hexs[coords[i]] = h[i];
	}

	// TuileDepart(const std::vector<const Hex*>& h = {})
	// {
	// 	std::vector<const Hex*> temp = h;
	// 	if(h.empty()) temp = getDefaultLayout();
	// 	if (h.size() != coords.size())
	// 		throw JeuException("TuileDepart n�cessite exactement 4 hexagones");

	// 	for (int i = 0; i < coords.size(); i++) hexs[coords[i]] = temp[i];
	// 	//id = 0;
	// 	//count++;
	// }
};


class TuileFactory {
	friend class Pioche;
	friend class Cite;

	static TuilePtr creerTuileStandard(const std::vector<const Hex*>& h) {
		return TuilePtr(new TuileStandard(h));
	}

	static TuilePtr creerTuileDepart(const std::vector<const Hex*>& h={}) {
		// 1. On décide des données AVANT d'appeler le constructeur
		std::vector<const Hex*> layoutToUse = h;
		
		if (layoutToUse.empty()) {
			// C'est ici qu'on appelle Jeu::getInstance()
			layoutToUse = TuileDepart::getDefaultLayout(); 
		}

		// 2. On appelle le constructeur avec les données prêtes
		return TuilePtr(new TuileDepart(layoutToUse));
	}

	static TuilePtr tuileStandardAleatoire();
};