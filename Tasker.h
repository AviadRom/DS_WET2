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
<<<<<<< HEAD
    Tasker (int size = 0, int taskIDs[] = NULL, int taskPriorities[] = NULL):IdHash(size){
=======
    Tasker (int size = 0, int taskIDs[] = NULL, int taskPriorities[] = NULL){
        //initialize hash table and heaps
>>>>>>> 61f1edb7a7f8d88830a506652e20bc884e664ab9
    }
    /*Get&Set methods for any relevant class property*/
    
    StatusType AddTask(int taskID, int priority){

   /*     if (IdHash.IsIn(taskID)){
            return FAILURE;
        }*/
<<<<<<< HEAD
    /*    try {
=======
        try {
>>>>>>> 61f1edb7a7f8d88830a506652e20bc884e664ab9
        	Task task(taskID,priority);
        	HashResult result=IdHash.Insert(task);
        	if (result == HASH_TABLE_DATA_ALREADY_EXIST){
        		return FAILURE;
        	}
<<<<<<< HEAD
        	MaxPriHeap.Insert(task);
        	MinPriHeap.Insert(task);
=======
        	MaxHeap.InsertElement(task);
        	MinHeap.InsertElement(task);
>>>>>>> 61f1edb7a7f8d88830a506652e20bc884e664ab9

        } catch (bad_alloc& b){
            return ALLOCATION_ERROR;
        }*/
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
       /* if (!IdHash.IsIn(taskID)){
            return FAILURE;
        }*/
        //1. get task from hash table
        //2. change priority
        //3. sift-down fixes to the heaps if neccessary.
        return SUCCESS;
    }
    
    StatusType Cancel (int taskID){
     /*   if (!IdHash.IsIn(taskID)){
            return FAILURE;
        }*/
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
<<<<<<< HEAD
        Task tmp = MinPriHeap.FindMax();//should change to the right heap function
        *taskID = tmp.GetId();
=======
        Task tmp = MinPriHeap.GetRoot();//should change to the right heap function
        *taskID = tmp.GetID();
>>>>>>> 61f1edb7a7f8d88830a506652e20bc884e664ab9
        *priority = tmp.GetPriority();
        return SUCCESS;
    }
    
    StatusType GetKthTask(int k, int* taskID, int* priority){
/*        if (taskID == NULL || priority == NULL || k > IdHash.GetNumOfElements() || k < 1){
            return INVALID_INPUT;
        }*/
        // DO MAGIC
        return SUCCESS;
    }
    
    ~Tasker(){}
};


#endif
