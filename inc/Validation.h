/**
 * @file Validation.h
 * @brief Fonctions de validation pour améliorer la robustesse
 * @author Mathis HUYNH, Chloé LAMEZEC, Lanaé HANOIRE, Arthur MAGOT
 * @date 2024
 */

#pragma once

#include <string>
#include <fstream>
#include "json.hpp"

using nlohmann::json;

namespace validation {

    /**
     * @brief Valide la structure d'un fichier JSON de partie
     * @param j Objet JSON à valider
     * @return true si valide, false sinon
     *
     * Vérifie que tous les champs requis sont présents et de bon type.
     */
    bool validerStructurePartie(const json& j);

    /**
     * @brief Valide un fichier JSON avant chargement
     * @param filename Nom du fichier à valider
     * @return true si valide, false sinon
     *
     * Vérifie que le fichier existe, est lisible et contient du JSON valide.
     */
    bool validerFichierJSON(const std::string& filename);

    /**
     * @brief Valide les données d'un joueur
     * @param j Objet JSON du joueur
     * @return true si valide, false sinon
     */
    bool validerJoueur(const json& j);

    /**
     * @brief Valide les limites (nombre de joueurs, taille, etc.)
     * @param j Objet JSON de la partie
     * @return true si dans les limites, false sinon
     */
    bool validerLimites(const json& j);

    /**
     * @brief Génère un message d'erreur détaillé
     * @param erreur Type d'erreur
     * @param details Détails supplémentaires
     * @return Message d'erreur formaté
     */
    std::string messageErreur(const std::string& erreur, const std::string& details = "");

} // namespace validation
