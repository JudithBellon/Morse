# Morse - Projet C++

Pour utiliser ce programme de codage/décodage de Morse, il suffit de :
* faire `make`  *(les warnings c'est pas grave)*
* lancer le programme avec `./morse`
* suivre les instructions :
  * pour coder un message en morse, entrer `1` puis
    * `1` pour entrer le message directement. Le résultat se trouvera alors dans le fichier `en_morse.wav`. (A titre d'exemple, il contient au départ le message "Vive le morse !")
    * `2` pour donner au programme le chemin vers un fichier texte. On trouvera alors le résultat dans un fichier de même nom (et même chemin d'accès), mais d'extension `.wav`.
  * pour décoder un message du morse vers le français, entrer `2`, puis le chemin vers le fichier son à décoder, et enfin
    * `1` pour afficher le texte dans le terminal
    * `2` pour l'enregistrer dans un fichier `.txt` de même nom


Ce programme ne permet pas de prendre en compte les accents ou autres caractères spéciaux : il est conseillé de ne pas en mettre dans vos messages. 
Si toutefois il y en avait, ces caratères seront simplement ignorés par le programme, qui codera par exemple "gnial" à la place de "génial".

Inversemment, si votre message morse utilise des caractères non pris en compte par mon programme ou comporte des erreurs, ils seront remplacés par des \*, ce qui devrait permettre au message de rester compréhensible.

Le dossier `Tests` contient :
- un fichier `Exemple.wav` et le texte associé `Exemple.txt`; 
- un fichier `Morse_court.txt` et la version morse associée;
- et un fichier `Morse.txt`, on pourra obtenir le fichier `Morse.wav` contenant la version en morse de ce texte (trop lourde pour passer sur GitHub) en entrant successivement  "1", "2" et "Tests/Morse.txt" lorsque le programme le demande.
