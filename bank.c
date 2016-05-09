/* bank project
 Yahel Tsufim 304952898
 Noam Stolero 201581683
 file:bank.c
 */

#include "bank.h"

void initBank(bank*);

#define CLIENTSROOT(STRUCT) STRUCT->root

int clientNumberOfBank_REC(client *head, amount *biggestBalance);
int clientNumberOfBank();

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
    if (name==NULL){
        getName(&(masterBank->name), BANKNAMEMAX, "please enter bank name:\n");
        return;
    }
    masterBank->name=name;
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
    client** bankRoot;
    
    bankRoot=getBankClientRoot();
  
    updateBankBalance(deleteC->balance, REMOVE);
    updateNumOfBankClients(REMOVE);

    *bankRoot=deleteClientFromTree(*bankRoot, deleteC->accNum);
    
}

/*add a new client to the bank.*/
void addNewClientToBank(client* createdClient){
	client  *newClient=NULL;

	newClient=ALLOC(client,1);

	*newClient=*createdClient;
    newClient->name=str_dup(createdClient->name);
    newClient->surname=str_dup(createdClient->name);

    
	CLIENTSROOT(masterBank)=insertClientTree(CLIENTSROOT(masterBank), newClient);

	masterBank->numOfClients++;
}

/*********_Update_bank_Fields_END_******************/

/*return number clients of bank.*/
int BankNumberOfClients(){
	return masterBank->numOfClients;
}


/*get client in bank Client list.*/
client* getBankClient(accountNum acc){
	client* getCl=NULL;
    getCl= getClient(CLIENTSROOT(masterBank), acc, NOCHECK);
	return getCl;
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


client ** getBankClientRoot (){
	return &(CLIENTSROOT(masterBank));
}

/* Delete the bank*/
void deleteBank(){
	deleteAllBranches();
    clearClientTree(masterBank->root);
	FREE(masterBank->name);
	FREE(masterBank);
}

/*return the bank name*/
char* getBankName(){
	return masterBank->name;
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
