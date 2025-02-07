#include <gtest/gtest.h>
#include "Bottin.h"
#include <fstream>
#include <iostream>

using namespace TP3;

// Test pour l'ouverture et la lecture du fichier
TEST(BottinTests, TestLectureFichier) {
    std::ifstream fichier("Bottin.txt");
    ASSERT_TRUE(fichier.is_open()) << "Impossible d'ouvrir le fichier Bottin.txt";

    Bottin bottin(fichier);
    fichier.close();

    EXPECT_GT(bottin.nombreEntrees(), 0) << "Le fichier Bottin.txt semble vide ou mal formaté";
}

// Test pour l'ajout d'une entrée
TEST(BottinTests, TestAjoutEntree) {
    std::ifstream fichier("Bottin.txt");
    ASSERT_TRUE(fichier.is_open()) << "Impossible d'ouvrir le fichier Bottin.txt";

    Bottin bottin(fichier);
    fichier.close();

    bottin.ajouter("fares", "majdoub", "(555) 123-4567", "(555) 765-4321", "fares.majdoub@gmail.com");


    const Bottin::Entree& entree = bottin.trouverAvecNomPrenom("fares", "majdoub");
    EXPECT_EQ(entree.m_nom, "fares");
    EXPECT_EQ(entree.m_prenom, "majdoub");
    EXPECT_EQ(entree.m_telephoneFixe, "(555) 123-4567");
}

// Test pour la recherche par nom et prénom
TEST(BottinTests, TestRechercheParNomPrenom) {
    std::ifstream fichier("Bottin.txt");
    ASSERT_TRUE(fichier.is_open()) << "Impossible d'ouvrir le fichier Bottin.txt";

    Bottin bottin(fichier);
    fichier.close();

    bottin.ajouter("fares", "majdoub", "(555) 123-4567", "(555) 765-4321", "fares.majdoub@gmail.com");

    const Bottin::Entree& entree = bottin.trouverAvecNomPrenom("fares", "majdoub");
    EXPECT_EQ(entree.m_nom, "fares");
    EXPECT_EQ(entree.m_prenom, "majdoub");
    EXPECT_EQ(entree.m_telephoneFixe, "(555) 123-4567");
}

// Test pour la recherche par numéro de téléphone
TEST(BottinTests, TestRechercheParTelephone) {
    std::ifstream fichier("Bottin.txt");
    ASSERT_TRUE(fichier.is_open()) << "Impossible d'ouvrir le fichier Bottin.txt";

    Bottin bottin(fichier);
    fichier.close();

    bottin.ajouter("fares", "majdoub", "(555) 123-4567", "(555) 765-4321", "fares.majdoub@gmail.com");

    const Bottin::Entree& entree = bottin.trouverAvecTelephone("(555) 123-4567");
    EXPECT_EQ(entree.m_nom, "fares");
    EXPECT_EQ(entree.m_prenom, "majdoub");
    EXPECT_EQ(entree.m_telephoneFixe, "(555) 123-4567");
}

TEST(BottinTests, TestAffichageBottin) {
    std::ifstream fichier("Bottin.txt");
    ASSERT_TRUE(fichier.is_open()) << "Impossible d'ouvrir le fichier Bottin.txt";

    Bottin bottin(fichier);
    fichier.close();

    std::cout << "Contenu du bottin :\n";
    bottin.afficherBottin(std::cout);
}

// Test pour les statistiques des collisions
TEST(BottinTests, TestStatistiquesCollisions) {
    std::ifstream fichier("Bottin.txt");
    ASSERT_TRUE(fichier.is_open()) << "Impossible d'ouvrir le fichier Bottin.txt";

    Bottin bottin(fichier);
    fichier.close();

    double ratioNomPrenom, ratioTelephone;
    int collisionsNomPrenom, collisionsTelephone;
    int maxCollisionsNomPrenom, maxCollisionsTelephone;

    bottin.statistiquesNomPrenom(ratioNomPrenom, collisionsNomPrenom, maxCollisionsNomPrenom);
    bottin.statistiquesTelephone(ratioTelephone, collisionsTelephone, maxCollisionsTelephone);

    EXPECT_GE(collisionsNomPrenom, 0);
    EXPECT_GE(collisionsTelephone, 0);

    std::cout << "\nStatistiques des collisions :\n";
    std::cout << "Nom/Prénom - Ratio : " << ratioNomPrenom
              << ", Collisions : " << collisionsNomPrenom
              << ", Max par insertion : " << maxCollisionsNomPrenom << "\n";
    std::cout << "Téléphone - Ratio : " << ratioTelephone
              << ", Collisions : " << collisionsTelephone
              << ", Max par insertion : " << maxCollisionsTelephone << "\n";
}