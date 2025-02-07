# Phone Directory - Hash Table Implementation

## 📌 Description
Ce projet implémente un **bottin téléphonique** en utilisant des **tables de hachage** avec **adressage ouvert**.  
L'objectif est d'assurer une recherche rapide des contacts par **numéro de téléphone** et **nom/prénom**.  
Le projet inclut des tests unitaires avec **Google Test (gtest)** pour valider l'intégrité des données et la gestion des collisions.

## 🚀 Fonctionnalités
- **Stockage efficace des contacts** (Nom, Prénom, Téléphone, Cellulaire, Email).
- **Recherche rapide** avec deux index :  
  - **Table de hachage des numéros de téléphone**  
  - **Table de hachage des noms/prénoms**  
- **Gestion des collisions** via **adressage ouvert**.
- **Calcul du ratio de collisions** et du **nombre maximal de collisions**.
- **Lecture et sauvegarde des contacts** depuis un fichier.
- **Tests unitaires avec Google Test**.

## 🏗️ Structure du projet
```
📂 **src/** - Code source  
  ├── `Bottin.h` / `Bottin.cpp` (Gestion du bottin téléphonique)  
  ├── `TableHachage.h` / `TableHachage.hpp` (Implémentation des tables de hachage)  
  ├── `FoncteurHachage.hpp` (Foncteur de hachage, à ne pas modifier)  
  ├── `ContratException.h` / `ContratException.cpp` (Gestion des exceptions)  
  ├── `main.cpp` (Programme principal)  
  ├── `tests/` (Tests unitaires avec Google Test)  
  ├── `CMakeLists.txt` (Compilation)  
  └── `docs/` (Documentation Doxygen)  
```

## 📊 Exemples de Simulation
### ⚡ Recherche par Nom/Prénom
```plaintext
Entrée trouvée :  
Nom : Dupont  
Prénom : Jean  
Téléphone : (418) 555-1234  
Cellulaire : (418) 555-5678  
Email : jean.dupont@example.com  
```
### ⚡ Recherche par Numéro de Téléphone
```plaintext
Contact trouvé pour (418) 555-1234 : Jean Dupont  
```
### ⚡ Statistiques sur les Collisions
```plaintext
Ratio de collisions (Nom/Prénom) : 3.5%  
Ratio de collisions (Téléphone) : 2.1%  
```

## ✍️ Auteurs
**Fares Majdoub** - Université Laval, GLO-2100/IFT-2008  

## 📜 Licence
Sous licence **MIT**.

