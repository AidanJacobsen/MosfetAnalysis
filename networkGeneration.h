#ifndef NETWORK_GENERATION_H
#define NETWORK_GENERATION_H

#include <stdbool.h>
#include "structs.h"

// Define the structures for Node, NodeList, Mosfet, and MosfetList here.

// Function prototype for networkGeneration.
Node* initializeNode();
void initializeNetwork();
Mosfet* generateMosfet(MosfetList* mList, Node* inputNode, Node* gateNode, Node* outputNode, bool type);
void removeMosfet(MosfetList* mosfetList, Mosfet* targetMosfet);
void generateAllCombinations(NodeList* nodeList, MosfetList* mosfetList, int * combinationCounter, int mosfetsLeft);
bool addNode(NodeList* nodeList);
removeNode(NodeList* nodeList, Node* targetNode);

#endif  // NETWORK_GENERATION_H