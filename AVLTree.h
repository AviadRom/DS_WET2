//
//  AVLTree.h
//  DS-WET2
//
//

#ifndef DS_WET2_AVLTree_h
#define DS_WET2_AVLTree_h
#include <iostream>
using namespace std;

typedef enum {NODE_EXISTS,NODE_TREE_NOW_EMPTY,NODE_SUCCESS} AVLNodeResult;
typedef enum {LEFT_SON,RIGHT_SON,BOTH_SONS,NO_SONS,NO_FATHER} AVLNodeStatus;
typedef enum {TREE_ELEMENT_EXISTS,TREE_SUCCESS,
    TREE_ELEMENT_DOES_NOT_EXIST} AVLTreeResult;

/* maxPositiveInt
 * Description: returns maximum value between 3 ints or max positiveVal between 2 ints
 */
static int maxPositiveInt(int a,int b,int c=0){
	if (a>=b && a>=c) return a;
	if (b>=a && b>=c) return b;
	return c;
}

template <class T,class TFunc>
//TFunc contains all functions needed for use of class T as used.
class AVLNode{
private:
	T   data;
	int maxValueInTree;
	int maxIdByValueInTree;
	int maxId;
	int treeHeight;
	int delta;
	AVLNode<T,TFunc> *leftSon,*rightSon,*father;
	TFunc operate;
        
	bool operator>(const AVLNode& b) const{
		if (operate.compareById(data,b.data)==1){
			return true;
		}
		return false;
	}
    
	bool operator<(const AVLNode& b) const{
		return (b>(*this));
	}
    
	bool operator==(const AVLNode& b) const{
		if (operate.compareById(data,b.data)==0) return true;
		return false;
	}
    
	/*assuming sons are with correct height - corrects current height */
    //correctTreeHeight
    //Corrects
	void correctTreeHeight(){
		if (leftSon==NULL && rightSon==NULL){
			treeHeight=0;
			return;
		}
		int rightHeight=0;
		int leftHeight=0;
		if (leftSon!=NULL) leftHeight=leftSon->treeHeight;
		if (rightSon!=NULL) rightHeight=rightSon->treeHeight;
		treeHeight=maxPositiveInt(rightHeight,leftHeight)+1;
	}
    
	/*assuming sons are with correct max - corrects current max:*/
	void correctMaxId(){
		if (rightSon!=NULL){
			maxId=rightSon->maxId;
		}else{
			maxId=operate.getId(data);
		}
		return;
	}
    
	/*assuming sons are with correct maxByVal - corrects current maxByVal:*/
	void correctMaxByValue(){
        
		int rightMax=-1;
		int leftMax=-1;
		if (leftSon!=NULL){
			leftMax=leftSon->getMaxVal();
		}
		if (rightSon!=NULL){
			rightMax=rightSon->getMaxVal();
		}
		if (rightMax<0) rightMax=0;
		if (leftMax<0) leftMax=0;
		int rootRealVal=operate.getVal(data);
		if (rootRealVal<0) rootRealVal=0;
		maxValueInTree=maxPositiveInt(rightMax,leftMax,rootRealVal);
		if (leftSon!=NULL && maxValueInTree==(leftMax)){
			maxIdByValueInTree=leftSon->maxIdByValueInTree;
		}
        
		if (maxValueInTree==rootRealVal){
			maxIdByValueInTree=operate.getId(data);
		}
        
		if (rightSon!=NULL && maxValueInTree==(rightMax)){
			maxIdByValueInTree=rightSon->maxIdByValueInTree;
		}
		return;
	}
    
	/*inserts into tree, assuming not in tree*/
	void insert(T& dataToInsert,int currentDelta=0){
		AVLNode<T,TFunc> temp(dataToInsert,this);
		if (temp>(*this)){
			if (maxId<operate.getId(dataToInsert)){//update maxId
				maxId=operate.getId(dataToInsert);
			}
			if (rightSon!=NULL){
				rightSon->insert(dataToInsert,currentDelta+delta);
			}else{
				operate.changeVal(dataToInsert,-currentDelta-delta);
				rightSon=new AVLNode<T,TFunc>(dataToInsert,this);
			}
		}else if (temp<(*this)){
			if (leftSon!=NULL){
				leftSon->insert(dataToInsert,currentDelta+delta);
			}else{
				operate.changeVal(dataToInsert,-currentDelta-delta);
				leftSon=new AVLNode<T,TFunc>(dataToInsert,this);
			}
		}
		correctTreeHeight();
		correctMaxId();
		correctMaxByValue();
		correctRolls();
		return;
	}
    
