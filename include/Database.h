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
 * Classe Database : Gestion centralisée des objets multimédias et groupes
 * 
 * - `std::map<std::string, std::shared_ptr<Multimedia>> multimediaTable` :
 *   Table associant un nom à un objet multimédia (accès rapide).
 * - `std::map<std::string, std::shared_ptr<Group>> groupTable` :
 *   Table associant un nom à un groupe.
 * 
 * - Méthodes `createPhoto()`, `createVideo()`, `createFilm()`, `createGroup()` :
 *   Créent un objet et l'ajoutent dans la table correspondante.
 * 
 * - `displayMultimedia()`, `displayGroup()` :
 *   Affichent les attributs d’un objet ou le contenu d’un groupe.
 * 
 * - `playMultimedia()` :
 *   Joue un objet multimédia par son nom.
 * 
 * - `deleteMultimedia()`, `deleteGroup()` :
 *   Suppriment un élément des tables, et un objet multimédia est retiré de tous les groupes.
*/

class Database {
private:
    std::map<std::string, MPtr> multimediaTable;
    std::map<std::string, GPtr> groupTable;

public:
    // Création des objets multimédias
    std::shared_ptr<Photo> createPhoto(const std::string& name, const std::string& path, double latitude, double longitude);
    std::shared_ptr<Video> createVideo(const std::string& name, const std::string& path, int duration);
    std::shared_ptr<Film> createFilm(const std::string& name, const std::string& path, int duration, const int* chapters, int nbChapters);
    std::shared_ptr<Group> createGroup(const std::string& name);

    // Recherche et affichage
    void displayMultimedia(const std::string& name, std::ostream& stream) const;
    void displayGroup(const std::string& name, std::ostream& stream) const;

    // Lecture d'un fichier multimédia
    void playMultimedia(const std::string& name) const;

    // Suppression d'un objet multimédia ou d'un groupe
    void deleteMultimedia(const std::string& name);
    void deleteGroup(const std::string& name);

    // Getters
    MPtr getMedia(const std::string& name) const;
    GPtr getGroup(const std::string& name) const;

    void listAllMedia(std::ostream&) const;
    void listAllGroups(std::ostream&) const;
    void searchPartial(const std::string& keyword, std::ostream&) const;
    void searchByType(const std::string& type, std::ostream&) const;
    bool deleteObject(const std::string& name);
    bool addMediaToGroup(const std::string& mediaName, const std::string& groupName);
    bool removeMediaFromGroup(const std::string& mediaName, const std::string& groupName);
    bool isMediaInGroup(const std::string& mediaName, const std::string& groupName) const;

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
    void saveGroupsToFile(const std::string& filename) const;
    void loadGroupsFromFile(const std::string& filename);

    
};

#endif // DATABASE_H
