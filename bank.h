/* bank project
 Yahel Tsufim 304952898
 Noam Stolero 201581683
 file:bank.h
 */


#ifndef bank_h
#define bank_h

#include "branch.h"

#define BANKNAMEMAX 10
#define MAXBANKCLIENTS 1e4

typedef struct banks{
    
    char* name;
    int numOfBranch;
    int numOfClients;
    int numOfActiveLoans;
    double balance;
    double yearProfit;
    
    clientsLinkedList clientsList;
}bank;




/*create and init M size client list. */
void createBankClientList();


/*return bank amount of clients.*/
int BankNumberOfClients();


/*find a client in bankClient List.*/
client *getBankClient(accountNum,client**);

/*update the bank balance.*/
void updateBankBalance(amount ,addremove);


/*update number of branches.*/
void updateNumOfBranches(addremove remove);


/*return current amount of branches.*/
int getNumOfBranches();

/*delete a client from the bank.*/
try deleteBankClient(accountNum );

/*update the number of active loans.*/
void updateNumOfActiveLoans(addremove remove);

/*create a single bank.*/
void createBank();

/*add a new client to the bank.*/
void addNewClientToBank(client* );

/*check if bank is full.*/
int isBankFull();

void deleteBank();

#endif /* bank_h */




