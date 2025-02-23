#include "Group.h"
#include "Database.h"


/**
 * @brief lecture groupe, vérification, ajout médias
 *
 * @param is   input stream, extraction groupe, compte médias
 * @param db   Database, accès médias, récupération par nom
 *
 * @details
 * - extraction nom groupe, nombre médias
 * - boucle sur mediaCount :
 *   - extraction nom média
 *   - récupération via db, ajout si valide
 * - gestion erreurs : flux invalide, média absent
 */
void Group::read(std::istream& is, const Database& db) {
    std::string groupName;
    int mediaCount;
    is >> groupName >> mediaCount;
    if (is.fail()) { std::cerr << "Erreur: Impossible de lire le groupe.\n"; return;}
    this->setName(groupName);
    for (int i = 0; i < mediaCount; ++i) {
        std::string mediaName;
        is >> mediaName;
        auto media = db.getMedia(mediaName);
        if (media) {
            this->push_back(media);
        } else {
            std::cerr << "⚠️ Erreur: Média '" << mediaName << "' introuvable, ignoré.\n";
        }
    }
}

