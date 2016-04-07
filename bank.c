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
    masterBank->bankClients=NULL;
    masterBank->numOfActiveLoans=0;
    masterBank->numOfBranch=0;
    masterBank->numOfClients=0;
    masterBank->yearProfit=0;
}


/*create a single bank struct.*/
void createBank(){
    masterBank=ALLOC(bank, 1);
    initBank(masterBank);
    getName(masterBank->name, BANKNAMEMAX, "please enter bank name:\n");
}


/*create and init M size client list*/
client* createBankClientList()
{
    int i=0;
    client* tempBankClientList=NULL;
    
    tempBankClientList=ALLOC(client, MAXBANKCLIENTS);
    
    for(i=0; i<MAXBANKCLIENTS; i++)
    {
        initClient(&tempBankClientList[i]);
    }
    
    /*assign the client list to the bank struct pointer.*/
    masterBank->bankClients=tempBankClientList;
    return tempBankClientList;
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
    client *getClient=NULL;
    
    /*find bank client;*/
    getClient=getBankClient(acc);
    if (!getClient) {
        return CLIENTNOTFOUND;
    }
    
    /*update bank balance / client size*/
    updateBankBalance(getClient->balance, REMOVE);
    updateNumOfBankClients(REMOVE);
    
    /*ovverride deleted client with last client;*/
    *getClient=masterBank->bankClients[masterBank->numOfClients];
    
    
    return SUCCESS;
}

/*add a new client to the bank.*/
void addNewClientToBank(client* newClient){
    masterBank->bankClients[masterBank->numOfClients]=*newClient;
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