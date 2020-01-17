#include <iostream>
#include <string>
#include <unordered_set>
#include <fstream>
#include <algorithm>

using namespace std;


/**
 * Fill an ordered set with lines from a text file
 * @param set set to fill with lines
 * @param file file from which get lines
 */
void fillUnorderedSet(std::unordered_set<string>& set,string file, char delim){
    ifstream myDictionary(file);
    string line;

    if(myDictionary.is_open()) {
        while (getline(myDictionary,line, delim)) {

            transform(line.begin(), line.end(), line.begin(),
                           [](unsigned char c){ return tolower(c); });
            //line.erase(remove_if(line.begin(), line.end(), [](char c) { return !isalpha(c); } ), line.end());

            set.insert(line);
        }
        myDictionary.close();
    }else{
        cout <<"Fail to open file : " << file << endl;
    }
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
    fillUnorderedSet(dictionary,myDictionary, '\n');

    for(string word : dictionary){
        //cout << word << endl;
    }

    cout << dictionary.size() << endl;
    
    std::unordered_set<string> input_sh;
    string myInput_sh = "input_sh.txt";
    fillUnorderedSet(input_sh,myInput_sh, ' ');

    for(string word : dictionary){
        //cout << word << endl;
    }
    
    cout << input_sh.size() << endl;
    
    
    
    
    
    return 0;
}
