#ifndef NEWPQ_H
#define NEWPQ_H

#include "Node.h"
#include <vector>
#pragma once

class NewPQ {                           //simplified version of PQ and Heap class w only extract, insert, and heapify
private:
    vector<Node*> heapArray;
    //unordered_map<int, size_t> position;
    int currentSize;
    int max;

public:
    vector<int> location;   
    NewPQ(int maxSize) {
        heapArray.reserve(maxSize + 1);         //make pq
        currentSize = 0;
        max = maxSize + 1;
    }

    void insert(Node* item) {
        heapArray.push_back(item);

        location.resize(max);
        location[item->nodeID] = currentSize;

        currentSize++;                      //insert into pq
        heapifyUp(currentSize - 1);

        
    }

    Node* removeMin() {
        if (isEmpty()) {
            return nullptr;
        }

        Node* minItem = heapArray[0];
        heapArray[0] = heapArray[currentSize - 1];      //extract min
        currentSize--;
        heapifyDown(0);

        return minItem;
    }

    bool isEmpty() const {
        return currentSize == 0;
    }

    void decreaseKey(Node* item, int newKey) {
        int index = location[item->nodeID];
        item->key = newKey;

        while (index > 0 && heapArray[index]->key < heapArray[(index - 1) / 2]->key) {
            swap(heapArray[index], heapArray[(index - 1) / 2]);
            location[heapArray[index]->nodeID] = index;
            location[heapArray[(index - 1) / 2]->nodeID] = (index - 1) / 2;
            index = (index - 1) / 2;
        }
    }

private:
    void heapifyUp(int index) {
        Node* newItem = heapArray[index];
        int parent = (index - 1) / 2;

        while (index > 0 && newItem->key < heapArray[parent]->key) {            //heapify, bubble up(compare w parent)
            heapArray[index] = heapArray[parent];
            index = parent;
            parent = (parent - 1) / 2;
        }

        heapArray[index] = newItem;
    }

    void heapifyDown(int index) {
        Node* root = heapArray[index];

        while (index * 2 + 1 < currentSize) {
            int child = 2 * index + 1;
            if (child < currentSize - 1 && heapArray[child]->key > heapArray[child + 1]->key) {     //heapify, bubble down(compare w child)
                child++;
            }

            if (root->key < heapArray[child]->key) {
                break;
            }

            heapArray[index] = heapArray[child];
            index = child;
        }

        heapArray[index] = root;
    }

    

};

#endif