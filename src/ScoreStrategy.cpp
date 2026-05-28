#include "ScoreStrategy.h"

size_t ScoreStrategy::calculerScore(const Cite& cite) const {
    size_t total = 0;
    for (const auto& r : regles) total += r->appliquer(cite);
    return total;
}


//-----------------------------------------------------------------------------------------------
//                                           STANDARDS
//-----------------------------------------------------------------------------------------------

size_t standardMaisons::appliquer(const Cite& cite) const { //marche
    size_t score = 0;
    const Grid& plateau=cite.getPlateau();
    for (Coord pos: cite.groupeMax(Couleur::bleu)) {score += plateau.at(pos).h;}
    return score*cite.getEtoiles(Couleur::bleu);
}

size_t standardMarches::appliquer(const Cite& cite) const { //marche
    size_t score = 0;
    const Grid& plateau = cite.getPlateau();
    for (Coord pos : cite.hexIsoles(Couleur::jaune)) { score += plateau.at(pos).h; }
    return score * cite.getEtoiles(Couleur::jaune);
}

size_t standardTemples::appliquer(const Cite& cite) const { //marche
    size_t score = 0;
    const Grid& plateau = cite.getPlateau();
    for (Coord pos : cite.hexEntoures(Couleur::violet)) { score += plateau.at(pos).h; }
    return score * cite.getEtoiles(Couleur::violet);
}

size_t standardJardins::appliquer(const Cite& cite) const { //marche
    size_t score = 0;
    const Grid& plateau = cite.getPlateau();
    for (Coord pos : cite.quartiers(Couleur::vert)) { score += plateau.at(pos).h; }
    return score * cite.getEtoiles(Couleur::vert);
}

size_t standardCasernes::appliquer(const Cite& cite) const { //marche
    size_t score = 0;
    const Grid& plateau = cite.getPlateau();
    for (Coord pos : cite.peripherieCouleur(Couleur::rouge)) { score += plateau.at(pos).h; }
    return score * cite.getEtoiles(Couleur::rouge);
}

//-----------------------------------------------------------------------------------------------
//                                           VARIANTES
//-----------------------------------------------------------------------------------------------
size_t varianteMaisons::appliquer(const Cite& cite) const {
    size_t score = 0;
    const Grid& plateau = cite.getPlateau();
    std::set<Coord> grpmax = cite.groupeMax(Couleur::bleu);
    for (Coord pos : grpmax) { score += plateau.at(pos).h; }
    if (grpmax.size() >= 10) score = score * 2;
    return score * cite.getEtoiles(Couleur::bleu);
}

size_t varianteMarches::appliquer(const Cite& cite) const {
    size_t score = 0;
    const Grid& plateau = cite.getPlateau();
    for (Coord pos : cite.hexIsoles(Couleur::jaune)) {
        if(cite.adjacentAPlaceCouleur(pos)) score += plateau.at(pos).h*2;
        else score += plateau.at(pos).h;
    }
    return score * cite.getEtoiles(Couleur::jaune);
}

size_t varianteTemples::appliquer(const Cite& cite) const {
    size_t score = 0;
    const Grid& plateau = cite.getPlateau();
    for (Coord pos : cite.hexEntoures(Couleur::violet)) {
        if (plateau.at(pos).h > 1) score += plateau.at(pos).h * 2;
        else score += plateau.at(pos).h;
    }
    return score * cite.getEtoiles(Couleur::violet);
}

size_t varianteJardins::appliquer(const Cite& cite) const {
    size_t score = 0;
    const Grid& plateau = cite.getPlateau();
    for (Coord pos : cite.quartiers(Couleur::vert)) {
        if(cite.adjacentALac(pos)) score += plateau.at(pos).h*2;
        else score += plateau.at(pos).h;
    }
    return score * cite.getEtoiles(Couleur::vert);
}

size_t varianteCasernes::appliquer(const Cite& cite) const {
    size_t score = 0;
    const Grid& plateau = cite.getPlateau();
    for (Coord pos : cite.peripherieCouleur(Couleur::rouge)) {
        if(cite.casesAdjacentes(pos).size()<=2) score += plateau.at(pos).h * 2;
        else score += plateau.at(pos).h;
    }
    return score * cite.getEtoiles(Couleur::rouge);
}
