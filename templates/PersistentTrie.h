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

node *get_copy(node *head) {
    node *res = new node();
    if(head!=NULL) {
        res->data = head->data;
        res->left = head->left;
        res->right = head->right;
    }
    return res;
}

class PersistentTrie {
    vector<node *> trie;

    public:

    PersistentTrie() {
        trie.push_back(new node());
    }

    void clear() {
        trie.clear();
    }

    vector<int> get_binary_number(int num) {
        vector<int> bin;
        int idx=29;
        while(idx>=0) {
            bin.insert(bin.begin(), num%2);
            num/=2;
            idx--;
        }
        return bin;
    }

    void insert(int num,int index) {
        node *head = get_copy(trie.at(index));
        node *cur = head;
        vector<int> bin = get_binary_number(num);
        for(int i=0;i<30;i++) {
            cur->data = cur->data ^ num;
            if(bin.at(i)) {
                cur->right = get_copy(cur->right);
                cur = cur->right;
            }
            else {
                cur->left = get_copy(cur->left);
                cur = cur->left;
            }
        }
        cur->data = cur->data ^ num;
        trie.push_back(head);
    }

    int get(int num, int index) {
        node *head = get_copy(trie.at(index));
        vector<int> bin = get_binary_number(num);
        int res = 0;
        for(int i=0;i<30;i++) {
            if(head==NULL)
                break;
            if(bin.at(i)) {
                if(head->left!=NULL)
                    res = res ^ head->left->data;
                head = head->right;
            }
            else
                head = head->left;
        }
        if(head!=NULL)
            res = res ^ head->data;
        return res;
    }
};