/*-------------------------------------------
Program 2: Search Engine
Course: CS 251, Fall 2023, UIC
System: Visual Studio Code
Author: Aleena Mehmood
------------------------------------------- */

#pragma once

#include <iostream>
#include <string>
#include <set>
#include <map>
#include <sstream>
#include <fstream>
#include <algorithm>
using namespace std;


// desciption: takes in a whitespace-separated string of characters that appears in the body text and 
// returns a "cleaned" version of that token, ready to be stored in the index
// "cleaned" means trimmed leading/trailing whitespace; removing punctuation not apart of word; lowercase
// edge case: Return the empty string if the token does not contain at least one letter
// parameter: string to be cleaned
// return: string in the cleaned form
string cleanToken(string s) {
    string cleanedString = "";
    size_t numOfLetters = 0;

    // remove leading whitespace/puncuation
    size_t sBegin = 0;
    while(sBegin < s.length() && (ispunct(s.at(sBegin)) || isspace(s.at(sBegin)))){
        sBegin ++;
    }

    // remove trailing whitespace/puncuation
    size_t sEnd = s.length() - 1;
    while((sEnd >= sBegin) && (ispunct(s.at(sEnd)) || isspace(s.at(sEnd)))){
        sEnd--;
    }

    //loop through string without leading/trailing whitespace/puncuation and store into new var
    for (int i = sBegin; i <= sEnd; i++){
        cleanedString += tolower(s.at(i));
    }

    // if there is not at least one letter in the string, return empty string
    for (char c : s){
        if (isalpha(c)){
            numOfLetters ++;
        }
    }
    if (numOfLetters == 0){
        cleanedString = "";
    }

    return cleanedString; 
}

// desciption: extracts the set of unique tokens from the body text.
// parameter: a string containing the body text from a single web page
// return:  a set of the unique cleaned tokens that appear in that body text
set<string> gatherTokens(string text) {
    set<string> tokens;
    istringstream ss(text);
    string word;
    string cleanedWord;

    cleanToken(text);

    while(ss>>word){
        cleanedWord = cleanToken(word);
        if (cleanedWord != ""){
            tokens.insert(cleanedWord);
        }
    }
    return tokens; 
}

// desciption:  reads the content from the file and processes it into an inverted index.
// parameter 1: the name of the database file of the web page data
// parameter 2:  the map to be populated with data for the inverted index.
// return:  the number of documents processed from the database file.
int buildIndex(string filename, map<string, set<string>>& index) {
    
    ifstream inFS;
    inFS.open(filename);
    
    if (!inFS.is_open()){
        cout << "**file not found" << endl;
        return 1; 
    }

    string URL;
    string fileContents;
    set<string> tempSet;
    int docCount = 0;
    
    while(!inFS.eof()){
        getline(inFS, URL);
        docCount++;
        getline(inFS, fileContents);

        tempSet = gatherTokens(fileContents);

        for(auto elem : tempSet){
            if (!URL.empty()){
                index[elem].emplace(URL);
            }
        }
    }
    return docCount - 1;
}

// desciption: helper function to apply modifer
// parameter 1: set to return with modifiers applied
// parameter 2: temp set to store URLs before modifiers
// parameter 3: modifier provided by user
// return: no return
void applyMod(set<string>& result, const set<string>& tempURL, char modifier){
    if (modifier == '+'){
        if (result.empty()){
            result = tempURL;
        } else{
            set<string> tempIntersection;
            set_intersection(result.begin(),result.end(),
                            tempURL.begin(),tempURL.end(),
                            inserter(tempIntersection, tempIntersection.begin()));
        result = tempIntersection;
        }

    } else if (modifier == '-'){
        set<string> tempDifference;
        set_difference(result.begin(),result.end(),
                        tempURL.begin(),tempURL.end(),
                        inserter(tempDifference, tempDifference.begin()));
        result = tempDifference;

    } else if (modifier == ' '){
        set<string> tempUnion;
        set_union(result.begin(),result.end(),
                        tempURL.begin(),tempURL.end(),
                        inserter(tempUnion, tempUnion.begin()));
        result = tempUnion;
    }

}

// desciption: implements saerch algorithm
// parameter 1: the map of the inverted index.
// parameter 2: can either be a single search term or a compound sequence of multiple terms
// For a single search term, matches are the URLs of the web pages that contain the specified term.
// A sequence of terms is handled as a compound query, where the matches from the individual terms are synthesized into one combined result.
// space: unionized. | +: intersected | -:difference
// return: updated set with query results
set<string> findQueryMatches(map<string, set<string>>& index, string sentence) {
    set<string> result;
    istringstream ss(sentence);
    string word;

    while(ss>>word){
        char modifier = ' ';

        // store modifier then remove:
        if (!word.empty() && word.at(0) == '+' || word.at(0) == '-'){
            modifier = word.at(0);
            word = word.substr(1);
        }

        string cleanedWord = cleanToken(word);

        //create temp set to store URLs before modifiers:
        set<string> tempURL = index[cleanedWord];

        applyMod(result, tempURL, modifier);
    }
    
    return result;
}

// desciption: user interface for search engine
// parameter: database file to be used
// return: no return
void searchEngine(string filename) {
    int docCount = 0;
    int numTokens = 0;
    string querySentence;
    map<string, set<string>> searchIndex;

    docCount = buildIndex(filename, searchIndex);
    numTokens = searchIndex.size();

    cout << "Stand by while building index..." << endl;

    cout << "Indexed " << docCount << " pages containing " << numTokens << " unique terms" << endl;

    cout << "Enter sentence you would like to search (press enter to quit): ";
    // cout << "Enter query sentence (press enter to quit): ";

    while (getline(cin, querySentence)){
        if (querySentence.empty()){
            break;
        }

        set<string> foundMatches = findQueryMatches(searchIndex, querySentence);
        cout << "Found "<< foundMatches.size() << " matching pages" << endl;

        for (auto match : foundMatches){
            cout << match << endl;
        }

        cout << "Enter query sentence (press enter to quit): ";
    }

     cout << "Thank you for searching!" << endl;
}