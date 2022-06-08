#include <iostream>

using namespace std;

void PrintMessage(string message, bool printTop = true, bool printBottom = true){
    bool front = true;
    if (printTop){
        cout << "+================================+" << endl;
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
}

int main(){
    PrintMessage("HANG MAN");
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