/* bank project
 Yahel Tsufim 304952898
 Noam Stolero 201581683
 file:bank.c
 */

#include "bank.h"

/*init a single bank struct*/
void initBank(bank*);

/* bank client root macro */
#define CLIENTSROOT(STRUCT) STRUCT->root


/*********_Bank_Creation_Functions_START_******************/


/* The bank instance, will be used only in this file*/
static bank* masterBank=NULL;


/*Initialize bank struct.*/
void initBank(bank* masterBank){
	masterBank->balance=0;
	masterBank->numOfActiveLoans=0;
	masterBank->numOfBranch=0;
	masterBank->numOfClients=0;
	masterBank->yearProfit=0;
	CLIENTSROOT(masterBank)=NULL;
}


/*create a single bank struct.*/
void createBank(char* name){
	masterBank=ALLOC(bank, 1);
	initBank(masterBank);

#ifndef TEST /* if its not a test, request for bank name*/
    if (name==NULL){
        getName(&(masterBank->name), BANKNAMEMAX, "please enter bank name:\n");
        return;
    }else
        masterBank->name=name;
#else
    masterBank->name=str_dup(testName); /* give a default name, test purpose */
    testName[0]+=1; /* change letter for test name */
#endif
}
/*********_Bank_Creation_Functions_END_******************/



/*********_Update_bank_Fields_START_******************/

/*update bank balance.*/
void updateBankBalance(amount money,addremove remove){
	if (remove) {
		if (masterBank->balance<=0 && money>0){
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
	}else
		masterBank->numOfBranch++;
}

/*update number of clients of the bank.*/
void updateNumOfBankClients(addremove remove){
	if (remove==REMOVE){
		masterBank->numOfClients--;
	}else{
		masterBank->numOfClients++;
	}
}
 
 
/*delete a client from the bank.*/
void deleteBankClient(client * deleteC) {
    genTree** bankRoot;
    
    bankRoot=getBankClientRoot();
  
    updateBankBalance(deleteC->balance, REMOVE);

    *bankRoot=deleteClientFromTree(*bankRoot, deleteC->accNum);
    updateNumOfBankClients(REMOVE);

}

/*add a new client to the bank.*/
void addNewClientToBank(client* createdClient){
	client  *newClient=NULL;

	newClient=ALLOC(client,1);

	*newClient=*createdClient; /*copy client fields */
    /* copy Name fields, deep copying */
    newClient->name=str_dup(createdClient->name);
    newClient->surname=str_dup(createdClient->name);

    /* insert the client to the bank clients tree */
	CLIENTSROOT(masterBank)=insertClientTree(CLIENTSROOT(masterBank), newClient);

	masterBank->numOfClients++;
}

/*********_Update_bank_Fields_END_******************/



/*********_Information_Functions_START_******************/



/*return number clients of bank.*/
int clientNumberOfBank(){
    return masterBank->numOfClients;
}


/*get client in bank Client list.*/
client* getBankClient(accountNum acc){
    client* getCl=NULL;
    getCl= getClient(CLIENTSROOT(masterBank), acc, NOCHECK);
    return getCl;
}


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

/*return the bank name*/
char* getBankName(){
    return masterBank->name;
}

/* return the bank clients tree */
genTree ** getBankClientRoot (){
    return &(CLIENTSROOT(masterBank));
}


/*********_Information_Functions_END_******************/




/* Delete the bank*/
void deleteBank(){
	deleteAllBranches(); /* delete all branches first */
    free_list(&CLIENTSROOT(masterBank), (genDelete)&freeClient);    /*delete client list */
	FREE(masterBank->name);
	FREE(masterBank);
}

/*print all of the bank information and status.*/
void printBankInfo()
{
	printf("Bank name: %s\n",masterBank->name);
	printf("Bank amount of branches: %d\n",masterBank->numOfBranch);
	printf("Number of clients: %d\n",masterBank->numOfClients);
	printf("Number of loans: %d\n",masterBank->numOfActiveLoans);
	printf("Bank balance: %g\n",masterBank->balance);
	printf("Yearly profit: %g\n",masterBank->yearProfit);
}
