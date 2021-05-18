#include "Triesdef.h"

int main() {
    std::string wordList[] = {"abc", "abd", "ac", "acd", "car", "cat", "dcs"};
    Trie t = Trie();

    for (auto s : wordList) {
        t.insertWord(s);
    }

    t.displayTrie();
    t.serialiseTrie();

    return 0;
}