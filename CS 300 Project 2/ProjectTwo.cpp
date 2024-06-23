//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Robert Umland
// Version     : 1.0
// Copyright   : Copyright © 2023 SNHU COCE
// Description : Project Two CS 300
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm> // Add this line for transform
using namespace std;

// Define a structure to hold course information
struct Course {
    string courseNumber;
    string title;
    vector<string> prerequisites;
};

// Define a node for the binary search tree
class Node {
public:
    Course course;
    Node* left;
    Node* right;

    Node(Course course) {
        this->course = course;
        left = right = nullptr;
    }
};

// Define the binary search tree class
class BinarySearchTree {
private:
    Node* root;

    // Helper method to recursively add a node to the tree
    void addNode(Node* node, Course course) {
        if (course.courseNumber < node->course.courseNumber) {
            if (node->left == nullptr) {
                node->left = new Node(course);
            }
            else {
                addNode(node->left, course);
            }
        }
        else {
            if (node->right == nullptr) {
                node->right = new Node(course);
            }
            else {
                addNode(node->right, course);
            }
        }
    }

    // Helper method to perform an in-order traversal of the tree
    void InOrderTraversal(Node* node) {
        if (node != nullptr) {
            InOrderTraversal(node->left);
            PrintCourse(node->course);
            InOrderTraversal(node->right);
        }
    }

public:
    BinarySearchTree() {
        root = nullptr;
    }
    Node* GetRoot() {
        return root;
    }
    // Public method to insert a course into the tree
    void Insert(Course course) {
        if (root == nullptr) {
            root = new Node(course);
        }
        else {
            addNode(root, course);
        }
    }

    // Public method to print course details
    void PrintCourse(Course course) {
        cout << "\n\nCourse Number: " << course.courseNumber << endl;
        cout << "Title: " << course.title << endl;
        cout << "Prerequisites: ";
        if (course.prerequisites.empty()) { // If no prereq, print NONE
            cout << "NONE";
        }
        else {
            for (const auto& prereq : course.prerequisites) { // Prints prereqs
                cout << prereq << " ";
            }
        }
        cout << endl << endl;
    }

    // Public method to search for a course in the tree
    void SearchCourse(Node* node, string courseNumber) {
        if (node == nullptr) {
            cout << "Course not found" << endl;
            return;
        }

        // Convert both course numbers to lowercase for case-insensitive comparison
        string currentNodeCourse = node->course.courseNumber;
        transform(currentNodeCourse.begin(), currentNodeCourse.end(), currentNodeCourse.begin(), ::tolower);

        if (currentNodeCourse == courseNumber) {
            PrintCourse(node->course);
        }
        else if (courseNumber < currentNodeCourse) {
            SearchCourse(node->left, courseNumber);
        }
        else {
            SearchCourse(node->right, courseNumber);
        }
    }

    // Public method to load courses from a file
    void LoadCourses(string filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error opening file" << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string courseNumber, title, prereq1, prereq2;
            getline(ss, courseNumber, ',');
            getline(ss, title, ',');
            getline(ss, prereq1, ',');
            getline(ss, prereq2, ',');

            Course course;
            course.courseNumber = courseNumber;
            course.title = title;

            if (prereq1 != "") {
                course.prerequisites.push_back(prereq1);
            }
            if (prereq2 != "") {
                course.prerequisites.push_back(prereq2);
            }

            Insert(course);
        }

        file.close();
    }

    // Public method to print all courses in the tree
    void PrintAllCourses() {
        InOrderTraversal(root);
    }
};

// Function to display the menu and handle user input
void Menu(BinarySearchTree& tree) {
    while (true) {
        cout << "1. Load courses" << endl;
        cout << "2. Print all courses" << endl;
        cout << "3. Print course details" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter option: ";

        int option;
        if (!(cin >> option)) {
            cout << "Invalid option. Please try again." << endl;
            cin.clear(); // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            continue; // Restart the loop
        }

        cin.ignore(); // Clear the input buffer

        if (option == 1) {
            string filename;
            cout << "Enter filename: ";
            getline(cin, filename);  // Read entire line, including spaces
            tree.LoadCourses(filename);
        }
        else if (option == 2) {
            tree.PrintAllCourses();
        }
        else if (option == 3) {
            string courseNumber;
            cout << "Enter course number: ";
            getline(cin, courseNumber); // Read entire line, including spaces
            tree.SearchCourse(tree.GetRoot(), courseNumber);
        }
        else if (option == 9) {
            break;
        }
        else {
            cout << "Invalid option. Please try again." << endl;
        }
    }
}

int main() {
    BinarySearchTree tree;
    Menu(tree);
    cout << endl;
    return 0;
}
