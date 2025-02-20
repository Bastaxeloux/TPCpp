#ifndef PHOTO_H
#define PHOTO_H

#include "Multimedia.h"

class Photo : public Multimedia {
private:
    double latitude;
    double longitude;

public:
    // Constructeur
    Photo(const std::string& name, const std::string& path, double lat, double lon)
        : Multimedia(name, path), latitude(lat), longitude(lon) {}

    // Getters
    double getLatitude() const { return latitude; }
    double getLongitude() const { return longitude; }

    // Setters
    void setLatitude(double lat) { latitude = lat; }
    void setLongitude(double lon) { longitude = lon; }

    // Affichage des informations
    void display(std::ostream& os) const override {
        Multimedia::display(os);
        os << "Latitude: " << latitude << ", Longitude: " << longitude << std::endl;
    }

    // Lecture de la photo
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
        
};

#endif // PHOTO_H
