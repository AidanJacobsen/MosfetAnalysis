#include <stdbool.h>
#include <stdlib.h>  // For memory allocation functions
#include <stdio.h>
#include "analysis.h"
#include "structs.h"
#define NUMOUTS 4


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


void printNodeIndex(Node * node, FILE* file)
{
    int index = 0;
    Node* currentNode = node;

    while(currentNode->prev != NULL)
    {
        index++;
        currentNode = currentNode->prev;
    }
    switch (index) {
        case 0:
            fprintf(file, "A");
            break;
        case 1:
            fprintf(file, "B");
            break;
        case 2:
            fprintf(file, "S");
            break;
        case 3:
            fprintf(file, "Out");
            break;
        case 4:
            fprintf(file, "High");
            break;
        case 5:
            fprintf(file, "Low");
            break;
        default:
            fprintf(file, "%d", index);
            break;
    }
}

void printMosfet(Mosfet * mosfet, FILE* file)
{
    if(mosfet->type == 1)
    {
        fprintf(file, "PMOS(");
        printNodeIndex(mosfet->input, file);
        fprintf(file, ", ");
        printNodeIndex(mosfet->gate, file);
        fprintf(file, ", ");
        printNodeIndex(mosfet->output, file);
        fprintf(file, ")\n");
    }
    else
    {
        fprintf(file, "NMOS(");
        printNodeIndex(mosfet->input, file);
        fprintf(file, ", ");
        printNodeIndex(mosfet->gate, file);
        fprintf(file, ", ");
        printNodeIndex(mosfet->output, file);
        fprintf(file, ")\n");
    }
}

