/*

An implementation of Trie
*/
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <queue>
#include <sstream>
#include <stack>
#include <vector>

class TrieNode {
    // class for node of Trie
    // each node contains
    // 1.the mapping of letter to node and
    // 2.whether the current node is the end of word or not.

   private:
    std::map<char, TrieNode *> children;
    bool endOfWord;

   public:
    // simple constructor for class
    TrieNode() { endOfWord = false; }

    // adds a link for a letter in current node
    TrieNode *setChild(char letter) {
        TrieNode *newNode = new TrieNode();
        children.insert(std::pair<char, TrieNode *>(letter, newNode));
        return newNode;
    }

    // sets EOW(end of word val) depending upon
    // if current node is end of word or not.
    void setEOW(bool val) { endOfWord = val; }

    // fetches EOW value
    bool getEOW() { return endOfWord; }

    // returns the node associated to the letter
    // returns nullptr if no such letter exists
    TrieNode *getChild(char letter) {
        if (children.find(letter) != children.end()) {
            return children[letter];
        } else {
            return nullptr;
        }
    }

    // removing the corresponding child node
    // of current node.
    void removeChild(char letter) {
        delete children[letter];
        children.erase(letter);
    }

    // returns true if current node
    // has any children
    bool hasChildren() {
        if (children.size() == 0) {
            return false;
        } else {
            return true;
        }
    }

    // gets all the letters that are the children
    // of current node.
    std::vector<char> getChildrenKeys() {
        std::vector<char> keys;

        for (auto element : children) {
            keys.push_back(element.first);
        }

        return keys;
    }

    // gets the number of children
    // of current node.
    int getNumOfChildren() { return children.size(); }
};

class Trie {
    // class for the actual trie

   private:
    // the root of the trie tree.
    TrieNode *root;

   public:
    // constructor class
    Trie() {
        root = new TrieNode();
        root->setEOW(false);
    }

    Trie(std::string filename) {
        root = new TrieNode();
        root->setEOW(false);

        std::ifstream trieFile(filename);

        if (!trieFile.is_open()) {
            std::cout
                << "No deserialisation occured as filename doesnt exist.\n";
        } else {
            deserialise(root, trieFile);
        }
    }

    void deserialise(TrieNode *node, std::ifstream &s) {
        char EOW;
        s.get(EOW);

        char numChildren;
        s.get(numChildren);

        if (EOW == '0') {
            node->setEOW(false);
        } else {
            node->setEOW(true);
        }

        int index = 0;
        char curLetter;

        while (index <(int) (numChildren - '0')) {
            s.get(curLetter);
            node->setChild(curLetter);
            deserialise(node->getChild(curLetter), s);
            index++;
        }
    }

    // insert word into Trie
    void insertWord(std::string word) {
        TrieNode *curNode = root;

        int wordLength = word.length();
        int index = 0;

        // finding the position for insertion of word
        // looking through nodes,if not present
        // creting new ones.
        while (index < wordLength) {
            char curLetter = word[index];
            TrieNode *childNode = curNode->getChild(curLetter);

            if (childNode == nullptr) {
                childNode = curNode->setChild(curLetter);
            }

            curNode = childNode;
            index++;
        }

        // setting EOW=True for cuurent node
        // to denote end of word
        curNode->setEOW(true);
    }

    void insertWordList(std::vector<std::string> wordList) {
        for (auto word : wordList) {
            insertWord(word);
        }
    }

    bool loadWords(std::string filename) {
        std::ifstream wordFile(filename);

        if (!wordFile.is_open()) {
            std::cout << "Couldnt load words file\n";
            return false;
        } else {
            std::vector<std::string> wordList;
            std::string word;

            while (!wordFile.eof()) {
                wordFile >> word;
                wordList.push_back(word);
            }

            insertWordList(wordList);
            return true;
        }
    }

    // check whether word exists in Trie
    bool wordExists(std::string word) {
        TrieNode *curNode = root;

        int wordLength = word.length();
        int index = 0;

        while (index < wordLength) {
            TrieNode *childNode = curNode->getChild(word[index]);

            if (childNode == nullptr) {
                return false;
            }
            curNode = childNode;
            index++;
        }

        return curNode->getEOW();
    }

