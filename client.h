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
    int balance;				/*client's balance*/
    int debt;					/*client's debt to bank/branch*/
    int investment;				/*client's investment*/
    
    struct clients *next;
}client;


typedef struct linkedList{
	client *head;
	client *tail;
}clientsLinkedList;

/*init client struct*/
void initClient(client*);

/*delete client from system.*/
void deleteClient(accountNum);

/*update the client balance.*/
try updateClientBalance(accountNum,amount,addremove);

/*make a deposit transaction, update all that neccssary.*/
try depositeMoneyToClientAccount();

/*make a loan transaction, update all that neccssary.*/
try loanToClient();

/*Get account number from user, check if exist or not.*/
accountNum getAcc(availble);


#endif /* client_h */
