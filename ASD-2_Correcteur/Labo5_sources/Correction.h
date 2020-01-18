//
// Created by lucas on 18.01.20.
//


#ifndef ASDLABO5_CORRECTION_H
#define ASDLABO5_CORRECTION_H


#include "Dictionary.h"

bool isWordInSet(Dictionary dico, string word) {
    return (dico.find_contains(word));
}

void letterInExcess(const Dictionary& dico, string word, vector<string>& corrections, bool& hasCorrection){
    string check;
    for(int i = 0; i < word.length(); ++i){
        check = word.substr(0, i) + word.substr(i+1, word.length());
        if(isWordInSet(dico,check)){
            hasCorrection = true;
            corrections.push_back("1:"+check);
        }
    }
}

void letterMissing(const Dictionary& dico, string word, vector<string>& corrections, bool& hasCorrection){
    string check;
    const string alphabet = "abcdefghijklmnopqrstuvwxyz'";
    const unsigned size = 1;
    for(int i = 0; i <= word.length(); ++i){
        for(int j = 0; j < alphabet.length(); ++j){
            check = word;
            check.insert(i, size, alphabet[j]);

            if(isWordInSet(dico, check)) {
                hasCorrection = true;
                corrections.push_back("2:"+check);

            }
        }
    }
}

void wrongLetter(const Dictionary& dico, string word, vector<string>& corrections, bool& hasCorrection){
    string check = word;
    const string alphabet = "abcdefghijklmnopqrstuvwxyz'";
    for(int i = 0; i < word.length(); ++i){
        check = word;
        for(int j = 0; j < alphabet.length(); ++j){
            check[i] = alphabet[j];
            if(isWordInSet(dico,check)){
                hasCorrection = true;
                corrections.push_back("3:"+check);
            }
        }

    }
}

void swappedLetter(const Dictionary& dico, string word, vector<string>& corrections, bool& hasCorrection){

    int len = word.length() -1;
    string temp = word;
    for(int i = 0; i < len;i++){
        temp = word;
        char ctemp = temp[i];
        temp[i] = temp[i+1];
        temp[i+1] = ctemp;
        if(isWordInSet(dico,temp)){
            hasCorrection = true;
            corrections.push_back("4:"+temp);
        }
    }
}


void setCorrections(const Dictionary& dico, string word, vector<string>& corrections){
    bool hasCorrection = false;
    corrections.push_back("*"+word);
    letterInExcess(dico,word,corrections,hasCorrection);
    letterMissing(dico,word,corrections,hasCorrection);
    wrongLetter(dico,word,corrections, hasCorrection);
    swappedLetter(dico,word,corrections,hasCorrection);
}

#endif //ASDLABO5_CORRECTION_H
