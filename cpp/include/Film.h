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

        void write(std::ostream& os) const override {
            os << "Film ";
            Multimedia::write(os);
            os << getDuration() << " " << nbChapters << " ";
            for (int i = 0; i < nbChapters; i++) {
                os << chapters[i] << " ";
            }
            os << "\n";
        }
        
        void read(std::istream& is) override {
            Multimedia::read(is);
            int tempDuration;
            is >> tempDuration >> nbChapters;
            setDuration(tempDuration);
            delete[] chapters;
            chapters = new int[nbChapters];
            for (int i = 0; i < nbChapters; i++) {
                is >> chapters[i];
            }
        }

        std::string getType() const override { return "Film"; }
};
    

#endif // FILM_H