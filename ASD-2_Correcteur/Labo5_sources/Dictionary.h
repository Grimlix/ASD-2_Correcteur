/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Dictionary.h
 * Author: nichu
 *
 * Created on 18. janvier 2020, 01:07
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "TST.h"
#include <string>
#include <regex>
#include <iostream>
#include <string>
#include <unordered_set>
#include <fstream>
#include <algorithm>
#include <regex>
#include <vector>

using namespace std;

class Dictionary{

private:
    TernarySearchTree dicoTST;
    unordered_set<string> dicoSTL;

    bool mode;


public :
    Dictionary(const string& filename, bool mode){

        this->mode = mode;

        ifstream file(filename);
        string line;

        if (file.is_open()) {

            regex words_regex("[a-z]+('[a-z]+)*");
            auto words_end = sregex_iterator();
            //for each word in dictionary
            while (getline(file, line)) {
                //lowercaps the word
                transform(line.begin(), line.end(), line.begin(),
                          [](unsigned char c) {
                              return tolower(c); });

                auto line_begin = sregex_iterator(line.begin(), line.end(), words_regex);
                auto line_end = sregex_iterator();

                for(sregex_iterator i = line_begin; i != line_end; i++){
                    smatch match = *i;
                    //add word in corresponding data structure
                    if(mode){
                        dicoTST.put(match.str());
                    }else{
                        dicoSTL.insert(match.str());
                    }
                }
            }
            file.close();
        } else {
            cout << "Fail to open file : " << filename << endl;
        }
    }


    bool find_contains(const string& word){

        // Si le mot est "vide", il est dans le dictionnaire
        if (word.empty()) {
            return true;
        }else{
            if(mode){
                return dicoTST.contains(word);
            }else{
                return (dicoSTL.count(word) != 0);
            }

        }


    }






};



#endif /* DICTIONARY_H */