	/* calculates Node Balance Factor */
	int BF(){
		int left=-1;
		int right=-1;
		if (leftSon!=NULL) left=leftSon->treeHeight;
		if (rightSon!=NULL) right=rightSon->treeHeight;
		return left-right;
	}
    
	/*assuming sons are with correct subTrees according to AVL terms:*/
	void LLroll(){
		//normalize A and B:
		if (leftSon!=NULL) leftSon->delta+=delta;
		if (rightSon!=NULL) rightSon->delta+=delta;
		operate.changeVal(data,delta);
		delta=0;
		if (leftSon!=NULL){
			if (leftSon->leftSon!=NULL) leftSon->leftSon->delta+=leftSon->delta;
			if (leftSon->rightSon!=NULL) leftSon->rightSon->delta+=leftSon->delta;
			operate.changeVal(leftSon->data,leftSon->delta);
			leftSon->delta=0;
		}
		//Acquire info:
		AVLNode<T,TFunc> *A(leftSon),*B(this),*AL(NULL),*AR(NULL),*BR(rightSon);
		if (leftSon!=NULL){
			AL=leftSon->leftSon;
			AR=leftSon->rightSon;
		}
		T Adata(A->data),Bdata(B->data);
		//modify B:
		data=A->data;
		leftSon=AL;
		rightSon=A;
		//modify A:
		A->data=Bdata;
		A->leftSon=AR;
		A->rightSon=BR;
		//modify AL:
		if (AL!=NULL){
			AL->father=B;
		}
		if (BR!=NULL){
			BR->father=A;
		}
		A->correctMaxId();
		A->correctMaxByValue();
		B->correctMaxId();
		B->correctMaxByValue();
		A->correctTreeHeight();
		B->correctTreeHeight();
		return;
	}
    
	void RRroll(){
		AVLNode<T,TFunc>* A=rightSon;
		/**** modify this *****/
		if (leftSon!=NULL){
			leftSon->delta+=delta;
		}
		if (A!=NULL){
			A->delta+=delta;
		}
		operate.changeVal(data,delta);
		delta=0;
		/***** modify A suns****/
		if (A->leftSon!=NULL){
			A->leftSon->delta+=A->delta;
		}
		if (A->rightSon!=NULL){
			A->rightSon->delta+=A->delta;
		}
		operate.changeVal(A->data,A->delta);
		A->delta=0;
		/**** make the roll****/
		T tempData=data;
		data=A->data;
		A->data=tempData;
		rightSon=A->rightSon;
		if (A->rightSon!=NULL){
			A->rightSon->father=this;
		}
		A->rightSon=A->leftSon;
		A->leftSon=leftSon;
		if (leftSon!=NULL){
			leftSon->father=A;
		}
		leftSon=A;
		A->correctMaxId();
		A->correctTreeHeight();
		A->correctMaxByValue();
		this->correctMaxId();
		this->correctMaxByValue();
		this->correctTreeHeight();
		return;
	}
    
	void RLroll(){
		assert(rightSon!=NULL);
		this->rightSon->LLroll();
		this->RRroll();
		return;
	}
    
	void LRroll(){
		assert(leftSon!=NULL);
		this->leftSon->RRroll();
		this->LLroll();
		return;
	}
    
    /* determines if roll is needed and executes */
	void correctRolls(){
		if (BF()==2){
			if (leftSon->BF()>=0){
				LLroll();
			}else{
                assert(leftSon->BF()==-1);
                LRroll();
			}
		}else if (BF()==-2){
			if (rightSon->BF()<=0){
				RRroll();
			}else{
                assert(rightSon->BF()==1);
                RLroll();
			}
		}
		return;
	}
    
	/* implements a series of rolls from given node top of tree */
	void correctNode(){
		AVLNode<T,TFunc>* current(this);
		while (current!=NULL){
			current->correctTreeHeight();
			current->correctMaxId();
			current->correctMaxByValue();
			correctRolls();
			current=current->father;
        }
		return;
	}
	/* returns the Ptr of the following node,if there isn't one, returns null,
	 * also returns the delta collected on route to following node as specified.
	 */
	AVLNode<T,TFunc>* getFollowingNode(int* deltaCollected) const {
		//delta collected on route to follower, not including root and including follower.
		if (this->rightSon==NULL) return NULL;
		AVLNode<T,TFunc>* following=this->rightSon;
		while (following->leftSon!=NULL){
			*deltaCollected+=following->delta;
			following=following->leftSon;
		}
		*deltaCollected+=following->delta;
		return following;
	}
    
