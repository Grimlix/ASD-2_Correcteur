/*
 * File:   main.cpp
 * Author: Gianinetti Lucas, Hungerbühler Nicolas, Wojciechowski Cassandre
 * Created on 18. janvier 2020
 *
 * Description: File in which we test our dictionary corrector with 2 differents data structure and a test txt file
 *
 * Remark:We chose stl structure unordered_set because it has O(1) complexity
 *        for reasearch. And we chose unordered_set instead of unordered_map
 *        because unordered_map insert the element when a research doesn't find an element
 *
 *
 */

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

// calculate execution time of corrections from a specific filename with a specific dictionary
void createOutputCorrectionsFile(string filename, Dictionary& dictionary){
    fstream file(filename);
    vector<string> corrections;

    string outputFilename = "out" + filename.substr(2,filename.length());

    auto beforCorrections = std::chrono::high_resolution_clock::now();

    generateCorrectionFromFile(file,corrections,dictionary);

    std::ofstream output("./" + outputFilename);
    std::ostream_iterator<std::string> output_iterator(output, "\n");
    std::copy(corrections.begin(), corrections.end(), output_iterator);

    auto afterCorrections = std::chrono::high_resolution_clock::now();
    auto correctionDuration = std::chrono::duration_cast<std::chrono::microseconds>(afterCorrections - beforCorrections);

    cout << "Time taken to generate corrections of " << filename << " into file " << outputFilename
    << " : " << correctionDuration.count() << " [μs]" << endl;
}


int main() {



    //boolean to chose which data structure we want to use for our dictionary
    //true -> Ternary Search Tree
    //false -> unordered_set<string>
    bool TST_MODE = false;

    //File from which we take our words to implement dictionary
    string myDictionary = "dictionary.txt";

    //chrono
    auto start = std::chrono::high_resolution_clock::now();

    //we create a wrapper for the data_structure
    Dictionary dictionary = Dictionary(myDictionary, TST_MODE);

    auto afterDico = std::chrono::high_resolution_clock::now();
    auto dicoDuration = std::chrono::duration_cast<std::chrono::microseconds>(afterDico - start);

    cout << "Time taken to create dictionary : " << dicoDuration.count() << " [μs] "<< endl;

    createOutputCorrectionsFile("input_wikipedia.txt",dictionary);
    createOutputCorrectionsFile("input_sh.txt",dictionary);
    createOutputCorrectionsFile("input_lates.txt",dictionary);
    createOutputCorrectionsFile("input_simple.txt",dictionary);




    return 0;
}
