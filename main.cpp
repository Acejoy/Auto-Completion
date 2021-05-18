#include "Triesdef.h"

int main() {
    
    std::string welcome =
        "=======================WELCOME==========================";
    std::string menu =
        "\nOptions:\
                    \n1. Load words from word file\
                    \n2. Add a word\
                    \n3. Display Trie\
                    \n4. Delete Word\
                    \n5. Get Suggestions\
                    \n6. Exit\n";

    std::cout<<welcome<<std::endl;

    Trie t = Trie("myTrie.txt");
    std::cout<<"Loading serialised Trie ......\n";
    std::cout << menu;
    std::cout << "====>Enter the option\n>>";


    int option;
    bool running = true;

    while (running) {
        std::cin >> option;

        switch (option) {
            case 1: {
                std::string wordFilename;
                std::cout << "Enter the name of txt file(without extension)>>";
                std::cin >> wordFilename;
                std::cout << "Loading Words............\n";

                delete &t;
                t = Trie();
                bool success = t.loadWords(wordFilename + ".txt");

                if (success) {
                    std::cout << "Loaded Words!!!\n";
                }
                break;
            }
            case 2: {
                std::cout << "Enter the word\n>>";
                std::string word;
                std::cin >> word;
                t.insertWord(word);
                break;
            }
            case 3: {
                t.displayTrie();
                break;
            }
            case 4: {
                std::cout << "Enter the word\n>>";
                std::string word;
                std::cin >> word;
                t.deleteWord(word);
                break;
            }
            case 5: {
                std::cout << "Enter the word\n>>";
                std::string word;
                std::cin >> word;
                t.getSuggestions(word);
                break;
            }
            case 6: {
                running = false;
                t.serialiseTrie();
                break;
            }
            default: {
                std::cout << "Enter valid option\n";
                break;
            }
        }

        if (running) {
            std::cout << menu + "====>Enter the option\n>>";
        }
    }
}