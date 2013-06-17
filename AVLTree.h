//
//  AVLTree.h
//  DS-WET2
//
//  Aviad Rom and Ohad Fireman
//
#ifndef AVLTREE_H_
#define AVLTREE_H_

#include <iostream>
#include <cstdio>
#include <assert.h>
using namespace std;

typedef enum {
	AVL_TREE_SUCCESS,
	AVL_TREE_FAILED,
	AVL_TREE_DATA_ALREADY_EXIST,
	AVL_TREE_DATA_NOT_EXIST
} AVLTreeResult;

typedef enum {
	ROOT, NO_SONS, LEFT_SON, RIGHT_SON, TWO_SONS
} NodeStatus;


static int GetBigger(int a, int b) {
	if (a >= b) {
		return a;
	}
	return b;
}

template<class T, class CmpFunc>
class AVLNode {
private:
	AVLNode* father;
	AVLNode* leftSon;
	AVLNode* rightSon;
	T data;
	int nodeHeight;
	CmpFunc comperFunc;
    
    //Corret node's height, while making assumption that node's sons
    //  have correct heights.
	void currectNodeHeight() {
		if (!leftSon && !rightSon) {
			nodeHeight = 0;
			return;
		}
		int leftHeight = 0;
        int rightHeight = 0;
		if (leftSon) {
			leftHeight = leftSon->nodeHeight;
		}
		if (rightSon) {
			rightHeight = rightSon->nodeHeight;
		}
		nodeHeight = GetBigger(leftHeight, rightHeight) + 1;
	}
    
	//Find a given data's node
    //param: 	data
    //output: 	ptr to matched node, null if not found
	AVLNode<T, CmpFunc>* FindNode(const T& DataToFind) {
		AVLNode NodeToFind(DataToFind);
		if (*this == NodeToFind) {
			return this;
		}
		if (*this > NodeToFind) {
			if (!leftSon) {
				return NULL;
			} else {
				return leftSon->FindNode(DataToFind);
			}
		} else {
			if (!rightSon) {
				return NULL;
			} else {
				return rightSon->FindNode(DataToFind);
			}
		}
	}
    
	//Gets node sons status
    //Output could be one of the following: NO_SONS, RIGHT_SON, LEFT_SON, TWO_SONS
	NodeStatus GetNodeSonsStatus() const {
		if (!leftSon && !rightSon)
			return NO_SONS;
		if (!leftSon && rightSon)
			return RIGHT_SON;
		if (leftSon && !rightSon)
			return LEFT_SON;
		return TWO_SONS;
	}
    
	//Gets node status regarding its parent.
	// Output could be one of the following: ROOT,RIGHT_SON,LEFT_SON
	NodeStatus GetNodeStatus() const {
		if (!father)
			return ROOT;
		if (father->rightSon == this)
			return RIGHT_SON;
		return LEFT_SON;
	}
    
	//Gets minimum node at the tree
    //Output: pointer to the minimum node.
	AVLNode* GetMinimumNode() {
		AVLNode* current(this);
		while (current->leftSon != NULL) {
			current = current->leftSon;
		}
		return current;
	}
    
	//Gets maximum node at the tree
	//Output: pointer to the maximum node.
	AVLNode* GetMaximumNode(){
		AVLNode* current(this);
		while(current->rightSon != NULL){
			current=current->rightSon;
		}
		return current;
	}
    
	//Gets the following node in ascending order
	//Output: pointer to the matched node. null if not found.
	AVLNode<T, CmpFunc>* GetTheFollowingNode() {
		if (rightSon == NULL) {
			AVLNode<T, CmpFunc>* current(this);
            AVLNode<T, CmpFunc>* following(this->father);
			while (following != NULL && current == following->rightSon) {
				current = following;
				following = following->father;
			}
			return following;
		}
		return this->rightSon->GetMinimumNode();
	}
    
	//Calculates the balance factor of node.
	int BF() const {
		int rightHeight = -1;
		int leftHeight = -1;
		if (leftSon)
			leftHeight = leftSon->nodeHeight;
		if (rightSon)
			rightHeight = rightSon->nodeHeight;
		return leftHeight - rightHeight;
	}
    
	bool operator==(const AVLNode& node) const {
		return comperFunc(data, node.data) == 0;
	}
    
	bool operator<(const AVLNode& node) const {
		return comperFunc(data, node.data) == -1;
	}
    
	bool operator>(const AVLNode& node) const {
		return comperFunc(data, node.data) == 1;
	}
    
