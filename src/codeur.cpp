#include <fstream>  
#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <string>

    /* Les paramètres */

std::ofstream audio;

    const double two_pi = 6.2831853;
    const double amplitude = 100;    // "volume"

    double hz_c  = 44000;     // fréquence d'échantillonnage
    double freqt = 330;       
    double freqp = 392;     // on fait les points plus aigus que les tirets "pour faire joli"
    double tau_c = 0.25;    // durée d'un point

    int N_c = hz_c * tau_c;   // nombre de samples pour un point



    /* Pour l'écriture du fichier en binaire */

namespace little_endian_io
{
    template <typename Word>
    std::ostream& write_word( std::ostream& outs, Word value, unsigned size = sizeof(Word) )
    {
        for (; size; --size, value >>= 8)
            outs.put( static_cast <char> (value & 0xFF) );
        return outs;
    }
}
using namespace little_endian_io;


void ecrit(std::vector<int> liste){
    for(unsigned int i=0; i<liste.size(); i++){
        write_word(audio, (int) liste[i], 1);
    }
}



std::map<char, std::vector<std::vector<int>>> alphabet;

std::vector<int> point(2*N_c, 0);
std::vector<int> tiret(4*N_c, 0);
std::vector<int> silence(2*N_c, 0);


void Alphabet(){

    for (int n=0; n<N_c; n++) {
        double value = sin((two_pi*n*freqp)/hz_c);
        point[n] = amplitude * value;
    }

    for (int n=0; n<3*N_c; n++) {
        double value = sin((two_pi*n*freqt)/hz_c);
        tiret[n] = amplitude * value;
    }
        

    alphabet['a'] = {point, tiret, silence} ;
    alphabet['b'] = {tiret, point, point, point, silence};
    alphabet['c'] = {tiret, point, tiret, point, silence};
    alphabet['d'] = {tiret, point, point, silence};
    alphabet['e'] = {point, silence};
    alphabet['f'] = {point, point, tiret, point, silence};
    alphabet['g'] = {tiret, tiret, point, silence};
    alphabet['h'] = {point, point, point, point, silence};
    alphabet['i'] = {point, point, silence};
    alphabet['j'] = {point, tiret, tiret, tiret, silence};
    alphabet['k'] = {tiret, point, tiret, silence};
    alphabet['l'] = {point, tiret, point, point, silence};
    alphabet['m'] = {tiret, tiret, silence};
    alphabet['n'] = {tiret, point, silence};
    alphabet['o'] = {tiret, tiret, tiret, silence};
    alphabet['p'] = {point, tiret, tiret, point, silence};
    alphabet['q'] = {tiret, tiret, point, tiret, silence};
    alphabet['r'] = {point, tiret, point, silence};
    alphabet['s'] = {point, point, point, silence};
    alphabet['t'] = {tiret, silence};
    alphabet['u'] = {point, point, tiret, silence};
    alphabet['v'] = {point, point, point, tiret, silence};
    alphabet['w'] = {point, tiret, tiret, silence};
    alphabet['x'] = {tiret, point, point, tiret, silence};
    alphabet['y'] = {tiret, point, tiret, tiret, silence};
    alphabet['z'] = {tiret, tiret, point, point, silence};

    alphabet['A'] = {point, tiret, silence} ;
    alphabet['B'] = {tiret, point, point, point, silence};
    alphabet['C'] = {tiret, point, tiret, point, silence};
    alphabet['D'] = {tiret, point, point, silence};
    alphabet['E'] = {point, silence};
    alphabet['F'] = {point, point, tiret, point, silence};
    alphabet['G'] = {tiret, tiret, point, silence};
    alphabet['H'] = {point, point, point, point, silence};
    alphabet['I'] = {point, point, silence};
    alphabet['J'] = {point, tiret, tiret, tiret, silence};
    alphabet['K'] = {tiret, point, tiret, silence};
    alphabet['L'] = {point, tiret, point, point, silence};
    alphabet['M'] = {tiret, tiret, silence};
    alphabet['N'] = {tiret, point, silence};
    alphabet['O'] = {tiret, tiret, tiret, silence};
    alphabet['P'] = {point, tiret, tiret, point, silence};
    alphabet['Q'] = {tiret, tiret, point, tiret, silence};
    alphabet['R'] = {point, tiret, point, silence};
    alphabet['S'] = {point, point, point, silence};
    alphabet['T'] = {tiret, silence};
    alphabet['U'] = {point, point, tiret, silence};
    alphabet['V'] = {point, point, point, tiret, silence};
    alphabet['W'] = {point, tiret, tiret, silence};
    alphabet['X'] = {tiret, point, point, tiret, silence};
    alphabet['Y'] = {tiret, point, tiret, tiret, silence};
    alphabet['Z'] = {tiret, tiret, point, point, silence};

    alphabet['0'] = {tiret, tiret, tiret, tiret, tiret, silence};
    alphabet['1'] = {point, tiret, tiret, tiret, tiret, silence};
    alphabet['2'] = {point, point, tiret, tiret, tiret, silence};
    alphabet['3'] = {point, point, point, tiret, tiret, silence};
    alphabet['4'] = {point, point, point, point, tiret, silence};
    alphabet['5'] = {point, point, point, point, point, silence};
    alphabet['6'] = {tiret, point, point, point, point, silence};
    alphabet['7'] = {tiret, tiret, point, point, point, silence};
    alphabet['8'] = {tiret, tiret, tiret, point, point, silence};
    alphabet['9'] = {tiret, tiret, tiret, tiret, point, silence};

    alphabet['.'] = {point, tiret, point, tiret, point, tiret, silence};  
    alphabet[','] = {tiret, tiret, point, point, tiret, tiret, silence};
    alphabet['?'] = {point, point, tiret, tiret, point, point, silence};
    alphabet['!'] = {tiret, point, tiret, point, tiret, tiret, silence};
    alphabet[':'] = {tiret, tiret, tiret, point, point, point, silence};
    alphabet[';'] = {tiret, point, tiret, point, tiret, point, silence};
    alphabet['-'] = {tiret, point, point, point, point, tiret, silence};
    alphabet['('] = {tiret, point, tiret, tiret, point, silence};
    alphabet[')'] = {tiret, point, tiret, tiret, point, tiret, silence};
    alphabet['\''] = {point, tiret, tiret, tiret, tiret, point, silence};

    alphabet[' '] = {silence, silence};
    alphabet['\n'] = {silence, silence};    // Je crois que celui-là ne sert jamais, mais dans le doute...

}



