#include <stdio.h>
#include "networkGeneration.h"
#include "structs.h"
#include "analysis.h"
#include <stdlib.h>
#define NUMOUTS 2

int main(int argc, char ** argv) {
    
    struct MosfetList mosfetList;  // Initialize your MOSFET list
    // Initialize your MOSFET list (e.g., mosfetList.head = NULL, mosfetList.tail = NULL)

    struct NodeList nodeList;  // Initialize your node list
    // Initialize your node list (e.g., nodeList.head = NULL, nodeList.tail = NULL)

    initializeNetwork(&nodeList, &mosfetList);

    bool expectedOutputs[NUMOUTS] = {0, 1};  // Placeholder for expected outputs

    // Process MOSFETs with conditions
    while () {
        initializeNetwork(&nodeList, &mosfetList);
        processMOSFETsWithConditions(&nodeList, &mosfetList, expectedOutputs, NUMOUTS)
        destroyNodeList(&nodeList);
        destroyMosfetList(&mosfetList);
    }
    printf("MOSFET processing with conditions successful.\n");
    return 0;
}




