#include <iostream>
#include <string>
#include <cmath>
#include <random>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>

#include "Graph.h"
#include "Node.h"

using namespace std;

using namespace chrono;

int main() {


Graph firsttry;

ifstream File("graph3.txt");       //CHANGE TEXT FILE HERE
if(!File.is_open()) {
    cout << "unable to open \n";
    return 1;
}






int vertex;

string line;
 while(getline(File, line)) {
    istringstream read(line);
    read >> vertex;
    firsttry.addNode(vertex);
    int neighbor; 
    double weight;                                              //reading in vertices and edges from file, placing them in nodes vector(adj list)
    while(read >> neighbor >> weight) {
        firsttry.addEdge(vertex, neighbor, weight);
    }
    
}

cout << "Vector filled\n";


 //NEW FUNCTIONS




auto startTime = high_resolution_clock::now();  //start timer
firsttry.MSTTravelingSalesman(); //Do MST Traveling Salesman
auto endTime = high_resolution_clock::now(); //finish timer
auto duration = duration_cast<milliseconds>(endTime - startTime); //calculate time

cout << "Time taken by function: " << duration.count() << " milliseconds" << endl; //print time



//BRUTE FORCE WILL GIVE LONG OUTPUT OF ALL PATHS SEARCHED, COMMENT IT OUT IF YOU WANT TO SEE MST OUTPUT AND DISTANCE(ABOVE)
//OR comment out all cout statements in brute force algorithm in Graph.h



 auto startTime2 = high_resolution_clock::now();  //start timer
cout << firsttry.BruteForceTS() << " is the shortest path" << endl; //do brute force 
auto endTime2 = high_resolution_clock::now(); //finish timer
auto duration2 = duration_cast<milliseconds>(endTime2 - startTime2); //calculate time

cout << "Time taken by function: " << duration2.count() << " milliseconds" << endl; //print time


cout << "Worked\n";



File.close(); 

    return 0;
}