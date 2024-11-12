#include <iostream>  // Inclut la bibliothèque pour l'entrée et la sortie de données
#include <fstream>   // Inclut la bibliothèque pour lire et écrire dans les fichiers
#include <string>    // Inclut la bibliothèque pour manipuler les chaînes de caractères
using namespace std; // Permet d'utiliser directement les éléments du namespace `std`

// Déclaration de la classe `Chiffrement` qui contient les méthodes pour chiffrer le texte
class Chiffrement {
private:
    string inputFile;    // Nom du fichier d'entrée
    string outputFile;   // Nom du fichier de sortie
    int mode;            // Mode de chiffrement choisi par l'utilisateur

    // Méthode de chiffrement César (substitution) qui déplace chaque lettre d'un certain nombre de positions
    string cesarCipher(const string& input, int key, bool encrypt) {
        string result = input;  // Initialise le résultat en copiant le texte d'entrée
        for (char& c : result) { // Parcourt chaque caractère du texte
            if (isalpha(c)) {   // Vérifie si le caractère est une lettre
                c = tolower(c); // Convertit en minuscule pour simplifier
                // Applique le décalage en fonction de la clé et de l'opération (chiffrement ou déchiffrement)
                c = ((c - 'a') + (encrypt ? key : -key)) % 26 + 'a';
            }
        }
        return result; // Retourne le texte chiffré/déchiffré
    }

    // Méthode de chiffrement XOR qui applique une opération XOR à chaque caractère
    string xorCipher(const string& input, char key) {
        string result = input;  // Initialise le résultat avec le texte d'entrée
        for (char& c : result) { // Parcourt chaque caractère du texte
            c ^= key;           // Applique l'opération XOR avec la clé
        }
        return result; // Retourne le texte chiffré/déchiffré
    }

public:
    // Méthode pour définir le fichier d'entrée
    void setInputFile(const string& file) {
        inputFile = file;
    }

    // Méthode pour définir le fichier de sortie
    void setOutputFile(const string& file) {
        outputFile = file;
    }

    // Méthode pour définir le mode de chiffrement
    void setMode(int m) {
        mode = m;
    }

    // Méthode principale pour traiter le fichier (lecture, chiffrement et écriture)
    void process() {
        string content;  // Contient le texte du fichier d'entrée
        ifstream inputStream(inputFile); // Ouvre le fichier d'entrée
        if (inputStream.is_open()) { // Vérifie si le fichier est bien ouvert
            // Lit tout le contenu du fichier dans `content`
            getline(inputStream, content, '\0');
            inputStream.close(); // Ferme le fichier d'entrée

            string encryptedContent; // Variable pour stocker le texte chiffré
            switch (mode) { // Sélectionne l'algorithme de chiffrement en fonction du mode choisi
            case 1: // Mode César
                encryptedContent = cesarCipher(content, 2, true); // Chiffre avec une clé de 2
                break;
            case 2: // Mode XOR
                encryptedContent = xorCipher(content, 'x'); // Chiffre avec une clé de XOR 'x'
                break;
            case 3: // Mode combiné (César + XOR)
                // Applique César puis XOR
                encryptedContent = xorCipher(cesarCipher(content, 2, true), 'x');
                break;
            default: // Si le mode est invalide
                cout << "Mode de chiffrement invalide." << endl;
                return;
            }

            ofstream outputStream(outputFile); // Ouvre le fichier de sortie pour écrire le texte chiffré
            if (outputStream.is_open()) { // Vérifie si le fichier de sortie est bien ouvert
                outputStream << encryptedContent; // Écrit le contenu chiffré
                outputStream.close(); // Ferme le fichier de sortie
                cout << "Opération terminée avec succès." << endl;
            }
            else {
                cout << "Impossible d'ouvrir le fichier de sortie." << endl;
            }
        }
        else {
            cout << "Impossible d'ouvrir le fichier d'entrée." << endl;
        }
    }
};

int main() {
    Chiffrement chiffrement; // Crée un objet de la classe `Chiffrement`
    int mode;                // Variable pour stocker le mode choisi

    // Demande à l'utilisateur de saisir le fichier source
    cout << "Entrez le fichier source (crypté ou non crypté) : ";
    string inputFile;
    getline(cin, inputFile);
    chiffrement.setInputFile(inputFile); // Définit le fichier d'entrée pour l'objet `chiffrement`

    // Affiche les options de chiffrement et demande à l'utilisateur de choisir
    cout << "Choisissez votre mode de sécurité :" << endl;
    cout << "1. Chiffrement de type César" << endl;
    cout << "2. Chiffrement utilisant l'opérateur XOR" << endl;
    cout << "3. Combinaison des deux modes de chiffrement" << endl;
    cout << "Votre choix : ";
    cin >> mode;
    chiffrement.setMode(mode); // Définit le mode de chiffrement

    // Demande à l'utilisateur de saisir le fichier de destination
    cout << "Entrez le fichier de destination : ";
    string outputFile;
    cin.ignore(); // Ignore le caractère de nouvelle ligne laissé par `cin`
    getline(cin, outputFile);
    chiffrement.setOutputFile(outputFile); // Définit le fichier de sortie

    // Lance le processus de chiffrement ou déchiffrement
    chiffrement.process();

    return 0; // Fin du programme
}
