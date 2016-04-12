/* bank project
 Yahel Tsufim 304952898
 Noam Stolero 201581683
 file:bank.c
 */

#include "bank.h"

void initBank(bank*);


/*********_Bank_Creation_Functions_START_******************/


/* The bank instance, will be used only in this file*/
bank* masterBank=NULL;


/*initalise bank struct.*/
void initBank(bank* masterBank){
    masterBank->balance=0;
    masterBank->numOfActiveLoans=0;
    masterBank->numOfBranch=0;
    masterBank->numOfClients=0;
    masterBank->yearProfit=0;
}


/*create a single bank struct.*/
void createBank(){
    masterBank=ALLOC(bank, 1);
    initBank(masterBank);
    masterBank->clientListHead=createBankClientList();
    getName(&(masterBank->name), BANKNAMEMAX, "please enter bank name:\n");
}


/*create and init client list*/
void createBankClientList()
{
    int i=0;
    client* tempHead=NULL, tempTail=NULL;
    tempHead=ALLOC(client,1);
    tempHead->next=NULL;

    tempTail=ALLOC(client,1);
    tempTail->next=NULL;

    masterBank->clientsList->head=tempHead;
    masterBank->clientsList->tail=tempTail;

    return;
}

/*********_Bank_Creation_Functions_END_******************/



/*********_Update_bank_Fields_START_******************/


/*update bank balance.*/
void updateBankBalance(amount money,addremove remove){
    if (remove) {
        if (masterBank->balance<=0){
            printf("no balance");
            return;
        }
        masterBank->balance-=money;
    }
    masterBank->balance+=money;
}

/*update number of active loans.*/
void updateNumOfActiveLoans(addremove remove){
    if (remove) {
        if (masterBank->numOfActiveLoans<=0) {
            printf("no active loans");
            return;
        }
        masterBank->numOfActiveLoans--;
    }
    masterBank->numOfActiveLoans++;
}



/*update number of branches.*/
void updateNumOfBranches(addremove remove){
    if (remove){
        if (masterBank->numOfBranch<=0) {
            printf("no branches\n");
            return;
        }
        masterBank->numOfBranch--;
    }
    masterBank->numOfBranch++;
}

/*update number of clients of the bank.*/
void updateNumOfBankClients(addremove REMOVE){
    masterBank->numOfClients++;
}


/*delete a client from the bank.*/
try deleteBankClient(accountNum acc){
    client *getPreClient=NULL, *getNextClient=NULL,
    		*clientToBeDeleted=NULL;
    /*find bank client;*/
    getPreClient=getBankClient(acc, &getNextClient);
    if (getPreClient==NULL && getNextClient==NULL) {
        return CLIENTNOTFOUND;
    }
    clientToBeDeleted=getPreClient->next;

    /*update bank balance / client size*/
    updateBankBalance(getPreClient->next->balance, REMOVE);
    updateNumOfBankClients(REMOVE);
    
    /*delete the Client*/
    
    
    return SUCCESS;
}

/*add a new client to the bank.*/
void addNewClientToBank(client* newClient){
    client *tempNext=NULL;
    if (masterBank->clientListHead->next!=NULL)
    	tempNext=masterBank->clientListHead->next->next;
    masterBank->clientListHead->next=newClient;
    newClient->next=tempNext;

    masterBank->numOfClients++;
}

/*********_Update_bank_Fields_END_******************/


/*return number clients of bank.*/
int clientNumberOfBank(){
    return masterBank->numOfClients;
}



/*find a client in bank Client list.*/
client* getBankClient(accountNum acc){
    int i=0;
    
    for (i=0; i<masterBank->numOfClients; i++)
    {
        if (masterBank->bankClients[i].accNum==acc ) {
            return &(masterBank->bankClients[i]);
        }
    }
    return NULL;
}

/*********_Information_Functions_START_******************/

/*return current number of branches.*/
int getNumOfBranches(){
    return masterBank->numOfBranch;
}


/*check if bank is full.*/
int isBankFull(){
    if (masterBank->numOfClients<=MAXBANKCLIENTS) {
        return FALSE;
    }
    return TRUE;
}

/*********_Information_Functions_END_******************/

/* Delete the bank*/
void deleteBank(){
    deleteAllBranches();
    FREE(masterBank->bankClients);
    FREE(masterBank);
}
