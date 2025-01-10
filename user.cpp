#include "user.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

// Constructeur
User::User(int id, const Password& password)
    : _id(id), _password(password), _is_logged_in(false) {}

// Sauvegarde l'utilisateur dans un fichier
void User::save() const {
    std::ofstream file("users.txt", std::ios::app);
    if (!file) {
        throw std::runtime_error("Erreur : impossible d'ouvrir le fichier pour la sauvegarde !");
    }
    file << _id << " " << _password.getEncrypted() << std::endl;
}

// Vérifie le mot de passe pour se connecter
bool User::authenticate(const std::string& raw_password) {
    if (_password.matches(raw_password)) {
        _is_logged_in = true;
        return true;
    }
    return false;
}

// Récupère un utilisateur depuis un fichier
User& User::fetch(int id) {
    static User dummy(0, Password("", true)); // Utilisateur par défaut
    std::ifstream file("users.txt");
    if (!file) {
        throw std::runtime_error("Erreur : impossible d'ouvrir le fichier !");
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int file_id;
        std::string encrypted_password;
        if (iss >> file_id >> encrypted_password && file_id == id) {
            dummy = User(file_id, Password(encrypted_password, true));
            break;
        }
    }

    return dummy;
}
