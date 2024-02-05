/*-------------------------------------------
Program 2: Search Engine
Course: CS 251, Fall 2023, UIC
System: Visual Studio Code
Author: Aleena Mehmood
------------------------------------------- */

#include "search.h"
using namespace std;


// function prototypes
bool testCleanToken();
void RunAllTests();


int main() {
    
    string filename;
    cout << "Files to chose from: cplusplus.txt; stackoverflow.txt; tiny.txt; uiccs-news.txt; wiki-uni.txtn" << endl;
    cout << "   Enter file name:" << endl;
    
    getline(cin, filename);
    searchEngine(filename);

    ///UNCOMMENT TO RUN UNIT TESTING 
    // RunAllTests(); 

    return 0;
}

// tests the removal of leading/trailing punctuation/whitespace 
bool testCleanToken1() {
  string ans = "hello";
    int pass = 0, fail = 0;
    
    ans == cleanToken(".hello") ? ++pass : ++fail;
    ans == cleanToken("...hello") ? ++pass : ++fail;
    ans == cleanToken("????hello???????") ? ++pass : ++fail;
    ans == cleanToken("            !hello!                ") ? ++pass : ++fail;
    
    return 0 == fail;
}

// tests returning empty string when no strings are in sentence
bool testCleanToken2() {
    string ans = "";
    int pass = 0, fail = 0;
    
    ans == cleanToken("123452") ? ++pass : ++fail;
    ans == cleanToken("!*&^#$%&      ") ? ++pass : ++fail;

    return 0 == fail;
}

// tests converting strings to lowercase
bool testCleanToken3() {
    string ans = "i am lowercase";
    int pass = 0, fail = 0;
    
    ans == cleanToken("I AM LOWERCASE") ? ++pass : ++fail;
    ans == cleanToken("    i Am LoWeRcAsE      ?") ? ++pass : ++fail;

    return 0 == fail;
}

// tests not removing punctuation within a string 
bool testCleanToken4() {
    string ans = "would've could've should've";
    int pass = 0, fail = 0;
    
    ans == cleanToken("????WoUlD'vE cOuLd'Ve ShOuLd'Ve ???????") ? ++pass : ++fail;
    ans == cleanToken("@#@@@@@!@@'@^@@@@ would've could'Ve Should've ??$%^&%$#@") ? ++pass : ++fail;
    ans == cleanToken("  !   would've could've should've     ? ") ? ++pass : ++fail;

    return 0 == fail;
}

// tests gathering tokens in general
bool testGatherTokens1(){
    int pass = 0, fail = 0;

    set<string> tokens = gatherTokens("to be or not to be");
    set<string> answers = {"to", "be", "or", "not"};

    tokens.size() == answers.size() ? ++pass : ++fail;
    tokens == answers ? ++pass : ++fail;

    return 0 == fail;
}

// tests only gathering unique tokens
bool testGatherTokens2(){
    int pass = 0, fail = 0;

    set<string> tokens = gatherTokens("no no repeats repeats please please");
    set<string> answers = {"no", "repeats", "please"};
    
    tokens.size() == answers.size() ? ++pass : ++fail;
    tokens == answers ? ++pass : ++fail;

    return 0 == fail;
}

// tests gathering lowercase
bool testGatherTokens3(){
    int pass = 0, fail = 0;

    set<string> tokens = gatherTokens("MAKE ME LOWERCASE plEaSe PLEASE PLEASE PLEASE");
    set<string> answers = {"make", "me", "lowercase", "please"};
    
    tokens.size() == answers.size() ? ++pass : ++fail;
    tokens == answers ? ++pass : ++fail;

    return 0 == fail;
}

