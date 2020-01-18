/*
 * File:   Correction.h
 * Author: Gianinetti Lucas, Hungerbühler Nicolas, Wojciechowski Cassandre
 * Created on 18. janvier 2020
 *
 * Description: Contains function to get corrections from an incorrect word with a specific dicitonary
 *
 *
 *
 */


#ifndef ASDLABO5_CORRECTION_H
#define ASDLABO5_CORRECTION_H


#include "Dictionary.h"

//If word is corresponding to a word in dictionary but with 1 more letter we had it to vector<string> corrections
void letterInExcess(Dictionary& dico, string word, vector<string>& corrections){
    string check;
    for(int i = 0; i < word.length(); ++i){
        check = word.substr(0, i) + word.substr(i+1, word.length());
        if(dico.find_contains(check)){
            corrections.push_back("1:"+check);
        }
    }
}

//If word is corresponding to a word in dictionary but with 1 missing letter we had it to vector<string> corrections
void letterMissing(Dictionary& dico, string word, vector<string>& corrections){
    string check;
    const string alphabet = "abcdefghijklmnopqrstuvwxyz'";
    const unsigned size = 1;
    for(int i = 0; i <= word.length(); ++i){
        for(int j = 0; j < alphabet.length(); ++j){
            check = word;
            check.insert(i, size, alphabet[j]);

            if(dico.find_contains(check)) {
                corrections.push_back("2:"+check);

            }
        }
    }
}

//If word is corresponding to a word in dictionary but with 1 misspelled letter we had it to vector<string> corrections
void wrongLetter(Dictionary& dico, string word, vector<string>& corrections){
    string check = word;
    const string alphabet = "abcdefghijklmnopqrstuvwxyz'";
    for(int i = 0; i < word.length(); ++i){
        check = word;
        for(int j = 0; j < alphabet.length(); ++j){
            check[i] = alphabet[j];
            if(dico.find_contains(check)){
                corrections.push_back("3:"+check);
            }
        }

    }
}

//If word is corresponding to a word in dictionary but with 2l letters in incorect order we had it to vector<string> corrections
void swappedLetter(Dictionary& dico, string word, vector<string>& corrections){

    int len = word.length() -1;
    string temp = word;
    for(int i = 0; i < len;i++){
        temp = word;
        char ctemp = temp[i];
        temp[i] = temp[i+1];
        temp[i+1] = ctemp;
        if(dico.find_contains(temp)){
            corrections.push_back("4:"+temp);
        }
    }
}

//get every correction for word and had it to corrections
void setCorrections(Dictionary& dico, string word, vector<string>& corrections){
    corrections.push_back("*"+word);
    letterInExcess(dico,word,corrections);
    letterMissing(dico,word,corrections);
    wrongLetter(dico,word,corrections);
    swappedLetter(dico,word,corrections);


}

#endif //ASDLABO5_CORRECTION_H
