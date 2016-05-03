/* bank project
 Yahel Tsufim 304952898
 Noam Stolero 201581683
 file:client.c
 */

#include "bank.h"
#define GETBRID(ACC) getBankClient(ACC )->brID


/*get the transaction info from user, accoun number and amount of money.*/
void getTransactionInfo(accountNum* acc,amount* money);

/*update client debt.*/
try updateClientDebt(accountNum acc, amount money, addremove add);



client * insertClientTree(client* root, client* newClient){

	if (!root){
		return newClient;
	}

	if (root->accNum> newClient->accNum){
		root->left = insertClientTree(root->left, newClient);
	}else{
		root->right=insertClientTree(root->right,newClient);
	}
	return root;
}

/*get the transaction info from user, accoun number and amount of money.*/
void getTransactionInfo(accountNum* acc,amount* money){

	*acc=getAcc(EXIST);

	getDouble(money,"Please enter amount:\n");
	while (*money<=0) {
		printf("Error: amount cant be negative.\n");
		getDouble(money,"Please enter amount:\n");
	}

}



/*init client struct*/
void initClient(client* c)
{
	c->brID=0;
	c->balance=0;
	c->debt=0;
	c->investment=0;
	c->maxOverdraft=0;
	c->accNum=0;
	c->next=NULL;
	c->left=NULL;
	c->right=NULL;
}

/*get information from user about new client.*/
client* getDetailsFromUser(branchID brID,char* bankName){
	client* newClient;
	newClient = ALLOC(client,1);
	initClient(newClient);
	getName(&(newClient->name), MAXNAME, "please enter client name:\n");
	getName(&(newClient->surname), MAXNAME, "please enter client surname:\n");
	newClient->bankName = bankName;
	getClientID(newClient->cID);
	newClient->accNum=getAcc(NOTEXIST);
	newClient->brID=brID;
	return newClient;
}

/*delete client from system.*/
try deleteClient(accountNum acc){
	try echo;
	client *deleteC=NULL;

	if (!acc) {
		/*get client acc from user*/
		acc=getAcc(EXIST);
	}
	deleteC=getBankClient(acc);

	/*delete client from branch*/
	echo=deleteBranchClient(deleteC->brID,acc);
	if (echo==CLIENTNOTFOUND) {
		printf("client not in any branch\n");
	}

	/*delete client from bank*/
	echo=deleteBankClient(acc);
	if (echo==CLIENTNOTFOUND) {
		printf("client not found in system.\n");
		return FAIL;
	}
	return SUCCESS;
}



/*******************************************************NEW***********/

void	printClientsLinkedList(client *clients){
	if (clients==NULL){
		return;
	}
	printClientsLinkedList(clients->next);
	clients->next=NULL;
	printClientInfo(clients);
}

/*******************************************************NEW***********/
void	findClientAcc(client *root, accountNum acc, client **foundClients){
	if (root==NULL)
		return;

	findClientID(root->left, acc, foundClients);
	if (root->accNum==acc){
		root->next=*foundClients;
		*foundClients=root;
	}
	findClientID(root->right, acc,foundClients);
	return;
}
/*******************************************************NEW***********/
void findClientID(client *root, clientID id, client **foundClients){
	if (root==NULL)
		return;

	findClientID(root->left, id, foundClients);
	if (root->cID==id){
		root->next=*foundClients;
		*foundClients=root;
	}
	findClientID(root->right, id ,foundClients);
	return;
}


/*******************************************************NEW***********/
void findClient (){
	char c;
	client* clients=NULL, * root=NULL;
	clientID id; accountNum acc;
	boolean finish=FALSE;
	//root=getBankClientRoot();

	while (finish!=TRUE){
		printf("Find Client by:\n"
				"1. ID\n"
				"2.Account Number\n");

		c=getchar();
		getchar();

		switch (c) {
		case 1:
			getClientID(&id);
			//clients=findClientsID(root, id, &clients);
			break;
		case 2:
			getInt(&acc,"Please Enter Account Number:\n");
			//clients=findClientsAcc(root,acc, &clients);
			break;
		default:
			printf("the number is not in the menu.\n try again\n");
			break;
		}
	}

	if (clients==NULL){
		printf("No clients found\n");
		return ;
	}
	printClientsLinkedList(clients);

}



client* getClient(client* root, accountNum acc){

	if (root==NULL){
		return NULL;
	}

	if (root->accNum>acc)
		return getClient(root->left, acc);

	if (root->accNum<acc)
		return getClient(root->right,acc);

	return root;
}


