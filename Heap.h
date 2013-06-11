//
//  Heap.h
//  DS-WET2
//  Aviad Rom and Ohad Fireman
//
#ifndef HEAP_H_
#define HEAP_H_

#include <iostream>
#include <cstdio>
using namespace std;


template<typename T,typename FuncObj>
class Heap{
private:
	int size;
	int numberOfElements;
	T* array;
	FuncObj FObj;
    
	/*Replace 2 elements in the array*/
	void SwapWithoutIndexChange(int i,int j){
		if((i>0 && i<=numberOfElements)&&(j>0 && j<=numberOfElements)){
			T temp=array[i];
			array[i]=array[j];
			array[j]=temp;
            
		}
	}
    
	/*Adds element to the Heap*/
	void InsertWithoutIndexChange(T data){
		array[numberOfElements+1]=data;
		numberOfElements++;
		MakeSiftUp(numberOfElements,false);
		ChangeSize();
	}
    
	/*Delete the biggest element at the Heap*/
	T RemoveMaxWithoutIndexChange(){
		T ret = array[1];
		SwapWithoutIndexChange(1,numberOfElements);
		numberOfElements--;
		MakeSiftDown(1,false);
		return ret;
	}
    
    
    
    
    /*  Swap 2 elements in the array and changes the index in the data
	 *
	 *  Input: i,j - 2 of the array's indexes should be swapped*/
	void Swap(int i,int j){
		if((i>0 && i<=numberOfElements)&&(j>0 && j<=numberOfElements)){
            
			FObj.changeIndex(array[i],j);
			FObj.changeIndex(array[j],i);
			T temp=array[i];
			array[i]=array[j];
			array[j]=temp;
            
		}
	}
    
	/*  Sift down the element in the array at index i
	 *  Input: i - the index where the data to sift down*/
	void MakeSiftDown(int i,bool changeIndex){
		if(i<1){
			return ;
		}
		if(2*i+1<=numberOfElements){
			if(FObj.compare(array[2*i],array[i]) || FObj.compare(array[2*i+1],array[i])){
                if(FObj.compare(array[2*i],array[2*i+1])){
                    if(changeIndex){
                        Swap(i,2*i);
                    }else{
                        SwapNotChangeIndex(i,2*i);
                    }
                    MakeSiftDown(2*i,changeIndex);
                }
                else{
                    if(changeIndex){
                        Swap(i,2*i+1);
                    }else{
                        SwapNotChangeIndex(i,2*i+1);
                    }
                    
                    MakeSiftDown(2*i+1,changeIndex);
                }
			}
		}
		else if(2*i<=numberOfElements){
			if(FObj.compare(array[2*i],array[i])){
				if(changeIndex){
					Swap(i,2*i);
				}else{
					SwapNotChangeIndex(i,2*i);
				}
			}
		}
	}
    
    /*  Sift up the element in the array at index i
	 *  Input: i - the index where the data to sift up*/
	void MakeSiftUp(int i,bool changeIndex){
		if((i<2)||(i>numberOfElements)){
			return;
		}
		if(FObj.compare(array[i],array[i/2])){
			if(changeIndex){
				Swap(i,i/2);
			}else{
				SwapNotChangeIndex(i,i/2);
			}
			MakeSiftUp(i/2,changeIndex);
		}
	}
    
	/*doing a standard  3/4 resize for a dynamic array.*/
	void ChangeSize(){
		double factorSize=(double)numberOfElements/size;
		if(factorSize>=0.75){
			size*=2;
			T* temp=array;
			array=new T[size];
			for(int i=1; i<=numberOfElements; i++){
				array[i]=temp[i];
			}
			delete[] temp;
		}
	}
    
public:
	/*Default c'tor*/
	Heap():size(0),numberOfElements(0),array(NULL){}
    
	/*c'tor*/
	Heap(int n):size(2*n+1),numberOfElements(0){
		if(n==0){
			size=4;
		}
		array=new T[size];
	}
    
    
	void MakeHeap(T* myArray,int n){
		if(n==0 || n==1){
			size=4;
		}
		else{
			size=2*n;
		}
		numberOfElements=n;
		array=new T[size];
		for(int i=1;i<=numberOfElements;i++){
			FObj.changeIndex(myArray[i-1],i);
			array[i]=myArray[i-1];
		}
		for(int i=numberOfElements/2;i>0;--i){
			MakeSiftDown(i,true);
		}
	}
    
	/*d'tor*/
	~Heap(){
		delete[] array;
	}
    
    /*  Change a key or any other data (of type int) in an object at the index i
	 *  Input: i - the index where the object to change
	 *  	   change - how big is the change*/
	void ChangeKeyValue(int i,int change){
		if((i<1)||(i>numberOfElements)){
			return;
		}
		FObj.AddVal(array[i],change);
		if(change>=0){
		    MakeSiftUp(i,true);
		}
		else{
			MakeSiftDown(i,true);
		}
	}
    
	/*  gets copy of object with the maximum value*/
	T FindMax(){return array[1];}
    
    /*  return the object with the maximum value and remove it from the heap.
	 *  after this operation the maximum object will be the next biggest value in the heap.*/
	T DeleteMax(){
		T ret = array[1];
		Swap(1,numberOfElements);
		numberOfElements--;
		MakeSiftDown(1,true);
		return ret;
	}
    
	/* insert a new object to the Heap*/
	void Insert(T data){
		array[numberOfElements+1]=data;
		numberOfElements++;
		FObj.changeIndex(array[numberOfElements],numberOfElements);
		SiftUp(numberOfElements,true);
		ChangeSize();
	}
    
	/*Gets the number of element in the heap*/
	int NumberOfElement()const{return numberOfElements;}
    
	/*Gets the size of the array*/
	int GetArraySize()const{return size;}
    
	/*print all the element in the heap*/
	void print(){
		for(int i=1;i<=numberOfElements;i++){
			std::cout<<"ID: "<<FObj.GetId(array[i])<<","<<"Index: "<<FObj.GetIndex(array[i])<<", ";
		}
		std::cout<<std::endl;
	}
    
	//Gets the K Biggest nodes at array.
	void GetKBiggest(Heap<T,FuncObj>& heap,T* arr, int k) const{
		if(k>numberOfElements){
			return;
		}
		int i=1,j=1;
		arr[0]=array[1];
		while(i<k){
			if(2*j+1<=numberOfElements){
				heap.InsertWithoutIndexChange(array[2*j]);
				heap.InsertWithoutIndexChange(array[2*j+1]);
			}else if(2*j<=numberOfElements){
				heap.InsertWithoutIndexChange(array[2*j]);
			}
			arr[i]=heap.RemoveMaxWithoutIndexChange();
			j=FObj.GetIndex(arr[i]);
			i++;
		}
	}
};




#endif /* HEAP_H_ */
