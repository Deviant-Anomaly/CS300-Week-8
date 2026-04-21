/* Makenzie VanAusdall
 CS300 Project Two
 April 13, 2026 */

#include <iostream>
#include <fstream> // for file handling
#include <vector> // to use vectors
#include <string> // to use strings
#include <sstream> // read lines in csv
#include <limits> // for numeric limits
#include <algorithm> // for transform function
#include <cctype> // for toUpper function

using namespace std;


// for case insensitive string comparison
static string toUpperStr(const string& s) {
    string out = s;
    transform(out.begin(), out.end(), out.begin(), [](unsigned char c) { return static_cast<char>(toupper(c)); });
    return out;
}

// define Course components for BST
struct Course {
    string courseNum;
    string courseTitle;
    vector <string> prerequisites;

    // initialize Course structure
    Course() = default;
};

// define Node for BST
struct Node {
    Course course;
    Node* left;
    Node* right;

    // default constructor for Node
    Node() {
        left = nullptr;
        right = nullptr;
    }
    // initialize node w/ a selected course
    Node (Course selCourse) {
        course = selCourse;
        left = nullptr;
        right = nullptr;
		}
};

// create BST class
class BinarySearchTree {
private: // private variables and functions
    Node* root;

    void addNode(Node* node, Course course);
    void inOrder(Node* node);
    void destroyNode(Node* node);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void insert(Course course);
    Course* search(string courseNum);
    void printAll();
};

// default constructor

BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}

void BinarySearchTree::destroyNode(Node* node) {
    if (node == nullptr) {
        return;
    }
    destroyNode(node->left);
    destroyNode(node->right);
    delete node;
}

// destructor to free memory
BinarySearchTree::~BinarySearchTree() {
    destroyNode(root);
}

// insert course
void BinarySearchTree::insert(Course course) {
    if (root == nullptr) {
        root = new Node(course);
    }
    else {
        addNode(root, course);
    }
}

void BinarySearchTree::addNode(Node* node, Course course) { // add new course to a node
    if (course.courseNum < node->course.courseNum) { // if course number is less than node course number, move left
        if (node->left == nullptr) {
            node->left = new Node(course);
        }
        else {
            addNode(node->left, course);
        }
    }
    else if (course.courseNum > node->course.courseNum) { // if course number is greater than node course number, move right
        if (node->right == nullptr) {
            node->right = new Node(course);
        }
        else {
            addNode(node->right, course);
        }
    }
    else { // if course number is the same, update the course info
        node->course = course;
    }
    return;
}
void BinarySearchTree::inOrder(Node* node) {
    if (node != nullptr) { // if not null, traverse left, print, traverse right
        inOrder(node->left);
        cout << node->course.courseNum << ": " << node->course.courseTitle << endl;
        inOrder(node->right);
    }
}

void BinarySearchTree::printAll() { // uses printAll to print inOrder
    inOrder(root);
}

// search for course with matching courseNum
Course* BinarySearchTree::search(string courseNum) {
    Node* current = root;
    while (current != nullptr) {
        if (courseNum == current->course.courseNum) {
            return &current->course;
        }
        else if (courseNum < current->course.courseNum) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    return nullptr; // course not found
}


// load file 
static void loadFile(string fileName, BinarySearchTree* bst) { // method to load a file
    string fields;
    string line;

    ifstream file(fileName); // open file

    if (file.is_open()) {
        while (getline(file, line)) {
            if (line.empty()) continue; // skip blank lines

            vector <string> prerequisites;
            stringstream ss(line);

            Course course;
            int ncount = 1; // counter to count fields in line

            while (getline(ss, fields, ',')) {
                if (ncount == 1) {
                    course.courseNum = toUpperStr(fields); // normalize course number to uppercase
                }
                else if (ncount == 2) {
                    course.courseTitle = fields;
                }
                else {
                    if (!fields.empty())
                        prerequisites.push_back(fields);
                }
                ncount++;
            }
            for (unsigned int i = 0; i < prerequisites.size(); ++i) { // remaining fields are prerequisites
                course.prerequisites.push_back(prerequisites[i]);
            }
            bst->insert(course); // store data into bst
        }
        file.close(); // remember to close file after done reading
    }
    else {
        cout << "Error opening file." << endl;
    }
}

int main(int argc, char* argv[]) {

    int userChoice = 0; // set variables and initialize
    string fileName = "";
    string searchCourse = "";

    // create BST instance
    BinarySearchTree* bst = new BinarySearchTree();

    do { // menu selection loop
        cout << "Welcome to the course planner. " << endl;
        cout << endl;
        cout << "   1. Load Data Structure." << endl;
        cout << "   2. Print Course List." << endl;
        cout << "   3. Print Course." << endl;
        cout << "   9. Exit" << endl;
        cout << endl;
        cout << "Enter your choice: " << endl;
        if (!(cin >> userChoice)) {
            // handles non-integer input
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max());
            cout << endl;
            cout << "Invalid input. Please enter a number from the menu." << endl;
            userChoice = 0; // resets userChoice to prevent infinite loop
            continue;
        }
      
        switch (userChoice) {
        case 1:
            cout << "Enter file name: " << endl;
            cin >> fileName;
            if (fileName.empty()) {
                cout << "File name cannot be empty. Please try again." << endl;
            }
            else {
            loadFile(fileName, bst);
            cout << "File loaded successfully. \n" << endl;
        }
            break;
        case 2:
            cout << "Here is a sample schedule:" << endl;
            cout << endl;
            bst->printAll(); // call printAll method
            cout << endl;
            
            break;
        case 3:
            cout << "What course do you want to know about? " << endl;
            cout << endl;
            cin >> searchCourse;
            searchCourse = toUpperStr(searchCourse); // normalize course number to uppercase
            {
                Course* found = bst->search(searchCourse);
                if (found != nullptr) {
                    cout << found->courseNum << ": " << found->courseTitle << endl;
					if (!found->prerequisites.empty()) { // if prereqs not empty, print them; otherwise list none
                        cout << "Prerequisites: ";
                        for (size_t i = 0; i < found->prerequisites.size(); ++i) {
                            cout << found->prerequisites[i];
                            if (i + 1 < found->prerequisites.size()) cout << ", ";
                        }
                        cout << endl;
                    }
                    else {
                        cout << "Prerequisites: None" << endl;
                    }
                }
                else { // course not in system
                    cout << "Course not found. Please make sure courses are loaded first." << endl;
                    cout << endl;
                }
            }
                break;
        case 9:
            cout << "Thank you for using the course planner!" << endl;
            break;
        default:
            if (userChoice != 1 && userChoice != 2 && userChoice != 3 && userChoice != 9) {
                cout << "Invalid menu option. Please select a valid menu option" << endl;
            }
            break;
            }
        } while (userChoice != 9); // exit when user selects 9

        return 0;
    }