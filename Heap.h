//
//  Heap.h
//  DS-WET2
//  Aviad Rom and Ohad Fireman
//
#ifndef HEAP_H_
#define HEAP_H_

#include <iostream>
#include <cstdio>
#include <string>
using namespace std;
using std::string;

template<typename T, typename FuncObj>
class Heap {
private:
	int size;
	int numberOfElements;
	T* array;
	FuncObj FObj;
    
	//Replace 2 elements in the array
	void Swap(int i, int j) {
		if ((i > 0 && i <= numberOfElements) && (j > 0 && j <= numberOfElements)) {
			FObj.SetIndex(array+i, j);
			FObj.SetIndex(array+j, i);
			T temp = array[i];
			array[i] = array[j];
			array[j] = temp;
		}
	}
	
	void SwapWithoutIndexChange(int i, int j) {
		if ((i > 0 && i <= numberOfElements)
            && (j > 0 && j <= numberOfElements)) {
			T temp = array[i];
			array[i] = array[j];
			array[j] = temp;
		}
	}
    
	//Adds element to the Heap
	void InsertElement(T& data,bool changeIndex) {
		array[numberOfElements + 1] = data;
		numberOfElements++;
		MakeSiftUp(numberOfElements,changeIndex);
		ChangeSize();
	}
    
	/*  Sift down the element in the array at index i
	 *  Input: i - the index where the data to sift down
     *         changeIndex- wether or not use the regular swap or swap without index change
     */
	void MakeSiftDown(int i, bool changeIndex) {
		if (i < 1) {
			return;
		}
		if (2 * i + 1 <= numberOfElements) {
			if (FObj.Compare(array[2 * i], array[i])
                || FObj.Compare(array[2 * i + 1], array[i])) {
				if (FObj.Compare(array[2 * i], array[2 * i + 1])) {
					if (changeIndex) {
						Swap(i, 2 * i);
					} else {
						SwapWithoutIndexChange(i, 2 * i);
					}
					MakeSiftDown(2 * i, changeIndex);
				} else {
					if (changeIndex) {
						Swap(i, 2 * i + 1);
					} else {
						SwapWithoutIndexChange(i, 2 * i + 1);
					}
					MakeSiftDown(2 * i + 1, changeIndex);
				}
			}
		} else if (2 * i <= numberOfElements) {
			if (FObj.Compare(array[2 * i], array[i])) {
				if (changeIndex) {
					Swap(i, 2 * i);
				} else {
					SwapWithoutIndexChange(i, 2 * i);
				}
			}
		}
	}
    
	/*  Sift up the element in the array at index i
	 *  Input: i - the index where the data to sift up
     *         changeIndex- wether or not use the regular swap or swap without index change
     */
	void MakeSiftUp(int i,bool changeIndex) {
		if ((i < 2) || (i > numberOfElements)) {
			return;
		}
		if (FObj.Compare(array[i], array[i / 2])) {
			if (changeIndex){
                Swap(i, i / 2);
            }
            else {
                SwapWithoutIndexChange(i,i/2);
            }
            MakeSiftUp(i / 2,changeIndex);
		}
	}
    
	//doing a standard  3/4 resize for a dynamic array
	void ChangeSize() {
		double factorSize = (double) numberOfElements / size;
		if (factorSize >= 0.75) {
			size *= 2;
			T* temp = array;
			array = new T[size];
			for (int i = 1; i <= numberOfElements; i++) {
				array[i] = temp[i];
			}
			delete[] temp;
		}
	}
    
public:
	//Default C'tor
	Heap() :
    size(0), numberOfElements(0), array(NULL) {
	}
    
	//C'tor
	Heap(int n) :
    size(2 * n + 1), numberOfElements(0) {
		if (n == 0) {
			size = 4;
		}
		array = new T[size];
	}
    
	//D'tor
	~Heap() {
		delete[] array;
	}
    
    //Get the data of element in array[index]
    //if the index is out of range, return the first element.
    T& getElement(int index) const{
		if (index>0 && index<=numberOfElements){
			return array[index];
		}
		return array[1];
	}
    
	void MakeHeap(T* myArray, int n) {
		if (n == 0 || n == 1) {
			size = 4;
		} else {
			size = 2 * n;
		}
		numberOfElements = n;
		array = new T[size];
		for (int i = 1; i <= numberOfElements; i++) {
			array[i] = myArray[i - 1];
			FObj.SetIndex(array + i, i);
		}
		for (int i = numberOfElements / 2; i > 0; --i) {
			MakeSiftDown(i,true);
		}
	}
    
    //Insert data to heap
	void Insert(T& data) {
		InsertElement(data,true);
	}
	//Removes The element in index at heap
	void RemoveElement(int index) {
		if (index == -1) {
			index = numberOfElements;
		}
		Swap(index, numberOfElements);
		numberOfElements--;
		MakeSiftDown(index,true);
		ChangeSize();
	}
    
	//Delete the biggest element at the Heap according to compare functions
	T RemoveMaxElement(bool changeIndex) {
		T ret = array[1];
		if (changeIndex) {
			Swap(1, numberOfElements);
		} else {
			SwapWithoutIndexChange(1, numberOfElements);
		}
		numberOfElements--;
		if (changeIndex) {
			MakeSiftDown(1, true);
		} else {
			MakeSiftDown(1, false);
		}
		return ret;
	}
    
	//Gets a reference to the object with the maximum value
	T& FindMax() {
		return array[1];
	}
    
	//Gets the number of elements in the heap
	int NumberOfElement() const {
		return numberOfElements;
	}
    
	//Gets the size of the array
	int GetArraySize() const {
		return size;
	}
    
    
    //Gets the K Biggest nodes at array to a provided pre-allocated array
	void GetKBiggest(Heap<T, FuncObj>& heap, T* arr, int k) const {
		if (k > numberOfElements) {
			return;
		}
		int i = 1, j = 1;
		arr[0] = array[1];
		while (i < k) {
			if (2 * j + 1 <= numberOfElements) {
				heap.InsertElement(array[2 * j], false);
				heap.InsertElement(array[2 * j + 1], false);
			} else if (2 * j <= numberOfElements) {
				heap.InsertElement(array[2 * j], false);
			}
			arr[i] = heap.RemoveMaxElement(false);
			j = arr[i].GetIndex();
			i++;
		}
	}
};

#endif /* HEAP_H_ */
