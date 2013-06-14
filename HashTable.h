//
//  HashTable.h
//  DS-WET2
//  Aviad Rom and Ohad Fireman
//

#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <iostream>
#include <cstdio>
#include <assert.h>
#include "AVLTree.h"
using namespace std;

typedef enum {
	HASH_TABLE_SUCCESS,
	HASH_TABLE_FAILED,
	HASH_TABLE_DATA_ALREADY_EXIST,
	HASH_TABLE_DATA_NOT_EXIST
} HashResult;

template<typename T, typename CmpFunc, typename helpFunc>
class HashTable {
private:
	int elements;
	AVLTree<T, CmpFunc>* hTable;
	int tableSize;
	CmpFunc compare;
	helpFunc func;
    
	void ReBuild(){
		double factorSize = (double) elements / tableSize;
		if  (factorSize < 4.0 && factorSize > 1.0) {
			return;
		}
		int tempTableSize=tableSize;
		if (factorSize >= 4.0) {
			tableSize *= 2;
		}
        if (factorSize <= 1.0){
            tableSize /= 2;
        }
        
		AVLTree<T, CmpFunc>* temp = hTable;
		hTable = new AVLTree<T, CmpFunc> [tableSize];
		for (int i = 0; i < tempTableSize; i++) {
			int arraySize = temp[i].GetTreeSize();
			T* tempDataArray = new T[arraySize]();
			temp[i].GetTreeInArray(tempDataArray);
			for (int j = 0; j < arraySize; j++) {
				int index = HashFunction( func.GetId(tempDataArray[j]) );
				(hTable[index]).insert(tempDataArray[j]);
			}
			delete[] tempDataArray;
		}
		delete[] temp;
        
	}
    
	int HashFunction(int id)const{
		int index = id % tableSize;
		return index > 0 ? index : (-1) * index;
	}
    
public:
	// Default c'tor
	HashTable(int n):elements(0),hTable(NULL),tableSize(2*n){
		if(n==0){
			tableSize=4;
		}
		hTable=new AVLTree<T, CmpFunc> [tableSize];
	}
    
	/*Default d'tor*/
	~HashTable(){
		delete[] hTable;
	}
    
	/*Adds an element to the hash table
	 *   Input: data - element of the hash table.
	 *
	 *	Output: HashResult.
	 *			HASH_TABLE_SUCCESS-in case of success
	 *			HASH_TABLE_DATA_ALREADY_EXIST-in case this element already in the hash table*/
	HashResult Insert(T& data){
		int index = HashFunction(func.GetId(data));
		if ((hTable[index]).insert(data) == AVL_TREE_DATA_ALREADY_EXIST) {
			return HASH_TABLE_DATA_ALREADY_EXIST;
		}
		elements++;
        if (elements >= 3){
            ReBuild();
        }
		return HASH_TABLE_SUCCESS;
	}

    /*Removes an element from the hash table if it exists*/
    HashResult Remove(const T& data){
        hTable->Remove(data);
        elements--;
        ReBuild();
        return HASH_TABLE_SUCCESS;
    }
    
	/*finds an element in the hashTable, assuming the element is in the HashTable
	 *  gets a data copy of given element's data in HashTable.
	 * */
	T* Find(T& data){
		int index = HashFunction(func.GetId(data)) ;
		return hTable[index].Find(data);
	}
    
	/*gets the size of the table*/
	int Size() const{
        return tableSize;
    }
    
	/*gets the number of element in the hashTable*/
	int NumberOfElement() const {
        return elements;
    }
    
    
    
	/*return true if data in the HashTable, other false*/
	bool IsIn(T& data)const{
		int index = HashFunction(func.GetId(data));
		return hTable[index].DataInTree(data);
	}
    
	/*print all the elements at the hashTable */
	void print(){
		for (int i = 0; i < tableSize; i++) {
			int size = hTable[i].GetTreeSize();
			T* arr = new T[size];
			hTable[i].GetTreeInArray(arr);
			std::cout << i << ": ";
			for (int j = 0; j < size; j++) {
				std::cout <<"ID: "<< func.getId(arr[j]) << " Balance: "<< arr[j]->GetBalance() << " NumberOfAccounts: "<<func.getVal(arr[j])<< ",";
			}
			std::cout << endl;
			delete[] arr;
		}
	}
    
    
};



#endif /* HASHTABLE_H_ */
