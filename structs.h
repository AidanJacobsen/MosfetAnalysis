#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdbool.h>

// Define the Node structure with two boolean members.
typedef struct Node {
    bool isSet;
    bool isHigh;
    struct Node* next;  // Pointer to the next Node in the NodeList.
    struct Node* prev;  // Pointer to the previous Node in the NodeList.
} Node;

// Define the NodeList structure that will hold Node elements.
typedef struct NodeList {
    struct Node* head;  // Pointer to the first Node in the list.
    struct Node* tail;  // Pointer to the last Node in the list.
} NodeList;

// Define the Mosfet structure with three pointers to Node and a boolean.
typedef struct Mosfet {
    struct Node* input;
    struct Node* gate;
    struct Node* output;
    bool type;
    struct Mosfet* next;  // Pointer to the next Mosfet in the MosfetList.
    struct Mosfet* prev;  // Pointer to the previous Mosfet in the MosfetList.
} Mosfet;

// Define the MosfetList structure that will hold Mosfet elements.
typedef struct MosfetList {
    Mosfet* head;  // Pointer to the first Mosfet in the list.
    Mosfet* tail;  // Pointer to the last Mosfet in the list.
} MosfetList;

#endif