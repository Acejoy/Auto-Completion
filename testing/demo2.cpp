#include "Triesdef.h"

int main(){

    Trie t = Trie();
    t.loadWords("words2.txt");
    t.displayTrie();
    t.deleteWord("dcs");
    t.displayTrie();
    return 0;
}