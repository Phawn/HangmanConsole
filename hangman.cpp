#include <iostream>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <string>
#include <time.h>
#include <windows.h>
using namespace std;


void PrintMessage(string message, int printTop, int printBottom);
void DrawHangman(int guessCount);
void PrintLetters(string input, char from, char to);
void PrintAvailableLetters(string taken);
bool PrintWordAndCheckWin(string word, string guessed);
string RandomWord(string path);
int guessLeft(string word, string guessed);
void gameLoop();
void close();
void about();

int main(){
    char option;
    system("cls");
    cout << "[Main Menu]" << endl;
    cout << "1) Start game" << endl;
    cout << "2) About" << endl;
    cout << "3) Exit" << endl;
    cout << "Enter option:";
    cin >> option;

    if (option == '1'){
        gameLoop();
    }
    else if (option == '2'){
        about();
    }
    else if (option == '3'){
        close();
    }

    return 0;
}


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
void gameLoop(){
    char option;
    srand(time(0));
    string guesses;
    string magicWord = RandomWord("wordLibrary.txt");
    int tries = 0;
    bool win = false;
    do
    {
        
        system("cls");
        cout << "Menu > Hangman" << endl;
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

    cout << "Do you wish to continue?" << endl;
    cout << "[y] yes | [n] no" << endl;
    cin >> option;

    if (option == 'y'){
        cout << "Loading game. Please wait..." << endl;
        system("Pause");
        gameLoop();
    } else if (option == 'n'){
        cout << "Returning to main menu. Please wait..." << endl;
        system("Pause");
        main();
    } else {
        system("cls");
        cout << "You have input an invalid key. Returning to menu..." << endl;
        system("Pause");
        main();
    }

    system("pause");
}

void close(){
    char x;
    int seconds;
    cout << "Menu > Exit" << endl;
    system("cls");
    cout << "Are you sure you want to quit?" << endl;
    cout << "[y] yes | [n] no" << endl;
    cin >> x;
    if (x == 'y'){
        cout << "Thank you!" << endl;
        exit(EXIT_SUCCESS);
    } else if (x == 'n'){
        cout << "Returning to main menu. Please wait..." << endl;
        system("Pause");
        main();
    } else {
        system("cls");
        cout << "Warning! Explotion will occur in..." << endl;
        for (seconds = 3; seconds >= 1; seconds--){
            cout << seconds << endl;
            Sleep(1000);
        }
        cout << "Joke, binuang ra bitaw to -- UwU " << endl;

        system("Pause");
        main();
    }
}
void about(){
    system("cls");
    cout << "Menu > About" << endl;
    cout << "==========================" << endl;
    cout << "| HangMan [Console Game] |" << endl;
    cout << "==========================" << endl;
    cout << "Programmer: Paolo Angelo E. Porlas" << endl << endl;
    cout << "            Don Lhean M. Otadoy" << endl;
    cout << "            Mika Dela Torre" << endl;
    cout << "Project: Finals Exam" << endl;
    cout << "Professor: David Matthew Derit" << endl;
    cout << "Course: Programming Logic and Design 2" << endl;

    system("Pause");
    main();
}
