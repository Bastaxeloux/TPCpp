#ifndef FILM_H
#define FILM_H

#include "Video.h"

class Film : public Video {
    private:
        int* chapters = nullptr;
        int nbChapters = 0;

    public:
        // Constructeur
        Film(const std::string& name, const std::string& path, int duration,const int* chapters, int nbChap);

        // Destructeur
        ~Film();

        // Constructeur de copie
        Film(const Film& other);

        // Opérateur d'affectation
        Film& operator=(const Film& other);

        // Modificateurs
        void setChapters(const int* chapters, int nbChap);

        // Accesseurs
        const int* getChapters() const; // Retourne un pointeur constant
        int getNbChapters() const; // Retourne le nombre de chapitres

        // Affichage 
        void display(std::ostream& os) const override;
    
};

#endif // FILM_H