	/* Description:   gets node status regarding his sons.
	 * Output:		  as stated.
	 */
	AVLNodeStatus getNodeStatus() const{
		if (leftSon!=NULL && rightSon!=NULL) return BOTH_SONS;
		if (leftSon!=NULL && rightSon==NULL) return LEFT_SON;
		if (leftSon==NULL && rightSon!=NULL) return RIGHT_SON;
		return NO_SONS;
	}
    
	/* Description:   gets node status regarding his father.
	 * Output:		  as stated.
	 */
	AVLNodeStatus getFatherStatus() const{
		if (father==NULL) return NO_FATHER;
		if (father->leftSon==this) return LEFT_SON;
		return RIGHT_SON;
	}
    
	/* Description:   finds a given element's node.
	 * Input:         element.
	 * Output:		  ptr to wanted node, null if not found,also delta collected on route to node.
	 */
	AVLNode<T,TFunc>* findNode(const T& dataToFind,int* currentDelta){
		AVLNode<T,TFunc> temp(dataToFind);
		if ((*this)==temp){
			return this;
		}else if ((*this)>temp){
			if (leftSon!=NULL){
				*currentDelta+=delta;
				return leftSon->findNode(dataToFind,currentDelta);
			}else{
				*currentDelta=0;
				return NULL;
			}
		}else{
			if ((*this)<temp){
				if (rightSon!=NULL){
					*currentDelta+=delta;
					return rightSon->findNode(dataToFind,currentDelta);
				}else{
					*currentDelta=0;
					return NULL;
				}
			}
		}
		return NULL;
	}
	/* assuming element is in tree, deletes element and corrects tree */
	void deleteFromNode(const T& element){
		assert(isInNode(element));
		int currentDelta=0;
		AVLNode<T,TFunc>* nodeToRemove=findNode(element,&currentDelta);
		AVLNodeStatus removedStatus=nodeToRemove->getNodeStatus();
		AVLNodeStatus removedFatherStatus=nodeToRemove->getFatherStatus();
		//=====================================
		if (removedStatus==NO_SONS){
			if (removedFatherStatus==NO_FATHER){
                //root removed and only one in tree
				return;	//tree is cleared in removeFromTree.
			}
			//remove leaf and fix relevant father's son
			if (removedFatherStatus==LEFT_SON){
				nodeToRemove->father->leftSon=NULL;
			}
			if (removedFatherStatus==RIGHT_SON){
				nodeToRemove->father->rightSon=NULL;
			}
			nodeToRemove->father->correctNode();
			delete nodeToRemove;
			return;
		}
		//=====================================
		if (removedStatus==LEFT_SON || removedStatus==RIGHT_SON){
			AVLNode<T,TFunc>* onlySon;
			if (removedStatus==LEFT_SON) onlySon=nodeToRemove->leftSon;
			if (removedStatus==RIGHT_SON) onlySon=nodeToRemove->rightSon;
			if (removedFatherStatus==NO_FATHER){
                //copy only son to deleted one (root) and delete (after nulling)
				onlySon->delta+=(nodeToRemove->delta);//correct Delta
				*nodeToRemove=*onlySon;	//copy fields
				nodeToRemove->father=NULL;//correctFather
				delete onlySon;
				//correct son's fathers.
				if (nodeToRemove->leftSon!=NULL){
					nodeToRemove->leftSon->father=nodeToRemove;
				}
				if (nodeToRemove->rightSon!=NULL){
					nodeToRemove->rightSon->father=nodeToRemove;
				}
				nodeToRemove->father->correctNode();//no need for corrections of tree height, max, etc.
				return;
			}else{
				//make father point to only son and delete after nulling.
				onlySon->delta+=nodeToRemove->delta;//correctDelta;
				if (removedFatherStatus==LEFT_SON){
					nodeToRemove->father->leftSon=onlySon;
				}
				if (removedFatherStatus==RIGHT_SON){
					nodeToRemove->father->rightSon=onlySon;
				}
				onlySon->father=nodeToRemove->father;
				nodeToRemove->leftSon=NULL;
				nodeToRemove->rightSon=NULL;
				delete nodeToRemove;
				onlySon->correctMaxByValue();//only correction needed for onlySon.
				onlySon->father->correctNode();
				return;
			}
		}
		//=====================================
		if (removedStatus==BOTH_SONS){
			nodeToRemove->leftSon->delta+=nodeToRemove->delta;
			nodeToRemove->rightSon->delta+=nodeToRemove->delta;
			operate.changeVal(nodeToRemove->data,nodeToRemove->delta);
			nodeToRemove->delta=0;
			int deltaToAddToFollower=0;
			AVLNode<T,TFunc>* following=nodeToRemove->getFollowingNode(&deltaToAddToFollower);
			AVLNodeStatus followingFatherStatus=following->getFatherStatus();
			assert(following!=NULL);
			//take following rightSon and link it to father of nodeToRemove.
			if (followingFatherStatus==LEFT_SON){
				following->father->leftSon=following->rightSon;
			}
			if (followingFatherStatus==RIGHT_SON){
				following->father->rightSon=following->rightSon;
			}
			if (following->rightSon!=NULL){
				following->rightSon->delta+=following->delta; //correct son's Delta;
				following->rightSon->father=following->father;
			}
			following->delta=0;
			//copy data to nodeToRemove and update value
			operate.changeVal(following->data,deltaToAddToFollower);
			nodeToRemove->data=following->data;
			if (following->rightSon!=NULL){
				following->rightSon->correctNode();
			}else{
				following->father->correctNode();
			}
			following->rightSon=NULL;
			delete following;
		}
		return;
	}
    
public:
	AVLNode<T,TFunc>(const T& element,AVLNode<T,TFunc>* father=NULL):
    data(element),maxValueInTree(0),maxIdByValueInTree(0),maxId(0),
    treeHeight(0),delta(0),leftSon(NULL),rightSon(NULL),father(father){
		maxValueInTree=operate.getVal(data);
		maxIdByValueInTree=maxId=operate.getId(data);
	};
    