void printMosfetArray(MosfetList * list)
{
    FILE* file = fopen("Sucessful_Files.txt","a");

    Mosfet * currentFet = list->head;
    while(currentFet != NULL)
    {
        printMosfet(currentFet, file);
        currentFet = currentFet->next;
    }
    fprintf(file, "\n");
    fclose(file);
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
    newNode->isDriving = false;
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

void removeMosfet(MosfetList* mosfetList, Mosfet* targetMosfet) {
    if (mosfetList->head == targetMosfet) {
        mosfetList->head = targetMosfet->next;
    }
    if (mosfetList->tail == targetMosfet) {
        mosfetList->tail = targetMosfet->prev;
    }
    if (targetMosfet->prev != NULL) {
        targetMosfet->prev->next = targetMosfet->next;
    }
    if (targetMosfet->next != NULL) {
        targetMosfet->next->prev = targetMosfet->prev;
    }
    
    // Free the memory of the removed Mosfet.
    free(targetMosfet);
}


void removeNode(NodeList* nodeList, Node* targetNode) {
    if (nodeList->head == targetNode) {
        nodeList->head = targetNode->next;
    }
    if (nodeList->tail == targetNode) {
        nodeList->tail = targetNode->prev;
    }
    if (targetNode->prev != NULL) {
        targetNode->prev->next = targetNode->next;
    }
    if (targetNode->next != NULL) {
        targetNode->next->prev = targetNode->prev;
    }
    
    // Free the memory of the removed Mosfet.
    free(targetNode);
}

// Function to add a node to a NodeList.
bool addNode(NodeList* nodeList) {
    // Create and initialize a new Node.
    Node* newNode = initializeNode();
    if (newNode == NULL) {
        // Memory allocation failed.
        return false;
    }

    // Check if the NodeList is empty.
    if (nodeList->head == NULL) {
        nodeList->head = newNode;
        nodeList->tail = newNode;
    } else {
        // Add the new node to the end of the list.
        newNode->prev = nodeList->tail;
        nodeList->tail->next = newNode;
        nodeList->tail = newNode;
    }

    return true;
}

void generateAllCombinations(NodeList* nodeList, MosfetList* mosfetList, unsigned long long * combinationCounter, int mosfetsLeft, int * succesCounter) {
    mosfetsLeft -= 1;
    Node* inputNode = nodeList->head;
    bool expectedOutputs[NUMOUTS] = {1, 1, 1, 0};  // Placeholder for expected outputs
    // Loop through the first node.
    while (inputNode != NULL) {
        Node* gateNode = nodeList->head;

        while (gateNode != NULL) {
            Node* outputNode = nodeList->head;

            while (outputNode != NULL) {
                //Check if combination won't loop (output node won't drive any mosfets already placed and wont drive itself)
                if(outputNode->isDriving == false && outputNode != inputNode && outputNode != gateNode)
                {
                    //Switch between nmos and pmoss
                    for(int mosfetType = 0; mosfetType < 2; mosfetType++)
                    {
                        // Create a new Mosfet for the combination.
                        Mosfet* newMosfet = generateMosfet(mosfetList, inputNode, gateNode, outputNode, mosfetType);//Input, gate, output
                        
                        bool previousInputDriving = inputNode->isDriving;
                        bool previousGateDriving = gateNode->isDriving;
                        inputNode->isDriving = true;
                        gateNode->isDriving = true;

                        if (newMosfet != NULL) {
                            // Successfully created a Mosfet with the combination.
                            // You can choose to perform additional actions here.

                            if(mosfetsLeft)
                            {
                                generateAllCombinations(nodeList, mosfetList, combinationCounter, mosfetsLeft, succesCounter);
                            }
                            else
                            {
                                //printf("Case %d:\n", *combinationCounter);
                                if(processMOSFETsWithConditions(nodeList, mosfetList, expectedOutputs, NUMOUTS))
                                {
                                    printf("Success\n");
                                    (*succesCounter)++;
                                    
                                    printMosfetArray(mosfetList);
                                    printf("\n\n");
                                }
                                //BASE CASE
                                (*combinationCounter) ++;
                                //printf("\n\n");
                            }
                        }

                        inputNode->isDriving = previousInputDriving;
                        gateNode->isDriving = previousGateDriving;
                        removeMosfet(mosfetList, newMosfet);
                    }
                }
                outputNode = outputNode->next;
            }
            gateNode = gateNode->next;
        }
        inputNode = inputNode->next;
    }

    if(mosfetsLeft != 0)
    {
        addNode(nodeList);
        inputNode = nodeList->head;

        // Loop through the first node.
        while (inputNode != NULL) {
            Node* gateNode = nodeList->head;

            while (gateNode != NULL) {
                Node* outputNode = nodeList->tail;//only allow final mosfet to be output

                while (outputNode != NULL) {
                    //Check if combination won't loop (output node won't drive any mosfets already placed and wont drive itself)
                    if(outputNode->isDriving == false && outputNode != inputNode && outputNode != gateNode)
                    {
                        //Switch between nmos and pmoss
                        for(int mosfetType = 0; mosfetType < 2; mosfetType++)
                        {
                            // Create a new Mosfet for the combination.
                            Mosfet* newMosfet = generateMosfet(mosfetList, inputNode, gateNode, outputNode, mosfetType);//Input, gate, output
                            
                            bool previousInputDriving = inputNode->isDriving;
                            bool previousGateDriving = gateNode->isDriving;
                            inputNode->isDriving = true;
                            gateNode->isDriving = true;

                            if (newMosfet != NULL) {
                                // Successfully created a Mosfet with the combination.
                                // You can choose to perform additional actions here.

                                if(mosfetsLeft)
                                {
                                    generateAllCombinations(nodeList, mosfetList, combinationCounter, mosfetsLeft, succesCounter);
                                }
                                else
                                {
                                    //BASE CASE
                                    //printf("Case %d:\n", *combinationCounter);
                                    if(processMOSFETsWithConditions(nodeList, mosfetList, expectedOutputs, NUMOUTS))
                                    {
                                        printf("Success");
                                        (*succesCounter)++;
                                        
                                        printMosfetArray(mosfetList);
                                        printf("\n\n");
                                    }
                                    (*combinationCounter) ++;
                                    //printf("\n\n");
                                }
                            }

                            inputNode->isDriving = previousInputDriving;
                            gateNode->isDriving = previousGateDriving;
                            removeMosfet(mosfetList, newMosfet);
                        }
                    }
                    outputNode = outputNode->next;
                }
                gateNode = gateNode->next;
            }
            inputNode = inputNode->next;
        }
        removeNode(nodeList, nodeList->tail);
    }
    return;
}


// Function to initialize the network with 4 initial nodes and 1 Mosfet.
void initializeNetwork(NodeList* nList, MosfetList* mList) {

    // Initialize a NodeList with 4 initial Nodes.
    nList->head = NULL;
    nList->tail = NULL;
    
    for (int i = 0; i < 6; i++) {
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
    
    // // Replace these with actual Node pointers and boolean values.
    // Node* inputNode = nList->head;
    // Node* gateNode = nList->head->next;
    // Node* outputNode = nList->tail;
    // bool mosfetType = true;
    
    // generateMosfet(mList, inputNode, gateNode, outputNode, mosfetType);

    // nList->head->isHigh = 2;
    // nList->tail->isHigh = 4;

    // printf("%d\n", mList->tail->output->isHigh);
    Node* A = nList->head;
    Node* B = nList->head->next;
    Node* S = nList->head->next->next;
    Node* O = nList->head->next->next->next;
    Node* H = nList->head->next->next->next->next;
    Node* L = nList->head->next->next->next->next->next;

    A->isDriving = 1;//Can't be driven
    B->isDriving = 1;//Can't be driven
    S->isDriving = 1;//Can't be driven

    int succesCounter = 0;
    unsigned long long combinationCounter = 0;
    generateAllCombinations(nList, mList, &combinationCounter, 4, &succesCounter);
    printf("Total combinations generated: %llu\n", combinationCounter);
    printf("Total successful combinations generated: %d\n", succesCounter);
    
    // Add more Mosfets or Nodes to the network as needed.
    // Don't forget to free the memory for all allocated Mosfets, Nodes, and Lists when done.
}