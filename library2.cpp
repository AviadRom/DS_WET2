/*
 * library2.cpp
 *
 *  Created on: Jun 11, 2013
 *      Author: OHAD FIREMAN
 */




#include "library2.h"
#include "Tasker.h"


void* Init(){
  Tasker* DS = new Tasker();
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

StatusType Quit(void** DS){
	return ((Tasker *)DS)->Quit();
}