	~AVLNode<T,TFunc>(){
		delete leftSon;
		delete rightSon;
	}
    
	bool isInNode(const T& dataToFind){
		AVLNode<T,TFunc> temp(dataToFind);
		if ((*this)==temp) return true;
		if ((*this)>temp){
			if (leftSon!=NULL){
				return leftSon->isInNode(dataToFind);
			}else{
				return false;
			}
		}
		if ((*this)<temp){
			if (rightSon!=NULL){
				return rightSon->isInNode(dataToFind);
			}else{
				return false;
			}
		}
		return false;
	}
    
	AVLNode<T,TFunc>& operator=(const AVLNode& a){
		data=a.data;
		maxValueInTree=a.maxValueInTree;
		maxIdByValueInTree=a.maxIdByValueInTree;
		maxId=a.maxId;
		treeHeight=a.treeHeight;
		delta=a.delta;
		rightSon=a.rightSon;
		leftSon=a.leftSon;
		father=a.father;
		return *this;
	}
    
	void addToNode(T& dataToInsert){
		if (isInNode(dataToInsert)) return;
		insert(dataToInsert);
		return;
	}
    
	int getMaxValId(){
		if (getMaxVal()==0) return maxId;
		return maxIdByValueInTree;
	}
    
	int getMaxVal(){
		return maxPositiveInt(maxValueInTree+delta,0);
	}
    
	int getHeight(){
		return treeHeight;
	}
    
	void printTree(){
		if (leftSon!=NULL){
			leftSon->printTree();
		}
		data.print();
		cout<<"height:"<<treeHeight<<"  delta:"<<delta<<"  maxId:"<<maxId<<endl;
		cout<<"maxValueId:"<<maxIdByValueInTree<<"  maxValue:"<<maxValueInTree<<endl<<endl;
		if (rightSon!=NULL){
			rightSon->printTree();
		}
	}
    
	//assuming id in tree, lowers delta as needed from necessary elements
	void lowerByDelta(int D,int id,int currentDelta=0){
		assert(D<=0 && id>=0);
		if (id<operate.getId(data)){
			assert(leftSon!=NULL);
			leftSon->lowerByDelta(D,id,currentDelta+delta);
		}else if (id>operate.getId(data)){
			operate.changeVal(data,D);
			if (leftSon!=NULL){
				leftSon->delta+=D;
			}
			assert(rightSon!=NULL);
			rightSon->lowerByDelta(D,id,currentDelta+delta);
		}else{//id == this id
			operate.changeVal(data,D);
			if (leftSon!=NULL){
				leftSon->delta+=D;
			}
		}
		if (leftSon!=NULL){
			leftSon->correctNode();
		}else{
			correctNode();
		}
		return;
	}
    
