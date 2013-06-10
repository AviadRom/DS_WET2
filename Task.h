//
//  Task.h
//  DS-WET2
//  Aviad Rom and Ohad Fireman
//

#ifndef DS_WET2_Task_h
#define DS_WET2_Task_h

class Task{
protected:
	int Id;
public:
	Task(int ID):Id(ID){};
	
    Task(const Task& b): Id(b.Id){};
	
    virtual ~Task(){};
	
    int GetId() const{
		return Id;
	}
	bool Compare(const Task& b) const{
		return (Id == b.Id);
	}
};

class TaskPriority: public Task{
private:
	int Priority;
public:
	TaskPriority(int ID,int priority):Task(ID),Priority(priority){};
    
	TaskPriority(const TaskPriority& b): Task(b),Priority(b.Priority){};
    
	TaskPriority& operator=(const TaskPriority& b){
		Priority = b.Priority;
		Id=b.Id;
		return *this;
	}
	~TaskPriority(){};
    
	int GetPriority() const{
		return Priority;
	}
	void SetPriority(int val){
		Priority = val;
	}
    
	void print(){
		cout<<"id:"<< Id <<"  p.Temp: "<< priority <<endl;
	}
};


class TaskCmp{
public:
	bool operator()(const Task& a,const Task& b) const{
		return a.compare(b);
	}
};

class TaskGetId{
public:
	int operator()(const Request& a) const{
		return a.getId();
	}
};

class TaskPriorityFunctions{
public:
	int GetId (const TaskPriority& a) const{
		return a.GetId();
	}
	int GetVal(const TaskPriority& a) const{
		return a.GetPriority();
	}
	void SetVal(TaskPriority& a, int val){
		a.SetPriority(val);
		return;
	}
	int compareById(const TaskPriority& a,const TaskPriority& b) const{
		if (getId(a)>getId(b)) return 1;
		if (getId(a)<getId(b)) return -1;
		return 0;
	}
};



#endif