    void deleteWord(std::string word) {
        // this method deletes a word from trie
        // the word may have a another word
        // as child, thus, the nodes for that word cant be removed
        // if no child we keep removing nodes
        // until we reach a node that has a child
        // or is end of a word.
        // removing nodes happen in the reverse order
        // meaning node farthest from root is removed first.

        // first, we reach the endofword for the word,
        // while storing the path nodes in stack.
        // if word doesnt exist, then print so.
        std::stack<TrieNode *> nodeStack;
        TrieNode *childNode, *curNode = root;

        int index = 0;
        int wordLength = word.length();

        while (index < wordLength) {
            nodeStack.push(curNode);
            childNode = curNode->getChild(word[index]);

            if (childNode == nullptr) {
                std::cout << "No such word exixts\n";
                return;
            }

            curNode = childNode;
            index++;
        }

        // curNode has the value of EOW for
        // this current word
        // setting EOW for this node to false,
        // to denote removal of word
        curNode->setEOW(false);

        // if last node has children,
        // then we cant delete any node.
        if (!curNode->hasChildren()) {
            int index = 0;
            curNode = nodeStack.top();
            nodeStack.pop();

            while (!nodeStack.empty()) {
                std::cout << "deleting letter....\n"
                          << word[wordLength - index - 1] << std::endl;
                curNode->removeChild(word[wordLength - index - 1]);
                index++;

                // if that node has EOW==true or hasChildren>0
                // then other we cant delete nodes anymore.
                // as haschildren>0 means other nodes are linked to it.
                // and EOW==true means this node is end of word for some word
                if (curNode->getEOW() || curNode->getNumOfChildren() > 0) {
                    break;
                } else {
                    curNode = nodeStack.top();
                    nodeStack.pop();
                }
            }
        }
    }

    // getting a word, and displaying
    // all the words in trie that have that word
    // as a prefix.
    void getSuggestions(std::string word) {
        // traverse the trie,until the given word
        // is exhausted. The node reached can be used for
        // finding required words, as its children will
        // contain words which have our argument word as prefix.
        TrieNode *curNode = root, *childNode;
        int index = 0;
        int wordLength = word.length();

        while (index < wordLength) {
            childNode = curNode->getChild(word[index]);

            if (childNode == nullptr) {
                std::cout << "No suggestions available" << std::endl;
                return;
            }
            index++;
            curNode = childNode;
        }

        // now curNode contains the node whose children are suggestions.
        std::vector<std::string> suggestionsList;
        std::vector<std::string>::iterator it;
        getSuggestionsHelper(curNode, suggestionsList, word);

        char delimiter;

        for (it = suggestionsList.begin(); it != suggestionsList.end(); it++) {
            if (it + 1 == suggestionsList.end()) {
                delimiter = ' ';
            } else {
                delimiter = ',';
            }
            std::cout << *it << delimiter;
        }

        std::cout << std::endl;
    }

    void getSuggestionsHelper(TrieNode *curNode,
                              std::vector<std::string> &suggestionsList,
                              std::string subWord) {
        if (curNode->getEOW()) {
            suggestionsList.push_back(subWord);
        }

        std::vector<char>::iterator it;
        std::vector<char> keys = curNode->getChildrenKeys();

        for (it = keys.begin(); it != keys.end(); it++) {
            getSuggestionsHelper(curNode->getChild(*it), suggestionsList,
                                 subWord + (*it));
        }
    }

    void displayTrie() {
        std::stringstream buffer;
        displayTrieHelper(root, '$', buffer, "", "");
        std::cout << buffer.str() << std::endl;
    }

    void displayTrieHelper(TrieNode *curNode, char val,
                           std::stringstream &buffer, std::string prefix,
                           std::string childrenPrefix) {
        buffer << prefix;
        buffer << val;
        buffer << '\n';
        std::vector<char>::iterator it;
        std::vector<char> keys = curNode->getChildrenKeys();
        for (it = keys.begin(); it != keys.end();) {
            char curVal;

            if (*it == ' ') {
                curVal = '_';
            } else {
                curVal = *it;
            }

            if ((it + 1) != keys.end()) {
                displayTrieHelper(curNode->getChild(*it), curVal, buffer,
                                  childrenPrefix + "├──",
                                  childrenPrefix + "│  ");
            } else {
                displayTrieHelper(curNode->getChild(*it), curVal, buffer,
                                  childrenPrefix + "└──",
                                  childrenPrefix + "   ");
            }

            it++;
        }
    }

    void serialiseTrie() {
        std::fstream trieFile;
        trieFile.open("myTrie.txt", std::ios::out | std::ios::trunc);

        if (!trieFile) {
            std::cout << "File creation failed!.\n";
        } else {
            std::cout << "File creation successfull!.\n";

            serialiseTrieHelper(root, trieFile);

            trieFile.close();
        }
    }

    void serialiseTrieHelper(TrieNode *node, std::fstream &s) {
        s << node->getEOW();

        int num = node->getNumOfChildren();
        std::vector<char> keys = node->getChildrenKeys();
        s << num;

        int index = 0;

        while (index < num) {
            s << keys[index];
            serialiseTrieHelper(node->getChild(keys[index]), s);
            index++;
        }
    }
};