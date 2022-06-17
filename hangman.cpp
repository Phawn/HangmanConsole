#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <string>
#include <time.h>
#include <windows.h>

using namespace std;

//general variables
string playerName;
int Escore = 0;
int Nscore = 0;
int Hscore = 0;
//database address
void PrintMessage(string message, int printTop, int printBottom);
void DrawHangman(int guessCount);
void PrintLetters(string input, char from, char to);
void PrintAvailableLetters(string taken);
void playerLog();
void HighScore();
bool PrintWordAndCheckWin(string word, string guessed);
string RandomWord(string path);
int guessLeft(string word, string guessed);
int pointSystem(int SCORE, int tries, int points);
//modes address
void gameHard();
void gameNormal();
void gameEasy();
//UI address
void gameStart();
void close();
void about();
void gameinstruct();

int main(){
    char option;
    system("cls");
    cout << "[Main Menu]" << endl;
    cout << "1) Start game" << endl;
    cout << "2) Login" << endl;
    cout << "3) Instructions" << endl;
    cout << "4) High Score" << endl;
    cout << "5) About" << endl;
    cout << "6) Exit" << endl;
    cout << "Enter option:";
    cin >> option;

    if (option == '1'){
        gameStart();
    }
    else if (option == '2'){
        playerLog();
    }
    else if (option == '3'){
        gameinstruct();
    }
    else if (option == '4'){
        HighScore();
    }
    else if (option == '5'){
        about();
    }
    else if (option == '6'){
        close();
    }
    else {
        system("cls");
        cout << "Warning! Explotion will occur in...";
        for (int seconds = 3; seconds >= 1; seconds--){
            cout << seconds << ".";
            Sleep(1000);
        }
        cout << "\nJoke UwU, Your options are only numbers 1-6" << endl;

        system("Pause");
        main();
    }
    

    return 0;
}
//game system and database
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
int pointSystem(int HSCORE, int tries, int points, int multiplier){
    int score;
    score = HSCORE + points - (tries * multiplier);
    cout << "Points: " << score << endl;
    return score;
}
//selection menu and game
void gameStart(){
    char x;
    system("cls");
    cout << "Menu > Start" << endl;
    cout << "Set difficulty" << endl;
    cout << "1. Easy" << endl;
    cout << "2. Normal" << endl;
    cout << "3. Hard" << endl;
    cout << ">";
    cin >> x;
    if (x == '1'){
        gameEasy();
    }
    else if (x == '2'){
        gameNormal();
    }
    else if (x == '3'){
        gameHard();
    }
    else {
        system("cls");
        cout << "Incorrect input. Returning to menu..." << endl;
        system("Pause");
        main();
    }

}
void gameEasy(){
    char option;
    srand(time(0));
    string guesses;
    string magicWord = RandomWord("Four-SixWords.txt");
    int tries = 0;
    bool win = false;
    do
    {
        
        system("cls");
        cout << "Menu > Hangman" << endl;
        PrintMessage("HANG MAN");
        DrawHangman(tries);
        PrintAvailableLetters(guesses);
        PrintMessage("THEME: [FRUITS & VEGGIES!]", 0, 2);
        win = PrintWordAndCheckWin(magicWord, guesses);

        if (win){
            break;
        }
        char x;
        cout << "Enter a letter:";
        cin >> x;
        x = toupper(x);
        if (guesses.find(x) == string::npos){
            guesses += x;
        }
        tries = guessLeft(magicWord, guesses);
    } while (tries < 10);
    
    if (win){
        PrintMessage("You WON!", 0, 1);
        Escore = pointSystem(Escore, tries, 10, 1);
    }
    else {
        system("cls");
        PrintMessage("HANG MAN");
        DrawHangman(tries);
        PrintAvailableLetters(guesses);
        PrintMessage("THEME: [FRUITS & VEGGIES!]", 0, 2);
        PrintMessage("GAME OVER", 0, 1);
        Escore = pointSystem(Escore, tries, 10, 1);
        cout << "SALVATION WORD: " << magicWord << endl;
    }

    cout << "Do you wish to continue?" << endl;
    cout << "[y] yes | [n] no" << endl;
    cin >> option;

    if (option == 'y'){
        cout << "Loading game. Please wait..." << endl;
        system("Pause");
        gameEasy();
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
void gameNormal(){
    char option;
    srand(time(0));
    string guesses;
    string magicWord = RandomWord("Seven-TenWords.txt");
    int tries = 0;
    bool win = false;
    do
    {
        
        system("cls");
        cout << "Menu > Hangman" << endl;
        PrintMessage("HANG MAN");
        DrawHangman(tries);
        PrintAvailableLetters(guesses);
        PrintMessage("THEME: [COUNTRIES / STATES]", 0, 2);
        win = PrintWordAndCheckWin(magicWord, guesses);

        if (win){
            break;
        }
        char x;
        cout << "Enter a letter:";
        cin >> x;
        x = toupper(x);
        if (guesses.find(x) == string::npos){
            guesses += x;
        }
        tries = guessLeft(magicWord, guesses);
    } while (tries < 10);
    
    if (win){
        PrintMessage("You WON!", 0, 1);
        Nscore = pointSystem(Nscore, tries, 10, 1.5);
    }
    else {
        system("cls");
        PrintMessage("HANG MAN");
        DrawHangman(tries);
        PrintAvailableLetters(guesses);
        PrintMessage("THEME: [COUNTRIES / STATES]", 0, 2);
        PrintMessage("GAME OVER", 0, 1);
        Nscore = pointSystem(Nscore, tries, 10, 1.5);
        cout << "SALVATION WORD: " << magicWord << endl;
    }

    cout << "Do you wish to continue?" << endl;
    cout << "[y] yes | [n] no" << endl;
    cin >> option;

    if (option == 'y'){
        cout << "Loading game. Please wait..." << endl;
        system("Pause");
        gameNormal();
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
void gameHard(){
    char option;
    srand(time(0));
    string guesses;
    string magicWord = RandomWord("Eleven-twelveWords.txt");
    int tries = 0;
    bool win = false;
    do
    {
        
        system("cls");
        cout << "Menu > Hangman" << endl;
        PrintMessage("HANG MAN");
        DrawHangman(tries);
        PrintAvailableLetters(guesses);
        PrintMessage("[ERROR THEME NOT FOUND]", 0, 2);
        win = PrintWordAndCheckWin(magicWord, guesses);

        if (win){
            break;
        }
        char x;
        cout << "Enter a letter:";
        cin >> x;
        x = toupper(x);
        if (guesses.find(x) == string::npos){
            guesses += x;
        }
        tries = guessLeft(magicWord, guesses);
    } while (tries < 10);
    
    if (win){
        PrintMessage("You WON!", 0, 1);
        Hscore = pointSystem(Hscore, tries, 23, 2);
    }
    else {
        system("cls");
        PrintMessage("HANG MAN");
        DrawHangman(tries);
        PrintAvailableLetters(guesses);
        PrintMessage("[ERROR THEME NOT FOUND]", 0, 2);
        PrintMessage("GAME OVER", 0, 1);
        Hscore = pointSystem(Hscore, tries, 23, 2);
        cout << "SALVATION WORD: " << magicWord << endl;
    }

    cout << "Do you wish to continue?" << endl;
    cout << "[y] yes | [n] no" << endl;
    cin >> option;

    if (option == 'y'){
        cout << "Loading game. Please wait..." << endl;
        system("Pause");
        gameHard();
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
void HighScore(){
    system("cls");
    cout << "\t\tHIGH SCORE" << endl;
    cout << setfill('.');
    cout << playerName << "(EASY)" << setw(33) << Escore << endl;
    cout << playerName << "(NORMAL)" << setw(33) << Nscore << endl;
    cout << playerName << "(HARD)" << setw(33) << Hscore << endl;
    system("pause");
    main();
}
void playerLog(){
    system("cls");
    cout << "Menu > Login" << endl;
    cout << "Enter your name:";
    cin >> playerName;
    cout << "Initializing username... Please wait.." << endl;
    Sleep(1000);
    cout << "Username initialized!" << endl;
    system("pause");
    main();
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
    cout << "Programmer: Paolo Angelo E. Porlas" << endl;
    cout << "            Don Lhean M. Otadoy (9/10)" << endl;
    cout << "            Mika Dela Torre (8/10)" << endl;
    cout << "Project: Finals Exam" << endl;
    cout << "Professor: David Matthew Derit" << endl;
    cout << "Course: Programming Logic and Design 2" << endl;

    system("Pause");
    main();
}
void gameinstruct(){
    system("cls");
    cout << "Menu > Instructions" << endl;
    cout << "==========================" << endl;
    cout << "| HangMan [Console Game] |" << endl;
    cout << "==========================" << endl;
    cout << "Hangman is a simple word guessing game. Players try to figure out an unknown word by guessing letters. If too many letters which do not appear in the word are guessed, the player is hanged (and loses)and if the player manage to guess the correct word, they win. Every time the player wins they earn points. Don't worry the game will give you some clue depending on the difficulty the player chose." << endl;

    system("Pause");
    main();
}
