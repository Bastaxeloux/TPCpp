/**
 * @file Video.h
 * @brief Déclaration de la classe Video.
 */

#ifndef VIDEO_H
#define VIDEO_H

#include "Multimedia.h"

/**
 * @class Video
 * @brief Sous-classe de Multimedia.
 */
class Video : public Multimedia {
private:
    int duration;  ///< durée en secondes

public:
    /**
     * @brief Constructeur.
     * @param name  Nom (clé).
     * @param path  Chemin (clé).
     * @param duration Durée (clé).
     */
    Video(const std::string& name, const std::string& path, int duration)
        : Multimedia(name, path), duration(duration) {}

    /**
     * @brief Getter durée.
     * @return durée.
     */
    int getDuration() const { return duration; }

    /**
     * @brief Setter durée.
     * @param d  Nouvelle durée.
     */
    void setDuration(int d) { duration = d; }

    /**
     * @brief Affichage infos.
     * @param os Flux de sortie.
     */
    void display(std::ostream& os) const override {
        Multimedia::display(os);
        os << "Durée: " << duration << " secondes" << std::endl;
    }

    /**
     * @brief Lecture.
     */
    void play() const override {
        std::string path = getPath();
        #ifdef _WIN32
            system(("start " + path).c_str());  // Windows
        #elif __APPLE__
            system(("open " + path + " &").c_str());  // macOS
        #else
            system(("xdg-open " + path + " &").c_str());  // Linux (Ubuntu, Debian, etc.)
        #endif
    }

    /**
     * @brief Sérialisation.
     * @param os Flux de sortie.
     */
    void write(std::ostream& os) const override {
        os << "Video ";
        Multimedia::write(os);
        os << duration << "\n";
    }
    
    /**
     * @brief Désérialisation.
     * @param is Flux d'entrée.
     */
    void read(std::istream& is) override {
        Multimedia::read(is);
        is >> duration;
    }
    
    /**
     * @brief Type d'objet.
     * @return "Video".
     */
    std::string getType() const override { return "Video"; }
};   

#endif // VIDEO_H