/*update client balance*/
try updateClientBalance(accountNum acc,amount money,addremove remove){
	client* getClient=NULL;


	/*find client in bank*/
	getClient=getBankClient(acc);
	if (!getClient) {
		return CLIENTNOTFOUND;
	}else{
		if (remove==REMOVE) {   /*add or remove money to his balance*/
			getClient->balance-=money;
		}else{
			getClient->balance+=money;
		}
		updateBankBalance(money, remove);   /*update bank balance*/
	}

	if (getClient->brID==0) {
		return SUCCESS;
	}

	/*find client in branch*/
	getClient=getBranchClient(acc, getClient->brID);
	if (!getClient) {
		printf("Client not belong in any branch\n");
	}else{
		if (remove) {   /*add or remove money to his balance*/
			getClient->balance-=money;
		}else{
			getClient->balance+=money;
		}
		updateBranchBalance(getClient->brID, money,remove); /*update branch balance*/
	}

	return SUCCESS;
}



/*deposit money to client*/
try depositeMoneyToClientAccount() {
	accountNum acc=0;
	amount money=0;
	try echo;

	printf("starting a deposit:\n");
	getTransactionInfo(&acc, &money);   /*get the transaction info.*/

	/*update client/bank/branch balance*/
	echo=updateClientBalance(acc, money, ADD);
	if (echo==CLIENTNOTFOUND) {
		printf("error: client not present in system.\n");
		return FAIL;
	}
	else
		printf("deposit finished succssefuly.\n");
	return SUCCESS;
}



/*update client debt.*/
try  updateClientDebt(accountNum acc, amount money, addremove  remove){

	client* getClient=NULL;
	/*find client in bank*/
	getClient=getBankClient(acc);
	if (!getClient) {
		return CLIENTNOTFOUND;
	}else{
		if (remove==REMOVE) {   /*add or remove money to his balance*/
			getClient->debt-=money;
		}else{
			getClient->debt+=money;
		}
		updateBankBalance(money, remove);   /*update bank balance*/
	}
	if (getClient->brID==0) {
		return SUCCESS;
	}
	/*find client in branch*/
	getClient=getBranchClient(acc, getClient->brID);
	if (!getClient) {
		printf("Client not belong in any branch\n");
	}else{
		if (remove) {   /*add or remove money to his balance*/
			getClient->debt-=money;
		}else{
			getClient->debt+=money;
		}
		updateBranchBalance(getClient->brID, money,remove); /*update branch balance*/
	}

	return SUCCESS;

}

/*loan money to client.*/
try loanToClient() {
	accountNum acc=0;
	amount money=0;
	try echo;

	printf("starting a loan:\n");
	getTransactionInfo(&acc, &money);   /*get the transaction info.*/

	echo=updateClientDebt(acc, money, ADD);  /*update client/bank/branch balance*/
	if (echo==CLIENTNOTFOUND) { /*if client is not found print error.*/
		printf("error: client not present in system.\n");
		return FAIL;
	}
	/*update the client data.*/
	updateBranchLoan(GETBRID(acc),ADD);
	updateNumOfActiveLoans(ADD);

	printf("loan finished succssefuly.\n");
	return SUCCESS;
}

/*Get account number from user*/

accountNum getAcc(availble checkif){
	boolean flag=FALSE;
	accountNum acc=0;


	do{
		getInt(&acc,"please enter client account number\n");

		if(getBankClient(acc)){
			if(checkif==EXIST){
				flag = TRUE;
			}else{
				printf("The account number is in use.\n");
			}
		}else if (checkif==NOTEXIST){
			flag=TRUE;
		}else{
			printf("Account not found.\n");
		}
	}while(flag == FALSE); /* check if id exist or not*/

	return acc;


}

void printClientInfo(client* c)
{
	accountNum accNumber;
	client *tempClient;
	if (c==NULL){

		accNumber = getAcc(EXIST);
		tempClient = getBankClient(accNumber);
	}else
		tempClient=c;

	printf("Client name: %s  %s\n",tempClient->name,tempClient->surname);
	printf("Client Bank name: %s\n",tempClient->bankName);
	printf("Client branch ID : %d\n",tempClient->brID);
	printf("Client account number: %d\n",tempClient->accNum);
	printf("Client ID: %s\n",tempClient->cID);
	printf("client balance: %g\n",tempClient->balance);
	printf("Client debt: %g\n",tempClient->debt);
	printf("Client's max overdraft: %d\n",tempClient->maxOverdraft);
}

