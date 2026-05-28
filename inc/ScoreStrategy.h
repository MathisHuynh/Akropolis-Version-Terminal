#pragma once
#include "Cite.h"

class Regle {
public:
	~Regle() = default;
	virtual size_t appliquer(const Cite& cite) const = 0;
};

using ReglePtr = std::unique_ptr<Regle>;

//using Rkey = std::pair<Couleur, bool>;

//catégories
class RegleMaisons : public Regle{};
class RegleMarches : public Regle {};
class RegleCasernes : public Regle {};
class RegleTemples : public Regle {};
class RegleJardins : public Regle {};

//Standard

class standardMaisons : public RegleMaisons{
	friend class RegleFactory;
	standardMaisons() = default;
public:
	size_t appliquer(const Cite& cite) const override;
};

class standardMarches : public RegleMarches {
	friend class RegleFactory;

	standardMarches() = default;
public:
	size_t appliquer(const Cite& cite) const override;
};

class standardCasernes : public RegleCasernes {
	friend class RegleFactory;

	standardCasernes() = default;
public:
	size_t appliquer(const Cite& cite) const override;
};

class standardTemples : public RegleTemples {
	friend class RegleFactory;

	standardTemples() = default;
public:
	size_t appliquer(const Cite& cite) const override;
};

class standardJardins : public RegleJardins {
	friend class RegleFactory;

	standardJardins() = default;
public:
	size_t appliquer(const Cite& cite) const override;
};

//Variantes

class varianteMaisons : public RegleMaisons {
	friend class RegleFactory;

	varianteMaisons() = default;
public:
	size_t appliquer(const Cite& cite) const override;
};

class varianteMarches : public RegleMarches {
	friend class RegleFactory;

	varianteMarches() = default;
public:
	size_t appliquer(const Cite& cite) const override;
};

class varianteCasernes : public RegleCasernes {
	friend class RegleFactory;

	varianteCasernes() = default;
public:
	size_t appliquer(const Cite& cite) const override;
};

class varianteTemples : public RegleTemples {
	friend class RegleFactory;

	varianteTemples() = default;
public:
	size_t appliquer(const Cite& cite) const override;
};

class varianteJardins : public RegleJardins {
	friend class RegleFactory;

	varianteJardins() = default;
public:
	size_t appliquer(const Cite& cite) const override;
};

class ScoreStrategy {
	friend class Partie;

	std::vector<ReglePtr> regles;
public:
	//ScoreStrategy(std::vector<ReglePtr>& r): regles(std::move(r)){}
	size_t calculerScore(const Cite& cite) const;
};


class RegleFactory {
	friend class VueTerminal;
	friend class VueGUI;

	static ReglePtr creer(Couleur c, bool v = false) {
		switch (c) {
		case Couleur::bleu: return creerRegleMaisons(v);
		case Couleur::rouge: return creerRegleCasernes(v);
		case Couleur::vert: return creerRegleJardins(v);
		case Couleur::violet: return creerRegleTemples(v);
		case Couleur::jaune: return creerRegleMarches(v);
		default: throw JeuException("Erreur: regle sur couleur inconnue");
		}
	}

	static ReglePtr creerRegleMaisons(bool variante) {
		if (variante) return ReglePtr(new varianteMaisons);
		return ReglePtr(new standardMaisons);
	}

	static ReglePtr creerRegleMarches(bool variante) {
		if (variante) return ReglePtr(new varianteMarches);
		return ReglePtr(new standardMarches);
	}

	static ReglePtr creerRegleCasernes(bool variante) {
		if (variante) return ReglePtr(new varianteCasernes);
		return ReglePtr(new standardCasernes);
	}

	static ReglePtr creerRegleJardins(bool variante) {
		if (variante) return ReglePtr(new varianteJardins);
		return ReglePtr(new standardJardins);
	}

	static ReglePtr creerRegleTemples(bool variante) {
		if (variante) return ReglePtr(new varianteTemples);
		return ReglePtr(new standardTemples);
	}
};
