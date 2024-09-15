#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <iostream>
#include "Edge.h"
#include "Node.h"
#include "NewPQ.h"
#include <unordered_map>
#include <stack>

#pragma once

class Graph
{
public:
    unordered_map<int, Node*> locationTable;
    //PriorityQueue pq(5);  //TRY TO REPLACE HEAPARRAY VECTOR IN HEAP W NODES VECTOR, OR COPY NODES TO HEAPARRAY
    vector<Node*> nodes;
   

    void addNode(int id) {
        Node* vert = new Node(id);          //creates Node instance and puts it into nodes list
        nodes.push_back(vert);
        locationTable[id] = vert;   
    }
    void addEdge(int s, int d, double w) {
        Node* source = nullptr;

        for(Node* node : nodes) {
            if(node->nodeID == s) {
                
                source = node;
                break;
            }
        }                //goes through nodes and finds matching source and destination for edge       
            
        if(source)  {                          //adds edge to that specific node's edges vector
        Edge edge(s, d, w);
        source->list.push_back(edge);
        
        
        }

    }


double BruteForceTS() {
    int start = 0;
    vector<int> vertices;                       //set start node and make vector of vertices to loop through

    
    

    for (Node* node : nodes) {
        if(node->nodeID != start) {
        vertices.push_back(node->nodeID); }   //put all nodeIds into vector except starting
}

double minDistance = INT_MAX;
vector<int> minPath;
cout << "Added all vertices to vector\n";

do{
    int currentIndex = start;
    double currDistance = 0.0;   
    vector<int> currentpath;                   //set currentindex as start and currentdistance as 0
for (int i = 0; i < vertices.size(); ++i) {
            Node* startNode = locationTable[currentIndex];                  //set start and end nodes(end depending on which iteration)
            Node* endNode = locationTable[vertices[i]];

            //cout << "start node: " << locationTable[currentIndex] << " end node: " << locationTable[vertices[i]] << endl;

            
            for (const Edge& edge : startNode->list) {
                if (edge.v == endNode->nodeID) {
                    currDistance += edge.w;
                    cout << "using endNode: " << endNode->nodeID << endl;           // Find the edge weight between the current and next vertex
                    cout << "curr distance now: " << currDistance << endl;
                    currentpath.push_back(endNode->nodeID);

                    if (currDistance > minDistance) {
                    break; // Break out of the loop for the current permutation(if over min distance)
                }

                break; // Break out of the inner loop(at end of path)
            }
            }

            currentIndex = vertices[i];                                 //set end index in path as current index(allows you to move to next vertice)
            cout << "curr index set to: " << vertices[i] << endl;
        }

        cout << "BROKE OUT OF LOOP--Path is done\n\n\n";            //breaks loop once path is completed
       
        Node* startNode = locationTable[currentIndex];
        Node* endNode = locationTable[start];                    // Add the weight of the edge from the last vertex back to the start
        for (const Edge& edge : startNode->list) {
            if (edge.v == endNode->nodeID) {
                currDistance += edge.w;
                currentpath.push_back(endNode->nodeID);
                break;
            }
        }

    
        cout << "Current shortest path val: " << currDistance << endl;

       
        minDistance = min(minDistance, currDistance);
        cout << "Updating minDistance(if applicable): " << minDistance << endl;    // Update the minimum path weight(if applicable) once path is done.
        if(currDistance < minDistance) {
            minPath = currentpath;
        }
        cout << "Minimum Path Nodes: ";
             for (int node : minPath) {   //print minPath
             cout << node << " ";
              }
        cout << endl;
        cout << "Restarting loop for new path...\n\n\n";

    } while (std::next_permutation(vertices.begin(), vertices.end()));      //starts next path

    return minDistance;                                                 //returns min path once all have been checked
}


void MSTTravelingSalesman() {

NewPQ MST(nodes.size());              //make Priority Queue for MST
                                      
    for (Node* node : nodes) {
        node->visited = false;
        node->parent = nullptr;      //Initialize all nodes in adj list and insert them into PQ
        node->key = 1e9;
        MST.insert(node);
    }

    
    nodes[0]->key = 0;
    MST.insert(nodes[0]);                   //insert source(0 vertex) into pq and make key=0

    while(!MST.isEmpty()) {
        Node* curr = MST.removeMin();    
        curr->visited = true;
        

        for(Edge edge : curr->list) {
            Node* neighbor = locationTable[edge.v];    //make neighbor node corresponding to current edge       
            

        if(!(neighbor->visited) && edge.w < neighbor->key) {    //if neighbor hasnt been visisted and key is larger
            neighbor->key = edge.w;
            neighbor->parent = curr;                                 //include next edge and set current as parent.
            MST.decreaseKey(neighbor, edge.w);
            
            
        }
     }
    }
    cout << " Prim done..." << endl;

    Node* startNode = nodes[0];
vector<int> parentList;

cout << "Preorder Tree Walk Output: \n";
vector<bool> visited(nodes.size(), false);
vector<int> list;               
list = preorderTraversal(startNode, visited, parentList);       //do preorder walk and save to list
list.push_back(nodes[0]->nodeID);
cout << endl;
for (int nodeID : list) {
    cout << nodeID << " ";                  //print preorder walk
}
cout << endl;

double totalDistance = calculateTotalDistance(list, nodes);
cout << "Total Distance: " << totalDistance << endl;                //print distance



cout << endl;

   
}




vector<int> preorderTraversal(Node* node, vector<bool>& visited, vector<int>& parentList) {
    vector<int> list;
    if (node != nullptr && !visited[node->nodeID]) {
        parentList.push_back(node->nodeID);
        visited[node->nodeID] = true;

        if (node->parent != nullptr) {
            preorderTraversal(node->parent, visited, parentList);       //base case(start node has no parent)
        }

        for (Edge edge : node->list) {
            preorderTraversal(locationTable[edge.v], visited, parentList);      //run again on neighbor
        }
    }
    return(parentList);
}

double calculateTotalDistance(const vector<int>& nodeList, const vector<Node*>& nodes) {
    double totalDistance = 0;

    
    for (size_t i = 1; i < nodeList.size(); ++i) {
        int currentNodeID = nodeList[i];                   
        Node* currentNode = nodes[currentNodeID];

        
        for (Edge edge : currentNode->list) {
            if (edge.v == nodeList[i - 1]) {        //go through nodes and add all distances
                totalDistance += edge.w;
                break;
            }
        }
    }

    return totalDistance;
}





private:
int numVertices;

};

#endif