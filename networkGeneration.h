#ifndef NETWORK_GENERATION_H
#define NETWORK_GENERATION_H

#include <stdbool.h>
#include "structs.h"

// Define the structures for Node, NodeList, Mosfet, and MosfetList here.

// Function prototype for networkGeneration.
Node* initializeNode();
void initializeNetwork(NodeList* nList, MosfetList* mList);
Mosfet* generateMosfet(MosfetList* mList, Node* inputNode, Node* gateNode, Node* outputNode, bool type);


#endif  // NETWORK_GENERATION_H