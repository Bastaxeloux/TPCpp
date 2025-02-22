#include "Database.h"

int main() {
    Database db;

    // Création de quelques objets
    auto photo1 = db.createPhoto("Montagne", "media/image.jpg", 45.5, 6.2);
    auto video1 = db.createVideo("Concert", "media/video.mp4", 120);
    
    int chapters[] = { 0, 60, 120, 180 };
    auto film1 = db.createFilm("Inception", "media/inception.mp4", 600, chapters, 4);

    // Création de groupes
    auto group1 = db.createGroup("Vacances");
    group1->push_back(photo1);
    group1->push_back(video1);

    auto group2 = db.createGroup("Films");
    group2->push_back(film1);
    group2->push_back(video1);

    // Tests
    db.displayMultimedia("Inception", std::cout);
    db.displayGroup("Films", std::cout);

    db.playMultimedia("Concert");

    db.deleteMultimedia("Concert");
    db.deleteGroup("Vacances");

    return 0;
}
