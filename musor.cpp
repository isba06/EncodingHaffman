//
// Created by wwwis on 10.11.2021.
//


class Tree {
public:
    tnode* root;
private:

    void destroySubTree(tnode* nodee) {			// Used to destroy a subtree

        if (nodee != nullptr) {
            destroySubTree(nodee->left);
            destroySubTree(nodee->right);

            delete nodee;

            nodee = nullptr;
        }
    }

    void inOrder(tnode* root) {				// Displaying binary tree
        if (root != nullptr) {
            inOrder(root->left);
            std::cout << "|     " << root->letter << "    |     " << root->freq << "\t|" << std::endl;
            std::cout << " ----------------------- " << std::endl;
            inOrder(root->right);
        }
    }

    void encodingTree(tnode* root, std::string str, int n, char charArray[], std::string stringArray[])  	// Recursively finds the bit strings for every symbol in the tree
    {
        if (root == nullptr)
            return;

        // found a leaf node
        if (!root->left && !root->right) {

            int index=0;
            for (int i = 0; i < n; i++) {
                if (charArray[i] == root->letter) {
                    index = i;
                    break;
                }
            }

            stringArray[index] = str;
        }

        encodingTree(root->left, str + "0", n, charArray, stringArray);
        encodingTree(root->right, str + "1", n, charArray, stringArray);
    }

    void copyTreeToSelf(tnode*& copiedTreeRoot, tnode* otherTreeRoot)  		// Copying second tree to the first
    {
        if (otherTreeRoot == nullptr)
            copiedTreeRoot = nullptr;

        else
        {
            copiedTreeRoot = new tnode;
            copiedTreeRoot->letter = otherTreeRoot->letter;
            copiedTreeRoot->freq = otherTreeRoot->freq;

            copyTreeToSelf(copiedTreeRoot->left, otherTreeRoot->left);
            copyTreeToSelf(copiedTreeRoot->right, otherTreeRoot->right);
        }
    }

public:

    Tree() {
        root = nullptr;
    }

    ~Tree()
    {
        this->destroySubTree(root);
    }

    void displayPostOrder()
    {
        std::cout << " ----------------------- " << std::endl;
        std::cout << "   Node    |    Freq " << std::endl;
        std::cout << " ----------------------- " << std::endl;
        this->inOrder(root);
    }

    void copyTree(tnode* otherTreeRoot)
    {
        this->copyTreeToSelf(root, otherTreeRoot);
    }

    void encode(int n, char charArray[], std::string stringArray[])
    {
        std::string str;
        this->encodingTree(root, str, n, charArray, stringArray);
    }
};


class Queue
{
    tnode* queueArray;
    int queueSize;
    int front;
    int rear;
    int numItems;

public:

    Queue()
    {
        queueArray = NULL;
        queueSize = 0;
        front = -1;
        rear = -1;
        numItems = 0;
    }

    Queue(int size)
    {
        queueArray = new tnode[size];
        queueSize = size;
        front = -1;
        rear = -1;
        numItems = 0;
    }

    void resize() {		// doubles the queue size

        tnode* temp = new tnode[queueSize];

        for (int i = 0; i < queueSize; i++)
            temp[i] = queueArray[i];

        delete[] queueArray;

        queueSize *= 2;
        queueArray = new tnode[queueSize];

        for (int i = 0; i < numItems; i++)
            queueArray[i] = temp[i];

        delete[] temp;
    }

    void initializeQueue(int size)
    {
        if (queueArray != NULL)
            delete[]queueArray;

        queueArray = new tnode[size];
        queueSize = size;
        front = -1;
        rear = -1;
        numItems = 0;
    }

    ~Queue()
    {
        delete[]queueArray;
    }

    bool isFull()
    {
        if (numItems < queueSize)
            return false;
        return true;
    }

    int returnIndex(char c)
    {
        for (int i = 0; i < numItems; i++)
        {
            if (queueArray[i].letter == c)
                return i;
        }

        return -1;
    }

    bool incFreq(int index)
    {
        if (queueArray != NULL and index >= 0 and index < numItems)
        {
            queueArray[index].freq++;
            return true;
        }

        return false;
    }

    void sort()
    {
        if (isEmpty())
            return;

        int i, j;
        for (i = front + 1; i < front + numItems; i++)
        {
            tnode temp = queueArray[i];
            for (j = i; j > 0 && temp.freq < queueArray[j - 1].freq; j--)
            {
                queueArray[j] = queueArray[j - 1];
            }
            queueArray[j] = temp;
        }
    }

    void enqueue(tnode dataItem)
    {
        if (front == -1)
            front = 0;

        rear = rear + 1;
        numItems++;
        queueArray[rear] = dataItem;

        if (numItems == queueSize)
            this->resize();

        sort();
    }

    tnode dequeue()
    {
        tnode temp;

        if (this->isEmpty())
        {
            std::cout << "Queue is empty.\n";
            return temp;
        }

        else
        {
            temp = queueArray[front];
            front++;
            numItems--;

            return temp;
        }
    }

    bool isEmpty() const
    {
        if (numItems == 0)
            return true;
        return false;
    }

    void display()
    {
        std::cout << " --------------------- " << std::endl;
        std::cout << " Character |    Freq " << std::endl;
        std::cout << " --------------------- " << std::endl;
        for (int i = front; i < front + numItems; i++)
        {
            std::cout << "|     " << queueArray[i].letter << "    |     " << queueArray[i].freq << "    | " << std::endl;
            std::cout << " --------------------- " << std::endl;
        }
    }

    int numOfItems()
    {
        return numItems;
    }
};
Queue freqQueue;
Tree tree;
void constructTree()
{
    tnode* tempRoot = new tnode;
    tnode left;
    tnode right;

    while (freqQueue.numOfItems() > 1) {

        // extracting first two nodes from the queue and copying their values to the temporary root //

        tempRoot->letter = '*';
        left = freqQueue.dequeue();
        right = freqQueue.dequeue();

        tempRoot->left = new tnode;
        tempRoot->right = new tnode;
        tempRoot->left->letter = left.letter;
        tempRoot->left->freq = left.freq;
        tempRoot->right->letter = right.letter;
        tempRoot->right->freq = right.freq;

        // copying the children (if any) of the dequeued nodes //

        if (left.left != nullptr)
            tempRoot->left->left = left.left;

        if (left.right != nullptr)
            tempRoot->left->right = left.right;

        if (right.left != nullptr)
            tempRoot->right->left = right.left;

        if (right.right != nullptr)
            tempRoot->right->right = right.right;

        tempRoot->freq = left.freq + right.freq;

        // enqueueing the new tree //

        freqQueue.enqueue(*tempRoot);

        freqQueue.sort();
        //freqQueue.display();
        //cout << "Insertion Completed" << endl << endl;
    }

    // dequeuing the last node (a fully formed tree) and copying it to the main symbol tree //

    tnode finalNode = freqQueue.dequeue();
    tree.copyTree(&finalNode);
}





//2

struct BinaryTree {
    tnode* root;

    BinaryTree() : root(nullptr) {}
    BinaryTree(tnode* _root) : root(_root) {}
    unsigned int getFreq() const {
        return root->freq;
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