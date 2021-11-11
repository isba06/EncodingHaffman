#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <queue>
#include <unordered_map>
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
    long freq;
    char letter;
    tnode* left;
    tnode* right;
    bool isLeaf() const {
        return ((left == nullptr)&& (right==nullptr));
    }
};

tnode* setNode(char _let, long _freq, tnode* _left, tnode* _right ) {
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

void encode (tnode* root, std::string str, std::unordered_map<char,std::string> &huffmanCode)
{
    if (root==nullptr)
        return;
    if (!(root->left) && !(root->right)) {
        huffmanCode[root->letter] = str;
    }
    encode(root->left, str + "0", huffmanCode);
    encode(root->right, str + "1", huffmanCode);

}



void buildTreeHuff (std::string namereadfile, std::string namecreatefile)
{
    std::unordered_map <char, long> tablefreq;
    char scanletter;
    std::ifstream fin(namereadfile);
    if (fin.is_open()) {
        while(!fin.eof()) {
            fin.get(scanletter);
            if(fin.eof())
                break;
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
    std::cout << priorityQueue.top() << std::endl;
    while(priorityQueue.size()!=1) {
        std::cout << priorityQueue.top() << std::endl;
        tnode *left = priorityQueue.top(); priorityQueue.pop();
        tnode *right = priorityQueue.top(); priorityQueue.pop();
        long sum = left->freq + right->freq;
        priorityQueue.push(setNode('\0', sum, left, right));
    }
    tnode* root = priorityQueue.top();
    std::unordered_map <char, std::string> huffCode;
    encode(root, "", huffCode);
    std::string str = "";



    std::ofstream fout(namecreatefile);
    fin.close();
    fin.open(namereadfile);
    if (fin.is_open()) {
        while(!fin.eof()) {
            fin.get(scanletter);
            if(fin.eof())
                break;
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
    for (auto&& item : tablefreq)
        std::cout << item.first << ": " << item.second << std::endl;
    fout.close();
    fin.close();
}


int main() {

    buildTreeHuff("testfile", "writefile");

    //for (auto&& item : tablefreq)
    //    std::cout << item.first << ": " << item.second << std::endl;
    return 0;
}
