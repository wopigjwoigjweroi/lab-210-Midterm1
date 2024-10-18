// COMSC-210 | Midterm #1 | Jeremiah Ortiz 
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

        if (temp->next) // 
            temp->next->prev = temp->prev; // Previous node is pointed at temporary node 
        else
            tail = temp->prev; // The temporary node's previous node is initialized at the tail 

        delete temp; // Temporary node is deleted
    }

    void delete_pos(int pos) { // Function that deletes position of a node
        if (!head) { // If theres no head, the list is empty 
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) { // If a position is found, 
            pop_front(); // remove the front node 
            return;
        }
    
        Node* temp = head; // Temporary node starts at the head of the list
    
        for (int i = 1; i < pos; i++){ // Traverses list, and if the temporary node exceeds the list size
            if (!temp) {
                cout << "Position doesn't exist." << endl; // the position doesn't exist
                return;
            }
            else
                temp = temp->next; // Temporary node points to the next node 
        }
        if (!temp) { // If the node exceeds the size limit
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) { // If the temporary node moves to the next node 
            pop_back(); // Calls the pop_back() function 
            return;
        }
        // Following pointers unlink multiple nodes
        Node* tempPrev = temp->prev; 
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp; // Temporary node is deleted
    }

    void push_back(int v) { // Function that adds nodes to the end of the list 
        Node* newNode = new Node(v); // A new node is created with a value
        if (!tail) // If theres no tail, then set the head and tail node equal to the new node
            head = tail = newNode;
        else {
            tail->next = newNode; // Tail node points next to the new node 
            newNode->prev = tail; // Tail node points previous to the end of the list 
            tail = newNode; // Tail node is updated to be the new node with the value
        }
    }
    
    void push_front(int v) { // Function that adds nodes to the front of the list
        Node* newNode = new Node(v); // New node is created with a value v
        if (!head) // If theres no head, then set the head and tail node equal to the new node 
            head = tail = newNode;
        else {
            newNode->next = head; // The node next to the new node points to the head 
            head->prev = newNode; // The node previous to the head node is the new node  
            head = newNode; // the head node is updated to be the new node 
        }
    }
    
    void pop_front() { // Function that removes head from the list 

        if (!head) { // If there is no head node, the list is empty 
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head; // Temporary node stores the head node

        if (head->next) { // If the head node points to another node
            head = head->next; // Move the head node to the node next to it 
            head->prev = nullptr; // The node previous to the head node becomes 0
        }
        else
            head = tail = nullptr; // Both the head and tail are set to nullptr 
        delete temp; // Delete the temporary head node 
    }

    void pop_back() { // Function that removes the tail from the list 
        if (!tail) { // If theres no tail node at the end, the list is empty 
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

    ~DoublyLinkedList() { // A destructor that allocates memory and deletes all the nodes 
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() { // Function that prints all the nodes from head to tail
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

    void print_reverse() { // Function that prints nodes from tail to head
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

 void every_other_element() {

        Node* current = head; // Starting point is at the head node 

        bool skip = false; // Ensures it skips every other element 

        while (current) {

            if (!skip) { // If theres an element that we don't want skipped, output it

                cout << current->data << " "; 
            }

            skip = !skip; // The skip bool functions simultaneously with the !skip statement

            current = current->next; // Current node is moved to the next one 
            
        }

        cout << endl; 
    }
};

int main() {

    DoublyLinkedList l; // Instance of class is created 
    
    l.push_back(1);  // Values are inputted into push_back function 
    l.push_back(2); 
    l.push_back(3);
    l.push_back(4); 
    l.push_back(5); 

    cout << "Every other element: "; 
    l.every_other_element(); 
    
    return 0;
}
