#include <iostream>  // Inclut la biblioth�que pour l'entr�e et la sortie de donn�es
#include <fstream>   // Inclut la biblioth�que pour lire et �crire dans les fichiers
#include <string>    // Inclut la biblioth�que pour manipuler les cha�nes de caract�res
using namespace std; // Permet d'utiliser directement les �l�ments du namespace `std`

// D�claration de la classe `Chiffrement` qui contient les m�thodes pour chiffrer le texte
class Chiffrement {
private:
    string inputFile;    // Nom du fichier d'entr�e
    string outputFile;   // Nom du fichier de sortie
    int mode;            // Mode de chiffrement choisi par l'utilisateur

    // M�thode de chiffrement C�sar (substitution) qui d�place chaque lettre d'un certain nombre de positions
    string cesarCipher(const string& input, int key, bool encrypt) {
        string result = input;  // Initialise le r�sultat en copiant le texte d'entr�e
        for (char& c : result) { // Parcourt chaque caract�re du texte
            if (isalpha(c)) {   // V�rifie si le caract�re est une lettre
                c = tolower(c); // Convertit en minuscule pour simplifier
                // Applique le d�calage en fonction de la cl� et de l'op�ration (chiffrement ou d�chiffrement)
                c = ((c - 'a') + (encrypt ? key : -key)) % 26 + 'a';
            }
        }
        return result; // Retourne le texte chiffr�/d�chiffr�
    }

    // M�thode de chiffrement XOR qui applique une op�ration XOR � chaque caract�re
    string xorCipher(const string& input, char key) {
        string result = input;  // Initialise le r�sultat avec le texte d'entr�e
        for (char& c : result) { // Parcourt chaque caract�re du texte
            c ^= key;           // Applique l'op�ration XOR avec la cl�
        }
        return result; // Retourne le texte chiffr�/d�chiffr�
    }

public:
    // M�thode pour d�finir le fichier d'entr�e
    void setInputFile(const string& file) {
        inputFile = file;
    }

    // M�thode pour d�finir le fichier de sortie
    void setOutputFile(const string& file) {
        outputFile = file;
    }

    // M�thode pour d�finir le mode de chiffrement
    void setMode(int m) {
        mode = m;
    }

    // M�thode principale pour traiter le fichier (lecture, chiffrement et �criture)
    void process() {
        string content;  // Contient le texte du fichier d'entr�e
        ifstream inputStream(inputFile); // Ouvre le fichier d'entr�e
        if (inputStream.is_open()) { // V�rifie si le fichier est bien ouvert
            // Lit tout le contenu du fichier dans `content`
            getline(inputStream, content, '\0');
            inputStream.close(); // Ferme le fichier d'entr�e

            string encryptedContent; // Variable pour stocker le texte chiffr�
            switch (mode) { // S�lectionne l'algorithme de chiffrement en fonction du mode choisi
            case 1: // Mode C�sar
                encryptedContent = cesarCipher(content, 2, true); // Chiffre avec une cl� de 2
                break;
            case 2: // Mode XOR
                encryptedContent = xorCipher(content, 'x'); // Chiffre avec une cl� de XOR 'x'
                break;
            case 3: // Mode combin� (C�sar + XOR)
                // Applique C�sar puis XOR
                encryptedContent = xorCipher(cesarCipher(content, 2, true), 'x');
                break;
            default: // Si le mode est invalide
                cout << "Mode de chiffrement invalide." << endl;
                return;
            }

            ofstream outputStream(outputFile); // Ouvre le fichier de sortie pour �crire le texte chiffr�
            if (outputStream.is_open()) { // V�rifie si le fichier de sortie est bien ouvert
                outputStream << encryptedContent; // �crit le contenu chiffr�
                outputStream.close(); // Ferme le fichier de sortie
                cout << "Op�ration termin�e avec succ�s." << endl;
            }
            else {
                cout << "Impossible d'ouvrir le fichier de sortie." << endl;
            }
        }
        else {
            cout << "Impossible d'ouvrir le fichier d'entr�e." << endl;
        }
    }
};

int main() {
    Chiffrement chiffrement; // Cr�e un objet de la classe `Chiffrement`
    int mode;                // Variable pour stocker le mode choisi

    // Demande � l'utilisateur de saisir le fichier source
    cout << "Entrez le fichier source (crypt� ou non crypt�) : ";
    string inputFile;
    getline(cin, inputFile);
    chiffrement.setInputFile(inputFile); // D�finit le fichier d'entr�e pour l'objet `chiffrement`

    // Affiche les options de chiffrement et demande � l'utilisateur de choisir
    cout << "Choisissez votre mode de s�curit� :" << endl;
    cout << "1. Chiffrement de type C�sar" << endl;
    cout << "2. Chiffrement utilisant l'op�rateur XOR" << endl;
    cout << "3. Combinaison des deux modes de chiffrement" << endl;
    cout << "Votre choix : ";
    cin >> mode;
    chiffrement.setMode(mode); // D�finit le mode de chiffrement

    // Demande � l'utilisateur de saisir le fichier de destination
    cout << "Entrez le fichier de destination : ";
    string outputFile;
    cin.ignore(); // Ignore le caract�re de nouvelle ligne laiss� par `cin`
    getline(cin, outputFile);
    chiffrement.setOutputFile(outputFile); // D�finit le fichier de sortie

    // Lance le processus de chiffrement ou d�chiffrement
    chiffrement.process();

    return 0; // Fin du programme
}
