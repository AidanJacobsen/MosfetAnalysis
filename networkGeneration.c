#include <stdbool.h>
#include <stdlib.h>  // For memory allocation functions
#include <stdio.h>

#include "structs.h"

// Define the structures as previously mentioned.

// Function to create a new Mosfet and add it to the end of MosfetList.
Mosfet * generateMosfet(MosfetList* mList,
                      Node* inputNode,
                      Node* gateNode,
                      Node* outputNode,
                      bool type) {
    // Create a new Mosfet.
    Mosfet* newMosfet = (Mosfet*)malloc(sizeof(Mosfet));
    
    if (newMosfet == NULL) {
        return NULL;
    }
    
    // Initialize the new Mosfet with the provided values.
    newMosfet->input = inputNode;
    newMosfet->gate = gateNode;
    newMosfet->output = outputNode;
    newMosfet->type = type;
    newMosfet->next = NULL;
    newMosfet->prev = NULL;
    
    // Check if the MosfetList is empty.
    if (mList->head == NULL) {
        mList->head = newMosfet;
        mList->tail = newMosfet;
    } else {
        // Add the new Mosfet to the end of the list.
        mList->tail->next = newMosfet;
        newMosfet->prev = mList->tail;
        mList->tail = newMosfet;
    }
    return newMosfet;
}

// Function to initialize a Node.
Node* initializeNode() {
    // Create and initialize a new Node.
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        // Handle memory allocation error by returning NULL.
        return NULL;
    }
    newNode->isSet = false;
    newNode->isHigh = false;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Function to copy one MosfetList into another with separate objects.
bool copyMosfetList(MosfetList* destList, const MosfetList* srcList) {
    // Initialize the destination MosfetList.
    destList->head = NULL;
    destList->tail = NULL;
    
    // Temporary pointer to keep track of the newly created Mosfet objects.
    Mosfet* newMosfet = NULL;

    // Iterate through the source MosfetList and create separate copies.
    Mosfet* srcMosfet = srcList->head;
    while (srcMosfet != NULL) {
        // Create a new Mosfet using generateMosfet.
        newMosfet = generateMosfet(destList, srcMosfet->input, srcMosfet->gate, srcMosfet->output, srcMosfet->type);
        if (newMosfet == NULL) {
            // Memory allocation error, free the Mosfet objects created so far.
            while (destList->head != NULL) {
                Mosfet* temp = destList->head;
                destList->head = destList->head->next;
                free(temp);
            }
            return false;
        }
        
        // Move to the next Mosfet in the source list.
        srcMosfet = srcMosfet->next;
    }
    
    // Return true when the copy operation is successful.
    return true;
}

// Function to initialize the network with 4 initial nodes and 1 Mosfet.
void initializeNetwork(NodeList* nList, MosfetList* mList) {

    // Initialize a NodeList with 4 initial Nodes.
    nList->head = NULL;
    nList->tail = NULL;
    
    for (int i = 0; i < 4; i++) {
        // Create and initialize a new Node.
        Node* newNode = initializeNode();
        
        // Add the new Node to the NodeList.
        if (nList->head == NULL) {
            nList->head = newNode;
            nList->tail = newNode;
        } else {
            newNode->prev = nList->tail;
            nList->tail->next = newNode;
            nList->tail = newNode;
        }
    }
    
    // Create and initialize a Mosfet and add it to the MosfetList.
    ;
    mList->head = NULL;
    mList->tail = NULL;
    
    // Replace these with actual Node pointers and boolean values.
    Node* inputNode = nList->head;
    Node* gateNode = nList->head->next;
    Node* outputNode = nList->tail;
    bool mosfetType = true;
    
    generateMosfet(mList, inputNode, gateNode, outputNode, mosfetType);

    nList->head->isHigh = 2;
    nList->tail->isHigh = 4;

    printf("%d\n", mList->tail->output->isHigh);
    
    // Add more Mosfets or Nodes to the network as needed.
    // Don't forget to free the memory for all allocated Mosfets, Nodes, and Lists when done.
}