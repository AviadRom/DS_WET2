/****************************************************************************/
/*                                                                          */
/* This file contains the interface functions                               */
/* you should use for the wet ex 2                                          */ 
/*                                                                          */ 
/****************************************************************************/

/****************************************************************************/
/*                                                                          */ 
/* File Name : library2.h                                                   */ 
/*                                                                          */ 
/****************************************************************************/

#ifndef _234218_WET2_
#define _234218_WET2_


#ifdef __cplusplus
extern "C" {
#endif




/* Return Values
 * ----------------------------------- */
typedef enum {
        SUCCESS = 0,
        FAILURE = -1,
        ALLOCATION_ERROR = -2,
        INVALID_INPUT = -3
} StatusType;



/* Required Interface for the Data Structure
 * -----------------------------------------*/



/* Description:   Initiates the data structure.
 * Input:         N - The number of tasks in the initial tasker.
 *                tasksIDs - ID numbers of the tasks in the initial tasker
 *                priorities - Priority level of the tasks in the initial tasker
 * Output:        None.
 * Return Values: A pointer to a new instance of the data structure - as a void* pointer.
 */
void*       Init(int N, int *tasksIDs, int *priorities);


/* Description:   Adds a new task to the tasker.
 * Input:         DS - A pointer to the data structure.
 *                taskID - ID number of the task that enters the tasker.
 *                priority - Priority level of the task that enters the tasker.
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL.
 *                FAILURE - if taskID is already in the DS.
 *                SUCCESS - Otherwise.
 */
StatusType  AddTask(void* DS, int taskID, int priority);


/* Description:   Sets the first task in the tasker to done (removing him from the tasker).
 * Input:         DS - A pointer to the data structure.
 *
 * Output:        taskID - A pointer to a variable to be updated with the ID number 
 *                            of the task that leaves the tasker.
 *                priority - A pointer to a variable to be updated with the priority level 
 *                           of the task that leaves the tasker.

 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If any of the input arguments is NULL.
 *                FAILURE - If the tasker is empty.
 *                SUCCESS - Otherwise.
 */
StatusType  NextTask(void* DS, int *taskID, int *priority);


/* Description:   Changes the priority level of a task.
 * Input:         DS - A pointer to the data structure.
 *                taskID - ID number of the task whose priority level is changed.
 *                priority - The new priority level of the task.
 *
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL.
 *                FAILURE - If taskID is not in the DS.
 *                SUCCESS - Otherwise.
 */
StatusType  SetPriority(void* DS, int taskID, int priority);


/* Description:   Task canceled and removed from the tasker.
 * Input:         DS - A pointer to the data structure.
 *                taskID - ID of the task that gives up.
 *
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL.
 *                FAILURE - If taskID is not in the DS.
 *                SUCCESS - Otherwise.
 */
StatusType  Cancel(void* DS, int taskID);


/* Description:   Returns information about the task that is last in tasker.
 * Input:         DS - A pointer to the data structure.
 *
 * Output:        taskID - A pointer to a variable to be updated with the ID number 
 *                            of the task that is last in tasker.
 *                priority - A pointer to a variable to be updated with the priority level 
 *                           of the task that is last in tasker.
 *
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If any of the arguments is NULL.
 *                FAILURE - If the tasker is empty.
 *                SUCCESS - Otherwise.
 */
StatusType  LastTask(void* DS, int *taskID, int *priority);


/* Description:   Returns information about the task that is in the Kth place in the tasker.
 * Input:         DS - A pointer to the data structure.
 *                k  - The index of the task whose information you should retrieve
 *
 * Output:        taskID - A pointer to a variable to be updated with the ID number 
 *                            of the task that is Kth in tasker.
 *                priority - A pointer to a variable to be updated with the priority level 
 *                            of the task that is Kth in tasker.
 *
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If any of the arguments is NULL or k <= 0.
 *                FAILURE - If the tasker size is smaller than k.
 *                SUCCESS - Otherwise.
 */
StatusType  GetKthTask(void* DS, int k, int *taskID, int *priority);


/* Description:   Quits and deletes the database.
 *                DS should be set to NULL.
 * Input:         DS - A pointer to the data structure.
 * Output:        None.
 * Return Values: None.
 */
void        Quit(void** DS);



#ifdef __cplusplus
}
#endif

#endif    /*_234218_WET2_ */ 

