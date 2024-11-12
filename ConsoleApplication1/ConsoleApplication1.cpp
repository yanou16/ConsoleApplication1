#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Chiffrement {
private:
    string inputFile;
    string outputFile;
    int mode;

    string cesarCipher(const string& input, int key, bool encrypt) {
        string result = input;
        for (char& c : result) {
            if (isalpha(c)) {
                c = tolower(c);
                c = ((c - 'a') + (encrypt ? key : -key)) % 26 + 'a';
            }
        }
        return result;
    }

    string xorCipher(const string& input, char key) {
        string result = input;
        for (char& c : result) {
            c ^= key;
        }
        return result;
    }

public:
    void setInputFile(const string& file) {
        inputFile = file;
    }

    void setOutputFile(const string& file) {
        outputFile = file;
    }

    void setMode(int m) {
        mode = m;
    }

    void process() {
        string content;
        ifstream inputStream(inputFile);
        if (inputStream.is_open()) {
            getline(inputStream, content, '\0');
            inputStream.close();

            string encryptedContent;
            switch (mode) {
            case 1:
                encryptedContent = cesarCipher(content, 2, true);
                break;
            case 2:
                encryptedContent = xorCipher(content, 'x');
                break;
            case 3:
                encryptedContent = xorCipher(cesarCipher(content, 2, true), 'x');
                break;
            default:
                cout << "Mode de chiffrement invalide." << endl;
                return;
            }

            ofstream outputStream(outputFile);
            if (outputStream.is_open()) {
                outputStream << encryptedContent;
                outputStream.close();
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
    Chiffrement chiffrement;
    int mode;

    cout << "Entrez le fichier source (crypt� ou non crypt�) : ";
    string inputFile;
    getline(cin, inputFile);
    chiffrement.setInputFile(inputFile);

    cout << "Choisissez votre mode de s�curit� :" << endl;
    cout << "1. Chiffrement de type C�sar" << endl;
    cout << "2. Chiffrement utilisant l'op�rateur XOR" << endl;
    cout << "3. Combinaison des deux modes de chiffrement" << endl;
    cout << "Votre choix : ";
    cin >> mode;
    chiffrement.setMode(mode);

    cout << "Entrez le fichier de destination : ";
    string outputFile;
    cin.ignore(); // Ignorer le \n laiss� par le pr�c�dent cin
    getline(cin, outputFile);
    chiffrement.setOutputFile(outputFile);

    chiffrement.process();

    return 0;
}