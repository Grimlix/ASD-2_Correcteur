#include <iostream>
#include <string>
#include <unordered_set>
#include <fstream>
#include <algorithm>
#include <regex>
#include <vector>

#include "TST.h"
#include "Dictionary.h"
#include "correction.h"


using namespace std;





int main() {


    //////////////////////////////////////////////////////////////////
    //                          FIRST PART                          //
    //////////////////////////////////////////////////////////////////

    //We chose stl structure unordered_set because it has O(1) complexity
    //for reasearch. And we chose unordered_set instead of unordered_map
    //because unordered_map insert the element when a research doesn't find an element

    bool TST_MODE = false;

    string myDictionary = "dictionary.txt";

    Dictionary dictionary = Dictionary(myDictionary, TST_MODE);

    int motDansDictionnaire = 0;
    int motPasDansDictionnaire = 0;

    fstream file("input_sh.txt");
    string line;
    vector<string> wrongWords;
    vector<string> corrections;

    if (file.is_open()) {

        std::regex words_regex("[a-z]+('[a-z]+)*");
        auto words_end = std::sregex_iterator();
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
                if(isWordInSet(dictionary, match.str())){
                    motDansDictionnaire++;
                }else{
                    motPasDansDictionnaire++;
                    wrongWords.push_back(match.str());

                }
            }
        }
        file.close();
    } else {
        cout << "Fail to open file : " << "input_wiki" << endl;
    }

    for(string word : wrongWords){
        setCorrections(dictionary,word, corrections);
    }


    for(string elem : corrections){
        cout << elem << endl;
    }

    cout << " nbr de mots faux : " << motPasDansDictionnaire;

    return 0;
}
