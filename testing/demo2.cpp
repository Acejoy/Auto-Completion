#include <fstream>
#include<iostream>
#include "../Triesdef.h"

int main(){

    std::ifstream s("test.txt");
    std::string word;

    while(!s.eof()) {
        getline(s, word, ' ');

        try{
            std::cout<<stoi(word)<<'\n';
        } catch(...) {
            // std::cerr<<word<<std::endl;
        }
    }

    s.close();
    return 0;
}