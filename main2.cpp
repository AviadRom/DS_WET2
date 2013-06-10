/***************************************************************************/
/*                                                                         */
/* 234218 Data DSs 1, Spring 2013                                          */
/*                                                                         */
/* Homework : Wet 2                                                        */
/*                                                                         */
/***************************************************************************/

/***************************************************************************/
/*                                                                         */
/* File Name : main2.cpp                                                   */
/*                       						   */	
/* Written By: Matan Hamilis                                               */
/* Holds the "int main()" function and the parser of the shell's           */
/* command line.                                                           */
/***************************************************************************/


#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "library2.h"
#include <string.h>

using namespace std;

#ifdef __cplusplus
extern "C" {
#endif




/* The command's strings */
typedef enum {
    NONE_CMD = -2,
    COMMENT_CMD = -1,
    INITBEGIN_CMD = 0,
    INITLIST_CMD = 1,
    INITEND_CMD = 2,
    ADDTASK_CMD = 3,
    NEXTTASK_CMD = 4,
    CHANGEPRIO_CMD = 5,
    CANCEL_CMD = 6,
    LAST_CMD = 7,
    GETKTH_CMD = 8,
    QUIT_CMD = 9
} commandType;



static const int   numActions   = 10;
static const char *commandStr[] = {
    "InitBegin",
    "InitList",
    "InitEnd",
    "AddTask",
    "NextTask",
    "SetPriority",
    "Cancel",
    "LastTask",
    "GetKthTask",
    "Quit"
};


static const char* ReturnValToStr(int val) {
    switch (val) {
        case (SUCCESS):          return "Success";
        case (FAILURE):          return "Failure";
        case (ALLOCATION_ERROR): return "Allocation_error";
        case (INVALID_INPUT):    return "Invalid_input";
        default:                 return "";
    }
}






/* we assume maximum string size is not longer than 256  */
#define MAX_STRING_INPUT_SIZE (255)
#define MAX_BUFFER_SIZE       (255)

#define StrCmp(Src1,Src2) ( strncmp((Src1),(Src2),strlen(Src1)) == 0 )

typedef enum {error_free, error} errorType;
static errorType parser(const char* const command);



#define ValidateRead(read_parameters,required_parameters,ErrorString) \
if ( (read_parameters)!=(required_parameters) ) { printf(ErrorString); return error; }


static bool isInit = false;


/* Print an array */
void PrintIntArray(const int* arr, int size) {
    for (int i = 0; i < size; ++i){
        printf("%d %c", arr[i], (i < size-1)? ',': '\n');
    }
}


/***************************************************************************/
/* main                                                                    */
/***************************************************************************/

int main(int argc, const char**argv) {
    FILE* inputFile = NULL;

    setlocale(LC_ALL, "");
    if(argc == 2){
        inputFile = fopen(argv[1], "r");
        if (inputFile == NULL){
            printf("Problem opening file %s, make sure correct path name is given.\n", argv[1]);
            return 0;
        }
    }
    else {
        inputFile = stdin;
    }

    char buffer[MAX_STRING_INPUT_SIZE];
    // Reading commands
    while ( fgets(buffer, MAX_STRING_INPUT_SIZE, inputFile) != NULL ) {
        fflush(stdout);
        if ( parser(buffer) == error ){
            printf("ERROR\n");
            break;
        }
    };
    fclose(inputFile);
    return 0;
}

/***************************************************************************/
/* Command Checker                                                         */
/***************************************************************************/

static commandType CheckCommand(const char* const command, const char** const command_arg) {
    if ( command == NULL || strlen(command) == 0 || StrCmp("\n", command) )
        return(NONE_CMD);
    if ( StrCmp("#", command) ) {
        if (strlen(command) > 1)
            printf("%s", command);
        return(COMMENT_CMD);
    };
    for (int index=0; index < numActions; index++) {
        if ( StrCmp(commandStr[index], command) ) {
            *command_arg = command + strlen(commandStr[index]) + 1;
            return((commandType)index);
        };
    };
    return(NONE_CMD);
}

/***************************************************************************/
/* Commands Functions                                                      */
/***************************************************************************/

static errorType OnInitBegin(void** DS, const char* const command, int* n, int** IDs, int** priorities);
static errorType OnInitList(void** DS, const char* const command, int n, int* IDs, int* priorities, int* read);
static errorType OnInitEnd(void** DS, const char* const command, int n, int read, int** IDs, int** priorities);
static errorType OnAddTask(void* DS, const char* const command);
static errorType OnNextTask(void* DS, const char* const command);
static errorType OnSetPriority(void* DS, const char* const command);
static errorType OnCancel(void* DS, const char* const command);
static errorType OnLastTask(void* DS, const char* const command);
static errorType OnGetKthTask(void* DS, const char* const command);
static errorType OnQuit(void** DS, const char* const command);




/***************************************************************************/
/* Parser                                                                  */
/***************************************************************************/

static errorType parser(const char* const command) { 
    static void *DS = NULL; /* The general data structure */
    const char* command_args = NULL;
    errorType rtn_val = error;

    static int n = -1;
    static int read = 0;
    static int *IDs = NULL;
    static int *priorities = NULL;

    commandType command_val = CheckCommand(command, &command_args);

    switch (command_val) {

        case (INITBEGIN_CMD):   rtn_val = OnInitBegin(&DS, command_args, &n, &IDs, &priorities);            break;
        case (INITLIST_CMD):    rtn_val = OnInitList(&DS, command_args, n, IDs, priorities, &read);            break;
        case (INITEND_CMD):     rtn_val = OnInitEnd(&DS, command_args, n, read, &IDs, &priorities);            break;
        case (ADDTASK_CMD):     rtn_val = OnAddTask(DS, command_args);       break;
        case (NEXTTASK_CMD):    rtn_val = OnNextTask(DS, command_args);      break;
        case (CHANGEPRIO_CMD):  rtn_val = OnSetPriority(DS, command_args);   break;
        case (CANCEL_CMD):      rtn_val = OnCancel(DS, command_args);           break;
        case (LAST_CMD):        rtn_val = OnLastTask(DS, command_args);       break;
        case (GETKTH_CMD):      rtn_val = OnGetKthTask(DS, command_args);    break;
        case (QUIT_CMD):        rtn_val = OnQuit(&DS, command_args);            break;

        case (COMMENT_CMD):     rtn_val = error_free;   break;
        case (NONE_CMD):        rtn_val = error;        break;
        default: assert(false);
    };
    return(rtn_val);
}





/***************************************************************************/
/* OnInitBegin                                                             */
/***************************************************************************/
static errorType OnInitBegin(void** DS, const char* const command, int* n, int** IDs, int** priorities){

    ValidateRead( sscanf(command, "%d", n), 1, "Init failed.\n" );
    if (n < 0){
        return error;
    }

    *IDs = (int*) malloc(sizeof(int) * (*n));
    *priorities = (int*) malloc(sizeof(int) * (*n));
    if (NULL == IDs || NULL == priorities){
        return error;
    }

    return error_free;
}


/***************************************************************************/
/* OnInitList                                                              */
/***************************************************************************/
static errorType OnInitList(void** DS, const char* const command, int n, int* IDs, int* priorities, int* read){

    if (*read >= n){
        return error;
    }

    ValidateRead( sscanf(command, "%d %d",&(IDs[*read]),&(priorities[*read])), 2, "Init failed.\n" );
    ++(*read);

    return error_free;
}


/***************************************************************************/
/* OnInitEnd                                                               */
/***************************************************************************/
static errorType OnInitEnd(void** DS, const char* const command, int n, int read, int** IDs, int** priorities){

    if(isInit) {
        printf("Init was already called.\n");
        return(error_free);
    }
    if (read < n){
        printf("Not all patients were set.\n");
        return error;
    }

    isInit = true;

    *DS = Init(n, *IDs, *priorities);
    free(*IDs);
    free(*priorities);
    *IDs = NULL;
    *priorities = NULL;

    if( *DS == NULL ) {
        printf("Init failed.\n");
        return(error);
    }
    printf("Init done.\n");

    return error_free;
}


/***************************************************************************/
/* OnAddPatient                                                             */
/***************************************************************************/
static errorType OnAddTask(void* DS, const char* const command) {
    int taskID;
    int priority;
    ValidateRead( sscanf(command, "%d %d",&taskID,&priority), 2, "AddTask failed.\n" );
    StatusType res = AddTask(DS, taskID, priority);

    printf("AddTask %d %d : %s\n",taskID, priority, ReturnValToStr(res));

    return error_free;
}


/***************************************************************************/
/* OnRemoveTeam                                                          */
/***************************************************************************/
static errorType OnNextTask(void* DS, const char* const command) {
    int taskID;
    int priority;
    StatusType res = NextTask(DS, &taskID, &priority);

    if (res != SUCCESS){
        printf("NextTask %s\n", ReturnValToStr(res));
    }
    else{
        printf("NextTask %s : %d %d\n", ReturnValToStr(res), taskID, priority);
    }

    return error_free;
}


/***************************************************************************/
/* OnAddPointsToTeam                                                       */
/***************************************************************************/
static errorType OnSetPriority(void* DS, const char* const command) {
    int taskID;
    int priority;
    ValidateRead( sscanf(command, "%d %d",&taskID,&priority), 2, "SetPriority failed.\n" );
    StatusType res = SetPriority(DS, taskID, priority);

    printf("SetPriority %d %d : %s\n", taskID, priority, ReturnValToStr(res));

    return error_free;
}


/***************************************************************************/
/* OnGetTeamPoints                                                         */
/***************************************************************************/
static errorType OnCancel(void* DS, const char* const command) {
    int taskID;
    ValidateRead( sscanf(command, "%d",&taskID), 1, "Cancel failed.\n" );
    StatusType res = Cancel(DS, taskID);

    printf("Cancel %d : %s\n", taskID, ReturnValToStr(res));

    return error_free;
}


/***************************************************************************/
/* OnMedianPoints                                                          */
/***************************************************************************/
static errorType OnLastTask(void* DS, const char* const command) {
    int taskID;
    int priority;
    StatusType res = LastTask(DS, &taskID, &priority);

    if (res != SUCCESS){
        printf("LastTask %s\n", ReturnValToStr(res));
    }
    else{
        printf("LastTask %s : %d %d\n", ReturnValToStr(res), taskID, priority);
    }

    return error_free;
}


/***************************************************************************/
/* OnMaximumPoints                                                         */
/***************************************************************************/
static errorType OnGetKthTask(void* DS, const char* const command) {
    int taskID;
    int priority;
    int k;
    ValidateRead( sscanf(command, "%d",&k), 1, "GetKthTask failed.\n" );
    StatusType res = GetKthTask(DS, k, &taskID, &priority);

    if (res != SUCCESS){
        printf("GetKthTask %s\n", ReturnValToStr(res));
    }
    else{
        printf("GetKthTask %s : The Task in place %d is %d %d\n", 
                ReturnValToStr(res), k, taskID, priority);
    }

    return error_free;
}


/***************************************************************************/
/* OnQuit                                                                  */
/***************************************************************************/
static errorType OnQuit(void** DS, const char* const command) {
    Quit(DS);
    if( *DS != NULL ) {
        printf("Quit failed.\n");
        return(error);
    };
    isInit = false;
    printf("Quit done.\n");

    return error_free;
}




#ifdef __cplusplus
}
#endif


