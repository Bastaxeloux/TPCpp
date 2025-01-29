#include "Film.h"

// Constructeur normal
Film::Film(const std::string& name, const std::string& pathname, int duration, const int* chapters, int numChapters)
    : Video(name, pathname, duration) {
    setChapters(chapters, numChapters);
}

// Destructeur (libère la mémoire du tableau)
Film::~Film() {
    delete[] chapters;
}

// Constructeur de copie (évite le partage du même tableau)
Film::Film(const Film& other) : Video(other) {
    setChapters(other.chapters, other.nbChapters);
}

// Opérateur d'affectation (évite le partage du même tableau)
Film& Film::operator=(const Film& other) {
    if (this != &other) { // Éviter l’auto-affectation (ex: obj = obj)
        Video::operator=(other); // Appelle l'affectation de Video
        setChapters(other.chapters, other.nbChapters);
    }
    return *this;
}

// Modifieur : Copie le tableau
void Film::setChapters(const int* newChapters, int newNumChapters) {
    delete[] chapters; // Libère l'ancien tableau
    if (newNumChapters > 0 && newChapters != nullptr) {
        nbChapters = newNumChapters;
        chapters = new int[nbChapters];
        for (int i = 0; i < nbChapters; ++i) {
            chapters[i] = newChapters[i];
        }
    } else {
        chapters = nullptr;
        nbChapters = 0;
    }
}

// Accesseurs
const int* Film::getChapters() const {
    return chapters;
}

int Film::getNbChapters() const {
    return nbChapters;
}

// Affichage
void Film::display(std::ostream& os) const {
    Video::display(os);
    os << "Chapitres (" << nbChapters << "): ";
    for (int i = 0; i < nbChapters; ++i) {
        os << chapters[i] << "s ";
    }
    os << std::endl;
}
