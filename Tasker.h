//
//  Tasker.h
//  DS-WET2
//
//  Created by Aviad Rom on 6/2/13.
//  Copyright (c) 2013 Aviad Rom. All rights reserved.
//

#ifndef DS_WET2_Tasker_h
#define DS_WET2_Tasker_h
#include <iostream>
#include "library2.h"
#include "Task.h"
#include "HashTable.h"
#include "Heap.h"

class Tasker{
private:
    HashTable IdHash;
    /*Data holders*/
    //max heap with priority key
    //min heap with priority key
    //hash table with ID key
public:
    Tasker (int size = 0, int[] taskIDs = NULL, int[] taskPriorities = NULL){
        //initialize hash table and heaps
    }
    /*Get&Set methods for any relevant class property*/
    
    StatusType AddTask(int taskID, int priority){
        if (HashTable.IsIn(taksID)){
            return FAILURE;
        }
        try {
            //add task to hash table and heaps.
        } catch (bad_alloc& b){
            return ALLOCATION_ERROR;
        }
        return SUCCESS;
    }
    
    StatusType NextTask(int* taskID, int* priority){
        if (taskID == NULL || priority == NULL){
            return FAILURE;
        }
        //maxheap.removemax();
        //fix heaps using siftdown
        //maxheap.getroot();
        //assign to pointers
        return SUCCESS;
    }
    
    StatusType SetPriority (int taskID,int priority){
        if (!HashTable.IsIn(taksID)){
            return FAILURE;
        }
        //1. get task from hash table
        //2. change priority
        //3. sift-down fixes to the heaps if neccessary.
        return SUCCESS;
    }
    
    StatusType Cancel (int taskID){
        if (!HashTable.IsIn(taksID)){
            return FAILURE;
        }
        // get task
        // remove from heaps and fix them
        // remove from hash table
        return SUCCESS;
    }
    
    StatusType LastTask(int* taskID, int* priority){
        if (taskID == NULL || priority == NULL){
            return INVALID_INPUT;
        }
        //get min-heap root
        Task tmp = MinHeap.GetRoot();
        *taskID = tmp.GetID();
        *priority = tmp.GetPriority();
        return SUCCESS;
    }

    StatusType GetKthTask(int k, int* taskID, int* priority){
        if (taskID == NULL || priority == NULL || k > HashTable.GetNumOfElements() || k < 1){
            return INVALID_INPUT;
        }
        // DO MAGIC
        return SUCCESS;
    }
    
    ~Tasker(){}
}


#endif
