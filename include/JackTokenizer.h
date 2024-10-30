#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <fstream>
#include <cctype>
#include <map>
#include <unordered_map>
#include <cstdlib>
#include <unordered_set>
#include <set>
#include <map>
#include <unordered_map>
#include <regex>
using namespace std;

//enum TokenType { KEYWORD, SYMBOL, IDENTIFIER, INT_CONST, STRING_CONST, NONE };


class JackTokenizer{
    private:
    ifstream infile;
    ofstream outfile;
    unordered_set<string> keywords = {"class", "constructor", "function", "method", "field", "static", 
                                            "var", "int", "char", "boolean", "void", "true", "false", 
                                            "null", "this", "let", "do", "if", "else", "while", "return"};

    unordered_set<char> symbols = {'{', '}', '(', ')', '[', ']', '.', ',', ';', '+', '-', '*', '/', '&', 
                                    '|', '<', '>', '=', '~'};
    
    string trim(string& s);


    string currentToken;
    //TokenType currentTokenType;

    
    int callCount;
    vector<string> split(string& s, char delim);
    bool isStringConst(string s);
    bool isIntegerConst(string s);
    bool isIdentifier(string s);

    public:
    //Constructor
    JackTokenizer(string filename);
    bool hasMoreTokens();
    string advance();
    vector<string> tokensList(string line);

    string tokenType(string s); //the token-type of the current token
    vector<string> tokens;

    string fileContent;
    string keyWord();
    string symbol();
    string identifier();
    string intVal();

};
