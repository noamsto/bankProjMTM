/* bank project
 Yahel Tsufim 304952898
 Noam Stolero 201581683
 file:common.h
 */
#ifndef common_h
#define common_h

#include "matam.h"
#include <string.h>

#include "genericList.h"

/* define for test purposes */
/* #define TEST */



/* definitions for and typdefs used in the program */
#define NOCHECK 0
#define CLIENTIDL 10
#define GETSPECIFIC NULL
#define BANK_AHAMELIM
#define CANCEL 0

typedef enum{ADD,REMOVE}addremove;
typedef enum{FALSE,TRUE}boolean;
typedef enum{NOTEXIST,EXIST}availble;   

typedef enum ret_val{SUCCESS, FAIL, ALOC_FAIL, MAX_BRANCH_REACHED, MAX_BANK_REACHED,NO_BALANCE, CLIENTNOTFOUND, BRANCHNOTFOUND, CANCELED} try;

typedef enum{deposit,loan,leaveBranch} transType;

typedef int branchID , accountNum;
typedef double amount;
typedef char clientID;

/* end of definitons */

/*testing purpose*/
#ifdef TEST
static char testName[2]= "a\0";
static accountNum testAcc[7] ={5,2,6,3,4,8,9};
static int testIndex=0;
static clientID testID[10] = "123123121\0";
static branchID testBID = 1;
#endif
/*testing purpose*/


void getName(char** , int, char*);
/*get string from user, check for legibility comparing to length of word*/

void getInt(int* num,char* output);
/*get string from user, check for legibility comparing to length of size*/

void getDouble(double* num, char* output);
/*get string from user, check for legibility comparing to length of size*/

void getClientID(clientID *);
/* get clinet id from user */

#endif /* common_h */


