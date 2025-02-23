/**
 * @file Multimedia.cpp
 * @brief Implémentation des méthodes de la classe Multimedia.
 */

#include "Multimedia.h"


/**
 * @brief Constructeur sans paramètres.
 * @keyword default, initialisation.
 */
Multimedia::Multimedia() : name(""), path("") {}

/**
 * @brief Constructeur avec paramètres.
 * @param nom Nom du média.
 * @param path Chemin d'accès au média.
 * @keyword paramétrage, initialisation.
 */
Multimedia::Multimedia(const std::string& nom, const std::string& path) : name(nom), path(path) {}

/**
 * @brief Destructeur.
 * @keyword destruction, nettoyage.
 */
Multimedia::~Multimedia() {
    std::cout << "Destruction de l'objet multimédia : " << name << std::endl;
}

/**
 * @brief Getter pour le nom.
 * @return Nom du média.
 * @keyword lecture, valeur.
 */
std::string Multimedia::getName() const {
    return name;
}

/**
 * @brief Getter pour le chemin d'accès.
 * @return Chemin d'accès du média.
 * @keyword lecture, valeur.
 */
std::string Multimedia::getPath() const {
    return path;
}

/**
 * @brief Setter pour le nom.
 * @param nom Nouveau nom du média.
 * @keyword modification, mise à jour.
 */
void Multimedia::setName(const std::string& nom) {
    name = nom;
}

/**
 * @brief Setter pour le chemin d'accès.
 * @param path Nouveau chemin d'accès au média.
 * @keyword modification, mise à jour.
 */
void Multimedia::setPath(const std::string& path) {
    this->path = path;
}

/**
 * @brief Affichage des informations du média.
 * @param out Flux de sortie.
 * @keyword affichage, sortie.
 */
void Multimedia::display(std::ostream& out) const {
    out << "Nom: " << name << ", Chemin d'accès: " << path << std::endl;
}

/**
 * @brief Ecriture des informations sur un flux.
 * @param os Flux de sortie.
 * @keyword sérialisation, sortie.
 */
void Multimedia::write(std::ostream& os) const {
    os << name << " " << path << " ";
}

/**
 * @brief Lecture des informations à partir d'un flux.
 * @param is Flux d'entrée.
 * @keyword désérialisation, entrée.
 */
void Multimedia::read(std::istream& is) {
    is >> name >> path;
}