// tests not gathering leading puncuation and whitespace
bool testGatherTokens4(){
    int pass = 0, fail = 0;

    set<string> tokens = gatherTokens("!!??    can YOu  Please reMove PunCt's From me       ???????");
    set<string> answers = {"can", "you", "please", "remove" , "punct's", "from", "me"};
    
    tokens.size() == answers.size() ? ++pass : ++fail;
    tokens == answers ? ++pass : ++fail;

    return 0 == fail;
}

// test tiny.txt
bool testBuildIndex1(){
    int pass = 0, fail = 0;

    string filename = "tiny.txt";
    map<string, set<string>> indexTest;

    int docCount = buildIndex(filename, indexTest);

    docCount == 4 ? ++pass : ++fail;
    indexTest["fish"].size() == 2 ? ++pass : ++fail;

    return 0 == fail;
}

// test cplusplus.txt
bool testBuildIndex2(){
    int pass = 0, fail = 0;

    string filename = "cplusplus.txt";
    map<string, set<string>> indexTest;

    int docCount = buildIndex(filename, indexTest);

    docCount == 86 ? ++pass : ++fail;

    return 0 == fail;
}

// test uiccs-news.txt
bool testBuildIndex3(){
    int pass = 0, fail = 0;

    string filename = "uiccs-news.txt";
    map<string, set<string>> indexTest;

    int docCount = buildIndex(filename, indexTest);

    docCount == 85 ? ++pass : ++fail;

    return 0 == fail;
}

// test wiki-uni.txt
bool testBuildIndex4(){
    int pass = 0, fail = 0;

    string filename = "wiki-uni.txt";
    map<string, set<string>> indexTest;

    int docCount = buildIndex(filename, indexTest);

    docCount == 148 ? ++pass : ++fail;

    return 0 == fail;
}

// test stackoverflow.txt
bool testBuildIndex5(){
    int pass = 0, fail = 0;

    string filename = "stackoverflow.txt";
    map<string, set<string>> indexTest;

    int docCount = buildIndex(filename, indexTest);

    docCount == 13 ? ++pass : ++fail;
    indexTest["to"].size() == 10 ? ++pass : ++fail;

    return 0 == fail;
}

// sample map for testing findQueryMatches
map<string, set<string>> sampleIndexMap() {
    map<string, set<string>> index;
    
    index["apple"] = {"file1", "file3"};
    index["banana"] = {"file1", "file2"};
    index["cherry"] = {"file2", "file3"};
    index["date"] = {"file3"};
    index["orange"] = {"file1", "file2", "file3"};
    index["watermelon"] = {"file1", "file2"};
    
    return index;
}

// testing single query:
bool testfindQueryMatches1(){
    int pass = 0, fail = 0;

    map<string, set<string>> sampleIndex = sampleIndexMap();
    string sentence = "apple";
    set<string> result = findQueryMatches(sampleIndex, sentence);

    result == sampleIndex["apple"] ? ++pass : ++fail;

    return 0 == fail;
}

// testing single query:
bool testfindQueryMatches2(){
    int pass = 0, fail = 0;

    map<string, set<string>> sampleIndex = sampleIndexMap();
    string sentence = "cherry";
    set<string> result = findQueryMatches(sampleIndex, sentence);

    result == sampleIndex["cherry"] ? ++pass : ++fail;

    return 0 == fail;
}

// testing union (' '):
bool testfindQueryMatches3(){
    int pass = 0, fail = 0;

    map<string, set<string>> sampleIndex = sampleIndexMap();
    string sentence = "cherry date";
    set<string> result = findQueryMatches(sampleIndex, sentence);

    result == sampleIndex["cherry"] ? ++pass : ++fail;

    return 0 == fail;
}

// testing union (' '):
bool testfindQueryMatches4(){
    int pass = 0, fail = 0;

    map<string, set<string>> sampleIndex = sampleIndexMap();
    string sentence = "watermelon orange";
    set<string> result = findQueryMatches(sampleIndex, sentence);

    result == sampleIndex["orange"] ? ++pass : ++fail;

    return 0 == fail;
}

