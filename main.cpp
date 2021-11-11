#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <queue>
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

/*    void addChild(tnode* newNode) {
        if(left==nullptr) {
            left = newNode;
        }
        else {
            if(left->freq <= newNode->freq)
                right = newNode;
            else {
                right = left;
                left = newNode;
            }
        }
        freq += newNode->freq;
    }*/
    bool isLeaf() const {
        return ((left == nullptr)&& (right==nullptr));
    }

    void printNode(tnode *root) const{
        if(root == nullptr)
            return;
        std::cout<<root->freq<<" "<<root->letter<<std::endl;
        printNode(root->left);
        printNode(root->right);
        }
};

tnode* setNode(char _let, unsigned int _freq, tnode* _left, tnode* _right ) {
    tnode* node = new tnode();
    node->letter = _let;
    node->freq = _freq;
    node->left = _left;
    node->right = _right;

    return node;
}


struct comp {
    bool operator() (tnode* l, tnode* r)
    {
        return l->freq > r->freq;
    }
};

void encode (tnode* root, std::string str, std::map<char,std::string> &huffmanCode)
{
    if (root==nullptr)
        return;
    if (!root->left && !root->right) {
        huffmanCode[root->letter] = str;
    }
    encode(root->left, str + "0", huffmanCode);
    encode(root->right, str + "1", huffmanCode);

}



void buildTreeHuff (std::string namereadfile, std::string namecreatefile)
{
    std::map <char, int> tablefreq;
    char scanletter;
    std::ifstream fin(namereadfile);

    if (fin.is_open()) {
        while(!fin.eof()) {
            fin.get(scanletter);
            tablefreq[scanletter]++;
        }
    }
    else {
        std::cout<<"Not open file"<<std::endl;
        return;
    }

    std::priority_queue<tnode*, std::vector<tnode*>, comp> priorityQueue;

    for(auto item: tablefreq) {
        priorityQueue.push(setNode(item.first, item.second, nullptr, nullptr));
    }

    while(priorityQueue.size()!=1) {
        tnode *left = priorityQueue.top(); priorityQueue.pop();
        tnode *right = priorityQueue.top(); priorityQueue.pop();
        unsigned int sum = left->freq + right->freq;
        priorityQueue.push(setNode((char) 0, sum, left, right));
    }
    tnode* root = priorityQueue.top();
    std::map <char, std::string> huffCode;
    encode(root, "", huffCode);
    std::string str = "";

    std::ofstream fout(namecreatefile);
    fin.close();
    fin.open(namereadfile);
    if (fin.is_open()) {
        while(!fin.eof()) {
            fin.get(scanletter);
            str+= huffCode[scanletter];
        }
    }
    else {
        std::cout<<"Not open file"<<std::endl;
        return;
    }
    fout<<str;

    for(auto item: huffCode) {
        fout<<item.second;
        std::cout << item.first << " " << item.second << std::endl;
    }
    fout.close();
    fin.close();
}



int main() {
  /*  std::map <char, int> tablefreq;
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

*/
    buildTreeHuff("testfile", "writefile");

    //for (auto&& item : tablefreq)
    //    std::cout << item.first << ": " << item.second << std::endl;
    return 0;
}
