/**
 * @file Serialization.h
 * @brief Sérialisation et désérialisation JSON pour la sauvegarde
 * @author Mathis HUYNH, Chloé LAMEZEC, Lanaé HANOIRE, Arthur MAGOT
 * @date 2024
 */

#pragma once

#include <string>
#include <memory>

class Tuile;
class Joueur;
class Partie;

// Forward declarations pour les types
using TuilePtr = std::unique_ptr<Tuile>;
using JoueurPtr = std::unique_ptr<Joueur>;

// Inclure json.hpp après les forward declarations pour éviter les problèmes
#include "json.hpp"

/**
 * @namespace ser
 * @brief Namespace pour les fonctions de sérialisation/désérialisation
 *
 * Toutes les fonctions de conversion entre objets C++ et JSON.
 */
namespace ser {
    using nlohmann::json;

    /**
     * @brief Convertit une tuile en JSON
     * @param t Tuile à sérialiser
     * @return Objet JSON représentant la tuile
     */
    json tuileToJson(const Tuile& t);

    /**
     * @brief Convertit un joueur en JSON
     * @param j Joueur à sérialiser
     * @return Objet JSON représentant le joueur
     */
    json joueurToJson(const Joueur& j);

    /**
     * @brief Convertit une partie en JSON
     * @param p Partie à sérialiser
     * @return Objet JSON représentant la partie complète
     */
    json partieToJson(const Partie& p);

    /**
     * @brief Reconstruit une tuile depuis JSON
     * @param j Objet JSON représentant la tuile
     * @return Pointeur unique vers la tuile reconstruite
     */
    TuilePtr tuileFromJson(const json& j);

    /**
     * @brief Reconstruit un joueur depuis JSON
     * @param j Objet JSON représentant le joueur
     * @return Pointeur unique vers le joueur reconstruit
     */
    JoueurPtr joueurFromJson(const json& j);

    /**
     * @brief Reconstruit une partie depuis JSON
     * @param j Objet JSON représentant la partie
     * @return Partie reconstruite (déplacée)
     */
    Partie partieFromJson(const json& j);

    /**
     * @brief Sauvegarde une partie dans un fichier JSON
     * @param p Partie à sauvegarder
     * @param filename Nom du fichier (avec ou sans extension .json)
     *
     * Le fichier sera créé dans le répertoire courant.
     */
    void savePartie(const Partie& p, const std::string& filename);

    /**
     * @brief Charge une partie depuis un fichier JSON
     * @param filename Nom du fichier à charger
     * @return Partie chargée (déplacée)
     * @throws std::runtime_error Si le fichier n'existe pas ou est invalide
     */
    Partie loadPartie(const std::string& filename);

} // namespace ser
