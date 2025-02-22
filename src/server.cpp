#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <functional>
#include <fstream>
#include "tcpserver.h"
#include "Database.h"

const int PORT = 3331;
Database db;
std::map<std::string, std::function<void(std::stringstream&, std::string&)>> commandMap;
void setupCommands();

int main() {
  setupCommands(); // Initialise les commandes

  auto dust2 = db.createPhoto("Dust2", "media/image.jpg", 45.5, 6.2);
  auto kato = db.createVideo("Vitality", "media/video.mp4", 120);
  auto mirage = db.createPhoto("Mirage", "media/image2.jpg", 43.5, 7.2);
  auto cesar = db.createPhoto("Cesar", "media/cesar.jpg", 43.5, 7.2);
  auto fire = db.createPhoto("Fire", "media/fire.jpg", 43.5, 7.2);
  auto france = db.createPhoto("France", "media/france.jpg", 43.5, 7.2);
  auto keyboard = db.createPhoto("Keyboard", "media/keyboard.jpg", 43.5, 7.2);
  auto leman = db.createPhoto("Leman", "media/leman.jpg", 43.5, 7.2);
  auto lighthouse = db.createPhoto("Lighthouse", "media/lighthouse.jpg", 43.5, 7.2);
  auto sailing = db.createPhoto("Sailing", "media/sailing.jpg", 43.5, 7.2);
  auto ski = db.createPhoto("Ski", "media/ski.jpg", 43.5, 7.2);
  auto storm = db.createPhoto("Storm", "media/storm.jpg", 43.5, 7.2);
  
  auto csgo = db.createGroup("CSGO");
  auto replay = db.createGroup("Replay");
  auto pexels = db.createGroup("Pexels");

  csgo->push_back(dust2);
  csgo->push_back(kato);
  csgo->push_back(mirage);

  replay->push_back(kato);

  pexels->push_back(cesar);
  pexels->push_back(fire);
  pexels->push_back(leman);
  pexels->push_back(lighthouse);
  pexels->push_back(sailing);
  pexels->push_back(ski);
  pexels->push_back(storm);

  db.saveToFile("database.txt");

  std::ifstream testFile("database.txt");
  std::cout << "📂 Contenu de database.txt :\n";
  std::cout << testFile.rdbuf();
  testFile.close();

  db.saveGroupsToFile("groups.txt");

  std::cout << "Sauvegarde effectuée.; " << std::endl;

  db = Database();
  std::cout << "Base réinitialisée.; ";

  db.loadFromFile("database.txt");
  db.loadGroupsFromFile("groups.txt"); 

  std::cout << "[DEBUG] Vérification des groupes après chargement :\n";
  db.listAllGroups(std::cout);

  std::cout << "Vérification après rechargement :; ";
  db.displayMultimedia("Dust2", std::cout);
  db.displayMultimedia("Vitality", std::cout);
  db.displayGroup("CSGO", std::cout);


  // Lancement du serveur
  TCPServer server([&](const std::string& request, std::string& response) {
      std::stringstream ss(request);
      std::string command;
      ss >> command;

      // Exécution de la commande si elle existe
      auto it = commandMap.find(command);
      if (it != commandMap.end()) {
          it->second(ss, response);
      } else {
          response = "Erreur : Commande inconnue.";
      }
      return true;
  });

  std::cout << "Serveur démarré sur le port" << PORT << std::endl;
  int status = server.run(PORT);

  if (status < 0) {
      std::cerr << "Impossible de démarrer le serveur sur le port" << PORT << std::endl;
      return 1;
  }
  else { return 0; }
}

