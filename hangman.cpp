#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <time.h>

using namespace std;

void PrintMessage(string message, int printTop = 1, int printBottom = 1){
    bool front = true;
    if (printTop == 1){
        cout << "+=================================+" << endl;
        cout << "|";
    } 
    else if (printTop == 2){
        cout << "+_________________________________+" << endl;
        cout << "|";
    }
    else if (printTop == 0){
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
    if (printBottom == 1){
        cout << "|" << endl ;
        cout << "+=================================+" << endl;
    }
    if (printBottom == 2){
        cout << "|" << endl ;
        cout << "+_________________________________+" << endl;
    }
    else if (printBottom == 0){
        cout << "|" << endl;
    }
}
void DrawHangman(int guessCount = 0){
    if (guessCount >= 1){
        PrintMessage("|", 0, 0);
    }
    else{
        PrintMessage("", 0, 0);
    }

    if (guessCount >= 2){
        PrintMessage("|", 0, 0);
    }
    else{
        PrintMessage("", 0, 0);
    }

    if (guessCount >= 3){
        PrintMessage("O", 0, 0);
    }
    else{
        PrintMessage("", 0, 0);
    }

    if (guessCount == 4){
        PrintMessage("/  ", 0, 0);
    }
    
    if (guessCount == 5){
        PrintMessage("/| ", 0, 0);
    }

    if (guessCount >= 6){
        PrintMessage("/|\\", 0, 0);
    }
    
    if (guessCount >= 7){
        PrintMessage("|", 0, 0);
    }
    else{
        PrintMessage("", 0, 0);
    }

    if (guessCount == 8){
        PrintMessage("/  ", 0, 0);
    }

    if (guessCount >= 9){
        PrintMessage("/ \\", 0, 0);
    }
    
    if (guessCount >= 10){
        PrintMessage(" ", 0, 0);
    }
    
    PrintMessage("+===========+", 0, 0);
    PrintMessage("|           |", 0, 2);
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
    PrintMessage(" ", 0, 0);
    PrintLetters(taken, 'A', 'M');
    PrintLetters(taken, 'N', 'Z');
    PrintMessage("_________________________________", 0, 0);
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
    PrintMessage(s, 0, 1);

    return won;
}
string RandomWord(string path){
    string word;
    vector<string> v;
    ifstream reader(path);
    if (reader.is_open()){
        while(std::getline(reader, word))
            v.push_back(word);
        
        int wordPicker = rand()  % v.size();

        word = v.at(wordPicker);
        reader.close();
    }

    return word;
}
int guessLeft(string word, string guessed){
    int error = 0;
    int gl = guessed.length();
    for (int i = 0; i < gl; i++){
        if (word.find(guessed[i]) == string::npos){
            error++;
        }
    }
    return error;
}
int main(){
    srand(time(0));
    string guesses;
    string magicWord = RandomWord("HangmanText.txt");
    int tries = 0;
    bool win = false;
    do
    {
        system("cls");
        PrintMessage("HANG MAN");
        DrawHangman(tries);
        PrintAvailableLetters(guesses);
        PrintMessage("[CLUE STATEMENT]", 0, 2);
        win = PrintWordAndCheckWin(magicWord, guesses);

        if (win){
            break;
        }
        char x;
        cout << "Enter the letter:";
        cin >> x;

        if (guesses.find(x) == string::npos){
            guesses += x;
        }
        tries = guessLeft(magicWord, guesses);
    } while (tries < 10);
    
    if (win){
        PrintMessage("You WON!", 0, 1);
    }
    else {
        system("cls");
        PrintMessage("HANG MAN");
        DrawHangman(tries);
        PrintAvailableLetters(guesses);
        PrintMessage("[CLUE STATEMENT]", 0, 2);
        PrintMessage("GAME OVER", 0, 1);
    }

    system("pause");
    return 0;
}

