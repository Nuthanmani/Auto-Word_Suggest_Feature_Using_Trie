#include <iostream>
#include <list>

using namespace std;

#define MAX_CHARS (26)

struct TrieNode
{
    TrieNode *children[MAX_CHARS];
    bool isEnd;
    TrieNode()
    {
        for (int i = 0; i < MAX_CHARS; i++)
        {
            this->children[i] = NULL;
        }
        this->isEnd = false;
    }
};

class Trie
{
    TrieNode *root;
    TrieNode *_findSubString(string subStr)
    {
        TrieNode *currNode = root;
        for (int i = 0; i < subStr.length(); i++)
        {
            char val = subStr.at(i);
            if (currNode->children[val - 'A'] == NULL)
            {
                return NULL;
            }
            currNode = currNode->children[val - 'A'];
        }
        return currNode;
    }

public:
    Trie()
    {
        root = new TrieNode();
    }
    ~Trie() {}

    void addWord(string word)
    {
        TrieNode *currNode = root;
        for (int i = 0; i < word.length(); i++)
        {
            char val = word.at(i);
            if (currNode->children[val - 'A'] == NULL)
            {
                currNode->children[val - 'A'] = new TrieNode();
            }
            currNode = currNode->children[val - 'A'];
        }
        currNode->isEnd = true;
    }
    bool searchWord(string word)
    {
        TrieNode *currNode = root;
        for (int i = 0; i < word.length(); i++)
        {
            char val = word.at(i);
            if (currNode->children[val - 'A'] == NULL)
            {
                return false;
            }
            currNode = currNode->children[val - 'A'];
        }
        if (currNode->isEnd == false)
        {
            return false;
        }
        return true;
    }
    void getDictionaryWords(TrieNode *root, string subStr, list<string> &result)
    {
        TrieNode *curr = root;
        if (curr == NULL)
            return;
        if (curr->isEnd)
        {
            result.push_back(subStr);
        }

        for (int i = 0; i < MAX_CHARS; i++)
        {
            string str = subStr + string(1, (char)('A' + i));
            if (curr->children[i] != NULL)
            {
                getDictionaryWords(curr->children[i], str, result);
            }
        }
    }
    list<string> dictWords(string subStr)
    {
        TrieNode *currNode = _findSubString(subStr);
        if (currNode != NULL)
        {
            list<string> result;
            getDictionaryWords(currNode, subStr, result);
            return result;
        }
        return list<string>();
    }
};

int main()
{
    Trie trie;
    trie.addWord("APPLE");
    trie.addWord("APE");
    trie.addWord("ANGLE");
    trie.addWord("GRAPE");
    trie.addWord("GOOD");
    trie.addWord("GOD");
    trie.addWord("GUN");
    list<string> res = trie.dictWords("A");
    list<string>::iterator itr;
    for (itr = res.begin(); itr != res.end(); itr++)
    {
        cout << *itr << endl;
    }
    return 0;
}
