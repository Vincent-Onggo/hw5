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

void permutateFloating(string in, const string& floating, set<string>& fixed, size_t index);
void tryCharacters(string in, size_t index, set<string>& sol, const set<string>& dict);
// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> sol;
    std::set<std::string> fixed;
    permutateFloating(in, floating, fixed, 0);
    for(set<string>::iterator it = fixed.begin(); it != fixed.end(); ++it){
        tryCharacters(*it,  0, sol, dict);
    }
    return sol;

}

// Define any helper functions here
void tryCharacters(string in, size_t index, set<string>& sol, const set<string>& dict){
    if(index == in.length()){
        if(dict.find(in) != dict.end()){
            sol.insert(in);
        }
        return;
    }
    if(in[index] != '-'){
        tryCharacters(in, index + 1, sol, dict);
    }else{
        for(int i=0; i<26; i++){
            string newString = in;
            newString[index] = 'a' + i;
            tryCharacters(newString, index + 1, sol, dict);
        }
    }
}

void permutateFloating(string in, const string& floating, set<string>& fixed, size_t index) {
    if (index == floating.length()) {
        fixed.insert(in);
        return;
    }

    for (size_t i = 0; i < in.length(); ++i) {
        if (in[i] == '-') {
            in[i] = floating[index];
            permutateFloating(in, floating, fixed, index + 1);
            in[i] = '-';
        }
    }
}