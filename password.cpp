#include "password.hpp"
#include <algorithm>
#include <stdexcept>

// Constructeur : initialise un mot de passe encrypté ou brut
Password::Password(const std::string& input, bool encrypted)
    : _original(input), _encrypted(encrypted ? input : "") {
    if (!encrypted) {
        encrypt();
    }
}

// Effectue une "encryption" simple en inversant les caractères
void Password::encrypt() {
    _encrypted = _original;
    std::reverse(_encrypted.begin(), _encrypted.end());
}

// Retourne l'état d'encryption
bool Password::isEncrypted() const {
    return !_encrypted.empty() && _encrypted != _original;
}

// Vérifie si le mot de passe correspond
bool Password::matches(const std::string& raw_input) const {
    Password temp(raw_input, false); // Crée un mot de passe encrypté temporaire
    return temp._encrypted == _encrypted;
}

// Retourne la version encryptée
std::string Password::getEncrypted() const {
    return _encrypted;
}
