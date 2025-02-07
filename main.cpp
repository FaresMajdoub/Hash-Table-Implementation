#include <iostream>
#include <fstream>
#include "Bottin.h"

int main() {

    std::ifstream fichier("Bottin.txt");
    if (!fichier.is_open()) {
        std::cerr << "Erreur : impossible d'ouvrir le fichier." << std::endl;
        return 1;
    }

    TP3::Bottin bottin(fichier);
    fichier.close();

    std::cout << "Contenu du bottin : " << std::endl;
    bottin.afficherBottin(std::cout);
    std::cout << "\nNombre total d'entrées dans le bottin : " << bottin.nombreEntrees() << std::endl;

    double ratioNomPrenom;
    int nbCollisionsNomPrenom;
    int maxCollisionsNomPrenom;
    bottin.statistiquesNomPrenom(ratioNomPrenom, nbCollisionsNomPrenom, maxCollisionsNomPrenom);


    std::cout << "\nStatistiques des noms/prénoms :" << std::endl;
    std::cout << "Ratio de collisions : " << ratioNomPrenom << std::endl;
    std::cout << "Nombre de collisions : " << nbCollisionsNomPrenom << std::endl;
    std::cout << "Nombre maximal de collisions pour une insertion : " << maxCollisionsNomPrenom << std::endl;

    double ratioTelephone;
    int nbCollisionsTelephone;
    int maxCollisionsTelephone;
    bottin.statistiquesTelephone(ratioTelephone, nbCollisionsTelephone, maxCollisionsTelephone);

    std::cout << "\nStatistiques des téléphones :" << std::endl;
    std::cout << "Ratio de collisions : " << ratioTelephone << std::endl;
    std::cout << "Nombre de collisions : " << nbCollisionsTelephone << std::endl;
    std::cout << "Nombre maximal de collisions pour une insertion : " << maxCollisionsTelephone << std::endl;


    try {
        const auto& entree = bottin.trouverAvecNomPrenom("Adam", "Carl");
        std::cout << "\nEntrée trouvée pour 'adam carl' : " << entree << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "\nErreur lors de la recherche par nom/prénom : " << e.what() << std::endl;
    }


    try {
        const auto& entree = bottin.trouverAvecTelephone("(909) 787-4746");
        std::cout << "Entrée trouvée pour le téléphone '(909) 787-4746' : " << entree << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Erreur lors de la recherche par téléphone : " << e.what() << std::endl;
    }





    return 0;
}