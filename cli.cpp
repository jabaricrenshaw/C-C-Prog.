/****************************
*   Jabari A. Crenshaw      *   
*   CSC 139, Prof. Mayer    *
*   cli.cpp                 *
*   27 April 2022           *
*****************************/

#include <iostream>
#include <cstring>
#include <unistd.h>
using namespace std;

void DisplayPrompt();
bool ChkString(string inputCommand);
void GetInputAndExec(int argc, char* argv[]);

//List of valid commands that can be used as arguments for the program.
const char* instructions[] = {"cd", "exec", "exit", "gcc",
                       "ls", "man", "more", "mv",
                       "rm", "pwd", "sh", "touch",
                       "which", "$path"};

//The total number of valid instructions.
const int instrLen = sizeof(instructions) / sizeof(instructions[0]);

int main(int argc, char* argv[]) {
    DisplayPrompt();
    GetInputAndExec(argc, argv);

    return 0;
}

/* 
* void GetInputAndExec(int argc, char* argv[]);
* This function is used to process and execute ./cli arguments through system().
*/
void GetInputAndExec(int argc, char* argv[]) {

    /*
    * If there are no arguments to process as
    * commands, return this message only.
    */
    if(argc < 2){
        cout << "\n!!! Please input a command as an argument. !!!" << "\n";
        return;
    }

    //Stores a command to be executed using system()
    char* cmd;

    /*
    * Pointer to the input[] string which stores
    * all commands given as arguments to ./cli
    */
    int charPointer = 0;

    //Number of usable commands given to ./cli
    int n = 0;

    /*
    * String array stores a list of concatenated
    * commands and their specified arguments.
    */
    string input[14];

    /*
    * This for loop processes all arguments given to ./cli, and places
    * them into string input[].
    * 
    * The first arguemnt is stored in input[0], and once a comma
    * is reached, charPointer is incremented to access input[1].
    * 
    * Data is initially retrieved from char** argv --> char* argv[].
    */
    for(int i = 1; i < argc; i++) {
        for(int j = 0; j < strlen(argv[i]); j++) {      
            if(argv[i][j] == ',') {
                charPointer++;
            }else{
                input[charPointer] += argv[i][j];
            }
        }
        if(input[charPointer] != "" && i < argc - 1) {    
            input[charPointer] += " ";
        }
    }

    /*
    * We will use charPointer to keep track of the number
    * of input[] fields that we have stored data.
    * 
    * A non empty input[] element means that it stores a command to be run.
    */
    cout << charPointer+1 << " executable strings passed to argv[]." << "\n\n";
    
    for(int i = 0; i < charPointer+1; i++) {
        cout << "next string is '" << input[i] << "'\n"
             << "new string is '" << input[i] << "'\n";
        if( ChkString(input[i]) ) {
        //If the input command is defined...
            cout << "Command " << i+1 << " is one of predefined." << "\n"
                 << "Executing..." << "\n";

            //If command is cd, change working directory of the running program.
            if(input[i].find("cd") != string::npos && input[i].size() > 2){
                chdir(input[i].substr(input[i].find("cd") +3).c_str());
            }

            //Continue execution of the program in the cwd.
            system(input[i].c_str());
        }else{
        /*
        * If the input command is not defined in this program,
        * we will attempt to run it anyway.
        */    
            cout << "!!! Command " << i+1 << " is not one of predefined. !!!" << "\n"
                 << "Attempting ..." << "\n";
            system(input[i].c_str());
        }
        cout << "\n";
    }
}

/* 
* bool ChkString(string inputCommand)
* This function is used to check if an input string is defined
* in our valid instruction[] array.
*
* Returns true if the principle command in the input string is valid.
* False otherwise.
*/
bool ChkString(string input) {

    /*
    * Splitting the input string if it containes arguments
    * seperated by whitespace.
    * 
    * ex. 1 the command "mv s.txt ../" will result in "mv",
    * which is the primary command.
    * 
    * ex. 2 the command "ls" will result in "ls", as the string
    * does not contain a whitespace and no args.
    */
    string cmd = input.substr(0, input.find(" "));

    /*
    * Iterate through the valid instruction[] array
    * to determine if input is defined.
    */
    for(int i = 0; i < instrLen; i++) {
        if( cmd == instructions[i]) {
            return true;
        }
    }
    return false;
}

/* 
* void DisplayPrompt()
* This function is used to print the opening dialog.
*/
void DisplayPrompt() {
    cout << "jac cli 4/25/2022" << "\n"
         << "Legal commands: ";
    for(int i = 0; i < instrLen; i++) {
        cout << instructions[i] << " ";
    }
    cout << "\n";
}