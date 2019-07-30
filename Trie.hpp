#include <iostream>
#include <unordered_map>
#include <iterator>
#include <vector>

struct Node {
    bool isEndOfWord;
    std::unordered_map<char, Node*> children;
};

class Trie {
    private:
        Node *root = new Node();
        std::vector<std::string> expandNode(Node *node, std::string key, std::string word, char *c, std::vector<std::string> &suggestions);
    public:
        Trie();
        void insertKey(std::string key);
        bool searchKey(std::string key);
        std::vector<std::string> suggest(std::string key);
        bool childExists(Node *currentNode, char c);
        bool isTrieEmpty();
        bool deleteKey(Node *root, std::string key, int keyLength, int dept);
        Node* getRootNode();
};

Trie::Trie() {
    this->root->isEndOfWord = false;
}

Node* Trie::getRootNode() {
    return this->root;
}

bool Trie::isTrieEmpty() {
    return this->root->children.empty();
}

bool Trie::childExists(Node *currentNode, char c) {
    if (currentNode->children.find(c) == currentNode->children.end()) {
        // current char not found
        return false;    
    }
    else {
        return true;
    }
}

void Trie::insertKey(std::string key) {
    int keyLength = key.length();
    Node *currentNode = this->root;

    for(int i = 0; i < keyLength; i++) {
        if (this->childExists(currentNode, key[i]) == false) {
            // current char not found, lets add it to the tree
            Node *newNode = new Node();
            currentNode->children.insert({key[i], newNode});
            currentNode = newNode;
            std::cout<<"created new node for "<<key[i]<<std::endl;
        }
        else {
            // current char found in current node's children, lets update current node to the children that we found!
            std::cout<<"node already exists for "<<key[i]<<std::endl;
            currentNode = currentNode->children.at(key[i]);
        }
    }
    currentNode->isEndOfWord = true;
}

bool Trie::searchKey(std::string key) {
    Node *currentNode = this->root;
    int keyLength = key.length();

    if (this->isTrieEmpty()) {
        std::cout<<"Trie is empty, aborting search!";
        return false;
    }
    else {
        for (int i = 0; i < keyLength; i++) {
            if (this->childExists(currentNode, key[i])) {
                // we found child exists, lets update current node to the child node and iterate to next node!
                currentNode = currentNode->children.at(key[i]);
            }
            else {
                // we could not find the ith element, thus the key does not exist!
                return false;
            }
        }
        // if we iterated to total elements in the key to search, and if that word already exists, then we found it!
        if (currentNode->isEndOfWord == true) return true;
        // As isEndOfWord was false, it means even though our Trie has key to be searched, it is not yet stored into trie yet!
        return false;
    }
}

std::vector<std::string> Trie::expandNode (Node *currentNode, std::string key, std::string word, char *c, std::vector<std::string> &suggestions) {
    
    std::unordered_map<char, Node*> children = currentNode->children;
    int totalCurrentChildren = children.size();
    
    if (c != NULL) {
        word += *c;
        if (currentNode->isEndOfWord)
            suggestions.push_back(word);
    }

    for (auto item: children) {
        char nextCharToAdd = item.first;
        Node *nextChild = item.second;
        this->expandNode(nextChild, key, word, &nextCharToAdd, suggestions);
    }

    return suggestions;
}

std::vector<std::string> Trie::suggest(std::string key) {
    std::vector<std::string> suggestions;

    Node *currentNode = this->root;
    int keyLength = key.length();
    bool keyExists = true;

    for (int i = 0; i < keyLength; i++) {
        if (this->childExists(currentNode, key[i]) == true) {
            // move to next node
            currentNode = currentNode->children.at(key[i]);
        }
        else {
            // key does not exist.. no suggestions available!
            keyExists = false;
            break;
        }
    } 

    if (keyExists) {
        // lets find out all the words that had the `key` as its prefix!
        suggestions = this->expandNode(currentNode, key, key, NULL, suggestions);
        int totalSuggestions = suggestions.size();
        std::cout<<"Printing suggestions"<<std::endl<<std::endl;
        for( int i = 0; i < totalSuggestions; i++) {
            std::cout<<suggestions.at(i)<<std::endl;
        }
        std::cout<<std::endl<<std::endl;
    }
    else{
        std::cout<<"Could not find the key in our trie, thus skipping suggestions"<<std::endl;
    }

    return suggestions;
}

bool Trie::deleteKey(Node *root, std::string key, int keyLength, int dept = 0) {
    Node *currentNode = root;
    Node *nextNode;
    int currentDept = dept;

    if (this->isTrieEmpty()) {
        std::cout<<"Trie is empty, aborting deletion";
        return false;
    }

    if (dept == (keyLength - 1)) {
        if (this->childExists(currentNode, key[dept]) == false) {
            std::cout<<"Could not find the key to delete 3"<<std::endl;
            return false;
        }
        nextNode = currentNode->children.at(key[dept]);
        std::cout<<"Deletion char: "<<key[dept]<<std::endl;
        std::cout<<"isEndOfWord: "<<nextNode->isEndOfWord<<std::endl;
       if (nextNode->isEndOfWord == true) {
           nextNode->isEndOfWord = false;
           if (nextNode->children.size() == 0)
                return true; // as no children are present, this is a leaf node, which can be deleted!
            else
                return false;
       }
       else {
           // given key does not exist in our trie
           std::cout<<"Could not find key for deletion 1: "<<key<<std::endl;
           return false;
       }
    }
    else {
        char currentChar = key[dept];
        std::cout<<"Deletion char: "<<currentChar<<std::endl;
        std::cout<<"isEndOfWord: "<<currentNode->isEndOfWord<<std::endl;
        if (currentNode->children.find(currentChar) != currentNode->children.end()) {
            // char is found
            nextNode = currentNode->children.at(currentChar);
            std::cout<<"moving to next char"<<std::endl;
        }
        else {
            std::cout<<"Could not find key for deletion 2: "<<key<<std::endl;;
            return false;
        }
    }

    bool canDelete = this->deleteKey(nextNode, key, keyLength, ++dept);

    if (canDelete) {
        currentNode->children.erase(key[currentDept]);
        std::cout<<"Node deleted for: "<<key[currentDept]<<std::endl;
        if (currentNode->children.size() == 0)
            return true;
        else
            return false;
    }
    else {
        return false;
    }
}