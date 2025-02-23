#include "Film.h"

/**
 * @brief Constructeur par défaut
 * @note initialisation Video, chapters null, nbChapters 0
 */
Film::Film() : Video("", "", 0), chapters(nullptr), nbChapters(0) {}

/**
 * @brief Constructeur paramétré
 * @param name identifiant
 * @param path chemin
 * @param duration durée
 * @param chapters tableau d'ints
 * @param nbChapters taille du tableau
 */
Film::Film(const std::string& name, const std::string& path, int duration, const int* chapters, int nbChapters)
    : Video(name, path, duration), chapters(nullptr), nbChapters(0) {
    setChapters(chapters, nbChapters);
}

/**
 * @brief Destructeur
 * @note Libère chapters
 */
Film::~Film() {
    delete [] chapters;
    std::cout << "Destruction de l'objet Film : " << getName() << std::endl;
}

/**
 * @brief Setter pour chapters
 * @param newChapitres nouveau tableau
 * @param newNbChapitres taille
 * @note Copie, efface ancien tableau
 */
void Film::setChapters(const int* newChapitres, int newNbChapitres) {
    delete [] chapters;
    if (newChapitres && newNbChapitres > 0) {
        nbChapters = newNbChapitres;
        chapters = new int[nbChapters];
        for (int i = 0; i < nbChapters; i++) {
            chapters[i] = newChapitres[i];
        }
    }
    else {
        nbChapters = 0;
        chapters = nullptr;
    }
}

/**
 * @brief Getter chapters
 * @return pointeur vers tableau constant
 */
const int* Film::getChapters() const {
    return chapters;
}

/**
 * @brief Getter nbChapters
 * @return nombre de chapitres
 */
int Film::getNbChapters() const {
    return nbChapters;
}

/**
 * @brief Affichage Film
 * @param stream flux de sortie
 * @note Affiche attributs Video et chapters
 */
void Film::display(std::ostream& stream) const {
    Video::display(stream);
    stream << "Chapitres: ";
    if (nbChapters > 0) {
        for (int i = 0; i < nbChapters; i++) {
            stream << chapters[i] << " ";
        }
    }
    else {
        stream << "Aucun chapitre";
    }
    stream << std::endl;
}

/**
 * @brief Constructeur de copie
 * @param other instance Film à copier
 * @note copie Video et tableau chapters
 */
Film::Film(const Film& other) : Video(other) {
    setChapters(other.chapters, other.nbChapters);
}

/**
 * @brief Opérateur d’affectation copie
 * @param other instance Film à copier
 * @return référence modifiée
 * @note Protection auto-affectation, copie Video
 */
Film& Film::operator=(const Film& other) {
    if (this != &other) {  // Protection contre l’auto-affectation
        Video::operator=(other);  // Copie des attributs de Video
        setChapters(other.chapters, other.nbChapters);
    }
    return *this;
}
