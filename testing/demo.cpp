#include "../Triesdef.h"

int main() {
    Trie t = Trie();
    t.loadWords("test2.txt");    
    
    t.displayTrie();
    t.serialiseTrie();

    return 0;
}