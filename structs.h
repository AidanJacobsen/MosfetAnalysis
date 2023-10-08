#include <stdbool.h>

// Define the Node structure with two boolean members.
struct Node {
    bool isSet;
    bool isHigh;
    struct Node* next;  // Pointer to the next Node in the NodeList.
    struct Node* prev;  // Pointer to the previous Node in the NodeList.
};

// Define the NodeList structure that will hold Node elements.
struct NodeList {
    struct Node* head;  // Pointer to the first Node in the list.
    struct Node* tail;  // Pointer to the last Node in the list.
};

// Define the Mosfet structure with three pointers to Node and a boolean.
struct Mosfet {
    struct Node* Input;
    struct Node* Gate;
    struct Node* Output;
    bool type;
    struct Mosfet* next;  // Pointer to the next Mosfet in the MosfetList.
    struct Mosfet* prev;  // Pointer to the previous Mosfet in the MosfetList.
};

// Define the MosfetList structure that will hold Mosfet elements.
struct MosfetList {
    struct Mosfet* head;  // Pointer to the first Mosfet in the list.
    struct Mosfet* tail;  // Pointer to the last Mosfet in the list.
};