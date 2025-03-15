#ifndef PASSWORD_HPP
#define PASSWORD_HPP

#include <string>

class Password {
private:
    std::string _original;  // Version brute du mot de passe
    // Dans l'idée on ne garde pas du tout le password original en mémoire
    std::string _encrypted; // Version encryptée

    void encrypt();

public:
    // Constructeur
    Password(const std::string& input, bool encrypted = false);

    // Vérifie si le mot de passe est encrypté
    bool isEncrypted() const;

    // Vérifie si le mot de passe correspond
    bool matches(const std::string& raw_input) const;

    // Retourne la version encryptée
    std::string getEncrypted() const;
};

#endif
