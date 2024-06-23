//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : Robert Umland
// Version     : 1.0
// Copyright   : Copyright © 2023 SNHU COCE
// Description : Lab 5-2 Binary Search Tree
//============================================================================

#include <iostream>
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

// Internal structure for tree node
struct Node {
    Bid bid;
    Node *left;
    Node *right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a bid
    Node(Bid aBid) :
            Node() {
        bid = aBid;
    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Bid bid);
    void inOrder(Node* node);
    void postOrder(Node* node);
    void preOrder(Node* node);
    Node* removeNode(Node* node, string bidId);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void PostOrder();
    void PreOrder();
    void Insert(Bid bid);
    void Remove(string bidId);
    Bid Search(string bidId);
    bool IsEmpty() {
        return root == nullptr;
    } //testing to see if binary search tree is empty.
    
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    //Initialize housekeeping variables
    root = nullptr;
}

/**
* Destructor helper
*/
void destroyNode(Node* node) { 
    if (node != nullptr) {
        destroyNode(node->left);
        destroyNode(node->right);
        delete node;
    }
}
/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {    
    // recurse from root deleting every node
    destroyNode(root);
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    // call inOrder fuction and pass root 
    inOrder(root);
}

/**
 * Traverse the tree in post-order
 */
void BinarySearchTree::PostOrder() {
    //call postOrder and pass root
    postOrder(root);
}

/**
 * Traverse the tree in pre-order
 */
void BinarySearchTree::PreOrder() {
    //call preOrder and pass root
    preOrder(root);
}



/**
 * Insert a bid
 */
void BinarySearchTree::Insert(Bid bid) {
    if (root == nullptr) {     // if root equarl to null ptr
        root = new Node(bid);  // root is equal to new node bid
    }
    else {
        addNode(root, bid);    // add Node root and bid
    }
}

/**
 * Remove a bid
 */
void BinarySearchTree::Remove(string bidId) {
    // remove node root bidID
    root = removeNode(root, bidId);
}

/**
 * Search for a bid
 */
Bid BinarySearchTree::Search(string bidId) {
    // set current node equal to root
    Node* current = root;

    // Traverse the tree until the bottom is reached or a matching bidId is found
    while (current != nullptr && current->bid.bidId != bidId) {
        if (bidId < current->bid.bidId) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    // If a matching bidId is found, return the bid
    if (current != nullptr && current->bid.bidId == bidId) {
        return current->bid;
    }
    // Return an empty bid if the bidId was not found
    Bid bid;
    return bid;
}

/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node* node, Bid bid) {
    if (bid.bidId < node->bid.bidId) { // if node is larger then add to left
        if (node->left == nullptr) {   // if no left node
            node->left = new Node(bid);// this node becomes left
        }
        else {
            addNode(node->left, bid);  // else recurse down the left node
        }
    }
    else {
        if (node->right == nullptr) {    // if no right node
            node->right = new Node(bid); // this node becomes right
        }
        else {
            addNode(node->right, bid);  // recurse down the left node
        }
    }
}
void BinarySearchTree::inOrder(Node* node) {
    if (node != nullptr) {    //if node is not equal to null ptr      
        inOrder(node->left);    //InOrder not left      
        cout << node->bid.bidId << " | " << node->bid.title << " | " << node->bid.amount << " | " << node->bid.fund << endl; //output bidID, title, amount, fund      
        inOrder(node->right);   //InOder right
    }
}
void BinarySearchTree::postOrder(Node* node) {
      //if node is not equal to null ptr
    if (node != nullptr) {
        postOrder(node->left);   //postOrder left
        postOrder(node->right);  //postOrder right
        cout << node->bid.bidId << " | " << node->bid.title << " | " << node->bid.amount << " | " << node->bid.fund << endl;//output bidID, title, amount, fund
    }
}

void BinarySearchTree::preOrder(Node* node) {
      //if node is not equal to null ptr   
    if (node != nullptr) {
        cout << node->bid.bidId << " | " << node->bid.title << " | " << node->bid.amount << " | " << node->bid.fund << endl; //output bidID, title, amount, fund
        preOrder(node->left); //postOrder left
        preOrder(node->right);//postOrder right
    }
}

/**
 * Remove a bid from some node (recursive)
 */
Node* BinarySearchTree::removeNode(Node* node, string bidId) {
    // Check if the node is null
    if (node == nullptr) {
        return node;
    }

    // Recurse down the left subtree if bidId is smaller
    if (bidId.compare(node->bid.bidId) < 0) {
        node->left = removeNode(node->left, bidId);
    }
    // Recurse down the right subtree if bidId is larger
    else if (bidId.compare(node->bid.bidId) > 0) {
        node->right = removeNode(node->right, bidId);
    }
    // Node to be deleted is found
    else {
        // Node is a leaf node
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            node = nullptr;
        }
        // Node has only one child (left)
        else if (node->left != nullptr && node->right == nullptr) {
            Node* temp = node;
            node = node->left;
            delete temp;
        }
        // Node has only one child (right)
        else if (node->right != nullptr && node->left == nullptr) {
            Node* temp = node;
            node = node->right;
            delete temp;
        }
        // Node has two children
        else {
            Node* temp = node->right;
            // Find the minimum node on the right subtree
            while (temp->left != nullptr) {
                temp = temp->left;
            }
            // Replace node's bid with temp's bid
            node->bid = temp->bid;
            // Remove the right node using recursive call
            node->right = removeNode(node->right, temp->bid.bidId);
        }
    }

    return node;
}




//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
            << bid.fund << endl;
    return;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadBids(string csvPath, BinarySearchTree* bst) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " | ";
    }
    cout << "" << endl;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            // push this bid to the end
            bst->Insert(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98223";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "CS 300 eBid_Monthly_Sales_Dec_2016.csv";
        //csvPath = "CS 300 eBid_Monthly_Sales.csv";
        bidKey = "98223";
    }

    // Define a timer variable
    clock_t ticks;

    // Define a binary search tree to hold all bids
    BinarySearchTree* bst;
    bst = new BinarySearchTree();
    Bid bid;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Find Bid" << endl;
        cout << "  4. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            
            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            loadBids(csvPath, bst);

            //cout << bst->Size() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            
            // Test if any bids were loaded
            if (bst->IsEmpty()) {
                cout << "No bids were loaded." << endl;
            }
            else {
                cout << "Bids loaded successfully." << endl;
            }

            break;

        case 2:
            bst->InOrder();
            break;

        case 3:
            ticks = clock();

            bid = bst->Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            } else {
            	cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 4:
            bst->Remove(bidKey);
            break;
        }
       
    }

    cout << "Good bye." << endl;

	return 0;
}
