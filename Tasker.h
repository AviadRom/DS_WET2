//
//  Tasker.h
//  DS-WET2
//
//  Aviad Rom and Ohad Fireman
//

#ifndef DS_WET2_Tasker_h
#define DS_WET2_Tasker_h
#include <iostream>
#include "library2.h"
#include "Task.h"
#include "HashTable.h"
#include "Heap.h"
#include "AVLTree.h"

typedef HashTable<Task*, TaskCmp, TaskFunctions> TaskHash;
typedef Heap<Task, TaskFunctions> MaxHeap;
typedef Heap<Task, TaskFunctionsForMinHeap> MinHeap;

class Tasker{
private:
    TaskHash IdHash;
    MinHeap MinPriHeap;
    MaxHeap MaxPriHeap;
    int NumberOfTasks;
public:
    Tasker (int size = 0, int taskIDs[] = NULL, int taskPriorities[] = NULL){
        //initialize hash table and heaps
    }
    /*Get&Set methods for any relevant class property*/
    
    StatusType AddTask(int taskID, int priority){

   /*     if (IdHash.IsIn(taskID)){
            return FAILURE;
        }*/
        try {
        	Task task(taskID,priority);
        	HashResult result=IdHash.Insert(task);
        	if (result == HASH_TABLE_DATA_ALREADY_EXIST){
        		return FAILURE;
        	}
        	MaxHeap.InsertElement(task);
        	MinHeap.InsertElement(task);

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
        Task tmp = MinPriHeap.GetRoot();//should change to the right heap function
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
