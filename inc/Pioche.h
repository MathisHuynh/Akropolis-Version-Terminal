#pragma once
#include "Tuile.h"

class Pioche {
    friend class Partie;

    std::vector<TuilePtr> tuiles;

    Pioche(size_t taille);
    Pioche(const Pioche& p) = delete;
    Pioche& operator=(const Pioche& p) = delete;

    TuilePtr piocher();
public:

    bool estVide() const { return tuiles.empty(); }
    size_t getNbTuiles() const { return tuiles.size(); }

    const std::vector<TuilePtr>& getTuiles() const{ return tuiles; }
};