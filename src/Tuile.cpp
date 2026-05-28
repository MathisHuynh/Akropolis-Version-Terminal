#include "Tuile.h"
#include "Jeu.h"

int Tuile::count = 0;

const std::vector<const Hex*>& TuileDepart::getDefaultLayout() {
    static const std::vector<const Hex*> layout = {
        Jeu::getInstance().getHexs()[1],
        Jeu::getInstance().getHexs()[10],
        Jeu::getInstance().getHexs()[10],
        Jeu::getInstance().getHexs()[10]
    };
    return layout;
}

int Tuile::rayon(){
	int rayon = 0;
	for (int i = 0; i < 6; i++) {
		for (const auto& pair : hexs) {
			int x = pair.first.first;
			int y = pair.first.second;
			int r = std::ceil(std::sqrt(x * x + y * y));
			if (r > rayon) rayon = r;
		}
		rotation(true);
	}
	return rayon;
}


void Tuile::rotation(bool horaire) {
	std::map<Coord, const Hex*> newhexs;
	for (const auto& pair : hexs) {
		const Coord& pos = pair.first;
		int x = pos.first, y = pos.second;
		Coord newPos;
		if (horaire) newPos = { x + y, -x };
		else newPos = { -y, x + y };
		newhexs[newPos] = pair.second;
	}
	hexs = newhexs;
}

std::map<Coord, const Hex*> Tuile::getCoordPlateau(const Coord& ancrage) const {
	std::map<Coord, const Hex*> res;
	for (const auto& pair : hexs) {
		const auto& pos = pair.first;
		int x = pos.first, y = pos.second;
		res[Coord({ ancrage.first + x,ancrage.second + y })] = pair.second;
	}
	return res;
}


void Tuile::setCentre(const Coord& pos) {
	std::map<Coord, const Hex*> newhexs;
	if (hexs.find(pos) != hexs.end()) {
		for (auto& pair : hexs) {
			const Coord& oldPos = pair.first;
			Coord newPos = { oldPos.first - pos.first,oldPos.second - pos.second };
			newhexs[newPos] = pair.second;
		}
		hexs = newhexs;
	}
	else return;
}

std::ostream& operator<<(std::ostream& f, const Tuile& t) {
	int ymin = 0, ymax = 0, xmin = 0, xmax = 0;
	const auto& hexs = t.getHexs();
	for (const auto& pair : hexs) {
		const Coord& pos = pair.first;
		if (ymin > pos.second) ymin = pos.second;
		if (ymax < pos.second) ymax = pos.second;
		if (xmin > pos.first) xmin = pos.first;
		if (xmax < pos.first) xmax = pos.first;
	}

	for (int y = ymin; y <= ymax; ++y) {
		// d�calage visuel pour les lignes
		f << std::string((y - ymin), ' ');
		for (int x = xmin; x <= xmax; ++x) {

			auto it = hexs.find({x, y});
			if (it != hexs.end()) f << *it->second << " ";
			else if (x != xmax) f << ". ";
		}
		f << "\n";
	}

	return f;
}


std::vector<std::string> Tuile::toLignes() const {
	int ymin = 0, ymax = 0, xmin = 0, xmax = 0;
	for (const auto& pair : hexs) {
		const Coord& pos = pair.first;
		if (ymin > pos.second) ymin = pos.second;
		if (ymax < pos.second) ymax = pos.second;
		if (xmin > pos.first) xmin = pos.first;
		if (xmax < pos.first) xmax = pos.first;
	}
	std::vector<std::string> res;
	for(int i=0; i<ymax-ymin+1;i++) res.emplace_back(" ");
	for (int y = ymin; y <= ymax; ++y) {
		// d�calage visuel pour les lignes
		res[y-ymin ]+= std::string(y - ymin, ' ');
		for (int x = xmin; x <= xmax; ++x) {

			const auto& it = hexs.find({ x, y });
			if (it != hexs.end()) {
				res[y - ymin] += toColor(it->second->getCouleur()); //10 chars
				res[y-ymin]+= std::to_string(it->second->getNbEtoile());
				res[y - ymin] += RESET; //9 char
				res[y - ymin] += " ";
			}
			else if (x != xmax) res[y-ymin] += ". ";
		}
	}
	std::reverse(res.begin(), res.end());
	return res;
}

std::vector<std::string> Tuile::toLignes(Coord pivot) const {
	int ymin = 0, ymax = 0, xmin = 0, xmax = 0;
	for (const auto& pair : hexs) {
		const Coord& pos = pair.first;
		if (ymin > pos.second) ymin = pos.second;
		if (ymax < pos.second) ymax = pos.second;
		if (xmin > pos.first) xmin = pos.first;
		if (xmax < pos.first) xmax = pos.first;
	}
	std::vector<std::string> res;
	for (int i = 0; i < ymax - ymin + 1; i++) res.emplace_back(" ");
	for (int y = ymin; y <= ymax; ++y) {
		// d�calage visuel pour les lignes
		res[y - ymin] += std::string(y - ymin, ' ');

		for (int x = xmin; x <= xmax; ++x) {

			const auto& it = hexs.find({ x, y });
			if (it != hexs.end()) {
				if (pivot.first == x && pivot.second == y) res[y - ymin][res[y - ymin].size()-1] = '>';
				res[y - ymin] += toColor(it->second->getCouleur()); //10 chars
				res[y - ymin] += std::to_string(it->second->getNbEtoile());
				res[y - ymin] += RESET; //9 char
				res[y - ymin] += " ";
			}
			else if (x != xmax) res[y - ymin] += ". ";
		}
	}
	std::reverse(res.begin(), res.end());
	return res;
}

bool Tuile::contientPlace() const {
	for (const auto& pair : hexs) {
		const Hex* h = pair.second;
		if (h->getNbEtoile() > 0)
			return true;
	}
	return false;
}



TuilePtr TuileFactory::tuileStandardAleatoire() {
	const std::vector<const Hex*>& all{ Jeu::getInstance().getHexs() };
	std::vector<const Hex*> hexs;
	for (int i = 0; i < 3; ++i) {
		hexs.push_back(all[rand() % all.size()]);
	}
	return creerTuileStandard(hexs);
}