	void removeFromNode (const T& dataToRemove){
		if (!isInNode(dataToRemove)) return;
		deleteFromNode(dataToRemove);
		return;
	}
    
	int getPriority(const T& data){
		if (!isInNode(data)) return -1;
		int priority=0;
		AVLNode<T,TFunc> temp(data);
		AVLNode<T,TFunc>* current=this;
		while (!(*(current)==temp)){
			priority+=(current->delta);
			if ((*(current))>temp){
				assert(current->leftSon!=NULL);
				current=current->leftSon;
			}else if ((*(current))<temp){
				assert(current->rightSon!=NULL);
				current=current->rightSon;
			}
		}
		priority+=operate.getVal(current->data)+(current->delta);
		if (priority<0) priority=0;
		return priority;
	}
};



template <class T,class TFunc>
class AVLTree{
private:
	AVLNode<T,TFunc>* root;
	int size;
	TFunc operate;
public:
    /* Description:   Empty Tree Ctor. */
	AVLTree<T,TFunc>():root(NULL),size(0){};
    /* Description:   Ctor For a Tree.
     * Input:         element.
     */
	AVLTree<T,TFunc>(const T& element):root(NULL),size(1){
		root=new AVLNode<T,TFunc>(element);
	}
    
    /* Description:   Dtor For a Tree. */
	~AVLTree<T,TFunc>(){
		delete root;
		root=NULL;
	}
    
    /* Description:   adds a given element to tree.
     * Input:         element.
     * Output:		  TREE_ELEMENT_EXISTS
     * 				  TREE_SUCCESS
     */
	AVLTreeResult addToTree(T& element){
		if (root==NULL){
			root=new AVLNode<T,TFunc>(element);
			size=1;
			return TREE_SUCCESS;
		}
		if (root->isInNode(element)){
			return TREE_ELEMENT_EXISTS;
		}
		root->addToNode(element);
		size++;
		return TREE_SUCCESS;
	}
    
    /* Description:   removes a given element from tree.
     * Input:         element.
     * Output:		  TREE_ELEMENT_DOES_NOT_EXIST
     * 				  TREE_SUCCESS
     */
	AVLTreeResult removeFromTree(const T& element){
		if (root==NULL){
			return TREE_ELEMENT_DOES_NOT_EXIST;
		}
		if (root->isInNode(element)==false){
			return TREE_ELEMENT_DOES_NOT_EXIST;
		}
		if(size==1){//and element is in tree.
			delete root;
			root=NULL;
			size--;
			return TREE_SUCCESS;
		}
		root->removeFromNode(element);
		size--;
		return TREE_SUCCESS;
	}
    
    /* Description:   returns tree size.*/
	int treeSize() const{
		return size;
	}
    
    /* Description:   checks if a given element is in tree.
     * Input:         element.
     * Output:		  true/false
     */
	bool isInTree(const T& element){
		if (root==NULL){
			return false;
		}
		return root->isInNode(element);
	}
    
    /* Description:   gets id of the maximal data by priority in tree.
     * Output:		  max data copy.
     * ImportantNotes:always check that tree isn't empty before use.
     */
	int getMaxInTree(){//always check that tree isn't empty before use
		assert(root!=NULL);
		return root->getMaxValId();
	}
	/* as required in exercise, assuming input is valid */
	void lowerByDeltaById (int delta,int id){
		assert(delta>=0 && id>=0);
		if (root==NULL) return;
		T temp(id,1);
		if (!(root->isInNode(temp))){
			root->addToNode(temp);
			root->lowerByDelta(-delta,id);
			root->removeFromNode(temp);
		}else{
			root->lowerByDelta(-delta,id);
		}
        
		return;
	}
    
	int getPriority(int id){
		assert(id>=0);
		T temp(id,1);
		assert(root!=NULL && root->isInNode(temp)==true);
		return root->getPriority(temp);
	}
    
	void printTree(){
		cout<<"*printTree:*"<<endl;
		cout<<"------------------------------------"<<endl;
		if (root!=NULL){
			root->printTree();
		}
		cout<<"===================================="<<endl;
	}
};



#endif
