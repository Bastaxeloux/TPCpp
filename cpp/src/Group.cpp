#include "Group.h"
#include "Database.h"

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

