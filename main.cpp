#include <iostream>
#include <string>
#include "codeur.h"
#include "decodeur.h"


int main(){

    std::string mode;
    std::string message;

    std::cout << "Voulez-vous coder (1) ou décoder (2) un message ?" << std::endl; 
    std::cin >> mode;
    if(mode[0] == '1'){
        std::cout << "Voulez-vous entrer votre message directement (1) ou utiliser un fichier (2) ?" << std::endl;
        std::string texte;
        std::cin >> texte;;
        if(texte[0] == '1'){
            std::cout << "Veuillez écrire votre message" << std::endl;
            std::cin >> std::ws;
            std::getline(std::cin, message);
            coder1(message);
        }
        else if(texte[0] == '2'){
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