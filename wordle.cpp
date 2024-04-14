#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm>
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;

char letters[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
std::set<std::string> sol;
// Add prototypes of helper functions here
void tryCharacter(string, string, int, int, const std::set<std::string>& );
void generatePossibleSol(string, string, const std::set<std::string>& );
bool floatingCheck(string in, string floating);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    generatePossibleSol(in, floating, dict);

    return sol;

}

// Define any helper functions here
void tryCharacter(string in, string floating, int blank_index, int letter, const std::set<std::string>& dict){
    if(letter == 26){
        return;
    }else{
        string newWord = in;
        newWord[blank_index] = letters[letter];
        generatePossibleSol(newWord, floating, dict);
        letter++;
        tryCharacter(in, floating, blank_index, letter, dict);
    }
}

void generatePossibleSol(string in, string floating, const std::set<std::string>& dict){
    for(int i=0; i<in.length(); i++){
        if(in[i] == '-'){
            tryCharacter(in, floating, i, 0, dict);
        }
    }
    if(dict.find(in) != dict.end() and floatingCheck(in, floating)){
        sol.insert(in);
    }
}

bool floatingCheck(string in, string floating){
    for(int i=0; i<floating.length(); i++){
        bool containsLetter = false;
        for(int j=0; j<in.length(); j++){
            if(in[j] == floating[i]){
                containsLetter = true;
            }
        }
        if(!containsLetter){
            return false;
        }
    }
    return true;
}