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

typedef HashTable<AVLTask, TaskCmp, TaskFunctions> TaskHash;
typedef Heap<HeapTask, HeapTaskFunctions> MaxHeap;
typedef Heap<HeapTask, MinHeapTaskFunctions> MinHeap;

class Tasker{
private:
    TaskHash IdHash;
    MinHeap MinPriHeap;
    MaxHeap MaxPriHeap;
    int NumberOfTasks;
public:
 Tasker (int size = 0, int taskIDs[] = NULL, int taskPriorities[] = NULL):IdHash(size),
    MinPriHeap(size), MaxPriHeap(size),NumberOfTasks(size){
        HeapTask* htArray = new HeapTask[size];
        for (int i = 0; i < size; i++){
            AVLTask avl(taskIDs[i], taskPriorities[i]);
            IdHash.Insert(avl);
            AVLTask* forHeap = IdHash.Find(avl);
            HeapTask tmp(taskIDs[i], taskPriorities[i],forHeap);
            htArray[i] = tmp;
        }
        MaxPriHeap.MakeHeap(htArray,size);
        MinPriHeap.MakeHeap(htArray,size);
        delete[] htArray;
        
    }
    /*Get&Set methods for any relevant class property*/
    
     StatusType AddTask(int taskID, int priority){
        try {
    		AVLTask avl(taskID,priority);
		HashResult result = IdHash.Insert(avl);
		if (result == HASH_TABLE_DATA_ALREADY_EXIST) {
			return FAILURE;
		}
		AVLTask* avlP = IdHash.Find(avl);
		HeapTask heap(taskID,priority);
		heap.SetNode(avlP);
		MaxPriHeap.Insert(heap);
		MinPriHeap.Insert(heap);
		int MaxHeapIndex=avlP->GetMaxIndex();
		int MinHeapIndex=avlP->GetMinIndex();
		if (MaxHeapIndex == -1) {
			MaxHeapIndex = MaxPriHeap.NumberOfElement();
			avlP->SetMaxIndex(MaxHeapIndex);
		}
		if (MinHeapIndex == -1) {
			MinHeapIndex = MinPriHeap.NumberOfElement();
			avlP->SetMinIndex(MinHeapIndex);
		}
		heap = MaxPriHeap.getElement(MaxHeapIndex);
		avlP->SetMaxTask(&heap);
		heap=MinPriHeap.getElement(MinHeapIndex);
		avlP->SetMinTask(&heap);
	} catch (bad_alloc& b) {
		return ALLOCATION_ERROR;
	}
	return SUCCESS;
    }
    
    StatusType NextTask(int* taskID, int* priority){
     /*   if (taskID == NULL || priority == NULL) {
			return FAILURE;
		}
		HeapTask tmp = MaxPriHeap.RemoveMaxElement();
		//Also need to remove from MinHeap and Hash Table.
		*taskID = tmp.GetId();
		*priority = tmp.GetPriority();*/
		return SUCCESS;
    }
    
    StatusType SetPriority(int taskID, int priority) {
	AVLTask tmp(taskID, priority);
	if (!IdHash.IsIn(tmp)) {
		return FAILURE;
	}
	try {
		AVLTask* hashP = IdHash.Find(tmp);
		int MaxHeapIndex = hashP->GetMaxIndex();
		int MinHeapIndex = hashP->GetMinIndex();
		MaxPriHeap.RemoveElement(MaxHeapIndex);
		MinPriHeap.RemoveElement(MinHeapIndex);
		HeapTask heap(taskID, priority, hashP);
		hashP->SetMaxIndex(-1);
		hashP->SetMinIndex(-1);
		MaxPriHeap.Insert(heap);
		MinPriHeap.Insert(heap);
		hashP->SetPriority(priority);
		MaxHeapIndex = hashP->GetMaxIndex();
		MinHeapIndex = hashP->GetMinIndex();
		if (MaxHeapIndex == -1) {
			MaxHeapIndex = MaxPriHeap.NumberOfElement();
			hashP->SetMaxIndex(MaxHeapIndex);
		}
		if (MinHeapIndex == -1) {
			MinHeapIndex = MinPriHeap.NumberOfElement();
			hashP->SetMinIndex(MinHeapIndex);
		}
	} catch (bad_alloc& b) {
		return ALLOCATION_ERROR;
	}
	return SUCCESS;
    }
    
    StatusType Cancel (int taskID){
/*        if (!IdHash.IsIn(taskID)) {
			return FAILURE;
		}
		Task tmp(taskID);
		Task* task = IdHash.Find(&tmp);
		try	{
			MaxPriHeap.RemoveElement(task->GetMaxHeapIndex(), "max");
			MinPriHeap.RemoveElement(task->GetMinHeapIndex(), "min");
			IdHash.Remove(&task);
		} catch (bad_alloc& b) {
			return ALLOCATION_ERROR;
		}*/
		return SUCCESS;
    }
    
    StatusType LastTask(int* taskID, int* priority){
        if (taskID == NULL || priority == NULL){
            return INVALID_INPUT;
        }
        //get min-heap root
        Task tmp = MinPriHeap.FindMax();//should change to the right heap function
        *taskID = tmp.GetId();
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