    //Perform LL roll assuming the sub-trees under the sons are in AVL form
	void LL() {
		//save info
		AVLNode* A(leftSon);
		AVLNode* B(this);
		AVLNode *AL(NULL), *AR(NULL), *BR(rightSon);
		T Adata(A->data), Bdata(B->data);
		if (A) {
			AL = A->leftSon;
			AR = A->rightSon;
		}
        
		//change B To A
		data = Adata;
		leftSon = AL;
		rightSon = A;
        
		//change A To B
		A->data = Bdata;
		A->leftSon = AR;
		A->rightSon = BR;
		if (AL) {
			AL->father = B;
		}
		if (BR) {
			BR->father = A;
		}
        
		A->currectNodeHeight();
		B->currectNodeHeight();
	}
    
    //Perform RR roll assuming the sub-trees under the sons are in AVL form
	void RR() {
		//save info
		AVLNode *A(this);
		AVLNode *B(rightSon);
		AVLNode *BR(NULL), *BL(NULL), *AL(leftSon);
		if (B) {
			BL = B->leftSon;
			BR = B->rightSon;
		}
		T AData(A->data), BData(B->data);
        
		//change A to B
		data = BData;
		leftSon = B;
		rightSon = BR;
        
		//change B to A
		B->data = AData;
		B->rightSon = BL;
		B->leftSon = AL;
        
		if (BR) {
			BR->father = A;
		}
		if (AL) {
			AL->father = B;
		}
        
		B->currectNodeHeight();
		A->currectNodeHeight();
	}
    
    //Perform LR roll
	void LR() {
		leftSon->RR();
		this->LL();
	}
    
    //Perform RL roll
	void RL() {
		rightSon->LL();
		this->RR();
	}
    
    //Perform roll corrections to the tree according to balance factors.
	void chooseAndDoRolls() {
		if (BF() == -2) {
			if (rightSon->BF() == 1) {
				this->RL();
			} else {
				this->RR();
			}
		} else if (BF() == 2) {
			if (leftSon->BF() == -1) {
				this->LR();
			} else {
				this->LL();
			}
		}
	}
    
	//go over the path from given node to the root, and correct the tree.
	void correctNode() {
		AVLNode* currentNode(this);
		while (currentNode) {
			currentNode->currectNodeHeight();
			currentNode->chooseAndDoRolls();
			currentNode = currentNode->father;
		}
	}
    
public:
	//c'tor
	AVLNode(const T& newData, AVLNode *father = NULL) :
    father(father), leftSon(NULL), rightSon(NULL), data(newData), nodeHeight(
                                                                             0) {
	}
    
	//d'tor
	~AVLNode() {
		delete leftSon;
		delete rightSon;
	}
    
	//Insert new data to the tree
	void insertToNode(const T& newData) {
		if (!dataIsIn(newData)) {
			AVLNode elementToInsert(newData);
			if (*this > elementToInsert) {
				if (leftSon == NULL) {
					leftSon = new AVLNode(newData, this);
				} else {
					leftSon->insertToNode(newData);
				}
			} else {
				if (rightSon == NULL) {
					rightSon = new AVLNode(newData, this);
				} else {
					rightSon->insertToNode(newData);
				}
			}
			currectNodeHeight();
			chooseAndDoRolls();
		}
	}
    
	//Gets a copy of the minimum data at the tree
	T GetMinimumData(){
		return GetMinimumNode()->data;
	}
    
	//Gets a copy of the maximum data at the tree
	T GetMaximumData(){
		return GetMaximumNode()->data;
	}
    
    //Gets a copy of given data in node, while making assumption data is in the tree
	T* FindInNode(const T& Data) {
		AVLNode elementToSearch(Data);
		if (*this > elementToSearch) {
			return leftSon->FindInNode(Data);
		} else if (*this < elementToSearch) {
			return rightSon->FindInNode(Data);
		}
		return &(this->data);
	}
    
