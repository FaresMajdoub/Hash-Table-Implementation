/**
* \file Bottin.h
 * \brief Classe définissant un bottin téléphonique.
 * \author Thierry Eude
 *
 */
#ifndef BOTTIN_H
#define BOTTIN_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "TableHachage.h"
#include "FoncteurHachage.hpp"

namespace TP3 {
    /**
     * \class Bottin
     * \brief Classe représentant un bottin téléphonique.
     * \details Cette classe permet de gérer un bottin avec des entrées contenant nom, prénom, numéros de téléphone et courriel.
     * Elle prend en charge l'ajout, la recherche et l'affichage des entrées, ainsi que le calcul des statistiques sur les collisions
     * dans les tables de hachage.
     */
class Bottin {
public:
    /**
 * \class Entree
 * \brief Représente une entrée individuelle dans le bottin.
 * \details Chaque entrée contient un nom, un prénom, un numéro de téléphone fixe, un numéro de téléphone cellulaire, et un courriel.
 */
    class Entree {

    public:
        std::string m_nom;
        std::string m_prenom;
        std::string m_telephoneFixe;
        std::string m_cellulaire;
        std::string m_courriel;
        /**
* \brief Constructeur de la classe Entree.
* \param[in] p_nom Nom de la personne.
* \param[in] p_prenom Prénom de la personne.
* \param[in] p_telephoneFixe Numéro de téléphone fixe.
* \param[in] p_cellulaire Numéro de téléphone cellulaire.
* \param[in] p_courriel Adresse courriel.
*/

        Entree(const std::string& p_nom, const std::string& p_prenom,
               const std::string& p_telephoneFixe, const std::string& p_cellulaire,
               const std::string& p_courriel)
            : m_nom(p_nom), m_prenom(p_prenom),
              m_telephoneFixe(p_telephoneFixe), m_cellulaire(p_cellulaire),
              m_courriel(p_courriel) {}
        /**
         * \brief Surcharge de l'opérateur `<<` pour afficher une entrée.
         * \param[in] os Flux de sortie.
         * \param[in] e Entrée à afficher.
         * \return Le flux de sortie.
         */
        friend std::ostream& operator<<(std::ostream& os, const Entree& e) {
            os << e.m_nom << ", " << e.m_prenom << ", " << e.m_telephoneFixe
               << ", " << e.m_cellulaire << ", " << e.m_courriel;
            return os;
        }
    };
    /**
 * \brief Constructeur de la classe Bottin.
 * \param[in] p_fichierEntree Fichier contenant les données à insérer dans le bottin.
 * \param[in] p_table_size Taille initiale des tables de hachage (valeur par défaut : 100).
 * \pre Le fichier doit être ouvert et contenir des données valides.
 * \post Le bottin est initialisé avec les données du fichier.
 */

    Bottin(std::ifstream& p_fichierEntree, size_t p_table_size = 100);
    /**
     * \brief Ajoute une nouvelle entrée au bottin.
     * \param[in] p_nom Nom de la personne.
     * \param[in] p_prenom Prénom de la personne.
     * \param[in] p_telephoneFixe Numéro de téléphone fixe.
     * \param[in] p_cellulaire Numéro de téléphone cellulaire.
     * \param[in] p_courriel Adresse courriel.
     * \pre Aucun des paramètres ne doit être vide.
     * \pre Les numéros de téléphone doivent être valides et les clés doivent être uniques.
     * \post Une nouvelle entrée est ajoutée aux structures internes du bottin.
     */
    void ajouter(const std::string& p_nom, const std::string& p_prenom,
                 const std::string& p_telephoneFixe, const std::string& p_cellulaire,
                 const std::string& p_courriel);

    void afficherBottin(std::ostream& p_out) const;
    /**
 * \brief Recherche une entrée par nom et prénom.
 * \param[in] p_nom Nom de la personne.
 * \param[in] p_prenom Prénom de la personne.
 * \return Une référence constante vers l'entrée correspondante.
 * \pre Les paramètres `p_nom` et `p_prenom` ne doivent pas être vides.
 * \throw std::runtime_error si aucune entrée correspondante n'est trouvée.
 */

    const Entree& trouverAvecNomPrenom(const std::string& p_nom, const std::string& p_prenom) const;
    /**
 * \brief Recherche une entrée par numéro de téléphone fixe.
 * \param[in] p_telephoneFixe Numéro de téléphone fixe.
 * \return Une référence constante vers l'entrée correspondante.
 * \pre Le paramètre `p_telephoneFixe` ne doit pas être vide.
 * \throw std::runtime_error si aucune entrée correspondante n'est trouvée.
 */
    const Entree& trouverAvecTelephone(const std::string& p_telephoneFixe) const;
    /**
     * \brief Retourne le nombre total d'entrées dans le bottin.
     * \return Nombre d'entrées dans le bottin.
     */
    int nombreEntrees() const;
    /**
     * \brief Calcule le ratio de collisions pour les entrées Nom/Prénom.
     * \return Le ratio des collisions.
     */
    double ratioDeCollisionsNomPrenom() const;
    /**
 * \brief Calcule le ratio de collisions pour les entrées Téléphone.
 * \return Le ratio des collisions.
 */
    double ratioDeCollisionTelephone() const;
    /**
     * \brief Retourne le nombre maximal de collisions pour une insertion dans la table Nom/Prénom.
     * \return Le nombre maximal de collisions.
     */
    int maximumNbCollisionNomPrenom() const;
    /**
 * \brief Retourne le nombre maximal de collisions pour une insertion dans la table Téléphone.
 * \return Le nombre maximal de collisions.
 */
    int maximumNbCollisionTelephone() const;

    /**
  * \brief Calcule les statistiques des collisions pour la table Nom/Prénom.
  * \param[out] p_ratio Ratio des collisions par insertion.
  * \param[out] p_nbCollisions Nombre total de collisions.
  * \param[out] p_maximumCollisionUneInsertion Nombre maximal de collisions pour une seule insertion.
  */
    void statistiquesNomPrenom(double& p_ratio, int& p_nbCollisions, int& p_maximumCollisionUneInsertion) const;
    /**
 * \brief Calcule les statistiques des collisions pour la table Téléphone.
 * \param[out] p_ratio Ratio des collisions par insertion.
 * \param[out] p_nbCollisions Nombre total de collisions.
 * \param[out] p_maximumCollisionUneInsertion Nombre maximal de collisions pour une seule insertion.
 */
    void statistiquesTelephone(double& p_ratio, int& p_nbCollisions, int& p_maximumCollisionUneInsertion) const;

private:
    std::vector<Entree> m_tableauDesEntrees;

    labTableHachage::TableHachage<std::string, size_t, labTableHachage::HString1> m_tableParNomPrenom;
    labTableHachage::TableHachage<std::string, size_t, labTableHachage::HString1> m_tableParTelephone;
};

} // namespace TP3

#endif // BOTTIN_H