// iostream is #include'd so we're able to output to the console
#include <iostream>
// By using namespace std, we can utilize the classes/functions/objects in the C++ Standard Libray without having to
//use the std:: scope resolution operator before every usage.
using namespace std;

// These are constants that are utilized in main()
const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

// The DoublyLinkedList class is an implementation of the doubly linked list data structure
class DoublyLinkedList {
// The below data members and struct are private, meaning they can only be accessed directly by the DoublyLinkedList
// class.
private:
    // The Node struct represents a node in a doubly linked list
    struct Node {
        // The actual data in the node is of type int
        int data;
        // prev is a pointer to the previous node in the doubly linked list
        Node* prev;
        // next is a pointer to the next node in the doubly linked list
        Node* next;
        // This is a constructor for the Node struct with default values of nullptr for prev and next.
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            // The value of data is updated to val
            data = val;
            // The pointer prev is updated to point to p
            prev = p;
            // The pointer next is updated to point to n
            next = n;
        }
    };

    // This points to the head node of the doubly linked list, which is where the list begins
    Node* head;
    // This points to the tail node of the doubly linked list, which is where the list ends
    Node* tail;

// The following code is accessible outside of the DoublyLinkedList class
public:
    // This is the default constructor for the DoublyLinkedList class. When an object is created, the head and tail
    // pointers are set to nullptr.
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    // This method inserts a node with a data value of value at the position position
    void insert_after(int value, int position) {
        // If the position passed in the argument is less than 0, it's not a valid position
        if (position < 0) {
            // This outputs "Position must be >= 0." and a line break
            cout << "Position must be >= 0." << endl;
            // Nothing is returned and the function finishes executing
            return;
        }

        // A pointer newNode is initialized pointing to a new Node struct with the data value value
        Node* newNode = new Node(value);
        // If there is no head, the list is empty
        if (!head) {
            // head and tail both point to the new node
            head = tail = newNode;
            // Nothing is returned and the function finishes executing
            return;
        }

        // A pointer of type Node, temp, is initialized pointing where the head node points
        Node* temp = head;
        // Iterating until the position in the argument is reached
        for (int i = 0; i < position && temp; ++i)
            // Updating temp to point to the next node in the doubly linked list
            temp = temp->next;

        // If the end of the list was reached without the position being reached, the position was not in the list
        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            // newNode is deleted to avoid memory leaks
            delete newNode;
            return;
        }

        // This runs if the correct position was found. The new node is being inserted.
        // newNode's next pointer points where temp's next pointer
        newNode->next = temp->next;
        // newNode's prev pointer points to temp
        newNode->prev = temp;
        // If there was a node after temp, i.e. after the current positon
        if (temp->next)
            // The prev pointer for that node after temp is updated to be newNode
            temp->next->prev = newNode;
        else
            // If not, that means newNode is the new end of the list, and tail is updated to point to the new node
            tail = newNode;
        // temp's next pointer now points to newNode, and the insertion is complete
        temp->next = newNode;
    }

    void delete_val(int value) {
        if (!head) return;

        Node* temp = head;
        
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; 

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; 

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        delete temp;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(int v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(int v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }

    // The below function will output every other element of the doubly linked list. The return type is void since it
    // only outputs the elements; it doesn't need to return anything.
    void every_other_element() {
        // The value of the local variable outputElem will change as we traverse the nodes in the doubly linked list.
        // Because the first element should be output, outputElem is initialized with the value true.
        bool outputElem = true;

        // The cur pointer will be updated to point to the list node we're currently visiting as we traverse the doubly
        // linked list. It is initialized with the head node because we are going to traverse the list forward.
        Node* cur = head;

        // The condition below is equivalent to saying while cur != nullptr. When cur points to nullptr, we have reached
        // the end of the linked list since tail->next is nullptr.
        while (cur) {
            // If outputElem is true, that means we are on the correct element, i.e. the first, third, fifth, etc.
            if (outputElem)
                // The value of data for the current node is outputted. After that, a space is outputted.
                cout << cur->data << " ";
            // cur is updated to point to where its next pointer points, i.e. to the next node in the doubly linked list
            cur = cur->next;
            // outputElem is updated to be false if it was currently true and true if it was currently false
            outputElem = !outputElem;
        }
    }
};

// This program is the driver, demonstrating the use of the DoublyLinkedList class.
int main() {
    // This outputs 134
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    // Declaring a DoublyLinkedList objected with the variable name list
    DoublyLinkedList list;

    // Looping until the local variable i, which was initialized with the value 0, is no longer less than 10. On each
    // loop, the value of i increases by 1.
    for (int i = 0; i < 10; i++) {
        // Inside the for loop, the value i + 1 is being passed as an argument to the method push_back(), thus adding a
        // new node with a data value of i + 1 to the end of the doubly linked list.
        list.push_back(i+1);
    }

    // The print() method is called on list. It outputs the following: 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
    list.print(); //
    // The every_other_element() method is called on list. It outputs the following: 1, 3, 5, 7, 9
    list.every_other_element();

    // The return type of main is int, so 0 is returned at the end of the main function.
    return 0;
}