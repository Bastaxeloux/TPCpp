#include "Multimedia.h"

// Constructeur sans paramètres
Multimedia::Multimedia() : name(""), path("") {}

// Constructeur avec paramètres
Multimedia::Multimedia(const std::string& nom, const std::string& path) : name(nom), path(path) {}
// on met & comme ca on ne copie pas le string mais on passe juste l'adresse

// Destructeur
Multimedia::~Multimedia() {}

// Getter pour le nom
std::string Multimedia::getName() const {
    return name;
}

// Getter pour le chemin d'accès
std::string Multimedia::getPath() const {
    return path;
}

// Setter pour le nom
void Multimedia::setName(const std::string& nom) {
    name = nom;
}

// Setter pour le chemin d'accès
void Multimedia::setPath(const std::string& path) {
    this->path = path;
}

// Affichage
void Multimedia::display(std::ostream& out) const {
    out << "Nom: " << name << ", Chemin d'accès: " << path << std::endl;
}