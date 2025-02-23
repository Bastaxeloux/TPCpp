#ifndef DATABASE_H
#define DATABASE_H

#include <map>
#include <memory>
#include <string>
#include <iostream>

#include "Multimedia.h"
#include "Photo.h"
#include "Video.h"
#include "Film.h"
#include "Group.h"

using MPtr = std::shared_ptr<Multimedia>;
using GPtr = std::shared_ptr<Group>;

/**
 * @class Database
 * @brief Gestion centralisée des objets multimédias et groupes.
 * 
 * Tables associatives :
 * - multimediaTable : nom -> Multimedia.
 * - groupTable : nom -> Group.
 */
class Database {
private:
    std::map<std::string, MPtr> multimediaTable;   ///< Table multimédia
    std::map<std::string, GPtr> groupTable;          ///< Table groupe

public:
    /**
     * @brief Crée photo.
     * @param name Nom de la photo.
     * @param path Chemin d'accès.
     * @param latitude Coord. latitude.
     * @param longitude Coord. longitude.
     * @return std::shared_ptr<Photo>
     */
    std::shared_ptr<Photo> createPhoto(const std::string& name, const std::string& path, double latitude, double longitude);

    /**
     * @brief Crée video.
     * @param name Nom de la vidéo.
     * @param path Chemin d'accès.
     * @param duration Durée.
     * @return std::shared_ptr<Video>
     */
    std::shared_ptr<Video> createVideo(const std::string& name, const std::string& path, int duration);

    /**
     * @brief Crée film.
     * @param name Nom du film.
     * @param path Chemin d'accès.
     * @param duration Durée.
     * @param chapters Tableau chapitres.
     * @param nbChapters Nombre de chapitres.
     * @return std::shared_ptr<Film>
     */
    std::shared_ptr<Film> createFilm(const std::string& name, const std::string& path, int duration, const int* chapters, int nbChapters);

    /**
     * @brief Crée groupe.
     * @param name Nom du groupe.
     * @return std::shared_ptr<Group>
     */
    std::shared_ptr<Group> createGroup(const std::string& name);

    /**
     * @brief Affiche attributs multimedia.
     * @param name Nom multimédia.
     * @param stream Flux de sortie.
     */
    void displayMultimedia(const std::string& name, std::ostream& stream) const;

    /**
     * @brief Affiche contenu groupe.
     * @param name Nom groupe.
     * @param stream Flux de sortie.
     */
    void displayGroup(const std::string& name, std::ostream& stream) const;

    /**
     * @brief Joue multimédia.
     * @param name Nom multimédia.
     */
    void playMultimedia(const std::string& name) const;

    /**
     * @brief Supprime multimédia.
     * @param name Nom multimédia.
     */
    void deleteMultimedia(const std::string& name);

    /**
     * @brief Supprime groupe.
     * @param name Nom groupe.
     */
    void deleteGroup(const std::string& name);

    /**
     * @brief Récupère multimedia.
     * @param name Nom multimédia.
     * @return MPtr
     */
    MPtr getMedia(const std::string& name) const;

    /**
     * @brief Récupère groupe.
     * @param name Nom groupe.
     * @return GPtr
     */
    GPtr getGroup(const std::string& name) const;

    /**
     * @brief Liste tous les multimédias.
     * @param os Flux de sortie.
     */
    void listAllMedia(std::ostream& os) const;

    /**
     * @brief Liste tous les groupes.
     * @param os Flux de sortie.
     */
    void listAllGroups(std::ostream& os) const;

    /**
     * @brief Recherche partielle.
     * @param keyword Mot-clé.
     * @param os Flux de sortie.
     */
    void searchPartial(const std::string& keyword, std::ostream& os) const;

    /**
     * @brief Recherche par type.
     * @param type Type multimédia.
     * @param os Flux de sortie.
     */
    void searchByType(const std::string& type, std::ostream& os) const;

    /**
     * @brief Supprime objet (multimedia ou groupe).
     * @param name Nom objet.
     * @return bool
     */
    bool deleteObject(const std::string& name);

    /**
     * @brief Ajoute multimedia dans groupe.
     * @param mediaName Nom multimédia.
     * @param groupName Nom groupe.
     * @return bool
     */
    bool addMediaToGroup(const std::string& mediaName, const std::string& groupName);

    /**
     * @brief Retire multimedia d'un groupe.
     * @param mediaName Nom multimédia.
     * @param groupName Nom groupe.
     * @return bool
     */
    bool removeMediaFromGroup(const std::string& mediaName, const std::string& groupName);

    /**
     * @brief Vérifie présence multimedia dans groupe.
     * @param mediaName Nom multimédia.
     * @param groupName Nom groupe.
     * @return bool
     */
    bool isMediaInGroup(const std::string& mediaName, const std::string& groupName) const;

    /**
     * @brief Sauvegarde multimedia.
     * @param filename Nom fichier.
     */
    void saveToFile(const std::string& filename) const;

    /**
     * @brief Charge multimedia.
     * @param filename Nom fichier.
     */
    void loadFromFile(const std::string& filename);

    /**
     * @brief Sauvegarde groupes.
     * @param filename Nom fichier.
     */
    void saveGroupsToFile(const std::string& filename) const;

    /**
     * @brief Charge groupes.
     * @param filename Nom fichier.
     */
    void loadGroupsFromFile(const std::string& filename);
};

#endif // DATABASE_H
