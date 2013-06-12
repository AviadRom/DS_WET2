//
//  Task.h
//  DS-WET2
//  Aviad Rom and Ohad Fireman
//

#ifndef DS_WET2_Task_h
#define DS_WET2_Task_h
#include <iostream>
using std::cout;
using std::endl;

class Task{
private:
	int Id;
	int Priority;
	int MaxHeapIndex;
	int MinHeapIndex;
public:
	Task(int ID = 0, int priority = 0):Id(ID), Priority(priority), MaxHeapIndex(0), MinHeapIndex(0){};
	
	Task(const Task& b): Id(b.GetId()), Priority(b.GetPriority()), MaxHeapIndex(0), MinHeapIndex(0){};
	
	~Task(){};
	
	int GetId() const{
		return Id;
	}
	
	bool Compare(const Task& b) const{
		return (Id == b.GetId());
	}
	
	Task& operator=(const Task& b){
		Priority = b.GetPriority();
		Id = b.GetId();
		return *this;
	}
	
	int GetPriority() const{
		return Priority;
	}
	
	void SetPriority(int pri){
		Priority = pri;
	}
	
	void SetMinHeapIndex(int index){
		MinHeapIndex = index;
	}
	
	int GetMinHeapIndex(){
		return MinHeapIndex;	
	}
	
	void SetMaxHeapIndex(int index){
		MaxHeapIndex = index;
	}
	
	int GetMaxHeapIndex(){
		return MaxHeapIndex;
	}
	
	void print(){
		cout<<"id:"<< Id <<"  Priority: "<< Priority <<endl;
	}
};



class TaskCmp{
public:
	bool operator()(const Task& a,const Task& b) const{
		return a.Compare(b);
	}
};

class TaskGetId{
public:
	int operator()(const Task& a) const{
		return a.GetId();
	}
};

class TaskFunctions{
public:
	int GetId (const Task& a) const{
		return a.GetId();
	}
	int GetVal(const Task& a) const{
		return a.GetPriority();
	}
	void SetVal(Task& a, int val){
		a.SetPriority(val);
	}
	int compareById(const Task& a,const Task& b) const{
		if (GetId(a) > GetId(b)){
			return 1;
		} 
		if (GetId(a) < GetId(b)){ 
			return -1;
		}
		return 0;
	}
	
	void SetIndex(Task* a, int index){
		a->SetMaxHeapIndex(index)
	}
	
	int GetIndex(Task* a){
		return a->GetMaxHeapIndex();
	}
};

//This class is exactly like TaskFunctions but the comparison by ID
//returns oposite values in order to use Heap as a min heap.
class TaskFunctionsForMinHeap{
public:
	int GetId (const Task& a) const{
		return a.GetId();
	}
	int GetVal(const Task& a) const{
		return a.GetPriority();
	}
	void SetVal(Task& a, int val){
		a.SetPriority(val);
	}
	int compareById(const Task& a,const Task& b) const{
		if (GetId(a) > GetId(b)){
			return -1;
		}
		if (GetId(a) < GetId(b)){
			return 1;
		}
		return 0;
	}
	
	void SetIndex(Task* a, int index){
		a->SetMinHeapIndex(index)
	}
	
	int GetIndex(Task* a){
		return a->GetMinHeapIndex();
	}
    
};



#endif
