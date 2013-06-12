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
            NumberOfTasks(size), MinPriHeap(size), MaxPriHeap(size){
                //initialize task array and heaps
                //makeheap for both heaps
                //get
                
                HeapTask* htArray = new HeapTask[size];
                AVLTask* avltArray = new AVLTask[size];
                for (int i = 0; i < size; i++){
                    HeapTask tmp(taskIDs[i],taskPriorities[i]);
                    htArray[i] = tmp;
                }
                MaxPriHeap.MakeHeap(htArray,size,"max");
                MinPriHeap.MakeHeap(htArray,size,"min");
                
    }
    /*Get&Set methods for any relevant class property*/
    
    StatusType AddTask(int taskID, int priority){
        try {
    		Task task(taskID, priority);
            AVLTask avl(task);
			HashResult result = IdHash.Insert(avl);
			if (result == HASH_TABLE_DATA_ALREADY_EXIST) {
				return FAILURE;
			}
            HeapTask heap(task);
			MaxPriHeap.Insert(heap, "max");
			MinPriHeap.Insert(heap, "min");
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
    
    StatusType SetPriority (int taskID,int priority){
        AVLTask tmp(taskID, priority);
        if (!IdHash.IsIn(tmp)) {
            return FAILURE;
        }
        try {
            AVLTask task = IdHash.Find(tmp);
            int taskMaxIndex = task.GetMaxIndex();
            MaxPriHeap.RemoveElement(taskMaxIndex, "max");
            MinPriHeap.RemoveElement(taskMaxIndex, "min");
            task.SetPriority(priority);
            MaxPriHeap.Insert(taskMaxIndex, "max");
            MinPriHeap.Insert(taskMaxIndex, "min");
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
