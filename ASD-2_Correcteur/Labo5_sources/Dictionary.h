/*
 * File:   main.cpp
 * Author: Gianinetti Lucas, Hungerbühler Nicolas, Wojciechowski Cassandre
 * Created on 18. janvier 2020
 *
 * Description: this is a wrapper that takes all the words in a file, in our case
 *              a dictionary. And it stocks all these words in 2 types of data
 *              structure depending on chosen mode.
 *              modeTST = true ==> stock values in a TernarySearchTree<string>
 *              modeSTL = false ==> stock values in a unordered_set<string>
 *
 *
 *
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <regex>
#include <iostream>
#include <string>
#include <unordered_set>
#include <fstream>
#include <algorithm>
#include <vector>

#include "TST.h"

using namespace std;

class Dictionary{

private:
   //Our two data structures
    TernarySearchTree dicoTST;
    unordered_set<string> dicoSTL;

    //Which mode is used, TST or set
    //If it is true it's TST
    bool modeTST;


public :
    Dictionary(const string& filename, bool mode){

        this->modeTST = mode;

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
                    if(modeTST){
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


    //Returns true if the words is found in corresponding data structure
    //set uses count and TST uses contains.
    bool find_contains(const string& word){
            if(modeTST){
                return dicoTST.contains(word);
            }else{
                return (dicoSTL.count(word) != 0);
            }
        }
   
};



#endif /* DICTIONARY_H */
