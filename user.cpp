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

int User::id() {
    return _id;
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
    // Le fait d'avoir utilisé une variable static induit en erreur ici
    // (bug pas si simple à trouver si en production pour être honnête c'est le genre de chose qui rend C/C++ difficile)
    // Le fait de déclarer static fait que l'espace mémoire est alloué une seule fois
    // autrement dit, dummy est toujours le même objet, même si la fonction get est rappelée
    // En appellant get(100) puis get(1), cela va retourner le même espace mémoire,
    // d'abord avec les données de l'user id 100 puis avec les données de l'user id 1
    // Le problème étant qu'au second appel, cela va donc modifier l'objet User qui avait l'id
    // 100 retourné la premiere fois, et donc le retourner avec l'id 1
    // J'ai mis un exemple dans main.cpp pour montrer le problème

    // Pour résoudre le problème, on enlève static User + soit:
    // - Retourner une copie de l'utilisateur : User User::fetch(int id)
    // - Retourner un pointeur vers l'utilisateur : User* User::fetch(int id)

    // En python on pourrait avoir le même genre de bug avec des variables statiques / attributs de classes, surtout si la variable est mutable
    return dummy;
}
