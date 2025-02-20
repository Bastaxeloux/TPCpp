#ifndef FILM_H
#define FILM_H

#include "Video.h"

class Film : public Video {
    private:
        int* chapters = nullptr;
        int nbChapters = 0;

    public:
        // Constructeur sans arguments 
        Film();

        // Constructeur avec arguments (implémenté dans Film.cpp)
        Film(const std::string& name, const std::string& path, int duration, const int* chapters, int nbChapters);

        // Destructeur (implémenté dans Film.cpp)
        ~Film();

        // Constructeur de copie
        Film(const Film& other);

        // Opérateur d’affectation
        Film& operator=(const Film& other);

        void setChapters(const int* newChapitres, int newNbChapitres);
        const int* getChapters() const; // le fait que ca soit const est important sinon on pourrait le modifier
        int getNbChapters() const;
        void display(std::ostream& stream) const override;
};

#endif // FILM_H