# ifndef MULTIMEDIA_H
# define MULTIMEDIA_H

# include <string>
# include <iostream>


class Multimedia {
    /**
     * @class Multimedia
     * @brief Une classe de base, qui servira de base pour tous les objets multimédias (photos, vidéos, films, etc.).
     *
     * Cette classe contiendra :
     * - Deux attributs std::string :
     *      - name → Nom de l'objet multimédia.
     *      - filename → Chemin du fichier associé.
     * - Un constructeur par défaut et un constructeur avec arguments.
     * - Un destructeur (virtuel pour permettre l'héritage propre).
     * - Des getters et setters pour les deux attributs.
     * - Une méthode display(std::ostream&) const pour afficher les informations.
     * - Une méthode play() const qui sera redéfinie dans les classes filles.
     * 
     * On va d'abord créer le fichier d'en-tête Multimedia.h dans include/, puis l'implémentation Multimedia.cpp dans src/.
     */
   
    protected:
        std::string name;
        std::string path;

    public:
        // Constructeurs
        Multimedia();
        Multimedia(const std::string& nom, const std::string& path);

        // Destructeur
        virtual ~Multimedia();

        // Getters
        std::string getName() const;
        std::string getPath() const;

        // Setters
        void setName(const std::string& nom);
        void setPath(const std::string& path);

        // Affichage
        virtual void display(std::ostream& out) const;

        // Lecture de l'objet (méthode virtuelle pure → rend la classe abstraite)
        virtual void play() const = 0;
};

# endif // MULTIMEDIA_H
