#include<iostream>
#include<fstream>

int main(){

    std::ifstream wordsFile;
    wordsFile.open("words.txt", std::ios::in);

    if(!wordsFile) {
        std::cout<<"No such file exists.\n";
    } else {
        std::cout<<"File opened successfully.\n";
        
        char c;
        std::string s;
        int count = 0;
        while(!wordsFile.eof()) {
            wordsFile>>s;
            std::cout<<s;
            count++;
            //std::cout<<c;
        }
        std::cout<<count<<std::endl;
        wordsFile.close();
    }
    
    return 0;
}