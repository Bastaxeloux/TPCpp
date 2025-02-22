#ifndef VIDEO_H
#define VIDEO_H

#include "Multimedia.h"

class Video : public Multimedia {
private:
    int duration;

public:
    // Constructeur
    Video(const std::string& name, const std::string& path, int duration)
        : Multimedia(name, path), duration(duration) {}

    // Getter
    int getDuration() const { return duration; }

    // Setter
    void setDuration(int d) { duration = d; }

    // Affichage des informations
    void display(std::ostream& os) const override {
        Multimedia::display(os);
        os << "Durée: " << duration << " secondes" << std::endl;
    }

    // Lecture de la vidéo
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

    void write(std::ostream& os) const override {
        os << "Video ";
        Multimedia::write(os);
        os << duration << "\n";
    }
    
    void read(std::istream& is) override {
        Multimedia::read(is);
        is >> duration;
    }
    
    std::string getType() const override { return "Video"; }
};   

#endif // VIDEO_H
