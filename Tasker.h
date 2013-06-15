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
        }
        for (int i=0;i<size;i++){
        	AVLTask avl(taskIDs[i], taskPriorities[i]);
        	AVLTask* forHeap = IdHash.Find(avl);
        	HeapTask tmp(taskIDs[i], taskPriorities[i],forHeap);
        	htArray[i] = tmp;
        }
        MaxPriHeap.MakeHeap(htArray,size);
        MinPriHeap.MakeHeap(htArray,size);
        delete[] htArray;
    }
    
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
		if (avlP->GetMaxIndex() == -1) {
			avlP->SetMaxIndex(MaxPriHeap.NumberOfElement());
		}
		if (avlP->GetMinIndex() == -1) {
			avlP->SetMinIndex(MinPriHeap.NumberOfElement());
		}
		heap = MaxPriHeap.getElement(avlP->GetMaxIndex());
		avlP->SetMaxTask(&heap);
		heap=MinPriHeap.getElement(avlP->GetMinIndex());
		avlP->SetMinTask(&heap);
	} catch (bad_alloc& b) {
		return ALLOCATION_ERROR;
	}
	NumberOfTasks++;
	return SUCCESS;
    }
    
      StatusType NextTask(int* taskID, int* priority){
        if (taskID == NULL || priority == NULL) {
            return INVALID_INPUT;
        }
        if (NumberOfTasks == 0){
            return FAILURE;
        }
        HeapTask tmp = MaxPriHeap.RemoveMaxElement();
        AVLTask* hashTask = tmp.GetNode();
        MinPriHeap.RemoveElement(hashTask->GetMinIndex());
        IdHash.Remove(*hashTask);
        *taskID = tmp.GetId();
        *priority = tmp.GetPriority();
        NumberOfTasks--;
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
	AVLTask tmp(taskID);
        if (!IdHash.IsIn(tmp)) {
            return FAILURE;
        }
        AVLTask* hashTask = IdHash.Find(tmp);
        
         try	{
         MaxPriHeap.RemoveElement(hashTask->GetMaxIndex());
         MinPriHeap.RemoveElement(hashTask->GetMinIndex());
         IdHash.Remove(tmp);
         } catch (bad_alloc& b) {
         return ALLOCATION_ERROR;
         }
         NumberOfTasks--;
		return SUCCESS;
    }
    
    StatusType LastTask(int* taskID, int* priority){
        if (taskID == NULL || priority == NULL){
            return INVALID_INPUT;
        }
        Task tmp = MinPriHeap.FindMax();
        *taskID = tmp.GetId();
        *priority = tmp.GetPriority();
        return SUCCESS;
    }
    
    StatusType GetKthTask(int k, int* taskID, int* priority) {
	if (taskID == NULL || priority == NULL || k > IdHash.NumberOfElement()
			|| k < 1) {
		return INVALID_INPUT;
	}
	try {
		MaxHeap heap(2 * k);
		HeapTask* array = new HeapTask[k];
		MaxPriHeap.GetKBiggest(heap, array, k);
		*taskID = array[k - 1].GetId();
		*priority = array[k - 1].GetPriority();
	} catch (bad_alloc& b) {
		return ALLOCATION_ERROR;
	}
	return SUCCESS;
   }
    
    ~Tasker(){}
};


#endif
