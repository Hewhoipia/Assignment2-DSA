#ifndef __CONCAT_STRING_TREE_H__
#define __CONCAT_STRING_TREE_H__

#include "main.h"

class ConcatStringTree {
public:
    class ParentsTree {
    public:
        enum BaEle { L, E, R };
        class PaNode {
        protected:
            int id;
            PaNode* Paright;
            PaNode* Paleft;
            ParentsTree::BaEle status;
        public:
            friend class ParentsTree;
            PaNode(int ID, BaEle _s = E, PaNode* left = nullptr, PaNode* right = nullptr) : id(ID), status(_s), Paright(right), Paleft(left) {}
        };
    public:
        friend class Node;
        friend class ConCatStringTree;
        PaNode* PaRoot = nullptr;
        int num = 0;
        ParentsTree(int ID) {
            PaRoot = new PaNode(ID);
            num++;
        }
        bool addPaNode(PaNode*& pRoot, int ID) {
            if (pRoot) {
                if (addPaNode(pRoot->Paright, ID)) {
                    return Rba(pRoot);
                }
                return 0;
            }
            else {
                pRoot = new PaNode(ID);
                num++;
                return 1;
            }
        }
        bool delPaNode(PaNode*& pRoot, int key) {
            if (!pRoot) return false;
            if (pRoot->id == key) {
                if (pRoot->Paleft && pRoot->Paright) {
                    PaNode* p = pRoot->Paleft;
                    while (p->Paright) { p = p->Paright; }
                    pRoot->id = p->id;
                    if (delPaNode(pRoot->Paleft, pRoot->id)) return !Rba(pRoot);
                }
                else if (pRoot->Paleft) { PaNode* p = pRoot; pRoot = pRoot->Paleft; delete p; num--; return true; }
                else if (pRoot->Paright) { PaNode* p = pRoot; pRoot = pRoot->Paright; delete p; num--; return true; }
                else { delete pRoot; pRoot = nullptr; num--; return true; }
            }
            else if (pRoot->id > key) {
                if (delPaNode(pRoot->Paleft, key)) return !Rba(pRoot);
            }
            else {
                if (delPaNode(pRoot->Paright, key)) return !Lba(pRoot);
            }
            return false;
        }
        bool Rba(PaNode*& pRoot) {
            if (PaRoot->status == E) {
                PaRoot->status = R;
                return true;
            }
            else if (PaRoot->status == L) {
                PaRoot->status = E;
                return false;
            }
            if (PaRoot->Paright->status == E) {
                rotateLeft(pRoot);
                pRoot->status = L;
                pRoot->Paleft->status = R;
                return true;
            }
            else if (PaRoot->Paright->status == R) {
                rotateLeft(pRoot);
                pRoot->status = pRoot->Paleft->status = E;
                return false;
            }
            rotateRight(pRoot->Paright);
            rotateLeft(pRoot);
            if (pRoot->status = E) {
                pRoot->Paleft->status = pRoot->Paright->status = E;
            }
            else if (pRoot->status = R) {
                pRoot->Paright->status = E;
                pRoot->Paleft->status = L;
            }
            else {
                pRoot->Paright->status = R;
                pRoot->Paleft->status = E;
            }
            pRoot->status = E;
            return false;
        }
        bool Lba(PaNode*& pRoot) {
            if (PaRoot->status == E) {
                PaRoot->status = L;
                return true;
            }
            else if (PaRoot->status == R) {
                PaRoot->status = E;
                return false;
            }
            if (PaRoot->Paleft->status == E) {
                rotateRight(pRoot);
                pRoot->status = R;
                pRoot->Paright->status = L;
                return true;
            }
            else if (PaRoot->Paleft->status == L) {
                rotateRight(pRoot);
                pRoot->status = pRoot->Paright->status = E;
                return false;
            }
            rotateLeft(pRoot->Paleft);
            rotateRight(pRoot);
            if (pRoot->status = E) {
                pRoot->Paleft->status = pRoot->Paright->status = E;
            }
            else if (pRoot->status = L) {
                pRoot->Paleft->status = E;
                pRoot->Paright->status = R;
            }
            else {
                pRoot->Paleft->status = L;
                pRoot->Paright->status = E;
            }
            pRoot->status = E;
            return false;
        }
        void rotateLeft(PaNode*& pRoot) {
            PaNode* p = pRoot->Paright;
            pRoot->Paright = p->Paleft;
            p->Paleft = pRoot;
            pRoot = p;
        }
        void rotateRight(PaNode*& pRoot) {
            PaNode* p = pRoot->Paleft;
            pRoot->Paleft = p->Paright;
            p->Paright = pRoot;
            pRoot = p;
        }
        int size()const {
            return num;
        }
        void TSPOtra(PaNode*pRoot, string &hold) const {
            if (!pRoot) {
                return;
            }
            else {
                hold = hold + "(id=" + to_string(pRoot->id) + ")" + ";";
                TSPOtra(pRoot->Paleft, hold);
                TSPOtra(pRoot->Paright, hold);
            }
        }
        string toStringPreOrder()const {
            string hold = "";
            TSPOtra(PaRoot, hold);
            hold.pop_back();
            string s = "ParentsTree[" + hold + "]";
            return s;
        }
    };
public:
    class Node {
    protected:
        string data;
        int leftLength;
        int length;
        Node* left;
        Node* right;
        int Nodeid;
    public:
        ParentsTree* PaTree = nullptr;
        Node(const char*s, Node*pLeft, Node*pRight, int length, int leftLength) {
            data = s;
            left = pLeft;
            right = pRight;
            this->length = length;
            this->leftLength = leftLength;
            PaTree = new ParentsTree(++ID);
            Nodeid = ID;
        }
        Node() {
            left = nullptr;
            right = nullptr;
        }
        friend class ConcatStringTree;
    };
public:
    Node* root = nullptr;
    ConcatStringTree(const char* s) {
        string hold = s;
        int length = hold.size();
        if (ID > (int)pow(10, 7)) {
            throw overflow_error("Id is overflow!");
        }
        else {
            root = new Node(s, nullptr, nullptr, length, 0);
        }
    }
    int length() const {
        return root->length;
    }
    char get(int index) {
        if (index >= 0 && index <= length() - 1) {
            return traverseGet(index, root);
        }
        else throw out_of_range("Index of string is invalid");
    }
    int indexOf(char c) {
        bool stop = 0;
        int index = 0;
        traverseIndexOf(c, index, root,stop);
        return index;
    }
    string toStringPreOrder() const {
        string hold = "";
        traverseTSPO(root, hold);
        if(hold!="") hold.pop_back();
        hold = "ConcatStringTree[" + hold + "]";
        return hold;
    }
    string toString() const {
        string hold = "";
        traverseTS(root, hold);
        hold = "ConcatStringTree[" + hold + "]";
        return hold;
    }
    ConcatStringTree concat(const ConcatStringTree& otherS) const {
        ConcatStringTree change("");
        change.root->left = this->root;
        change.root->right = otherS.root;
        change.root->leftLength = this->root->length;
        change.root->length = this->root->length + otherS.root->length;
        if (ID > (int)pow(10, 7)) {
            throw overflow_error("Id is overflow!");
        }
        else {
            this->root->PaTree->addPaNode(this->root->PaTree->PaRoot,ID);
            otherS.root->PaTree->addPaNode(otherS.root->PaTree->PaRoot, ID);
        }
        isChange = 1;
        return change;
    }
    ConcatStringTree subString(int from, int to) const {
        if (from >= to) {
            throw logic_error("Invalid range!");
        }
        if (from <0 || to > this->length()) {
            throw out_of_range("Index of string is invalid!");
        }
        isChange = 1;
        ConcatStringTree change;
        change.root = new Node();
        traverseSub(root,change.root,from,to);
        return change;
    }
    ConcatStringTree reverse() const {
        isChange = 1;
        ConcatStringTree change;
        change.root = new Node();
        traverseReverse(root, change.root);
        return change;
    }
    int getParTreeSize(const string& query) const {
        return traverseGetPTS(root,query);
    }
    string getParTreeStringPreOrder(const string& query) const {
        return traverseGetPTSPO(root, query);
    }

