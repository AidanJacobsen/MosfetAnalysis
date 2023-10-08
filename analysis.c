#include <stdio.h>  // Standard input/Output Library
#include <stdlib.h> // Standard Library
#include "structs.h"  // Include the header file that defines MOSFET structures
#define NUMOUTS 8

bool processAllMOSFETs(struct MosfetList* mosfetList);
bool processMOSFET(struct Mosfet* mosfet);
void resetMOSFETNodes(struct Mosfet* mosfet);
bool processMOSFETsWithConditions(struct NodeList* nodeList, struct MosfetList* mosfetList, bool* expectedOutputs, int numOuts);

int main() {
    // Initialize your MosfetList and NodeList and expectedOutputs here
    struct MosfetList mosfetList;  // Initialize your MOSFET list
    // Initialize your MOSFET list (e.g., mosfetList.head = NULL, mosfetList.tail = NULL)

    struct NodeList nodeList;  // Initialize your node list
    // Initialize your node list (e.g., nodeList.head = NULL, nodeList.tail = NULL)

    bool expectedOutputs[NUMOUTS] = {0, 1, 0, 1, 0, 1, 0, 1};  // Placeholder for expected outputs

    // Process MOSFETs with conditions
    if (!(processMOSFETsWithConditions(&nodeList, &mosfetList, expectedOutputs, NUMOUTS))) {
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

bool processMOSFET(struct Mosfet* mosfet) {
    if (mosfet->type && mosfet->input->isSet && mosfet->input->isHigh && mosfet->gate->isSet && !(mosfet->gate->isHigh)) {
        if(mosfet->output->isSet && !(mosfet->output->isHigh)){
            printf("error 1=0");
            return 1;
        }    
        mosfet->output->isSet = true;
        mosfet->output->isHigh = true;
        return 0;

    } else if (!(mosfet->type) && mosfet->input->isSet && !(mosfet->input->isHigh) && mosfet->gate->isSet && mosfet->gate->isHigh) {
        if(mosfet->output->isSet && mosfet->output->isHigh){
            printf("error 0=1");
            return 1;
        }        
        mosfet->output->isSet = true;
        return 0;
    }
    return 0;
}

void resetNodes(struct Node* node) {
    while (node != NULL) {
        node->isSet = false;
        node->isHigh = false;

        node = node->next;  // Move to the next node
    }
}

bool processMOSFETsWithConditions(struct NodeList* nodeList, struct MosfetList* mosfetList, bool* expectedOutputs, int numOuts) {
    struct Node* outputNode = nodeList->head->next->next->next;
    struct Node* firstNode = nodeList->head;

    for (int i = 0; i < numOuts; i++) {
        resetNodes(firstNode);

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