#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
/*
std::string nameFile, buff;
//std::cin >> nameFile;
//nameFile = "testfile.file";
std::ifstream fin("testfile", std::ios_base::binary);
if (fin.is_open()) {
std::getline(fin, buff);
std::cout << buff << std::endl;
}
else {
std::cout<<"Not open file"<<std::endl;
}
*/
struct tnode {
    unsigned int freq;
    char letter;
    tnode* left;
    tnode* right;
    tnode() : letter('0'), freq(0), left(nullptr), right(nullptr) {}
    tnode(char _letter, unsigned int fr) : letter(_letter), freq(fr), left(nullptr), right(nullptr) {}

    void addChild(tnode* newNode) {
        if(left==nullptr) {
            left = newNode;
        }
        else {
            if(left->getFreq() <= newNode->getFreq())
                right = newNode;
            else {
                right = left;
                left = newNode;
            }
        }
        freq += newNode->getFreq();
    }
    unsigned int getFreq() const{
        return freq;
    }
    char getLetter() const {
        return letter;
    }
    bool isLeaf() const {
        return ((left == nullptr)&& (right==nullptr));
    }
    tnode* getLeft() const {
        return left;
    }
    tnode* getRight() const {
        return right;
    }
    void printNode(tnode *root) const{
        if(root == nullptr)
            return;
        std::cout<<root->freq<<" "<<root->letter<<std::endl;
        printNode(root->left);
        printNode(root->right);
        }
};

struct BinaryTree {
    tnode* root;

    BinaryTree() : root(nullptr) {}
    BinaryTree(tnode* _root) : root(_root) {}
    unsigned int getFreq() const {
        return root->getFreq();
    }
    tnode* getRoot() const {
        return root;
    }

    void inOrder(tnode* _root) {				// Displaying binary tree
        if (_root != nullptr) {
            inOrder(_root->left);
            std::cout << "|     " << _root->letter<< "    |     " << _root->freq << "\t|" << std::endl;
            std::cout << " ----------------------- " << std::endl;
            inOrder(_root->right);
        }
    }
};

struct PriorityQueue {
    std::vector <BinaryTree> data;
    int n;

    PriorityQueue() : n(0) {}
    void insert(BinaryTree newTree) {
        if (n==0)
            data.push_back(newTree);
        else {
            for (int i = 0; i < n; i++)
                if(data.at(i).getFreq()>newTree.getFreq()) {
                    data.at(i) = newTree;
                }
        }
        n++;
    }

};

struct HuffmanTreeBuild {
    BinaryTree huffmanTree;
    std::map <char, int> tablefreq;
};

int main() {
    std::map <char, int> tablefreq;
    std::string nameFile;
    char sim;
    //std::cin >> nameFile;
    //nameFile = "testfile.file";
    std::ifstream fin("testfile");
    if (fin.is_open()) {
        while(!fin.eof()) {
            fin.get(sim);
            tablefreq[sim]++;
        }
    }
    else {
        std::cout<<"Not open file"<<std::endl;
    }
    fin.close();

    tnode* root;
    root = nullptr;


    //for (auto&& item : tablefreq)
    //    std::cout << item.first << ": " << item.second << std::endl;
    return 0;
}
