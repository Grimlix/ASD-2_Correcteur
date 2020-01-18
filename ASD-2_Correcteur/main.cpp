#include <iostream>
#include <string>
#include <unordered_set>
#include <fstream>
#include <algorithm>
#include <regex>
#include <vector>

#include "TST.h"
#include "Dictionary.h"


using namespace std;


bool isWordInSet(Dictionary dico, string word) {
    return (dico.find_contains(word));
}
/*
bool isWordInVector(const std::vector<string>& v, string word){
    return std::count(v.begin(),v.end(),word);
}*/

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
    const string alphabet = "abcdefghijklmnopqrstuvwxyz";
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
    const string alphabet = "abcdefghijklmnopqrstuvwxyz";
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
    /* if(!hasCorrection){
         corrections.pop_back();
     }*/
}

int main() {


    //////////////////////////////////////////////////////////////////
    //                          FIRST PART                          //
    //////////////////////////////////////////////////////////////////

    //We chose stl structure unordered_set because it has O(1) complexity
    //for reasearch. And we chose unordered_set instead of unordered_map
    //because unordered_map insert the element when a research doesn't find an element

    const int TST_MODE = 1;
    const int STL_MODE = 2;

    string myDictionary = "dictionary.txt";

    Dictionary dictionary = Dictionary(myDictionary, STL_MODE);

    int motDansDictionnaire = 0;
    int motPasDansDictionnaire = 0;

    fstream nicoLaBite("input_wikipedia.txt");
    string line;
    vector<string> wrongWords;
    vector<string> corrections;

    if (nicoLaBite.is_open()) {

        std::regex words_regex("[a-z]+('[a-z]+)*");
        auto words_end = std::sregex_iterator();
        //for each word in dictionary
        while (getline(nicoLaBite, line)) {
            //lowercaps the word
            transform(line.begin(), line.end(), line.begin(),
                      [](unsigned char c) {
                          return tolower(c); });


            auto line_begin = sregex_iterator(line.begin(), line.end(), words_regex);
            auto line_end = sregex_iterator();

            for(sregex_iterator i = line_begin; i != line_end; i++){
                smatch match = *i;
                if(isWordInSet(dictionary, match.str())){
                    cout << "Je suis là 1" << endl;
                    motDansDictionnaire++;
                }else{
                    motPasDansDictionnaire++;
                    wrongWords.push_back(match.str());

                }
            }
        }
        cout << "Je suis là 2" << endl;
        nicoLaBite.close();
        cout << "Je suis là 3" << endl;
    } else {
        cout << "Fail to open file : " << "input_wiki" << endl;
    }

    for(string word : wrongWords){
        cout << "Je suis là 4" << endl;
        setCorrections(dictionary,word, corrections);
    }

    //cout << "Mots totaux dans le dictionnaire : " << dictionary.size() << endl;

    /*
    cout << "mots pas dans le dico : " << motPasDansDictionnaire << endl;
    cout << "mots dans le dico : " << motDansDictionnaire << endl;*/

    for(string elem : corrections){
        cout << elem << endl;
    }

    cout << " nbr de mots faux : " << motPasDansDictionnaire;

    return 0;
}
