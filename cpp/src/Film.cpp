#include "Film.h"

Film::Film() : Video("", "", 0), chapters(nullptr), nbChapters(0) {}

Film::Film(const std::string& name, const std::string& path, int duration, const int* chapters, int nbChapters)
    : Video(name, path, duration), chapters(nullptr), nbChapters(0) {
    setChapters(chapters, nbChapters);
}

Film::~Film() {
    delete [] chapters;
    std::cout << "Destruction de l'objet Film : " << getName() << std::endl;
}

// Setters et getters

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

const int* Film::getChapters() const { // le fait que ca soit const est important sinon on pourrait le modifier
    return chapters;
}
int Film::getNbChapters() const {
    return nbChapters;
}

// Enfin on implémente la méthode display

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
 * Problème : 
 * - `chapters` est un pointeur, la copie par défaut copie l'adresse, 
 *   pas les valeurs → plusieurs objets Film partagent le même tableau.
 * - Si un objet est détruit, l'autre a un pointeur invalide (dangling pointer).
 * - Si un objet modifie `chapters`, l'autre est aussi affecté.
 * 
 * Solution :
 * - **Constructeur de copie** : alloue un nouveau tableau et copie les valeurs.
 * - **Opérateur `=`** : libère l'ancien tableau, copie les valeurs.
 * - **Vérification `this != &other`** dans `operator=` pour éviter l'auto-affectation.
*/


// Constructeur de copie
Film::Film(const Film& other) : Video(other) {
    setChapters(other.chapters, other.nbChapters);
}

// Opérateur d’affectation
Film& Film::operator=(const Film& other) {
    if (this != &other) {  // Protection contre l’auto-affectation
        Video::operator=(other);  // Copie des attributs de Video
        setChapters(other.chapters, other.nbChapters);
    }
    return *this;
}

