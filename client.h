/* bank project
 Yahel Tsufim 304952898
 Noam Stolero 201581683
 file:client.h
 */


#ifndef client_h
#define client_h

#include "common.h"

#define MAXNAME 20

typedef struct clients{
    char* name;					/*client's name*/
    char* surname;				/*client's family name*/
    char* bankName;				/*name of bank, client is registered to*/
    clientID cID[CLIENTIDL];	/*client's ID number*/
    branchID brID;				/*the ID number of the branch the client belongs to*/
    accountNum accNum;			/*the account number of the client*/
    int maxOverdraft;			/*the maximum overdraft allowed to the client*/
    amount balance;				/*client's balance*/
    amount debt;				/*client's debt to bank/branch*/
    int investment;				/*client's investment*/
    
}client;




/* find client function, recieve either ID or Balance from user and build linked list with all relevant client.*/
void findClient ();


/* insert client to tree */
genTree * insertClientTree(genTree* root, client* newClient);


/* get information from user about new client.*/
client* getDetailsFromUser(branchID ,char* );

/* find a client in a tree structure*/
client* getClient(genTree* root, accountNum acc, client**);


/* init client struct*/
void initClient(client* );

/* delete client from tree.*/
genTree * deleteClientFromTree(genTree *root, accountNum acc);

/* delete client from system.*/
try deleteClient(accountNum);

/* update the client balance.*/
try updateClientBalance(accountNum,amount,addremove);

/* make a deposit transaction, update all that necessary.*/
try depositeMoneyToClientAccount();

/* make a loan transaction, update all that necessary.*/
try loanToClient();

/* Get account number from user, check if exist or not.*/
accountNum getAcc(availble);


/* print client info (according to account number) to screen. get client account number from user*/
void printClientInfo();

/* comparison function for 2 client struct*/
comparison cmpClient(client* c1, client* c2);


/* free a client struct */
void freeClient(client *c);


#endif /* client_h */
