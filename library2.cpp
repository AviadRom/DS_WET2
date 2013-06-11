<<<<<<< HEAD
/*library2.cpp
 *
 *  Created on: Jun 11, 2013
 *       Author: OHAD FIREMAN
 *
=======
/*
 * library2.cpp
 *
 *  Created on: Jun 11, 2013
 *      Author: OHAD FIREMAN
>>>>>>> 61f1edb7a7f8d88830a506652e20bc884e664ab9
 */




#include "library2.h"
#include "Tasker.h"


<<<<<<< HEAD
void* Init(int N, int *tasksIDs, int *priorities){
  Tasker* DS = new Tasker(N, tasksIDs, priorities);
=======
void* Init(){
  Tasker* DS = new Tasker();
>>>>>>> 61f1edb7a7f8d88830a506652e20bc884e664ab9
	return (void*)DS;
}

StatusType AddTask(void* DS,int taskID,int priority){
	return ((Tasker *)DS)->AddTask(taskID,priority);
}

StatusType NextTask(void* DS,int* taskID,int* priority){
	return ((Tasker *)DS)->NextTask(taskID,priority);
}

StatusType SetPriority(void* DS,int taskID,int priority){
	return ((Tasker *)DS)->SetPriority(taskID,priority);
}

StatusType Cancel(void* DS,int taskID){
	return ((Tasker *)DS)->Cancel(taskID);
}

StatusType LastTask(void* DS,int* taskID,int* priority){
	return ((Tasker *)DS)->LastTask(taskID,priority);
}

StatusType GetKthTask(void* DS,int k,int* taskID,int* priority){
	return ((Tasker *)DS)->GetKthTask(k,taskID,priority);
}

<<<<<<< HEAD
void Quit(void** DS){
	Tasker* tmp = (Tasker*)*DS;
	delete tmp;
	DS = NULL;
}


=======
StatusType Quit(void** DS){
	return ((Tasker *)DS)->Quit();
}

>>>>>>> 61f1edb7a7f8d88830a506652e20bc884e664ab9
