#include <iostream>
#include <vector>
#include "Photo.h"
#include "Video.h"
#include "Film.h"

int main() {

    int chapters[] = {10,5,5,10};

    std::vector<Multimedia*> Tableau;

    Tableau.push_back(new Photo("Image", "/mnt/c/Users/maell/SynologyDrive/Telecom/Cours2AAAAAAAAAAA/Cours/INF224/TPC/image.jpg", 48.8, 12.2));
    // Tableau.push_back(new Video("Vidéo", "/mnt/c/Users/maell/SynologyDrive/Telecom/Cours2AAAAAAAAAAA/Cours/INF224/TPC/video.mp4", 60));
    Tableau.push_back(new Photo("Image2", "/mnt/c/Users/maell/SynologyDrive/Telecom/Cours2AAAAAAAAAAA/Cours/INF224/TPC/image2.jpg", 48.8, 12.2));
    Tableau.push_back(new Film("Film", "/mnt/c/Users/maell/SynologyDrive/Telecom/Cours2AAAAAAAAAAA/Cours/INF224/TPC/video.mp4", 120, chapters, 4));

    // Boucle polymorphique pour afficher les informations
    std::cout << "Affichage des objets Multimedia :" << std::endl;
    for (const auto& media : Tableau) {
        media->display(std::cout);
    }

    // Boucle polymorphique pour jouer les fichiers
    std::cout << "\nLecture des fichiers multimédias..." << std::endl;
    for (const auto& media : Tableau) {
        media->play();
    }

    for (auto& media : Tableau) {
        delete media;
    }

    return 0;
}