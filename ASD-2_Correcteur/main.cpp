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
void fillUnorderedSet(std::unordered_set<string>& set, string file, char delim) {
   ifstream myDictionary(file);
   string line;

   if (myDictionary.is_open()) {
      //for each word in dictionary
      while (getline(myDictionary, line, delim)) {

         //lowercaps the word
         transform(line.begin(), line.end(), line.begin(),
                 [](unsigned char c) {
                    return tolower(c); });

         //remove non alpha of the words but leave '\''
         int i = 0;
         int len = line.length();

         while (i < len) {
            if (!isalpha(line[i]) && line[i] != '\'') {
               line.erase(i, 1);
               len--;
            } else {
               i++;
            }
         }

         set.insert(line);
      }
      myDictionary.close();
   } else {
      cout << "Fail to open file : " << file << endl;
   }
}

bool isWordInSet(std::unordered_set<string>& set, string word) {
   for (string wordInSet : set) {
      if (!word.compare(wordInSet)) {
         return true;
      }
   }
   return false;
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


   std::unordered_set<string> input_sh;
   string myInput_sh = "input_sh.txt";
   fillUnorderedSet(input_sh, myInput_sh, ' ');
   
   
   unordered_set<string>::const_iterator it = input_sh.begin();
   unordered_set<string>::const_iterator got;
   
   cout << "Mots totaux : " << input_sh.size() << endl;
   
   int motDansDictionnaire = 0;
   int motPasDansDictionnaire = 0;
   string value;
   for(it; it != input_sh.end(); it++){
      got = dictionary.find(*it);
      
      if(got == input_sh.end()){
         //cout << *it << " n'est pas dans le dictionnaire" << endl;  
         motPasDansDictionnaire++;
      }else{
         //cout << *it << " est dans le dictionnaire." << endl;
         motDansDictionnaire++;
      }

   }


   cout << "Mots dans le dictionnaire : " << motDansDictionnaire << endl;
   cout << "Mots pas dans le dictionnaire : " << motPasDansDictionnaire << endl;




   /*
   ifstream myFile("input_wikipedia.txt");
   string line;
   int j = 0;
   if(myFile.is_open()){
       while(getline(myFile,line)){
           j++;
           cout << "fuck ASD " << endl;bool isWordInSet(std::unordered_set<string>& set,string word){
   for(string wordInSet: set){
       if(!word.compare(wordInSet)){
           return true;
       }
   }
   return false;
   }
       }
   }else{
       cout << "Fail to op file : " << line << endl;
   }
    */

   /*
       std::unordered_set<string> input_sh;
       string myInput_sh = "input_sh.txt";
       fillUnorderedSet(input_sh,myInput_sh, ' ');

       for(string word : dictionary){
           cout << word << endl;
       }

       cout << input_sh.size() << endl;*/


   return 0;
}
