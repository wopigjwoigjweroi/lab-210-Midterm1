#include <iostream>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20; // We create four constant integer variables 

// DoublyLinkedList class is created 
class DoublyLinkedList {
private:
    struct Node { // Struct named 'Node' is created which declares elements for the linked list
        int data;
        Node* prev;
        Node* next;
        Node(int val, Node* p = nullptr, Node* n = nullptr) {  // Consturctor for Node struct is created 
            data = val; 
            prev = p; // prev pointer is initialized with p
            next = n; // next pointer is initialized with p 
        }
    };

    Node* head; // Points to the head of the linked list
    Node* tail; // Points to the end of the linked list 

public:
    DoublyLinkedList() { head = nullptr; tail = nullptr; } // Class constructor initializes head and tail of linked list

    void insert_after(int value, int position) { // Function which creates a node if a position is specified 
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value); // New node is created 
        if (!head) {  // If statement stating if the head is empty then initialize the head and tail with the new node
            head = tail = newNode;
            return;
        }

        Node* temp = head; // Temporary node is created 
        for (int i = 0; i < position && temp; ++i) // Temporary node and position traverse the linked list
            temp = temp->next;

        if (!temp) { // If the temporary node has exceeded the size limit
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode; // Gets rid of the new node
            return;
        }

        newNode->next = temp->next; // Next to the new node points to the node next to the temporary node
        newNode->prev = temp; // Previous to the new node points to the temporary node
        if (temp->next) // If the temporary node points to the next node,
            temp->next->prev = newNode; // initialize the previous pointer to the new node
        else
            tail = newNode; // The new node creates becomes the tail 
        temp->next = newNode; // The node next to the temporary node points to the new node
    }

    void delete_val(int value) { // Function that deletes value of the first node 
        if (!head) return; // If theres no head node, the list is empty 

        Node* temp = head; // Temporary pointer node becomes the head node, and traverses from there
        
        while (temp && temp->data != value) // Traverse list until a node with a value is found
            temp = temp->next; // 

        if (!temp) return; // If theres no node with a value, stop

        if (temp->prev) // Temporary pointer node points to previous node 
            temp->prev->next = temp->next; // The previous temporary node becomes the next node 
        else
            head = temp->next; // Head is updated to the node next to the temporary node

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
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    
    return 0;
}
