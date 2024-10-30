#include <iostream>
#include "JackTokenizer.h"

int main(){
    JackTokenizer tokenize("Prog.jack");
    while(tokenize.hasMoreTokens()){
        cout << tokenize.advance() << endl;
    }

}