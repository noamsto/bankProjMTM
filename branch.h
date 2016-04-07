/* bank project
 Yahel Tsufim 304952898
 Noam Stolero 201581683
 file:branch.h
 */

#ifndef branch_h
#define branch_h
#define NOID 0
#include "client.h"

typedef struct branches{
    branchID brID;
    char name[MAXNAME];
    int currentClients;
    int numOfActiveLoans;
    int closeTime;
    int openTime;
    int balance;
    int yearProfit;
    client *branchClients;
    
}branch;



branch* createBranchList();
/*create and init branch array of 'N' size */

try addNewBranch();
/*add new branch to list*/

client* createBranchClientList();
/*create and init 'L' size client list. returns client list pointer*/

try addNewClientToBranch();
/*add client to branch. receive data from user*/

int clientNumberWithGivenBalance();
/*get branch ID and balance from user. returns amount of clients with higher balance*/

try deleteAllBranchClients(branchID);
/*delete all clients of a certain branch. returns whether the action succeeded*/

try deleteBranchClient(branchID, accountNum);
/*delete the information of a client in branch. return feedback of success*/

try deleteBranch(branchID);
/*receive branch ID from user and delete the branch*/

void deleteAllBranches();
/*delete all branches of bank*/

try updateBranchBalance(branchID, amount,addremove);
/*update the balance of a certain branch. enter branch ID the amount needed and whether add or remove the amount*/

void updateBranchLoan(branchID, addremove);
/*update amount of loans from branch*/

branch* getBranch(branchID);
/*enter branch ID and receive pointer to the wanted branch*/

client *getBranchClient(accountNum,branchID);
/* send client account and branch ID and receive client pointer if exist*/


boolean checkBranchID(branchID brID);
/*check if branch ID is used*/

#endif /* branch_h */
