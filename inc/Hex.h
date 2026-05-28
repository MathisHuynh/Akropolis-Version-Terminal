#pragma once
#include "Header.h"

struct Case;

class Joueur;

class Hex {
	friend class HexFactory;

protected:

	static std::map<Couleur,size_t> Netoiles;

	Couleur couleur;
	size_t etoiles{ 0 };


	//Constructeur
	Hex(Couleur c, size_t n) : couleur(c), etoiles(n) {}
	Hex(Couleur c, bool p) : couleur(c) { if (p) etoiles = Netoiles[c]; }
	//Constructeur

public:

	virtual int recouvert() const;

	~Hex() = default;

	//Méthodes get
	Couleur getCouleur() const { return this->couleur; }
	size_t getNbEtoile() const { return this->etoiles; }
	//Méthodes get

	//bool operator==(const Hex& h) const { return couleur == h.couleur && etoiles == h.etoiles; }
};


using HexPtr = std::unique_ptr<Hex>;


std::ostream& operator<<(std::ostream& f, const Hex& h);

class HexBleu :public Hex {
	friend class HexFactory;

	HexBleu(size_t n): Hex(Couleur::bleu,n){}
	HexBleu(bool p): Hex(Couleur::bleu,p){}
};

class HexRouge :public Hex {
	friend class HexFactory;

	HexRouge(size_t n) : Hex(Couleur::rouge, n) {}
	HexRouge(bool p) : Hex(Couleur::rouge, p) {}
};

class HexVert :public Hex {
	friend class HexFactory;

	HexVert(size_t n) : Hex(Couleur::vert, n) {}
	HexVert(bool p) : Hex(Couleur::vert, p) {}
};

class HexViolet :public Hex {
	friend class HexFactory;

	HexViolet(size_t n) : Hex(Couleur::violet, n) {}
	HexViolet(bool p) : Hex(Couleur::violet, p) {}
};

class HexJaune :public Hex {
	friend class HexFactory;

	HexJaune(size_t n) : Hex(Couleur::jaune, n) {}
	HexJaune(bool p) : Hex(Couleur::jaune, p) {}
};

class HexBlanc :public Hex {
	friend class HexFactory;

	HexBlanc(size_t n) : Hex(Couleur::blanc, n) {}
	HexBlanc() : Hex(Couleur::blanc, false) {}
public:
	int recouvert() const;
};

//Hex Factory
class HexFactory {
	friend class Jeu;

	static HexPtr creer(Couleur c, size_t etoiles = 0) {
		switch (c) {
		case Couleur::bleu: return HexPtr(new HexBleu(etoiles));
		case Couleur::rouge: return HexPtr(new HexRouge(etoiles));
		case Couleur::vert: return HexPtr(new HexVert(etoiles));
		case Couleur::violet: return HexPtr(new HexViolet(etoiles));
		case Couleur::jaune: return HexPtr(new HexJaune(etoiles));
		case Couleur::blanc: return HexPtr(new HexBlanc(etoiles));; //pour l'instant, hex blanc jamais une place
		default: return  HexPtr(new Hex(c,etoiles));
		}
	}

	static HexPtr creer(Couleur c, bool p = false) {
		switch (c) {
		case Couleur::bleu: return HexPtr(new HexBleu(p));
		case Couleur::rouge: return HexPtr(new HexRouge(p));
		case Couleur::vert: return HexPtr(new HexVert(p));
		case Couleur::violet: return HexPtr(new HexViolet(p));
		case Couleur::jaune: return HexPtr(new HexJaune(p));
		case Couleur::blanc: return HexPtr(new HexBlanc(p));; //pour l'instant, hex blanc jamais une place
		default: return  HexPtr(new Hex(c, p));
		}
	}

	static std::vector<HexPtr> generateAll() {
		std::vector<HexPtr> pool;

		//Hexs standards
		for (const auto& c : Couleurs) {
			pool.push_back(std::move(creer(c, false)));
			if(c!=Couleur::blanc) pool.push_back(std::move(creer(c, true)));
		}

		//Hexs spéciaux


		return pool;
	}
};