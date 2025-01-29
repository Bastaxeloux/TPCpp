# ifndef MULTIMEDIA_H
# define MULTIMEDIA_H

# include <string>
# include <iostream>

class Multimedia {
    protected:
        std::string name; // nom du fichier
        std::string path; // chemin d'accès au fichier

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
