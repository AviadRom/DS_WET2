//
//  Task.h
//  DS-WET2
//  Aviad Rom and Ohad Fireman
//

#ifndef DS_WET2_Task_h
#define DS_WET2_Task_h

class Task{
private:
	int Id;
	int Priority;
public:
	Task(int ID = 0, int priority = 0):Id(ID),Priority(priority){};
	
	Task(const Task& b): Id(b.GetId()), Priority(b.GetPriority()){};
	
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
	}
	
	int GetPriority() const{
		return Priority;
	}
	void SetPriority(int val){
		Priority = val;
	}
	
	void print(){
		cout<<"id:"<< Id <<"  priority: "<< priority <<endl;
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
		return;
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
};



#endif
