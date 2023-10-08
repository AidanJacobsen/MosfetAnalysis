#include <stdio.h>  // Standard Input/Output Library
#include <stdlib.h> // Standard Library
#include "mosfet.h"  // Include the header file that defines MOSFET structures

int main() {
    // Initialize your MosfetList and NodeList and expectedOutputs here
    struct MosfetList mosfetList;  // Initialize your MOSFET list
    // Initialize your MOSFET list (e.g., mosfetList.head = NULL, mosfetList.tail = NULL)

    struct NodeList nodeList;  // Initialize your node list
    // Initialize your node list (e.g., nodeList.head = NULL, nodeList.tail = NULL)

    bool expectedOutputs[8] = {0, 1, 0, 1, 0, 1, 0, 1};  // Placeholder for expected outputs

    // Process MOSFETs with conditions
    if (!(processMOSFETsWithConditions(&nodeList, &mosfetList, expectedOutputs))) {
        printf("MOSFET processing with conditions successful.\n");
    }

    return 0;
}

bool processAllMOSFETs(struct MosfetList* mosfetList) {
    struct Mosfet* currentMOSFET = mosfetList->head;

    // Traverse the MOSFET list and process each MOSFET
    while (currentMOSFET != NULL) {
        // Process the current MOSFET
        if(processMOSFET(currentMOSFET)){break;}
        currentMOSFET = currentMOSFET->next;  // Move to the next MOSFET
    }
    if(currentMOSFET != NULL){
        return 1;
    }
    return 0;
}

bool processMOSFET(struct Mosfet* mosfet, ) {
    if (mosfet->type && mosfet->Input->isSet && mosfet->Input->isHigh && mosfet->Gate->isSet && !(mosfet->Gate->isHigh)) {
        if(mosfet->Output->isSet && !(mosfet->Output->isHigh)){
            printf("error 1=0");
            return 1;
        }    
        mosfet->Output->isSet = true;
        mosfet->Output->isHigh = true;
        return 0

    } else if (!(mosfet->type) && mosfet->Input->isSet && !(mosfet->Input->isHigh) && mosfet->Gate->isSet && mosfet->Gate->isHigh) {
        if(mosfet->Output->isSet && mosfet->Output->isHigh){
            printf("error 0=1");
            return 1;
        }        
        mosfet->Output->isSet = true;
        return 0
    }
    
}

void resetMOSFETNodes(struct Mosfet* mosfet) {
    while (mosfet != NULL) {
        mosfet->Input->isSet = false;
        mosfet->Input->isHigh = false;

        mosfet->Gate->isSet = false;
        mosfet->Gate->isHigh = false;

        mosfet->Output->isSet = false;
        mosfet->Output->isHigh = false;

        mosfet = mosfet->next;  // Move to the next MOSFET
    }
}

bool processMOSFETsWithConditions(struct NodeList* nodeList, struct MosfetList* mosfetList, bool* expectedOutputs) {
    struct Node* outputNode = nodeList->head->next->next->next;
    struct Node* firstNode = nodeList->head;

    for (int i = 0; i < 8; i++) {
        resetMOSFETNodes(mosfetList);

        // Set node properties based on the iteration
        firstNode->isSet = true;
        firstNode->isHigh = (i > 3);
        firstNode->next->isSet = true;
        firstNode->next->isHigh = (i > 5 || (i < 4 && i > 1));
        firstNode->next->next->isSet = true;
        firstNode->next->next->isHigh = (i % 2 == 1);

        if (processAllMOSFETs(mosfetList)) {
            return true;  // Error occurred during MOSFET processing
        }

        if (!(outputNode->isSet) || !(expectedOutputs[i] == outputNode->isHigh)) {
            printf("Output node isHigh: %d, Expected: %d\n", outputNode->isHigh, expectedOutputs[i]);
            return true;  // Error in expected output
        }
    }

    return false;  // All conditions passed successfully
}