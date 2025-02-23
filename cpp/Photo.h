#ifndef PHOTO_H
#define PHOTO_H

#include "Multimedia.h"

/**
 * @file Photo.h
 * @brief Photo class declaration.
 */

/**
 * @class Photo
 * @brief Hérite de Multimedia.
 * @details latitude, longitude; display, play, read, write.
 */
class Photo : public Multimedia {
private:
    double latitude;  ///< latitude
    double longitude; ///< longitude

public:
    /**
     * @brief Constructeur.
     * @param name nom
     * @param path chemin
     * @param lat latitude
     * @param lon longitude
     */
    Photo(const std::string& name, const std::string& path, double lat, double lon)
        : Multimedia(name, path), latitude(lat), longitude(lon) {}

    /// @brief get latitude
    double getLatitude() const { return latitude; }
    /// @brief get longitude
    double getLongitude() const { return longitude; }

    /// @brief set latitude
    void setLatitude(double lat) { latitude = lat; }
    /// @brief set longitude
    void setLongitude(double lon) { longitude = lon; }

    /**
     * @brief Affichage.
     * @param os flux de sortie
     */
    void display(std::ostream& os) const override {
        Multimedia::display(os);
        os << "Latitude: " << latitude << ", Longitude: " << longitude << std::endl;
    }

    /**
     * @brief Lecture.
     * @details spécifique selon OS.
     */
    void play() const override { // on est obligés de faire ca car chaque systeme d'exploitation a sa propre commande pour ouvrir une photo
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
     * @brief Écriture.
     * @param os flux de sortie
     */
    void write(std::ostream& os) const override {
        os << "Photo ";
        Multimedia::write(os);
        os << latitude << " " << longitude << "\n";
    }
    
    /**
     * @brief Lecture.
     * @param is flux d'entrée
     */
    void read(std::istream& is) override {
        Multimedia::read(is);
        is >> latitude >> longitude;
    }

    /// @brief Type de média
    std::string getType() const override { return "Photo"; }
        
};

#endif // PHOTO_H
