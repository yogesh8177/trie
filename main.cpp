/* main.cpp */
#include <iostream>
#include <map>
#include <unordered_map>
#include <iterator>
#include "Trie.hpp"
using namespace std;


int main()
{   
    Trie *t = new Trie();
    string isTrieEmpty = t->isTrieEmpty() == 1 ? "true" : "false";
    cout<<"Is Trie empty? "<< isTrieEmpty;
    cout<<endl<<endl;

    t->insertKey("hello");
    cout<<"Added a word to Trie!"<<endl;
    isTrieEmpty = t->isTrieEmpty() == 1 ? "true" : "false";
    cout<<endl<<endl;

    cout<<"Is Trie empty? "<< isTrieEmpty;
    cout<<endl<<endl;

    string foundKey = t->searchKey("hell")  ? "true" : "false";;
    cout<<"search result for key, found: "<<foundKey;
    cout<<endl<<endl;

    foundKey = t->searchKey("hello")  ? "true" : "false";;
    cout<<"search result for key, found: "<<foundKey;
    cout<<endl<<endl;

    t->insertKey("hot");
    cout<<"Added a word to Trie!"<<endl;
    cout<<endl<<endl;

    foundKey = t->searchKey("hot")  ? "true" : "false";;
    cout<<"search result for key, found: "<<foundKey;
    cout<<endl<<endl;

    //t->deleteKey(t->getRootNode(), "hot", 3, 0);

    foundKey = t->searchKey("hot")  ? "true" : "false";;
    cout<<"search result for key, found: "<<foundKey;
    cout<<endl<<endl;

    
    t->deleteKey(t->getRootNode(), "mt", 2, 0);

    t->insertKey("health");
    t->insertKey("help");
    t->insertKey("hellos");

    // cout<<"Suggest for he"<<endl;
    // t->suggest("he");

    cout<<"Suggest for h"<<endl;
    t->suggest("h");

    foundKey = t->searchKey("halth")  ? "true" : "false";;
    cout<<"search result for halth, found: "<<foundKey;
    cout<<endl<<endl;

    return 0;
}