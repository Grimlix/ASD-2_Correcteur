#include <iostream>
#include <string>
#include <unordered_set>
#include <fstream>
#include <algorithm>
#include <regex>
#include <vector>
#include <chrono>
#include "TST.h"
#include "Dictionary.h"
#include "correction.h"


using namespace std;





int main() {

    ////////////////////////////////////////////////////////////////////////////////////////
    //                                                                                    //
    //  We chose stl structure unordered_set because it has O(1) complexity               //
    //  for reasearch. And we chose unordered_set instead of unordered_map                //
    //  because unordered_map insert the element when a research doesn't find an element  //
    //                                                                                    //
    ////////////////////////////////////////////////////////////////////////////////////////


    bool TST_MODE = false;

    string myDictionary = "dictionary.txt";
    //chrono
    auto start = std::chrono::high_resolution_clock::now();
    Dictionary dictionary = Dictionary(myDictionary, TST_MODE);
    auto afterDico = std::chrono::high_resolution_clock::now();
    auto dicoDuration = std::chrono::duration_cast<std::chrono::milliseconds>(afterDico - start);
    cout << "Time take for dictionary creation (ms) : " << dicoDuration.count() << endl;
    int motDansDictionnaire = 0;
    int motPasDansDictionnaire = 0;

    fstream file("input_simple.txt");
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

    //for each wrong word generate corrections in vector<string>corrections
    for(string word : wrongWords){
        setCorrections(dictionary,word, corrections);
    }

    //write corrections in output file
    std::ofstream output_file("./output_corrections.txt");
    std::ostream_iterator<std::string> output_iterator(output_file, "\n");
    std::copy(corrections.begin(), corrections.end(), output_iterator);

    auto afterCorrections = std::chrono::high_resolution_clock::now();
    auto correctionsDuration = std::chrono::duration_cast<std::chrono::milliseconds>(afterCorrections - afterDico);

    cout << "Time take for corrections creation (ms) : " << correctionsDuration.count() << endl;


    return 0;
}
