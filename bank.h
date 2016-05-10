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
    
    char* name;					/*name of bank*/
    int numOfBranch;			/*number of branches in bank*/
    int numOfClients;			/*number of clients registered to bank*/
    int numOfActiveLoans;		/*number of loans currently activated in bank*/
    double balance;				/*balance of bank*/
    double yearProfit;			/*the yearly profit of the bank*/
    
    client* root;			/*list of all the clients registered to bank*/
}bank;



client ** getBankClientRoot ();



/*create and init M size client list. */
void createBankClientList();


/*find a client in bankClient List.*/
client *getBankClient(accountNum);

/*update the bank balance.*/
void updateBankBalance(amount ,addremove);


/*update number of branches.*/
void updateNumOfBranches(addremove remove);


/*return current amount of branches.*/
int getNumOfBranches();

/*delete a client from the bank.*/
void deleteBankClient(client* );

/*update the number of active loans.*/
void updateNumOfActiveLoans(addremove remove);

/*create a single bank.*/
void createBank();

/*add a new client to the bank.*/
void addNewClientToBank(client* );

/*check if bank is full.*/
int isBankFull();

/*delete the bank anll all of his database*/
void deleteBank();

/*get bank name*/
char* getBankName();

/*print all of the bank info*/
void printBankInfo();

/*return the number of clients in bank*/
int clientNumberOfBank();

#endif /* bank_h */




