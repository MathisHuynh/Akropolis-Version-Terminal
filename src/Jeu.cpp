#include "Jeu.h"

Jeu::Handler Jeu::handler = Handler();

Jeu::Jeu() {
	pool = std::move(HexFactory::generateAll());
}

void Jeu::printHexs() const{
	for (int i = 0; i < pool.size(); i++) std::cout << *pool[i] << "\n";
}
