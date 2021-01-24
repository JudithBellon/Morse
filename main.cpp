#include <iostream>
#include <string>
#include "codeur.h"
#include "decodeur.h"


int main(){

    std::string mode;      // mode = 1 pour français -> morse, mode = 2 pour morse -> français
    std::string message;   // contiendra l'argument de la fonction appelée (un nom de fichier ou une chaine de caractères à coder)

    std::cout << "Voulez-vous coder (1) ou décoder (2) un message ?" << std::endl; 
    std::cin >> mode;

    if(mode[0] == '1'){
        std::cout << "Voulez-vous entrer votre message directement (1) ou utiliser un fichier (2) ?" << std::endl;
        std::string choix;
        std::cin >> choix;
        if(choix[0] == '1'){
            std::cout << "Veuillez écrire votre message" << std::endl;
            std::cin >> std::ws;
            std::getline(std::cin, message);
            coder1(message);
        }
        else if(choix[0] == '2'){
            std::cout << "Quel est ce fichier ?" << std::endl;
            std::cin >> message;
            coder2(message);
        }
    }

    else if(mode[0] == '2'){
        std::cout << "Quel fichier voulez-vous décoder ?" << std::endl;
        std::cin >> message;
        decoder(message);
    }


}