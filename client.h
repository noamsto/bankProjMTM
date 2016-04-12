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
    char* name;
    char* surname;
    clientID cID[CLIENTIDL];
    branchID brID;
    accountNum accNum;
    int maxOverdraft;
    int balance;
    int debt;
    int investment;
    
}client;




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
