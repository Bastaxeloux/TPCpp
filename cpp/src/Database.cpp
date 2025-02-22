#include "Database.h"
#include <fstream>

/**
 * Les 4 méthodes suivantes créent un objet multimédia (Photo, Video, Film) ou un groupe.
 */

std::shared_ptr<Photo> Database::createPhoto(const std::string& name, const std::string& path, double latitude, double longitude) {
    auto photo = std::make_shared<Photo>(name, path, latitude, longitude);
    multimediaTable[name] = photo;
    return photo;
}

std::shared_ptr<Video> Database::createVideo(const std::string& name, const std::string& path, int duration) {
    auto video = std::make_shared<Video>(name, path, duration);
    multimediaTable[name] = video;
    return video;
}

std::shared_ptr<Film> Database::createFilm(const std::string& name, const std::string& path, int duration, const int* chapters, int nbChapters) {
    auto film = std::make_shared<Film>(name, path, duration, chapters, nbChapters);
    multimediaTable[name] = film;
    return film;
}

std::shared_ptr<Group> Database::createGroup(const std::string& name) {
    auto group = std::make_shared<Group>(name);
    groupTable[name] = group;
    return group;
}

// Ensuite on affiche soit les objets multimédias, soit les groupes.

void Database::displayMultimedia(const std::string& name, std::ostream& stream) const {
    auto item = multimediaTable.find(name);
    if (item != multimediaTable.end()) {
        item->second->display(stream);
    } else {
        stream << "Erreur : Média '" << name << "' introuvable.";
    }
}

void Database::displayGroup(const std::string& name, std::ostream& stream) const {
    auto item = groupTable.find(name);
    if (item != groupTable.end()) {
        item->second->display(stream);
    } else {
        stream << "Erreur : Groupe '" << name << "' introuvable.";
    }
}

// On veut pouvoir lire nos objets multimédias.
void Database::playMultimedia(const std::string& name) const {
    auto item = multimediaTable.find(name);
    if (item != multimediaTable.end()) {
        item->second->play();
    } else {
        std::cout << "Objet multimédia '" << name << "' introuvable." << std::endl;
    }
}




/**
 * Ci dessous on définit les deux méthodes pour supprimer un objet multimédia ou un groupe proprement.
 */

void Database::deleteMultimedia(const std::string& name) {
    auto item = multimediaTable.find(name);
    if (item != multimediaTable.end()) {
        // Retirer de tous les groupes
        for (auto& couple : groupTable) {
            auto group = couple.second;
            group->remove_if([&](const MPtr& obj) { return obj == item->second; });
        }
        multimediaTable.erase(item);
        std::cout << "Objet multimédia '" << name << "' supprimé." << std::endl;
    } else {
        std::cout << "Objet multimédia '" << name << "' introuvable." << std::endl;
    }
}

void Database::deleteGroup(const std::string& name) {
    auto item = groupTable.find(name);
    if (item != groupTable.end()) {
        groupTable.erase(item);
        std::cout << "Groupe '" << name << "' supprimé." << std::endl;
    } else {
        std::cout << "Groupe '" << name << "' introuvable." << std::endl;
    }
}





MPtr Database::getMedia(const std::string& name) const {
    auto item = multimediaTable.find(name);
    if (item != multimediaTable.end()) {
        return item->second;
    }
    return nullptr;
}

GPtr Database::getGroup(const std::string& name) const {
    auto item = groupTable.find(name);
    if (item != groupTable.end()) {
        return item->second;
    }
    return nullptr;
}



void Database::listAllMedia(std::ostream& stream) const {
    stream << "Liste des médias disponibles : (" << multimediaTable.size() << " objets); ";
    for (const auto& pair : multimediaTable) {
        auto media = pair.second;
        if (media) {
            stream << "Nom: " << pair.first << " (Type: ";
            if (dynamic_cast<Photo*>(media.get())) stream << "Photo";
            else if (dynamic_cast<Video*>(media.get())) stream << "Video";
            else if (dynamic_cast<Film*>(media.get())) stream << "Film";
            else stream << "Inconnu";
            stream << "); ";
        }
    }
}

void Database::listAllGroups(std::ostream& stream) const {
    stream << "Liste des groupes disponibles | ";
    for (const auto& pair : groupTable) {
        stream << "Nom du groupe: " << pair.first << " | ";
    }
}

void Database::searchPartial(const std::string& substring, std::ostream& stream) const {
    stream << "Résultats de la recherche pour '" << substring << "' : ";
    bool found = false;

    for (const auto& pair : multimediaTable) {
        if (pair.first.find(substring) != std::string::npos) {
            stream << "[Nom: " << pair.first << ", Type: ";
            if (dynamic_cast<Photo*>(pair.second.get())) stream << "Photo";
            else if (dynamic_cast<Video*>(pair.second.get())) stream << "Video";
            else if (dynamic_cast<Film*>(pair.second.get())) stream << "Film";
            else stream << "Inconnu";
            stream << ", Chemin: " << pair.second->getPath() << "]; ";

            found = true;
        }
    }
    if (!found) stream << "Aucun média trouvé.";
}


