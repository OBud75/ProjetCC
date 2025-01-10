#include "password.hpp"
#include "user.hpp"
#include <cassert>
#include <iostream>

int main() {
    // Création d'un mot de passe et d'un utilisateur avec ID 100
    Password password("secure123", false);
    User user(100, password);

    // Vérifie que le mot de passe est encrypté
    assert(password.isEncrypted() && "Le mot de passe n'est pas correctement encrypté.");

    // Sauvegarde de l'utilisateur dans le fichier
    user.save();

    // Récupération de l'utilisateur et vérification de la connexion
    User& retrieved_user = User::fetch(100);
    assert(retrieved_user.authenticate("secure123") && "Connexion échouée.");

    std::cout << "Tous les tests ont réussi !" << std::endl;
    return 0;
}