// testing intersection ('+'):
bool testfindQueryMatches5(){
    int pass = 0, fail = 0;

    map<string, set<string>> sampleIndex = sampleIndexMap();
    string sentence = "watermelon +orange";
    set<string> result = findQueryMatches(sampleIndex, sentence);

    result == sampleIndex["watermelon"] ? ++pass : ++fail;

    return 0 == fail;
}

// testing intersection ('+'):
bool testfindQueryMatches6(){
    int pass = 0, fail = 0;

    map<string, set<string>> sampleIndex = sampleIndexMap();
    string sentence = "banana +cherry";
    set<string> result = findQueryMatches(sampleIndex, sentence);

    result == set<string>{"file2"} ? ++pass : ++fail;

    return 0 == fail;
}

// testing difference ('-'):
bool testfindQueryMatches7(){
    int pass = 0, fail = 0;

    map<string, set<string>> sampleIndex = sampleIndexMap();
    string sentence = "orange -date";
    set<string> result = findQueryMatches(sampleIndex, sentence);

    result == set<string>{"file1", "file2"} ? ++pass : ++fail;

    return 0 == fail;
}

// testing difference ('-'):
bool testfindQueryMatches8(){
    int pass = 0, fail = 0;

    map<string, set<string>> sampleIndex = sampleIndexMap();
    string sentence = "apple -watermelon";
    set<string> result = findQueryMatches(sampleIndex, sentence);

    result == set<string>{"file3"} ? ++pass : ++fail;

    return 0 == fail;
}

// testing compund:
bool testfindQueryMatches9(){
    int pass = 0, fail = 0;

    map<string, set<string>> sampleIndex = sampleIndexMap();
    string sentence = "orange cherry -date";
    set<string> result = findQueryMatches(sampleIndex, sentence);

    result == set<string>{"file1", "file2"} ? ++pass : ++fail;

    return 0 == fail;
}

// testing compund 2:
bool testfindQueryMatches10(){
    int pass = 0, fail = 0;

    map<string, set<string>> sampleIndex = sampleIndexMap();
    string sentence = "watermelon orange -banana";
    set<string> result = findQueryMatches(sampleIndex, sentence);

    result == set<string>{"file3"} ? ++pass : ++fail;

    return 0 == fail;
}


void RunAllTests(){
    int pass = 0;
    int fail = 0;

    (testCleanToken1()) ? pass++ : fail++;
    (testCleanToken2()) ? pass++ : fail++;
    (testCleanToken3()) ? pass++ : fail++;
    (testCleanToken4()) ? pass++ : fail++;

    (testGatherTokens1()) ? pass++ : fail++;
    (testGatherTokens2()) ? pass++ : fail++;
    (testGatherTokens3()) ? pass++ : fail++;
    (testGatherTokens4()) ? pass++ : fail++;

    (testBuildIndex1()) ? pass++ : fail++;   
    (testBuildIndex2()) ? pass++ : fail++; 
    (testBuildIndex3()) ? pass++ : fail++;
    (testBuildIndex4()) ? pass++ : fail++;
    (testBuildIndex5()) ? pass++ : fail++;

    (testfindQueryMatches1()) ? pass++ : fail++;  
    (testfindQueryMatches2()) ? pass++ : fail++;
    (testfindQueryMatches3()) ? pass++ : fail++;
    (testfindQueryMatches4()) ? pass++ : fail++;
    (testfindQueryMatches5()) ? pass++ : fail++;
    (testfindQueryMatches6()) ? pass++ : fail++;
    (testfindQueryMatches7()) ? pass++ : fail++;
    (testfindQueryMatches8()) ? pass++ : fail++;
    (testfindQueryMatches9()) ? pass++ : fail++;
    (testfindQueryMatches10()) ? pass++ : fail++;

    cout << "Test cases passed: " << pass << endl;
    cout << "Test cases failed: " << fail << endl;
}
