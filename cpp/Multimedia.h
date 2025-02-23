# ifndef MULTIMEDIA_H
# define MULTIMEDIA_H

# include <string>
# include <iostream>

/**
 * @brief Base, Multimedia
 * @details multimédia générique, classe abstraite, héritage.
 */
class Multimedia {
    protected:
        std::string name; ///< id, nom de l'objet
        std::string path; ///< chemin, localisation du fichier

    public:
        /// Constructeur, initialisation par défaut.
        Multimedia();
        /// Constructeur, initialise avec nom et chemin.
        Multimedia(const std::string& nom, const std::string& path);

        /// Destructeur virtuel, gestion mémoire, polymorphisme.
        virtual ~Multimedia();

        /// Getter, retourne le nom.
        std::string getName() const;
        /// Getter, retourne le chemin.
        std::string getPath() const;

        /// Setter, modifie le nom.
        void setName(const std::string& nom);
        /// Setter, modifie le chemin.
        void setPath(const std::string& path);

        /// Affichage, stream, sortie infos.
        virtual void display(std::ostream& out) const;

        /// Méthode virtuelle pure, lecture, redéfinition obligatoire.
        virtual void play() const = 0;
        /// Méthode virtuelle pure, type, redéfinition obligatoire.
        virtual std::string getType() const = 0;

        /// Sérialisation, écriture dans un flux.
        virtual void write(std::ostream& os) const;
        /// Désérialisation, lecture depuis un flux.
        virtual void read(std::istream& is);
};

# endif // MULTIMEDIA_H