void coder1(std::string message){

        /* Entete du fichier .wav */

    audio.open("en_morse.wav", std::ios::binary);  
    audio << "RIFF____WAVEfmt ";
    write_word(audio, 16,4);     // Subchunk1Size 
    write_word(audio, 1, 2);     // AudioFormat (non compréssé)
    write_word(audio, 1, 2);     // NumChannels (mono)
    write_word(audio, 44000, 4); // SampleRate
    write_word(audio, 44000, 4); // ByteRate (SampleRate * NumChannels * BitsPerSample/8)
    write_word(audio, 1, 2);     // BlockAlign (NumChannels * BitsPerSample/8)
    write_word(audio, 8, 2);     // BitsPerSample
    size_t data_chunk_pos = audio.tellp();
    audio << "data____";


    Alphabet();      // On rempli le dictionnaire du code morse

        /* Traduction du message en morse audio */

    for(auto x : message){
        for(auto y : alphabet[x]){
            ecrit(y);
        }
    }

        /* On met les bonnes valeurs pour les tailles dans l'entete */

    size_t taille = audio.tellp();
    audio.seekp(0 + 4);
    write_word(audio, taille - 8, 4);
    audio.seekp(data_chunk_pos + 4);
    write_word(audio, taille - data_chunk_pos + 8, 4);
    audio.close();
    
}




void coder2(std::string message){  // ici, message contient le chemin vers un fichier

    std::string::size_type const p(message.find_last_of('.'));
    std::string mess = message.substr(0, p);
    audio.open((mess+".wav"), std::ios::binary);  // on crée un fichier audio pour mettre le résultat
    
    audio << "RIFF____WAVEfmt ";
    write_word(audio, 16,4);     // Subchunk1Size 
    write_word(audio, 1, 2);     // AudioFormat (non compréssé)
    write_word(audio, 1, 2);     // NumChannels 
    write_word(audio, 44000, 4); // SampleRate
    write_word(audio, 44000, 4); // ByteRate (SampleRate * NumChannels * BitsPerSample/8)
    write_word(audio, 1, 2);     // BlockAlign (NumChannels * BitsPerSample/8)
    write_word(audio, 8, 2);     // BitsPerSample
    size_t data_chunk_pos = audio.tellp();
    audio << "data____";


    Alphabet();

    std::ifstream texte;
    texte.open(message);
    std::string a;
    while(!texte.eof()){
        std::getline(texte, a);
        for(auto x : a){
            for(auto y : alphabet[x]){
                ecrit(y);
            }
        }
        ecrit(silence);  // Pour le changement de ligne
        ecrit(silence);
    }
    texte.close();


    size_t taille = audio.tellp();
    audio.seekp(0 + 4);
    write_word(audio, taille - 8, 4);
    audio.seekp(data_chunk_pos + 4);
    write_word(audio, taille - data_chunk_pos + 8, 4);
    audio.close();

}
