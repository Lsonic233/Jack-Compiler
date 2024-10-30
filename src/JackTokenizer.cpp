#include "JackTokenizer.h"

string JackTokenizer::trim(string& s){
    string result;
    s.erase(std::remove(s.begin(), s.end(), '\r'), s.end());
    size_t pos = s.find("//");
    if(pos!=string::npos) result = s.substr(0,pos);
    else result = s;

    size_t start = 0;
    while(start!=s.length() && isspace((unsigned char)(s[start])))
    {
        start++;
    }
    result = result.substr(start);
    size_t end = result.find_last_not_of(' ');
    if(end!=string::npos) result = result.substr(0,end + 1);
    return result;
}

vector<string> JackTokenizer::split(string &str, char delim){
    vector<string> tokens;
    string token;
    istringstream s(str);
    while(getline(s, token, delim))
    {
        tokens.push_back(token);
    }
    return tokens;
}

bool JackTokenizer::isStringConst(string s){
    if(s.length()>=2 && s[0] == '"' && s[s.length()-1]=='"'){
        for(int i=1; i < s.length()-1; i++){
            if(s[i]=='"' || s[i]=='\n'){
                return false;
            }
        }
        return true;
    }
    return false;
}
bool JackTokenizer::isIntegerConst(string s){
    if(s.empty())return false;
    for(char c : s){
        if(!isdigit(c))return false;
    }
    int num = stoi(s);
    if(num>=0 && num<=32767) return true;
    else return false;
}

bool JackTokenizer::isIdentifier(string s){
    if(isdigit(s[0])) return false;
    regex pattern("^[a-zA-Z_][a-z0-9A-Z_]*");
    if(regex_match(s, pattern)) return true;
    else return false;
}

JackTokenizer::JackTokenizer(string filename){
    ifstream infile(filename);
    string outfilename = split(filename, '.')[0] + ".xml";  
    ofstream outfile(outfilename);
    string input;
    while(getline(infile, input)){
        fileContent += trim(input);
    }
    callCount=0;
    tokens = tokensList(fileContent);
}

string JackTokenizer::tokenType(string s){
        if(keywords.find(s)!=keywords.end()){
        //s is a keyword
            return "KEYWORD";
        }
        else if(s.length()==1 && symbols.find(s[0])!=symbols.end()){
            //s is a symbol
            return "SYMBOL";
        }
        else if(isStringConst(s)){
            return "STRING_CONST";
        }
        else if(isIntegerConst(s)){
            return "INT_CONST";
        }
        else if(isIdentifier(s)){
            return "IDENTIFIER";
        }
        return "NONE";
}

vector<string>JackTokenizer::tokensList(string input){
    vector<string> tokens;
    input = trim(input);
    vector<string> initial = split(input, ' ');
    for(string s : initial){
        if(tokenType(s)!="NONE"){
            tokens.push_back(s);
        }
        else{
            string t;
            t+=s[0];
            for(int i=0; i < s.length()-1; i++){
                if(tokenType(t+s[i+1])!="NONE"){
                    t+=s[i+1];
                }
                else{
                    tokens.push_back(t);
                    t=s[i+1];
                }
            }
        }
    }
    return tokens;
}

bool JackTokenizer::hasMoreTokens(){
    if(tokens.size()>0 && callCount<tokens.size()){
        return true;
    }
    return false;
}

string JackTokenizer::advance(){
    return tokens[callCount++];
}