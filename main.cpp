#include "password.hpp"
#include "user.hpp"
#include <cassert>
#include <iostream>

int main() {
    // Création d'un mot de passe et d'un utilisateur avec ID 100
    Password password("secure123", false);
    User user(100, password);
    // Le commentaire est inutile et ajoute de la maintenance : le jour où
    // vous voulez changer l'id il faudra penser à changer le commentaire.

    // Vérifie que le mot de passe est encrypté
    assert(password.isEncrypted() && "Le mot de passe n'est pas correctement encrypté.");

    // Sauvegarde de l'utilisateur dans le fichier
    user.save();

    // Récupération de l'utilisateur et vérification de la connexion
    User& retrieved_user = User::fetch(100);
    assert(retrieved_user.authenticate("secure123") && "Connexion échouée.");


    User test(9999999, password);
    test.save();

    std::cout << "id before : " << retrieved_user.id() << std::endl;
    User& toto = User::fetch(9999999);
    std::cout << "id after : " << retrieved_user.id() << std::endl;

    std::cout << "Tous les tests ont réussi !" << std::endl;
    return 0;
}
// https://youtu.be/Bf7vDBBOBUA?si=1YFmCe_XlkSWJXAk

// Il y avait aussi normalement un partie d'exercice à faire en C avec sort et swap
// Autrement c'est bon : utilisation des références plutôt que des pointeurs quand ce n'est pas necessaire
// On a du coup vu avec la variable static qu'il est assez facile de faire des erreurs, des fois renvoyer
// un pointeur est ce dont on a besoin...
// Si vous continuez à faire du C++ regardez la gestion de la mémoire avec unique_ptr, shared_ptr
// et la fonction move qui permet de ne pas copier une variable quand on l'initialise
