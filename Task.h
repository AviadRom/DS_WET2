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
public:
    
    Task(int ID = 0, int pri = 0):Id(ID), Priority(pri){};
    
    Task(const Task& b): Id(b.GetId()), Priority(b.GetPriority()){};
    
    virtual ~Task(){};
    
    void SetId(int n){
        Id = n;
    }
	
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
    
    
};

class AVLTask;

class HeapTask: public Task{
private:
    AVLTask* AVLNode;
    int Index;
public:
    HeapTask(int ID = 0, int pri = 0, AVLTask* node = NULL):Task(ID, pri), AVLNode(node),Index(0) {};
    
    HeapTask(const HeapTask& b): Task(b),AVLNode(b.GetNode()), Index(b.GetIndex()){};
    
    HeapTask(Task& task): Task(task),AVLNode(NULL), Index(-1){};
    
    const bool operator=(HeapTask b){
        SetId(b.GetId());
        SetPriority(b.GetPriority());
        Index = b.GetIndex();
        AVLNode = b.GetNode();
        return true;
    }
    
    AVLTask* getAVLNode(){
    	return AVLNode;
    }
    void changeAVLNode(AVLTask* task){
    	if (task){
    	AVLNode=task;
    	}
    }

    int GetIndex() const{
        return Index;
    }
    
    AVLTask* GetNode() const{
        return AVLNode;
    }
    
    void SetIndex(int index){
        Index = index;
    }
    
    void SetNode (AVLTask* node){
        AVLNode = node;
    }
    
    ~HeapTask(){}
};


class AVLTask: public Task{
private:
	int MaxIndex;
	int MinIndex;
    HeapTask* MinTask;
    HeapTask* MaxTask;
public:
    //Default C'tor
    AVLTask(int ID = 0, int pri = 0, HeapTask* min = NULL, HeapTask* max = NULL):
    Task(ID, pri), MinTask(min), MaxTask(max){
        if (min){
            MinIndex = min->GetIndex();
        }else {
            MinIndex = -1;
        }
        if (max){
            MaxIndex = max->GetIndex();
        }else {
            MaxIndex = -1;
        }
    }
    
    //Copy C'tor
    AVLTask(const AVLTask& b): Task(b), MaxIndex(b.GetMaxIndex()),
    MinIndex(b.GetMinIndex()),MinTask(b.GetMinTask()),MaxTask(b.GetMaxTask()) {};
    
    //Another usable variation of a C'tor
    AVLTask(Task& task, HeapTask* max = NULL, HeapTask* min = NULL): Task(task),MinTask(min), MaxTask(max) {
        if (min){
            MinIndex = min->GetIndex();
        }else {
            MinIndex = -1;
        }
        if (max){
            MaxIndex = max->GetIndex();
        }else {
            MaxIndex = -1;
        }
    }
    
    
    ~AVLTask(){}
    
    int GetMaxIndex() const{
        return MaxIndex;
    }
    
    int GetMinIndex() const{
        return MinIndex;
    }
    
    HeapTask* GetMaxTask() const{
        return MaxTask;
    }
    
    HeapTask* GetMinTask() const{
        return MinTask;
    }
    
    void SetMaxIndex(int index){
        MaxIndex = index;
    }
    
    void SetMinIndex(int index){
        MinIndex = index;
    }
    
    void SetMaxTask(HeapTask* max){
        MaxTask = max;
    }
    
    void SetMinTask(HeapTask* min){
        MinTask = min;
    }
};


class TaskCmp{
public:
	int operator()(const Task& a,const Task& b) const{
		if (a.GetId() > b.GetId()){
			return 1;
		}
		if (a.GetId() < b.GetId()){
			return -1;
		}
		return 0;
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
public:
	int GetId (Task& a) const{
		return a.GetId();
	}
	int GetVal(Task& a) const{
		return a.GetPriority();
	}
	void SetVal(Task& a, int val){
		a.SetPriority(val);
	}
    
	int compareById(const Task& a,const Task& b) const{
		if (a.GetId() > b.GetId()){
			return 1;
		}
		if (a.GetId() < b.GetId()){
			return -1;
		}
		return 0;
	}
    
    virtual bool Compare(Task& a, Task& b){
        if  (a.GetPriority() == b.GetPriority()){
            if (a.GetId() > b.GetId()){
                return true;
            }
            return false;
        }
        if (a.GetPriority() > b.GetPriority()){
            return true;
        }
        return false;
    }
};
//Refering Max Heap
class HeapTaskFunctions: public TaskFunctions{
public:
	void SetIndex(HeapTask* a, int index){
		a->SetIndex(index);
        AVLTask* tempNode = a->GetNode();
        if (tempNode){
            tempNode->SetMaxIndex(index);
            tempNode->SetMaxTask(a);
        }
	}
	
	int GetIndex(HeapTask* a){
		return a->GetIndex();
	}
    
};

class MinHeapTaskFunctions: public TaskFunctions{
public:
    void SetIndex(HeapTask* a, int index){
		a->SetIndex(index);
        AVLTask* tempNode = a->GetNode();
        if (tempNode){
            tempNode->SetMinIndex(index);
            tempNode->SetMinTask(a);
            
        }
	}
	
	int GetIndex(HeapTask* a){
		return a->GetIndex();
	}
    bool Compare(Task& a, Task& b){
        if  (a.GetPriority() == b.GetPriority()){
            if (a.GetId() < b.GetId()){
                return true;
            }
            return false;
        }
        if (a.GetPriority() < b.GetPriority()){
            return true;
        }
        return false;
    }
};





#endif
