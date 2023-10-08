#ifndef ANALYSIS_H
#define ANALYSIS_H

#include <stdbool.h>
#include "structs.h"

bool processAllMOSFETs(struct MosfetList* mosfetList);
bool processMOSFET(struct Mosfet* mosfet);
void resetNodes(struct Node* mosfet);
bool processMOSFETsWithConditions(struct NodeList* nodeList, struct MosfetList* mosfetList, bool* expectedOutputs, int numOuts);
void destroyMosfetList(struct MosfetList* mosfetList);
void destroyNodeList(struct NodeList* nodeList);

#endif  // NETWORK_GENERATION_H
