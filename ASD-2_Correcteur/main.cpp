#include <iostream>
#include <string>
#include <unordered_set>
#include <fstream>
#include <algorithm>
#include <regex>
#include <vector>






using namespace std;

/**
 * Fill an ordered set with lines from a text file
 * @param set set to fill with lines
 * @param file file from which get lines
 */
void fillUnorderedSet(std::unordered_set<string>& set, string file, char delim) {
    ifstream myDictionary(file);
    string line;


    if (myDictionary.is_open()) {

        std::regex words_regex("[a-z]+('[a-z]+)*");
        auto words_end = std::sregex_iterator();
        //for each word in dictionary
        while (getline(myDictionary, line)) {
            //lowercaps the word
            transform(line.begin(), line.end(), line.begin(),
                      [](unsigned char c) {
                          return tolower(c); });


            auto line_begin = sregex_iterator(line.begin(), line.end(), words_regex);
            auto line_end = sregex_iterator();

            for(sregex_iterator i = line_begin; i != line_end; i++){
                smatch match = *i;
                set.insert(match.str());
            }
        }
        myDictionary.close();
    } else {
        cout << "Fail to open file : " << file << endl;
    }
}

bool isWordInSet(const std::unordered_set<string>& set, string word) {
    return set.count(word) != 0;
}

void letterInExcess(const unordered_set<string>& dico, string word, vector<string>& corrections, bool& hasCorrection){
    string check;
    for(int i = 0; i < word.length(); ++i){
        check = word.substr(0, i) + word.substr(i+1, word.length());
        if(isWordInSet(dico,check)){
            hasCorrection = true;
            corrections.push_back("1:"+check);
        }
    }
}

void letterMissing(const unordered_set<string>& dico, string word, vector<string>& corrections, bool& hasCorrection){
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

void wrongLetter(const unordered_set<string>& dico, string word, vector<string>& corrections, bool& hasCorrection){
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

void swappedLetter(const unordered_set<string>& dico, string word, vector<string>& corrections, bool& hasCorrection){

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


void setCorrections(const unordered_set<string>& dico, string word, vector<string>& corrections){
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

    //637850

    //////////////////////////////////////////////////////////////////
    //                          FIRST PART                          //
    //////////////////////////////////////////////////////////////////

    //We chose stl structure unordered_set because it has O(1) complexity
    //for reasearch. And we chose unordered_set instead of unordered_map
    //because unordered_map insert the element when a research doesn't find an element

    //Create a unordered_set and fill it with words from dictionary
    std::unordered_set<string> dictionary;
    string myDictionary = "dictionary.txt";
    fillUnorderedSet(dictionary, myDictionary, '\n');

    int motDansDictionnaire = 0;
    int motPasDansDictionnaire = 0;


    fstream nicoLaBite("input_wikipedia.txt");
    string line;
    vector<string> wrongWords;
    vector<string> corrections;

    if (nicoLaBite.is_open()) {

        std::regex words_regex("([a-z]|[A-Z])+('([a-z]|[A-Z])+)*");
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

                if(dictionary.count(match.str()) != 0){
                    motDansDictionnaire++;
                    //cout << match.str() << endl;
                }else{
                    motPasDansDictionnaire++;
                    //Si le motPasDansDictionnaire n'a pas deja été traité
                 //   if(!isWordInVector(wrongWords,match.str())){
                        wrongWords.push_back(match.str());
                    //}
                }
            }
        }
        nicoLaBite.close();
    } else {
        cout << "Fail to open file : " << "input_wiki" << endl;
    }

    for(string word : wrongWords){
        setCorrections(dictionary,word, corrections);
    }

    cout << "Mots totaux dans le dictionnaire : " << dictionary.size() << endl;


    for(string elem : corrections){
        cout << elem << endl;
    }

    cout << " nbr de mots faux : " << wrongWords.size();

    cout << " mot pas dans dico : " << motPasDansDictionnaire << endl;


    return 0;
}
