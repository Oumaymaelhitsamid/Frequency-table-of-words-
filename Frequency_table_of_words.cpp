/*******************************
 * Lab 3: exercise 1            *
 * Frequency table of words     *
 *******************************/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>   //std::pair
#include <fstream>
#include <cassert>

#include<algorithm>

#include<iomanip>
#include<cctype>
#include<iterator>
/*******************************
 * 1. Declarations              *
 ********************************/


using pair = std::pair<std::string, int>;
// To get the lowercase form  function 
void toLower(std::string& word) {
    std::for_each(word.begin(), word.end(), [](char& c) {
        c = ::tolower(c);
        });
}
// Function to detect punctuation signs
struct isNotSpecChar {
    bool operator()(char& c) {

        std::string specChar = ".,!?:/();\"";

        if (specChar.find(c) != std::string::npos) {
            return false;
        }
        else {
            return true;
        }
    }
};
// function to remove the punctuation signs
std::string removeSpecChar(std::string& word) {
    std::string temp;
    std::copy_if(word.begin(), word.end(), std::back_inserter(temp), isNotSpecChar());
    return temp;
}

struct displayWord {
    void operator()(pair w) {
        std::cout << std::left << std::setw(25) << w.first << w.second << std::endl;
    }
};

// A function to test the tables created by the program
void test(const std::map<std::string, int>& t, const std::vector<std::pair<std::string, int>>& v,
          const std::string& file_name, int n);

/*******************************
 * 2. Main function             *
 *******************************/

bool sortByFreq(const pair& a, const pair& b) {
    return a.second > b.second;
}
void print(const pair& a) {
    std::cout << a.first << " " << a.second << std::endl;
}
int main() {
    std::map<std::string, int> frequencyTable;
    std::string word;
    std::string wordNoSpec;
    int numberOfWords = 0;
    std::string name;
    std::cout << "Text file: ";
    std::cin >> name;

    std::ifstream in_File{name};

    if (!in_File) {
        std::cout << "Could not open input file!!\n";
        return 0;

    }
    //read words
    while (in_File >> word) { //map create words automatically
        toLower(word);
        word = removeSpecChar(word);

       // auto it = frequencyTable.find(word);

        //if (it != frequencyTable.end()) {
            frequencyTable[word]++;
        //}
        //else {
            //frequencyTable.insert({ word, 1 });
       // }

        numberOfWords++;
    }
    std::map<std::string, int> table;
    int counter{0};  // to count total number of words read from the input file

    //ADD CODE to build table
   


    std::vector<std::pair<std::string, int>> freq;

    //ADD CODE to build vector freq
    std::vector<pair> sortedFrequency(frequencyTable.size());

    std::copy(frequencyTable.begin(), frequencyTable.end(), sortedFrequency.begin());
    std::sort(sortedFrequency.begin(), sortedFrequency.end(), sortByFreq);

    std::cout << std::endl << std::endl << "Frequency table sorted by frequency..." << std::endl;
    std::for_each(sortedFrequency.begin(), sortedFrequency.end(), print);


    /* ************** Testing **************** */

    test(table, freq, name, counter);
}


/*******************************
 * 2. Test implementation      *
 * Do not modify               *
 *******************************/

void test(const std::map<std::string, int>& t, const std::vector<std::pair<std::string, int>>& v,
          const std::string& file_name, int n) {

    std::ifstream file{file_name};

    // Test if stream is in good state
    assert(bool(file) == true);

    std::map<std::string, int> result1;
    std::string word;
    int counter{0};
    int total{0};

    // load expected frequency table sorted alphabetically
    while (file >> word >> counter && counter > 0) {
        result1[word] = counter;
        total += counter;
    }
	
	/*
    * uppgift1_kort: 69 words
    * uppgift1.txt: 1063 words
    */

    assert(total == n);  // test if total number of words is correct
    assert(t == result1);

    std::vector<std::pair<std::string, int>> result2;

    // load expected frequency table sorted by frequence
    //while (file >> word >> counter) {
        //result2.push_back(std::pair{word, counter});
    //}

    assert(v == result2);

    std::cout << "\nPassed all tests successfully!!\n";
}
