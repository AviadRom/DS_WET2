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

	/*Replace 2 elements in the array*/
	void Swap(int i, int j, string type) {
		if ((i > 0 && i <= numberOfElements)
				&& (j > 0 && j <= numberOfElements)) {
			T temp = array[i];
			array[i] = array[j];
			array[j] = temp;
			if (type.compare("min")){
				array[i].SetMinHeapIndex(j);
				array[j].SetMinHeapIndex(i);
			} else {
				array[i].SetMaxHeapIndex(j);
				array[j].SetMaxHeapIndex(i);
			}

		}
	}


/*Adds element to the Heap*/
void InsertElement(T data) {
	array[numberOfElements + 1] = data;
	numberOfElements++;
	MakeSiftUp (numberOfElements);
	ChangeSize();
}

/*  Sift down the element in the array at index i
 *  Input: i - the index where the data to sift down*/
void MakeSiftDown(int i) {
	if (i < 1) {
		return;
	}
	if (2 * i + 1 <= numberOfElements) {
		if (FObj.compare(array[2 * i], array[i])
				|| FObj.compare(array[2 * i + 1], array[i])) {
			if (FObj.compare(array[2 * i], array[2 * i + 1])) {
				Swap(i, 2 * i);
				MakeSiftDown(2 * i);
			} else {
				Swap(i, 2 * i + 1);
				MakeSiftDown(2 * i + 1);
			}
		}
	} else if (2 * i <= numberOfElements) {
		if (FObj.compare(array[2 * i], array[i])) {
			Swap(i, 2 * i);
		}
	}
}

/*  Sift up the element in the array at index i
 *  Input: i - the index where the data to sift up*/
void MakeSiftUp(int i) {
	if ((i < 2) || (i > numberOfElements)) {
		return;
	}
	if (FObj.compare(array[i], array[i / 2])) {
		Swap(i, i / 2);
		MakeSiftUp(i / 2);
	}
}

/*doing a standard  3/4 resize for a dynamic array.*/
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
/*Default c'tor*/
Heap() :
size(0), numberOfElements(0), array(NULL) {
}

/*c'tor*/
Heap(int n) :
size(2 * n + 1), numberOfElements(0) {
	if (n == 0) {
		size = 4;
	}
	array = new T[size];
}

/*d'tor*/
~Heap() {
	delete[] array;
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
	}
	for (int i = numberOfElements / 2; i > 0; --i) {
		MakeSiftDown(i);
	}
}

void Insert(T data) {
	InsertElement(data);
}

void RemoveElement(Task task, string type) {
	if (type.compare("min")) {
		int index = task.GetMinHeapIndex();
		Swap(index, numberOfElements, type);
		numberOfElements--;
		MakeSiftDown (index);
	} else {
		int index = task.GetMaxHeapIndex();
		Swap(index, numberOfElements, type);
		numberOfElements--;
		MakeSiftDown (index);
	}


}

/*Delete the biggest element at the Heap*/
T RemoveMaxElement() {
	T ret = array[1];
	Swap(1, numberOfElements);
	numberOfElements--;
	MakeSiftDown(1);
	return ret;
}

/*  Change a key or any other data (of type int) in an object at the index i
 *  Input: i - the index where the object to change
 *  	   change - how big is the change*/
void ChangeKeyValue(int i, int change) {
	if ((i < 1) || (i > numberOfElements)) {
		return;
	}
	FObj.AddVal(array[i], change);
	if (change >= 0) {
		MakeSiftUp(i);
	} else {
		MakeSiftDown(i);
	}
}

/*  gets copy of object with the maximum value*/
T FindMax() {
	return array[1];
}

/*Gets the number of element in the heap*/
int NumberOfElement() const {
	return numberOfElements;
}

/*Gets the size of the array*/
int GetArraySize() const {
	return size;
}

//Gets the K Biggest nodes at array.
void GetKBiggest(Heap<T, FuncObj>& heap, T* arr, int k) const {
	if (k > numberOfElements) {
		return;
	}
	int i = 1, j = 1;
	arr[0] = array[1];
	while (i < k) {
		if (2 * j + 1 <= numberOfElements) {
			heap.InsertElement(array[2 * j]);
			heap.InsertElement(array[2 * j + 1]);
		} else if (2 * j <= numberOfElements) {
			heap.InsertElement(array[2 * j]);
		}
		arr[i] = heap.RemoveMaxElement();
		j = FObj.GetIndex(arr[i]);
		i++;
	}
}
};

#endif /* HEAP_H_ */
