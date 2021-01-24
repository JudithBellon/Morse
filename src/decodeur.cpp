#include <fstream>  
#include <iostream>
#include <vector>
#include <string>

    /* Les paramètres, à éventuellement modifier s'ils ne correspondent pas au fichier à décoder */

double hz = 44000;    // samples par seconde
double tau = 0.25;   // durée d'un point
int N = hz * tau; 


    /* Représentation sous forme de tableau de l'arbre binaire du morse */
        // on va à gauche pour un point et à droite pour un tiret.

std::vector<char> tab_alphabet =                                                                                                                                  {' ', 
                                                                                'e',                                                                                                                                                          't',
                                        'i',                                                                                'a',                                                                      'n',                                                                             'm', 
                  's',                                      'u',                                    'r',                                   'w',                                    'd',                                    'k',                                 'g',                                      'o',
         'h',                'v',                'f',                '*',                'l',                '*',                'p',                'j',                'b',                'x',                'c',                'y',                'z',               'q',                 '*',               '*',
    '5',      '4',      '3',      '*',      '*',      '*',      '*',      '2',      '*',      '*',      '*',      '*',      '*',     '*',       '*',      '1',      '6',     '*',       '*',      '*',      '*',      '*',     '*',       '*',      '7',     '*',      '*',      '*',       '8',      '*',      '9',     '0',
 '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '?', '*', '*', '*', '*', '*', '*', '*', '*', '.', '*', '*', '*', '*', '*', '*', '*', '*', '\'', '*', '*', '-', '*', '*', '*', '*', '*', '*', '*', '*', ';', '!', '*', '*', '*', '*', '*', '*', '*', ',', '*', '*', '*', '*', ':', '*', '*', '*', '*', '*', '*', '*'};



    /* Représentation sous forme de tableau de l'arbre binaire dans lequel on va à gauche quand il y a "du bruit" et à droite lors d'un silence */
        // p = point, t = tiret, f = fin de lettre

std::vector<char> elem =            {'*',
                    '*',                                   '*',
        '*',               'p',                '*',                'f', 
    '*',     '*',     '*',      '*',      '*',      '*',       '*',     '*', 
'*', 't', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'};        




void decoder(std::string message){


    std::ifstream audio;
    audio.open(message, std::ios::binary);
    char entete[44];    
    audio.read(entete, 44);   

    int8_t lu;
    int ia = -1;        // indice pour tab_alphabet

    while(!audio.eof()){

        int ie = 0;     // indice pour elem
        while(elem[ie] == '*'){
            int s = 0; 
            for(int i=0; i<N; i++){
                audio.read(reinterpret_cast<char*>(&lu), 1);
                if(lu > 1){
                    s += 1;
                }
            }
            if(s > N/4){
                ie = ie*2 + 1;   // "bruit", on va à gauche
            }
            else{
                ie = ie*2 + 2;  // silence, on va à droite
            } 
        }

        if (ia == -1){   
            if (elem[ie] == 'f'){
                ia = 0;
            }
            if (elem[ie] == 'p'){
                ia = 1;
            }
            if (elem[ie] == 't'){
                ia = 2;
            }
        }
        else if (ia >= tab_alphabet.size()){
            std::cout << "*";     // erreur dans le morse (ou élément non pris en compte), on met * ce qui ne devrait pas empécher la compréhension du reste du texte)
        }
        else {
            if (elem[ie] == 'p'){
                ia = ia*2 + 1;    // on va à gauche
            }
            if (elem[ie] == 't'){
                ia = ia*2 + 2;    // on va à droite
            }
            if (elem[ie] == 'f'){
                std::cout << tab_alphabet[ia];    // On affiche le caractère obtenu
                ia = -1;                          // puis on réinitialise ia
            }        
        }

    }

    std::cout << std::endl;
    audio.close();

}