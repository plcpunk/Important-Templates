#include <vector>

struct node {
    int data;
    node *left;
    node *right;
    node() {
        data = 0;
        left = NULL;
        right = NULL;
    }
};

class PersistentTrie {
    vector<node *> trie;

    public:

    PersistentTrie() {
        trie.push_back(new node());
    }

    void insert(int num,int index) {

    }
};