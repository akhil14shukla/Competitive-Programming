#include <bits/stdc++.h>
#include <stack>
#define ll long long
#define rep(i, n) for (ll i = 0; i < n; i++)
#define ALPHABET_SIZE (int)26
using namespace std;
// template<T>
struct TrieNode{
    struct TrieNode* children[ALPHABET_SIZE];
    int count = 0;
    bool isEndOfWord; 
};
struct TrieNode *getNode(void) 
{ 
    struct TrieNode *pNode =  new TrieNode; 
  
    pNode->isEndOfWord = false; 
  
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        pNode->children[i] = NULL; 
        pNode->count = 0;
    }
  
    return pNode; 
};

// If not present, inserts key into trie 
// If the key is prefix of trie node, just 
// marks leaf node 
void insert(struct TrieNode *root, string key) 
{ 
    struct TrieNode *pCrawl = root; 
  
    for (int i = 0; i < key.length(); i++) 
    { 
        int index = key[i] - 'a'; 
        if (!pCrawl->children[index]){ 
            pCrawl->children[index] = getNode(); 
        }
  
        pCrawl = pCrawl->children[index]; 
        pCrawl->count++;
    } 
  
    // mark last node as leaf 
    pCrawl->isEndOfWord = true; 
} 

bool search(struct TrieNode *root, string key) 
{ 
    struct TrieNode *pCrawl = root; 
  
    for (int i = 0; i < key.length(); i++) 
    { 
        int index = key[i] - 'a'; 
        if (!pCrawl->children[index]) 
            return false; 
  
        pCrawl = pCrawl->children[index]; 
    } 
  
    return (pCrawl != NULL && pCrawl->isEndOfWord); 
} 



// int main(){

//     return 0;
// }