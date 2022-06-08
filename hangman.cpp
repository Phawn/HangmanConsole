#include <iostream>

using namespace std;

void PrintMessage(string message, bool printTop = true, bool printBottom = true){
    bool front = true;
    if (printTop){
        cout << "+================================+" << endl;
        cout << "|";
    }
    else {
        cout << "|";
    }
    for (int i = message.length(); i < 33; i++ ){
        if (front){
            message = " " + message;
        }
        else {
            message = message + " ";
        }
        front = !front;
    }
    cout << message.c_str();
    if (printBottom){
        cout << "|" << endl ;
        cout << "+================================+" << endl;
    }
    else {
        cout << "|" << endl;
    }
}
void DrawHangman(int guessCount = 0){
    if (guessCount >= 1){
        PrintMessage("|", false, false);
    }
    else{
        PrintMessage("", false, false);
    }

    if (guessCount >= 2){
        PrintMessage("|", false, false);
    }
    else{
        PrintMessage("", false, false);
    }

    if (guessCount >= 3){
        PrintMessage("O", false, false);
    }
    else{
        PrintMessage("", false, false);
    }

    if (guessCount == 4){
        PrintMessage("/  ", false, false);
    }
    
    if (guessCount == 5){
        PrintMessage("/| ", false, false);
    }

    if (guessCount >= 6){
        PrintMessage("/|\\", false, false);
    }
    
    if (guessCount >= 7){
        PrintMessage("|", false, false);
    }
    else{
        PrintMessage("", false, false);
    }

    if (guessCount == 8){
        PrintMessage("/  ", false, false);
    }

    if (guessCount >= 9){
        PrintMessage("/ \\", false, false);
    }
    
    PrintMessage("+===========+", false, false);
    PrintMessage("|           |", false, false);
}
void PrintLetters(string input, char from, char to){
    string s;
    for (char i = from; i <= to; i++){
        if (input.find(i) == string::npos){
            s += i;
            s += " ";
        }
        else {
            s += " ";
        }
    }
    PrintMessage(s, false, false);
}
void PrintAvailableLetters(string taken){
    PrintMessage("_________________________________", false, false);
    PrintMessage(" ", false, false);
    PrintLetters(taken, 'A', 'M');
    PrintLetters(taken, 'N', 'Z');
    PrintMessage("_________________________________", false, false);
}
bool PrintWordAndCheckWin(string word, string guessed){
    string s;
    int wl = word.length();
    bool won = true;

    for (int i = 0; i < wl; i++){
        if (guessed.find(word[i]) == string::npos){
            won = false;
            s += "_ ";
        }
        else {
            s += word[i];
            s += " ";
        }
    }
    PrintMessage("_________________________________", false, false);
    PrintMessage(s, false);

    return won;
}

int main(){
    string guesses = "PSQUARED";
    PrintMessage("HANG MAN");
    DrawHangman(0);
    PrintAvailableLetters(guesses);
    PrintMessage("[CLUE STATEMENT]", false, false);
    PrintWordAndCheckWin("PAOPE", guesses);
    return 0;
}

/*
+=================================+
|            HANG MAN             |
+=================================+
|                |                |
|                |                |
|                O                |
|               /|\               |
|                |                |
|               / \               |
|          +===========+          |
|          |           |          |
+=================================+
|       [Question or statment]    |
+=================================+
|  _ _ _ _ _ _ _ _ _ _ _ _ _ _ _  |
+=================================+
|    A B C D E F G H I J K L M    |
|    N O P Q R S T U V W X Y Z    |
+=================================+
Input a letter:
*/