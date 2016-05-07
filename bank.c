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
void createBank(){
	masterBank=ALLOC(bank, 1);
	initBank(masterBank);
	getName(&(masterBank->name), BANKNAMEMAX, "please enter bank name:\n");
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




/*find Client With max balance*/

client *findMaxACC(client *root){
    if (!root)
        return NULL;
    if (!root->right)
        return root;
    
    return findMaxACC(root->right);
}

/*find Client With min balance*/

client *findMinACC(client *root){
    if (!root)
        return NULL;
    if (!root->left)
        return root;
    
    return findMaxACC(root->left);
}

/*swap 2 clients nodes*/
void swapClients(client **client1, client**client2){
    client tempclient;
    tempclient=**client1;
    *client1=*client2;
    **client2=tempclient;
}






/*delete a client from the bank **new**.*/

client * deleteBankCLient(client *root, accountNum acc){
    client *findClient= NULL, *swapClient=NULL,  *parent=NULL;
    
    if (!root)
        return NULL;
        
    findClient=getClient(root,acc, &parent);
    
    if (!findClient){
        printf("client to be deleted not found\n");
        return NULL;
    }
        
    if (findClient->left){
        swapClient=findMaxACC(findClient->left);
        swapClients(&findClient,&swapClient);
        findClient->left=deleteBankCLient(findClient->left, acc);
        return findClient;
    }else if (findClient->right){
        swapClient=findMinACC(findClient->right);
        swapClients(&findClient,&swapClient);
        findClient->right=deleteBankCLient(findClient->right, acc);
        return findClient;
    }
    
    
    updateBankBalance(findClient->balance, REMOVE);
    updateNumOfBankClients(REMOVE);
    
    if (parent->left==findClient)
        parent->left=NULL;
    else
        parent->right=NULL;
    
    
    FREE(findClient->name);
    FREE(findClient->surname);
    FREE(findClient);
    
    return root;
}
 
 
 
 
 
 
 
 
 
 
/*delete a client from the bank.*/
try deleteBankClient(accountNum acc){
	client *clientToBeDeleted=NULL;

	/*find bank client;*/
		clientToBeDeleted=getBankClient(acc);

	if (clientToBeDeleted==NULL) {
		return CLIENTNOTFOUND;
	}


	/*update bank balance / client size*/
	updateBankBalance(clientToBeDeleted->balance, REMOVE);
	updateNumOfBankClients(REMOVE);

	FREE(clientToBeDeleted->name);
	FREE(clientToBeDeleted->surname);
	FREE(clientToBeDeleted);
	return SUCCESS;
}

/*add a new client to the bank.*/
void addNewClientToBank(client* createdClient){
	client  *newClient=NULL;

	newClient=ALLOC(client,1);

	*newClient=*createdClient;

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

/*
print the number of richest client and the bigget balance
void clientNumberOfBank_print(){
	int counter;
	amount maxBalance=0;
	the recursive calculation of the number of richest client and the biggest balance
	counter = clientNumberOfBank_REC(CLIENTSHEAD(masterBank),&maxBalance);
	printf("Recursive check:\n");
	printf("There %s: %d clients with max Balance of: %g\n", counter==1? "is":"are" , counter,  maxBalance);

	the Iterative calculation of the number of richest client and the biggest balance
	printf("Iterative check:\n");
	counter = clientNumberOfBank(&maxBalance);
	printf("There %s: %d clients with max Balance of: %g\n", counter==1? "is":"are" , counter,  maxBalance);
}
*/

/* check Recursively which are the client/s with biggest balance and return their number and
 * biggest balance.
 */
/******need testsss *******/
/*int clientNumberOfBank_REC(client *head, amount *biggestBalance){
	int counter=0;
	amount maxBalance=0;

	if (head==CLIENTSTAIL(masterBank)){
		*biggestBalance=0;
		return 0;
	}

	counter= clientNumberOfBank_REC(head->next,&maxBalance);

	if (head->balance==maxBalance){
		counter+=1;
	}else if(head->balance>maxBalance){
		counter=1;
		maxBalance=head->balance;
	}
	*biggestBalance=maxBalance;
	return counter;

}*/


/* check which are the client/s with biggest balance and return their number and
 * biggest balance.
 */
/*int clientNumberOfBank(amount *biggestBalance){
	client* current=CLIENTSHEAD(masterBank);
	int counter=0;
	*biggestBalance=0;

	while (current!=CLIENTSTAIL(masterBank)){
		if(*biggestBalance==current->balance){
			counter++;
		}else if(*biggestBalance<current->balance ){
			counter=1;
			*biggestBalance=current->balance;
		}
			current=current->next;
	}
	return counter;

}*/

/*********_Information_Functions_END_******************/


client * getBankClientRoot (){
	return CLIENTSROOT(masterBank);
}

/* Delete the bank*/
void deleteBank(){
	deleteAllBranches();
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