// Définition de la fonction `setupCommands()`
void setupCommands() {
    // Liste les médias disponibles
    commandMap["list_media"] = [](std::stringstream& ss, std::string& response) {
        std::ostringstream oss;
        db.listAllMedia(oss);
        std::cout << "[DEBUG] Réponse envoyée : " << oss.str() << std::endl;
        response = oss.str();
    };

    // Liste les groupes disponibles
    commandMap["list_groups"] = [](std::stringstream& ss, std::string& response) {
        std::ostringstream oss;
        db.listAllGroups(oss);
        response = oss.str();
    };

    // Recherche un média par son nom
    commandMap["search_media"] = [](std::stringstream& ss, std::string& response) {
        std::string name;
        ss >> name;
        std::ostringstream oss;
        db.displayMultimedia(name, oss);
        response = oss.str();
    };

    // Recherche un groupe par son nom
    commandMap["search_group"] = [](std::stringstream& ss, std::string& response) {
        std::string name;
        ss >> name;
        std::ostringstream oss;
        db.displayGroup(name, oss);
        response = oss.str();
    };

    // Joue un média (ouvre le fichier)
    commandMap["play"] = [](std::stringstream& ss, std::string& response) {
        std::string name;
        ss >> name;
        db.playMultimedia(name);
        response = "Lecture de " + name;
    };

    // Recherche partielle (mots-clés)
    commandMap["search_partial"] = [](std::stringstream& ss, std::string& response) {
        std::string keyword;
        ss >> keyword;
        std::ostringstream oss;
        db.searchPartial(keyword, oss);
        response = oss.str();
    };

    // Recherche par type d'objet
    commandMap["search_type"] = [](std::stringstream& ss, std::string& response) {
        std::string type;
        ss >> type;
        std::ostringstream oss;
        db.searchByType(type, oss);
        response = oss.str();
    };

    // Suppression d'un média ou groupe
    commandMap["delete"] = [](std::stringstream& ss, std::string& response) {
        std::string name;
        ss >> name;
        if (db.deleteObject(name)) {
            response = "Objet '" + name + "' supprimé.";
        } else {
            response = "Erreur : L'objet '" + name + "' n'existe pas.";
        }
    };

    // Ajout d'un média
    commandMap["add_media"] = [](std::stringstream& ss, std::string& response) {
        std::string type, name, path;
        ss >> type >> name >> path;
        if (type == "photo") {
            double lat, lon;
            ss >> lat >> lon;
            db.createPhoto(name, path, lat, lon);
        } else if (type == "video") {
            int duration;
            ss >> duration;
            db.createVideo(name, path, duration);
        } else if (type == "film") {
            int duration, nbChapters;
            ss >> duration >> nbChapters;
            int* chapters = new int[nbChapters];
            for (int i = 0; i < nbChapters; ++i) {
                ss >> chapters[i];
            }
            db.createFilm(name, path, duration, chapters, nbChapters);
            delete[] chapters;
        } else {
            response = "Erreur : Type inconnu.";
            return;
        }
        response = "Média '" + name + "' ajouté.";
    };

    // Ajout d'un groupe
    commandMap["add_group"] = [](std::stringstream& ss, std::string& response) {
        std::string name;
        ss >> name;
        db.createGroup(name);
        response = "Groupe '" + name + "' ajouté.";
    };

    // Ajouter un média à un groupe
    commandMap["add_to_group"] = [](std::stringstream& ss, std::string& response) {
        std::string mediaName, groupName;
        ss >> mediaName >> groupName;
        if (db.addMediaToGroup(mediaName, groupName)) {
            response = "Média '" + mediaName + "' ajouté au groupe '" + groupName + "'.";
        } else {
            response = "Erreur : Impossible d'ajouter le média au groupe.";
        }
    };

    // Supprimer un média d'un groupe
    commandMap["remove_from_group"] = [](std::stringstream& ss, std::string& response) {
        std::string mediaName, groupName;
        ss >> mediaName >> groupName;
        if (db.removeMediaFromGroup(mediaName, groupName)) {
            response = "Média '" + mediaName + "' supprimé du groupe '" + groupName + "'.";
        } else {
            response = "Erreur : Impossible de supprimer le média du groupe.";
        }
    };

    // Vérifier si un média est dans un groupe
    commandMap["is_in_group"] = [](std::stringstream& ss, std::string& response) {
        std::string mediaName, groupName;
        ss >> mediaName >> groupName;
        if (db.isMediaInGroup(mediaName, groupName)) {
            response = "Oui, le média '" + mediaName + "' est dans le groupe '" + groupName + "'.";
        } else {
            response = "Non, le média '" + mediaName + "' n'est PAS dans le groupe '" + groupName + "'.";
        }
    };
}
