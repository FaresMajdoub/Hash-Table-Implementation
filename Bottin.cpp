#include "Bottin.h"
#include <sstream>
#include <stdexcept>
#include <regex>

namespace TP3 {
    /**
     * \brief Constructeur de la classe Bottin.
     * \details Initialise les structures internes et remplit le bottin à partir d'un fichier d'entrée.
     * \param[in] p_fichierEntree Fichier contenant les données à insérer dans le bottin.
     * \param[in] p_table_size Taille initiale des tables de hachage.
     * \pre Le fichier doit être ouvert et non vide.
     * \post Les données valides du fichier sont insérées dans le bottin.
     */
Bottin::Bottin(std::ifstream& p_fichierEntree, size_t p_table_size)
    : m_tableauDesEntrees(),
      m_tableParNomPrenom(p_table_size),
      m_tableParTelephone(p_table_size) {
    PRECONDITION(p_fichierEntree.is_open());
    std::string line;

    // Ignorer la première ligne (en-tête)
    if (std::getline(p_fichierEntree, line)) {
        std::cout << "En-tête ignoré : " << line << std::endl;
    }else {
        PRECONDITION(false && "Le fichier est vide ou mal formaté");
    }

    // Lire chaque ligne du fichier
    while (std::getline(p_fichierEntree, line)) {
        std::stringstream ss(line);
        std::string nom_prenom, p_nom, p_prenom, p_telephoneFixe, p_telephoneCellulaire, p_courriel;

        std::getline(ss, nom_prenom, '\t');
        std::getline(ss, p_telephoneFixe, '\t');
        std::getline(ss, p_telephoneCellulaire, '\t');
        std::getline(ss, p_courriel, '\t');


        size_t pos = nom_prenom.find(',');
        if (pos != std::string::npos) {
            p_nom = nom_prenom.substr(0, pos);
            p_prenom = nom_prenom.substr(pos + 2);
        } else {
            p_nom = nom_prenom;
            p_prenom = "";
        }

        ajouter(p_nom, p_prenom, p_telephoneFixe, p_telephoneCellulaire, p_courriel);
    }
}
    /**
     * \brief Ajoute une entrée au bottin.
     * \param[in] p_nom Nom de la personne.
     * \param[in] p_prenom Prénom de la personne.
     * \param[in] p_telephoneFixe Numéro de téléphone fixe.
     * \param[in] p_cellulaire Numéro de téléphone cellulaire.
     * \param[in] p_courriel Adresse courriel.
     * \pre Aucun des paramètres ne doit être vide.
     * \pre Les numéros de téléphone doivent être dans un format valide (e.g., (555) 123-4567).
     * \pre La combinaison nom/prénom et le téléphone fixe doivent être uniques dans le bottin.
     * \post L'entrée est ajoutée aux structures internes et est accessible par recherche.
     */
void Bottin::ajouter(const std::string& p_nom, const std::string& p_prenom,
                     const std::string& p_telephoneFixe, const std::string& p_cellulaire,
                     const std::string& p_courriel) {

    PRECONDITION(!p_nom.empty() && "Le nom ne peut pas être vide");
    PRECONDITION(!p_prenom.empty() && "Le prénom ne peut pas être vide");
    PRECONDITION(!p_telephoneFixe.empty() && "Le téléphone fixe ne peut pas être vide");
    PRECONDITION(!p_cellulaire.empty() && "Le téléphone cellulaire ne peut pas être vide");
    PRECONDITION(!p_courriel.empty() && "L'adresse courriel ne peut pas être vide");
    std::regex telRegex(R"(\(\d{3}\) \d{3}-\d{4})");
    PRECONDITION(std::regex_match(p_telephoneFixe, telRegex) && "Le numéro de téléphone fixe n'est pas valide");
    PRECONDITION(std::regex_match(p_cellulaire, telRegex) && "Le numéro de téléphone cellulaire n'est pas valide");



    std::string cleNomPrenom = p_nom + " " + p_prenom;
    PRECONDITION(!m_tableParNomPrenom.contient(cleNomPrenom));
    PRECONDITION(!m_tableParTelephone.contient(p_telephoneFixe)); //Supposant que chaque numero est unique

    Entree nouvelleEntree(p_nom, p_prenom, p_telephoneFixe, p_cellulaire, p_courriel);
    m_tableauDesEntrees.push_back(nouvelleEntree);




    m_tableParNomPrenom.inserer(cleNomPrenom, m_tableauDesEntrees.size() - 1);
    m_tableParTelephone.inserer(p_telephoneFixe, m_tableauDesEntrees.size() - 1);


    POSTCONDITION(m_tableParNomPrenom.contient(cleNomPrenom) && "La clé NomPrenom n'a pas été insérée correctement");
    POSTCONDITION(m_tableParTelephone.contient(p_telephoneFixe) && "La clé Téléphone fixe n'a pas été insérée correctement");


    POSTCONDITION(m_tableauDesEntrees.back().m_nom == p_nom && "Le nom n'a pas été inséré correctement dans le tableau");
    POSTCONDITION(m_tableauDesEntrees.back().m_prenom == p_prenom && "Le prénom n'a pas été inséré correctement dans le tableau");
    POSTCONDITION(m_tableauDesEntrees.back().m_telephoneFixe == p_telephoneFixe && "Le téléphone fixe n'a pas été inséré correctement dans le tableau");
    POSTCONDITION(m_tableauDesEntrees.back().m_cellulaire == p_cellulaire && "Le téléphone cellulaire n'a pas été inséré correctement dans le tableau");
    POSTCONDITION(m_tableauDesEntrees.back().m_courriel == p_courriel && "L'adresse courriel n'a pas été insérée correctement dans le tableau");
}
    /**
     * \brief Affiche toutes les entrées du bottin.
     * \param[out] p_out Flux de sortie où afficher les entrées.
     * \post Aucune modification des données internes.
     */
void Bottin::afficherBottin(std::ostream& p_out) const {
    for (const auto& entree : m_tableauDesEntrees) {
        p_out << entree << std::endl;
    }
}
    /**
     * \brief Recherche une entrée par nom et prénom.
     * \param[in] p_nom Nom de la personne à rechercher.
     * \param[in] p_prenom Prénom de la personne à rechercher.
     * \return Une référence constante vers l'entrée correspondante.
     * \pre Les paramètres nom et prénom ne doivent pas être vides.
     * \throw std::runtime_error si l'entrée n'est pas trouvée.
     * \post Aucune modification des données internes.
     */
const Bottin::Entree& Bottin::trouverAvecNomPrenom(const std::string& p_nom, const std::string& p_prenom) const {

    PRECONDITION(!p_nom.empty() && "Le nom ne peut pas être vide");
    PRECONDITION(!p_prenom.empty() && "Le prénom ne peut pas être vide");

    std::string cleNomPrenom = p_nom + " " + p_prenom;

    if (!m_tableParNomPrenom.contient(cleNomPrenom)) {
        throw std::runtime_error("Erreur : Le nom et prénom '" + cleNomPrenom + "' n'existent pas dans le bottin.");
    }

    size_t index = m_tableParNomPrenom.element(cleNomPrenom);
    POSTCONDITION(index < m_tableauDesEntrees.size() && "L'index récupéré est invalide.");
    return m_tableauDesEntrees.at(index);

}/**
 * \brief Recherche une entrée par numéro de téléphone fixe.
 * \param[in] p_telephoneFixe Numéro de téléphone fixe à rechercher.
 * \return Une référence constante vers l'entrée correspondante.
 * \pre Le numéro de téléphone fixe ne doit pas être vide.
 * \throw std::runtime_error si l'entrée n'est pas trouvée.
 * \post Aucune modification des données internes.
 */
    const Bottin::Entree& Bottin::trouverAvecTelephone(const std::string& p_telephoneFixe) const {

    PRECONDITION(!p_telephoneFixe.empty() && "Le numéro de téléphone fixe ne peut pas être vide.");

    if (!m_tableParTelephone.contient(p_telephoneFixe)) {
        throw std::runtime_error("Erreur : Le numéro de téléphone fixe '" + p_telephoneFixe + "' n'existe pas dans le bottin.");
    }

    size_t index = m_tableParTelephone.element(p_telephoneFixe);

    POSTCONDITION(index < m_tableauDesEntrees.size() && "L'index récupéré est invalide.");
    return m_tableauDesEntrees.at(index);
}
    /**
 * \brief Retourne le nombre d'entrées dans le bottin.
 * \return Le nombre total d'entrées.
 * \post Aucune modification des données internes.
 */
int Bottin::nombreEntrees() const {
    return m_tableauDesEntrees.size();
}

/**
 * \brief Calcule le ratio des collisions par insertion dans la table Nom/Prénom.
 * \return Le ratio des collisions.
 * \post Aucune modification des données internes.
 */
double Bottin::ratioDeCollisionsNomPrenom() const {
    double ratio = 0.0;
    int nbCollisions, maxCollisions;
    m_tableParNomPrenom.statistiques(ratio, nbCollisions, maxCollisions);
    return ratio;
}
 /**
     * \brief Calcule le ratio des collisions par insertion dans la table Téléphone.
     * \return Le ratio des collisions.
     * \post Aucune modification des données internes.
     */
double Bottin::ratioDeCollisionTelephone() const {
    double ratio = 0.0;
    int nbCollisions, maxCollisions;
    m_tableParTelephone.statistiques(ratio, nbCollisions, maxCollisions);
    return ratio;
}
    /**
     * \brief Retourne le nombre maximal de collisions pour une insertion dans la table Nom/Prénom.
     * \return Le nombre maximal de collisions.
     * \post Aucune modification des données internes.
     */
int Bottin::maximumNbCollisionNomPrenom() const {
    double ratio;
    int nbCollisions, maxCollisions;
    m_tableParNomPrenom.statistiques(ratio, nbCollisions, maxCollisions);
    return maxCollisions;
}
    /**
     * \brief Retourne le nombre maximal de collisions pour une insertion dans la table Téléphone.
     * \return Le nombre maximal de collisions.
     * \post Aucune modification des données internes.
     */
int Bottin::maximumNbCollisionTelephone() const {
    double ratio;
    int nbCollisions, maxCollisions;
    m_tableParTelephone.statistiques(ratio, nbCollisions, maxCollisions);
    return maxCollisions;
}
    /**
 * \brief Calcule les statistiques des collisions dans la table Nom/Prénom.
 * \param[out] p_ratio Ratio des collisions par insertion.
 * \param[out] p_nbCollisions Nombre total de collisions.
 * \param[out] p_maximumCollisionUneInsertion Nombre maximal de collisions pour une seule insertion.
 * \post Aucune modification des données internes.
 */
    void Bottin::statistiquesNomPrenom(double& p_ratio, int& p_nbCollisions, int& p_maximumCollisionUneInsertion) const {
    m_tableParNomPrenom.statistiques(p_ratio, p_nbCollisions, p_maximumCollisionUneInsertion);
}
    /**
     * \brief Calcule les statistiques des collisions dans la table Téléphone.
     * \param[out] p_ratio Ratio des collisions par insertion.
     * \param[out] p_nbCollisions Nombre total de collisions.
     * \param[out] p_maximumCollisionUneInsertion Nombre maximal de collisions pour une seule insertion.
     * \post Aucune modification des données internes.
     */
    void Bottin::statistiquesTelephone(double& p_ratio, int& p_nbCollisions, int& p_maximumCollisionUneInsertion) const {
    m_tableParTelephone.statistiques(p_ratio, p_nbCollisions, p_maximumCollisionUneInsertion);
}
} // namespace TP3