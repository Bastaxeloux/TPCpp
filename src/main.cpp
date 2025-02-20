#include <iostream>
#include <vector>
#include "Photo.h"
#include "Video.h"
#include "Film.h"

int main() {
    // Définition des chapitres
    int chapters1[] = { 0, 120, 240, 360 };

    // Création d'un film
    Film film1("Inception", "media/inception.mp4", 600, chapters1, 4);
    std::cout << "Film 1 :" << std::endl;
    film1.display(std::cout);

    // **Test du constructeur de copie**
    Film film2 = film1;
    std::cout << "\nFilm 2 (copie de film1) :" << std::endl;
    film2.display(std::cout);

    // **Test de l’opérateur `=`**
    Film film3;
    film3 = film1;
    std::cout << "\nFilm 3 (après affectation de film1) :" << std::endl;
    film3.display(std::cout);

    // **Test de la modification des chapitres**
    int chapters2[] = { 0, 60, 120, 180, 240, 300, 360 };
    film1.setChapters(chapters2, 7);
    std::cout << "\nFilm 1 (après modification des chapitres) :" << std::endl;
    film1.display(std::cout);
    std::cout << "\nFilm 2 (copie de film1) :" << std::endl;
    film2.display(std::cout);
    std::cout << "\nLes chapitres de Film 2 n'ont pas changé ! Nickel !" << std::endl;
    
    return 0;
}


