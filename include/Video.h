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
        std::string command = "mpv " + path + " &";
        system(command.c_str());
    }
};

#endif // VIDEO_H
