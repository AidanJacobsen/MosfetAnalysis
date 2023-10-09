#include <stdio.h>  // Standard input/Output Library
#include <stdlib.h> // Standard Library
#include "structs.h"  // Include the header file that defines MOSFET structures
#include "analysis.h"

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
            //printf("error 1=0");
            return 1;
        }    
        mosfet->output->isSet = true;
        mosfet->output->isHigh = true;
        return 0;

    } else if (!(mosfet->type) && mosfet->input->isSet && !(mosfet->input->isHigh) && mosfet->gate->isSet && mosfet->gate->isHigh) {
        if(mosfet->output->isSet && mosfet->output->isHigh){
            //printf("error 0=1");
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
    Node* A = nodeList->head;
    Node* B = nodeList->head->next;
    Node* S = nodeList->head->next->next;
    Node* O = nodeList->head->next->next->next;
    Node* H = nodeList->head->next->next->next->next;
    Node* L = nodeList->head->next->next->next->next->next;
    for (int i = 0; i < numOuts; i++) {
        resetNodes(nodeList->head);

        // Set node properties based on the iteration
        switch (i) 
        {
            case 0:
                A->isHigh = 0;
                B->isHigh = 0;
                S->isHigh = 0;
                break;
            case 1:
                A->isHigh = 0;
                B->isHigh = 0;
                S->isHigh = 1;
                break;
            case 2:
                A->isHigh = 0;
                B->isHigh = 1;
                S->isHigh = 0;
                break;
            case 3:
                A->isHigh = 0;
                B->isHigh = 1;
                S->isHigh = 1;
                break;
            case 4:
                A->isHigh = 1;
                B->isHigh = 0;
                S->isHigh = 0;
                break;
            case 5:
                A->isHigh = 1;
                B->isHigh = 0;
                S->isHigh = 1;
                break;
            case 6:
                A->isHigh = 1;
                B->isHigh = 1;
                S->isHigh = 0;
                break;
            case 7:
                A->isHigh = 1;
                B->isHigh = 1;
                S->isHigh = 1;
                break;
            default:
                A->isHigh = 0;
                B->isHigh = 0;
                S->isHigh = 0;
        }
        A->isSet = true;
        B->isSet = true;

        S->isSet = true;

        H->isSet = true;
        H->isHigh = 1;

        L->isSet = true;
        L->isHigh = 0;

        if (processAllMOSFETs(mosfetList)) {
            return false;  // Error occurred during MOSFET processing
        }

        if (!(O->isSet) || !(expectedOutputs[i] == O->isHigh)) {
            //printf("Set %d\nOutput: %d\nExpected: %d\n", O->isSet, O->isHigh, expectedOutputs[i]);
            return false;  // Error in expected output
        }
        else
        {
            //printf("Succeeded on %d\n", i);
        }
    }

    return true;  // All conditions passed successfully
}

void destroyNodeList(struct NodeList* nodeList) {
    struct Node* current = nodeList->head;
    struct Node* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    // Reset the list
    nodeList->head = NULL;
    nodeList->tail = NULL;
}

void destroyMosfetList(struct MosfetList* mosfetList) {
    struct Mosfet* current = mosfetList->head;
    struct Mosfet* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    // Reset the list
    mosfetList->head = NULL;
    mosfetList->tail = NULL;
}