void Database::searchByType(const std::string& type, std::ostream& stream) const {
    stream << "Résultats pour les médias de type '" << type << "' : ";
    bool found = false;

    for (const auto& pair : multimediaTable) {
        auto media = pair.second;
        if ((type == "Photo" && dynamic_cast<Photo*>(media.get())) ||
            (type == "Video" && dynamic_cast<Video*>(media.get())) ||
            (type == "Film" && dynamic_cast<Film*>(media.get()))) {
            
            if (found) stream << " | ";
            stream << "Nom: " << pair.first << ", Chemin d'accès: " << media->getPath() << "; ";
            found = true;
        }
    }
    if (!found) {
        stream << "Aucun média trouvé.";
    }
}


bool Database::deleteObject(const std::string& name) {
    // Suppression dans multimediaTable
    auto mediaIt = multimediaTable.find(name);
    if (mediaIt != multimediaTable.end()) {
        // Retirer de tous les groupes
        for (auto& pair : groupTable) {
            auto& group = pair.second;
            group->remove_if([&](const MPtr& obj) { return obj == mediaIt->second; });
        }
        multimediaTable.erase(mediaIt);
        return true;
    }

    // Suppression dans groupTable
    auto groupIt = groupTable.find(name);
    if (groupIt != groupTable.end()) {
        groupTable.erase(groupIt);
        return true;
    }

    return false;
}

bool Database::addMediaToGroup(const std::string& mediaName, const std::string& groupName) {
    auto mediaIt = multimediaTable.find(mediaName);
    auto groupIt = groupTable.find(groupName);

    if (mediaIt != multimediaTable.end() && groupIt != groupTable.end()) {
        groupIt->second->push_back(mediaIt->second);
        return true;
    }
    return false;
}

bool Database::removeMediaFromGroup(const std::string& mediaName, const std::string& groupName) {
    auto groupIt = groupTable.find(groupName);
    if (groupIt == groupTable.end()) return false;

    auto& group = *groupIt->second;
    for (auto it = group.begin(); it != group.end(); ++it) {
        if ((*it)->getName() == mediaName) {
            group.erase(it);
            return true;
        }
    }
    return false;
}

bool Database::isMediaInGroup(const std::string& mediaName, const std::string& groupName) const {
    auto groupIt = groupTable.find(groupName);
    if (groupIt == groupTable.end()) return false; // Groupe non trouvé

    auto mediaIt = multimediaTable.find(mediaName);
    if (mediaIt == multimediaTable.end()) return false; // Média non trouvé

    auto& group = groupIt->second;
    for (const auto& media : *group) {
        if (media == mediaIt->second) return true; // Trouvé dans le groupe
    }
    return false;
}

void Database::saveGroupsToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Erreur: Impossible d'ouvrir le fichier.\n";
        return;
    }

    for (const auto& pair : groupTable) {
        pair.second->write(file);
    }
    file.close();
}

void Database::loadGroupsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Erreur: Impossible d'ouvrir le fichier.\n";
        return;
    }

    groupTable.clear();
    std::string type;
    while (file >> type) {
        if (type == "Group") {
            auto group = std::make_shared<Group>("");
            group->read(file, *this);
            groupTable[group->getName()] = group;
        }
    }
    file.close();
}

void Database::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Erreur: Impossible d'ouvrir le fichier pour l'écriture.";
        return;
    }
    
    for (const auto& pair : multimediaTable) {
        pair.second->write(file);
    }
    file.close();
}

void Database::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Erreur: Impossible d'ouvrir le fichier pour la lecture.\n";
        return;
    }

    multimediaTable.clear();
    std::string type;
    
    while (file >> type) {
        if (type == "Photo") {
            std::string name, path;
            double latitude = 0, longitude = 0;

            file >> name >> path >> latitude >> longitude;
            if (file.fail()) {
                std::cerr << "Erreur: Format incorrect pour la photo '" << name << "'.\n";
                file.clear();
                file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            auto photo = std::make_shared<Photo>(name, path, latitude, longitude);
            multimediaTable[photo->getName()] = photo;
            std::cout << "[DEBUG] Photo chargée: " << name << " (" << latitude << ", " << longitude << ")\n";
        }
        else if (type == "Video") {
            std::string name, path;
            int duration = 0;

            file >> name >> path >> duration;
            if (file.fail()) {
                std::cerr << "Erreur: Format incorrect pour la vidéo '" << name << "'.\n";
                file.clear();
                file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            auto video = std::make_shared<Video>(name, path, duration);
            multimediaTable[video->getName()] = video;
            std::cout << "[DEBUG] Vidéo chargée: " << name << " (" << duration << "s)\n";
        }
        else if (type == "Film") {
            std::string name, path;
            int duration = 0, nbChapters = 0;

            file >> name >> path >> duration >> nbChapters;
            if (file.fail()) {
                std::cerr << "Erreur: Format incorrect pour le film '" << name << "'.\n";
                file.clear();
                file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            auto film = std::make_shared<Film>(name, path, duration, nullptr, nbChapters);
            film->setChapters(new int[nbChapters], nbChapters);
            multimediaTable[film->getName()] = film;
            std::cout << "[DEBUG] Film chargé: " << name << " (" << duration << "s, " << nbChapters << " chapitres)\n";
        }
        else {
            std::cerr << "Erreur: Type inconnu '" << type << "' trouvé dans le fichier.\n";
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    file.close();
}

