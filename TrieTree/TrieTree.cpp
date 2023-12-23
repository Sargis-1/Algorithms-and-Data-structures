#include <iostream>
#include <unordered_map>
#include <string>


//Trie tree is a data structure which contains any words(strings) and provides effective insertion, searching and deleting methods.
class Node {
public:
    std::unordered_map<char, Node*> children;
    bool isWord;

    Node() : isWord(false){}
};


class TrieTree {
private:
    Node* root = nullptr;
public:
    TrieTree(): root(new Node){}

    void insertIt(std::string word) {
        Node* node = root;
        for (int i = 0; i < word.size(); ++i) {
            if (node->children.find(word[i]) == node->children.end()) {
                Node* newnode = new Node();
                node->children[word[i]] = newnode;
            }
            node = node->children[word[i]];
        }

        node->isWord = true;
    }

    void insertRec(std::string word) {
        Node* node = root;
        insertHelper(node, word, 0);
    }

    bool search(std::string word) {
        if (!root || word.size() == 0)
            return false;

        Node* curr = root;
        for (int i = 0; i < word.size(); ++i) {
            if (!curr->children[word[i]])
                return false;
            curr = curr->children[word[i]];
        }

        return curr->isWord;
    }

    bool deleteWord(std::string word) {
        if (!root || word.size() == 0)
            return false;
        else {
            Node* curr = root;
            return deleteHelper(curr, word, 0);
        }
    }

    void printTree() {
        Node* curr = root;
        if (!root) {
            std::cout << "No words in tree" << std::endl;
            return;
        }

        std::string currword = "";
        printhelper(curr, currword);
    }
private:
    void insertHelper(Node* node, std::string word, int i) {
        if (i == word.size()) {
            node->isWord = true;
            return;
        }

        Node* newnode = node->children[word[i]];
        if (!newnode) {
            newnode = new Node();
            node->children[word[i]] = newnode;
        }
        insertHelper(newnode, word, i + 1);
    }

    bool deleteHelper(Node* curr, std::string word, int i) {
        if (i == word.size()) {
            if (!curr->isWord)
                return false;
            curr->isWord = false;
            return curr->children.empty();
        }

        Node* node = curr->children[word[i]];
        if (!node)
            return false;

        bool shouldBeDeleted = deleteHelper(node, word, i + 1);
        if (shouldBeDeleted) {
            Node* toremove = curr->children[word[i]];
            curr->children.erase(word[i]);
            delete toremove;
            return curr->children.empty() && !curr->isWord;// !curr->isWord is neccessary for right removement, case: when you 
        }                                                  // delete abcd abc is being also deleted without this check

        return false;
    }

    void printhelper(Node* node, std::string& curr) {
        if (node->isWord)
            std::cout << curr << std::endl;

        for (auto elem : node->children) {
            curr += elem.first;
            printhelper(node->children[elem.first], curr);
            curr.pop_back();
        }
    }
};



int main()
{
    TrieTree tree;
    tree.insertRec("abc");
    tree.insertRec("abgl");
    tree.insertRec("cdf");
    tree.insertRec("abcd");
    tree.insertRec("lmn");
    

    tree.printTree();
    tree.deleteWord("abcd");
    std::cout << std::endl;
    tree.printTree();
    std::cout << tree.search("abgl") << std::endl;

    return 0;
}