	// Removes a node from the tree (with matching data) and corrects the tree
    // back to AVL form
	void removeFromNode(const T& DataToRemove) {
		if (!dataIsIn(DataToRemove)) {
			return;
		}
		AVLNode* nodeToRemove = this->FindNode(DataToRemove);
		NodeStatus sonsStatus = nodeToRemove->GetNodeSonsStatus();
		NodeStatus nodeStatus = nodeToRemove->GetNodeStatus();
		//NO SONS
		if (sonsStatus == NO_SONS) {
			if (nodeToRemove->father == NULL) {
				return;
			}
			if (nodeStatus == RIGHT_SON) {
				nodeToRemove->father->rightSon = NULL;
			}
			if (nodeStatus == LEFT_SON) {
				nodeToRemove->father->leftSon = NULL;
			}
			nodeToRemove->father->correctNode();
			delete nodeToRemove;
			return;
		}
		//ONE_SON
		if (sonsStatus == RIGHT_SON || sonsStatus == LEFT_SON) {
			AVLNode* son;
			if (sonsStatus == RIGHT_SON) {
				son = nodeToRemove->rightSon;
			} else {
				son = nodeToRemove->leftSon;
			}
			if (nodeStatus == ROOT) {
				*nodeToRemove = *son;
				delete son;
				nodeToRemove->father = NULL;
				if (nodeToRemove->leftSon) {
					nodeToRemove->leftSon->father = nodeToRemove;
				}
				if (nodeToRemove->rightSon) {
					nodeToRemove->rightSon->father = nodeToRemove;
				}
				return;
			} else {
				if (nodeStatus == RIGHT_SON) {
					nodeToRemove->father->rightSon = son;
				} else {
					nodeToRemove->father->leftSon = son;
				}
				son->father = nodeToRemove->father;
				nodeToRemove->leftSon = NULL;
				nodeToRemove->rightSon = NULL;
				delete nodeToRemove;
				son->father->correctNode();
				return;
			}
		}
		//TWO SONS
		if (sonsStatus == TWO_SONS) {
			AVLNode* following = nodeToRemove->GetTheFollowingNode();
			NodeStatus followingStatus = following->GetNodeStatus();
			if (followingStatus == RIGHT_SON) {
				following->father->rightSon = following->rightSon;
			}
			if (followingStatus == LEFT_SON) {
				following->father->leftSon = following->rightSon;
			}
			if (following->rightSon) {
				following->rightSon->father = following->father;
			}
			nodeToRemove->data = following->data;
			if (following->rightSon) {
				following->rightSon->correctNode();
			} else {
				following->father->correctNode();
			}
			following->rightSon = NULL;
			delete following;
		}
		return;
	}
    
	//Return true if the data is at the tree, other false
	bool dataIsIn(const T& data) {
		AVLNode elementToSearch(data);
		if (*this == elementToSearch) {
			return true;
		}
		if (*this < elementToSearch) {
			if (rightSon != NULL) {
				return rightSon->dataIsIn(data);
			} else {
				return false;
			}
		} else {
			if (leftSon != NULL) {
				return leftSon->dataIsIn(data);
			} else {
				return false;
			}
		}
	}
    
	//Gets nodes and subs nodes into a pre-allocated array
	void GetNodeIntoArray(T* array, int& i) {
		if (leftSon) {
			leftSon->GetNodeIntoArray(array, i);
		}
        
		array[i] = data;
		i++;
		if (rightSon) {
			rightSon->GetNodeIntoArray(array, i);
		}
		return;
	}
    
	//Gets data of the following node
	T& GetFollowingData() {
		AVLNode* following = this->GetTheFollowingNode();
		return following->data;
	}
    
    
};

template<class T, class CmpFunc>
class AVLTree {
private:
	AVLNode<T, CmpFunc>* root;
	int size;
	CmpFunc comperInt;
public:
	//Default constructor: empty tree
	AVLTree() :
    root(NULL), size(0) {
	}
    
	//C'tor
	AVLTree(const T& newData) :
    size(1) {
		try {
			root = new AVLNode<T, CmpFunc>(newData);
		} catch (...) {
		}
	}
    
	//D'tor
	~AVLTree() {
		delete root;
		root = NULL;
	}
    
	//Insert data to the tree
	AVLTreeResult insert(const T& data) {
		if (root == NULL) {
			root = new AVLNode<T, CmpFunc>(data);
			size++;
			return AVL_TREE_SUCCESS;
		}
		if (root->dataIsIn(data)) {
			return AVL_TREE_DATA_ALREADY_EXIST;
		}
		root->insertToNode(data);
		size++;
		return AVL_TREE_SUCCESS;
	}
    
    //Gets a data pointer of given element's data in tree. Assuming data is in the tree.
	T* Find(const T& data) const {
		assert(root!= NULL);// && root->dataIsIn(data));
		return root->FindInNode(data);
	}
    
	//Delete data from the tree
	AVLTreeResult Remove(const T& dataToRemove) {
		if (!root) {
			return AVL_TREE_DATA_NOT_EXIST;
		}
		if (!root->dataIsIn(dataToRemove)) {
			return AVL_TREE_DATA_NOT_EXIST;
		}
		if (size == 1) {
			delete root;
			root = NULL;
			size--;
			return AVL_TREE_SUCCESS;
		}
		root->removeFromNode(dataToRemove);
		size--;
		return AVL_TREE_SUCCESS;
	}
    
	//Gets a tree into a pre-allocated array.*/
	void GetTreeInArray(T* array) const {
		int i = 0;
		if (root) {
			root->GetNodeIntoArray(array, i);
		}
	}
    
	int GetTreeSize() {
		return size;
	}
    
	//Gets a copy of the minimal data in the tree,assuming the tree  not empty.
	T GetMinimum(){
		return root->GetMinimumData();
	}
    
	//Gets a copy of the maximal data in the tree,assuming the tree  not empty.
	T GetMaximum(){
		return root->GetMaximumData();
	}
    
	//return true if data in the tree, otherwise false
	bool DataInTree(T& data){
		if(root){
			return root->dataIsIn(data);
		}
		return false;
	}
    
    
};

#endif /* AVLTREE_H_ */
