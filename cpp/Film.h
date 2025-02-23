#ifndef FILM_H
#define FILM_H

/**
 * @file Film.h
 * @brief Définition de la classe Film.
 */

#include "Video.h"

/**
 * @class Film
 * @brief Classe Film.
 * @details Hérite de Video. Gestion de chapitres avec attributs : 
 *          - chapters : tableau dynamique des durées.
 *          - nbChapters : nombre de chapitres.
 */
class Film : public Video {
    private:
        int* chapters = nullptr; ///< tableau dynamique, durée par chapitre
        int nbChapters = 0;      ///< nombre de chapitres

    public:
        /**
         * @brief Constructeur sans arguments.
         */
        Film();

        /**
         * @brief Constructeur avec paramètres.
         * @param name nom
         * @param path chemin du fichier
         * @param duration durée de la vidéo
         * @param chapters tableau des chapitres
         * @param nbChapters nombre de chapitres
         */
        Film(const std::string& name, const std::string& path, int duration, const int* chapters, int nbChapters);

        /**
         * @brief Destructeur.
         */
        ~Film();

        /**
         * @brief Constructeur de copie.
         * @param other instance à copier
         */
        Film(const Film& other);

        /**
         * @brief Opérateur d’affectation.
         * @param other instance source
         * @return référence à l’instance modifiée
         */
        Film& operator=(const Film& other);

        /**
         * @brief Définit les chapitres.
         * @param newChapitres nouveaux chapitres (tableau)
         * @param newNbChapitres nombre de chapitres
         */
        void setChapters(const int* newChapitres, int newNbChapitres);

        /**
         * @brief Accès en lecture aux chapitres.
         * @return pointeur constant sur les chapitres
         */
        const int* getChapters() const;

        /**
         * @brief Accès au nombre de chapitres.
         * @return nombre de chapitres
         */
        int getNbChapters() const;

        /**
         * @brief Affichage.
         * @param stream flux de sortie
         */
        void display(std::ostream& stream) const override;

        /**
         * @brief Ecriture des infos du film.
         * @param os flux de sortie
         */
        void write(std::ostream& os) const override {
            os << "Film ";
            Multimedia::write(os);
            os << getDuration() << " " << nbChapters << " ";
            for (int i = 0; i < nbChapters; i++) {
                os << chapters[i] << " ";
            }
            os << "\n";
        }
        
        /**
         * @brief Lecture des infos du film.
         * @param is flux d'entrée
         */
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

        /**
         * @brief Retourne le type.
         * @return "Film"
         */
        std::string getType() const override { return "Film"; }
};
    

#endif // FILM_H