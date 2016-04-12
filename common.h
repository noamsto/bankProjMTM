/* bank project
 Yahel Tsufim 304952898
 Noam Stolero 201581683
 file:common.h
 */
#ifndef common_h
#define common_h

#include "matam.h"


#define NOCHECK 0
#define CLIENTIDL 9


typedef enum{ADD,REMOVE}addremove;
typedef enum{FALSE,TRUE}boolean;
typedef enum{NOTEXIST,EXIST}availble;   

typedef enum ret_val{SUCCESS, FAIL, ALOC_FAIL, MAX_BRANCH_REACHED, MAX_BANK_REACHED,NO_BALANCE, CLIENTNOTFOUND, BRANCHNOTFOUND} try;

typedef enum{deposit,loan,leaveBranch} transType;

typedef int branchID, amount, accountNum;
typedef char clientID;

void getName(char** , int, char*);
/*get string from user, check for legibility comparing to length of word*/

void getInt(int* num,char* output);
/*get string from user, check for legibility comparing to length of size*/

void getClientID(clientID *);

#endif /* common_h */


