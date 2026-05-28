#pragma once
#include "ScoreStrategy.h"

//Classe Jeu (singleton)
class Jeu {
	friend class HexFactory;
	
	std::vector<HexPtr> pool;

	//std::map<Rkey,ReglePtr> regles;
	
	//~Jeu();
	Jeu();
	Jeu(const Jeu&) = delete;
	Jeu& operator=(const Jeu&) = delete;

	struct Handler {
		Jeu* instance{ nullptr };
		~Handler() { delete instance; }
	};
	static Handler handler;

public:

	std::vector<const Hex*> getHexs() const {
		std::vector<const Hex*> res;
		for (auto& p : pool)
			res.push_back(p.get());
		return res;
	}

	static Jeu& getInstance() {
		if (handler.instance == nullptr) {
			handler.instance = new Jeu();
		}
		return *handler.instance;
	}
	static void freeInstance() { // supprimer l'instance pour en créer une nouvelle
		delete handler.instance;
		handler.instance = nullptr;
	}

	void printHexs() const;
};