#ifndef USER_HPP
#define USER_HPP

#include "password.hpp"
#include <string>

class User {
private:
    int _id;                // ID de l'utilisateur
    Password _password;     // Mot de passe encrypté
    bool _is_logged_in;     // Indique si l'utilisateur est connecté

public:
    // Constructeur
    User(int id, const Password& password);

    // Sauvegarde l'utilisateur dans un fichier
    void save() const;

    // Authentification
    bool authenticate(const std::string& raw_password);

    // Récupère un utilisateur depuis le fichier
    static User& fetch(int id);
    int id();
};

#endif
