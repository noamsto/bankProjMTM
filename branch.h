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
    branchID brID;				/*the ID of the branch*/
    char* bankName;				/*the name of the bank the branch belongs to*/
    char* branchName;			/*the name of the branch*/
    int currentClients;			/*amount of clients currently registered to branch*/
    int numOfActiveLoans;		/*amount of loans currently activated in branch*/
    int closeTime;				/*closing hours of the branch*/
    int openTime;				/*opening hours of the branch*/
    double balance;				/*the branch's balance*/
    double yearProfit;			/*profit of current year in branch*/
    client* clientList;			/*list of all the clients registered to branch*/
    struct branches *left;		/*point to left leaf of branch tree list*/
    struct branches *right;		/*point to left leaf of branch tree list*/

}branch;



branch* createBranchList();
/*create branch list */

try addNewBranch();
/*create a new branch and add to list. get info from user*/

void createBranchClientList(clientsLinkedList*);
/*create list of clients to branch*/

try addNewClientToBranch();
/*create new client and add to client list belong to branch. get info from user*/

int clientNumberWithGivenBalance();
/*get branch ID and balance from user. returns amount of clients with higher balance*/

int clientNumberWithBiggerLoansThanBalance(client*);
/* print to screen amount of clients with debt higher then balance. receive branch ID from user */

int clientNumberWithBiggerLoansThanBalance_rec(client*);
/* print to screen amount of clients with debt higher then balance. receive branch ID from user. the function is done recursively */

void clientNumberWithBiggerLoansThanBalance_print();

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

branch* getBranch(branchID,branch**);
/*enter branch ID and receive pointer to the wanted branch*/

client *getBranchClient(accountNum,branchID,client**);
/* send client account and branch ID and receive client pointer if exist*/


boolean checkBranchID(branchID brID);
/*check if branch ID is used*/

void printBranchInfo();
/*print all the information on branch. receive the branch ID from the user*/

#endif /* branch_h */