    //Additional Functions
public:
    ConcatStringTree() {}
    ~ConcatStringTree() {
        if (isChange) {
            isChange = 0;
        }
        else {
            destructor(this->root, this->root->Nodeid);
        }
    }
    void destructor(Node*&pRoot, int&Nodeid) {
        pRoot->PaTree->delPaNode(pRoot->PaTree->PaRoot, Nodeid);
        if (!pRoot->PaTree->PaRoot) {
            if (pRoot->left) destructor(pRoot->left, Nodeid);
            if (pRoot->right) destructor(pRoot->right, Nodeid);
            delete pRoot->PaTree;
            delete pRoot;
            pRoot = nullptr;
        }
        else {
            return;
        }
    }
    static bool isChange;
    static int ID;
    char traverseGet(int index, Node* pRoot) { //traverse function for get()
        if (pRoot->left == nullptr && pRoot->right==nullptr) {
            return pRoot->data[index];
        }
        else {
            if (index < pRoot->leftLength && pRoot->left != nullptr) {
                return traverseGet(index,pRoot->left);
            }
            else return traverseGet(index - pRoot->leftLength, pRoot->right);
        }
    }
    void traverseIndexOf(char c,int& index, Node* pRoot,bool&stop) { //traverse function for indexOf()
        if (stop) {
            return;
        }
        if (pRoot->left == nullptr && pRoot->right == nullptr) {
            for (int i = 0; i < pRoot->length; i++) {
                if (pRoot->data[i] == c) {
                    stop = 1;
                    return;
                }
                index++;
            }
            return;
        }
        else {
            if (pRoot->left!=nullptr) {
                traverseIndexOf(c, index, pRoot->left,stop);
            }
            if (pRoot->right != nullptr) {
                traverseIndexOf(c, index, pRoot->right,stop);
            }
        }
    }
    void traverseTSPO(Node* pRoot, string & hold) const {
        if (!pRoot) {
            return;
        }
        else {
            string s = "";
            if (pRoot->data[0]) {
                s = pRoot->data;
            }
            else {
                s = "<NULL>";
            }
            hold = hold + "(LL=" + to_string(pRoot->leftLength) + ",L=" + to_string(pRoot->length) + "," + s + ")" + ";";
            traverseTSPO(pRoot->left,hold);
            traverseTSPO(pRoot->right,hold);
        }
    }
    void traverseTS(Node* pRoot,string&hold) const { //traverse toString()
        if (!pRoot) {
            return;
        }
        else {
            hold = hold + pRoot->data;
            traverseTS(pRoot->left, hold);
            traverseTS(pRoot->right, hold);
        }
    }
    void traverseSub(Node* pRoot,Node*&cRoot,int& from, int &to) const{
        if (pRoot->left == nullptr && pRoot->right == nullptr) {
            if (to == 0) {
                delete cRoot;
                cRoot = nullptr;
                return;
            }
            if (from >= pRoot->length) {
                from = from - pRoot->length;
                to = to - pRoot->length;
                delete cRoot;
                cRoot = nullptr;
                return;
            }
            else if (from <pRoot->length) {
                if (to > pRoot->length) {
                    if (from == 0) {
                        cRoot->data = pRoot->data;
                        cRoot->leftLength = 0;
                        cRoot->length = pRoot->length;
                        to = to - pRoot->length;
                        return;
                    }
                    else {
                        cRoot->data = pRoot->data.substr(from,pRoot->length);
                        cRoot->leftLength = 0;
                        cRoot->length = cRoot->data.size();
                        from = 0;
                        to = to - pRoot->length;
                    }
                }
                else {
                    cRoot->data = pRoot->data.substr(from, to);
                    cRoot->leftLength = 0;
                    cRoot->length = cRoot->data.size();
                    to = 0;
                }
            }
        }
        else {
            if (pRoot->left != nullptr) {
                cRoot->left = new Node();
                traverseSub(pRoot->left,cRoot->left,from,to);
            }
            if (cRoot->left == nullptr) {
                cRoot->leftLength = 0;
            }
            else {
                cRoot->leftLength = cRoot->left->length;
            }
            if (pRoot->right != nullptr) {
                cRoot->right = new Node();
                traverseSub(pRoot->right,cRoot->right,from, to);
            }
            if (cRoot->right == nullptr) {
                cRoot->length = cRoot->leftLength;
            }
            else {
                cRoot->length = cRoot->leftLength + cRoot->right->length;
            }
        }
    }
    void traverseReverse(Node*pRoot, Node*&cRoot) const {
        if (pRoot->left == nullptr && pRoot->right == nullptr) {
            cRoot->data = pRoot->data;
            for (int i = 0; i < pRoot->length; i++) {
                cRoot->data[i] = pRoot->data[pRoot->length - i - 1];
            }
            cRoot->length = pRoot->length;
            cRoot->leftLength = 0;
        }
        else {
            if (pRoot->right != nullptr) {
                cRoot->left = new Node();
                traverseReverse(pRoot->right, cRoot->left);
            }
            if (cRoot->left == nullptr) {
                cRoot->leftLength = 0;
            }
            else {
                cRoot->leftLength = cRoot->left->length;
            }
            if (pRoot->left != nullptr) {
                cRoot->right = new Node();
                traverseReverse(pRoot->left, cRoot->right);
            }
            if (cRoot->right == nullptr) {
                cRoot->length = cRoot->leftLength;
            }
            else {
                cRoot->length = cRoot->leftLength + cRoot->right->length;
            }
        }
    }
    int traverseGetPTS(Node*pRoot,string hold) const {
        for (int i = 0; i < hold.size(); i++) {
            if (!pRoot) {
                throw runtime_error("Invalid query: reaching NULL");
            }
            if (hold[i] == 'l') {
                pRoot = pRoot->left;
            }
            else if (hold[i] == 'r') {
                pRoot = pRoot->right;
            }
            else {
                throw runtime_error("Invalid character of query");
            }
        }
        if (!pRoot) {
            throw runtime_error("Invalid query: reaching NULL");
        }
        return pRoot->PaTree->size();
    }
    string traverseGetPTSPO(Node* pRoot, string hold) const {
        for (int i = 0; i < hold.size(); i++) {
            if (!pRoot) {
                throw runtime_error("Invalid query: reaching NULL");
            }
            if (hold[i] == 'l') {
                pRoot = pRoot->left;
            }
            else if (hold[i] == 'r') {
                pRoot = pRoot->right;
            }
            else {
                throw runtime_error("Invalid character of query");
            }
        }
        if (!pRoot) {
            throw runtime_error("Invalid query: reaching NULL");
        }
        return pRoot->PaTree->toStringPreOrder();
    }
    //end
};

class ReducedConcatStringTree; // forward declaration
class LitStringHash; // forward declaration

class HashConfig {
private:
    int p;
    double c1, c2;
    double lambda;
    double alpha;
    int initSize;

    friend class ReducedConcatStringTree;
    friend class LitStringHash;
};

class LitStringHash {
public:
    LitStringHash(const HashConfig& hashConfig) {
        HCF = hashConfig;
    }
    int getLastInsertedIndex() const;
    string toString() const;
    HashConfig HCF;
    string* hashTable=nullptr;
};

class ReducedConcatStringTree : public ConcatStringTree {
public:
    ReducedConcatStringTree(const char* s, LitStringHash* litStringHash) {

        this->litStringHash = litStringHash;
    }
    int hashFunc(string &s, LitStringHash* litStringHash) {
        int hs = 0;
        for (int i = 0; i < s.size(); i++) {
            hs = hs + s[i] * pow(litStringHash->HCF.p, i);
        }
        return hs % litStringHash->hashTable->size();

    }
    void insert(string &s, LitStringHash* litStringHash) {
        if (litStringHash->hashTable == nullptr) {
            litStringHash->hashTable = new string(s);
        }
    }
    LitStringHash* litStringHash;
};

#endif // __CONCAT_STRING_TREE_H__