/* bank project
 Yahel Tsufim 304952898
 Noam Stolero 201581683
 file:client.c
 */

#include "bank.h"




/*get the transaction info from user, accoun number and amount of money.*/
void getTransactionInfo(accountNum* acc,amount* money);

/*update client debt.*/
void updateClientDebt(accountNum acc, amount money, addremove add);





/*get the transaction info from user, accoun number and amount of money.*/
void getTransactionInfo(accountNum* acc,amount* money){
    
    *acc=getAcc(EXIST);

    getInt(money,"Please enter amount:\n");
    while (*money<=0) {
        printf("Error: amount cant be negative.\n");
        getInt(money,"Please enter amount:\n");
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
}


/*delete client from system.*/
void deleteClient(accountNum acc){
    try echo;
    client *deleteC=NULL;
    
    
    printf("client deletion:\n");
    
    if (!acc) {
        /*get client acc from user*/
        acc=getAcc(EXIST);
    }
    deleteC=getBankClient(acc,GETSPECIFIC);
    
    /*delete client from branch*/
    echo=deleteBranchClient(deleteC->brID,acc);
    if (echo==CLIENTNOTFOUND) {
        printf("client not in any branch\n");
    }
    
    /*delete client from bank*/
    echo=deleteBankClient(acc);
    if (echo==CLIENTNOTFOUND) {
        printf("client not found in system.\n");
    }
}


/*update client balance*/
try updateClientBalance(accountNum acc,amount money,addremove remove){
    client* getClient=NULL;
    
    
    /*find client in bank*/
    getClient=getBankClient(acc,GETSPECIFIC);
    if (!getClient) {
        return CLIENTNOTFOUND;
    }else{
        if (remove) {   /*add or remove money to his balance*/
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
    getClient=getBranchClient(acc, getClient->brID,GETSPECIFIC);
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
    printf("deposit finished succssefuly.\n");
    return SUCCESS;
}



/*update client debt.*/
void updateClientDebt(accountNum acc, amount money, addremove add){
    client* getClient=NULL;
    
    
    getClient=getBankClient(acc,GETSPECIFIC);
    getClient->debt+=money;
    
    getClient=getBranchClient(acc,getClient->brID,GETSPECIFIC);
    if (getClient)
        getClient->debt+=money;
}

/*loan money to client.*/
try loanToClient() {
    accountNum acc=0;
    amount money=0;
    try echo;
    
    printf("starting a loan:\n");
    getTransactionInfo(&acc, &money);   /*get the transaction info.*/
    
    echo=updateClientBalance(acc, money, ADD);  /*update client/bank/branch balance*/
    if (echo==CLIENTNOTFOUND) { /*if client is not found print error.*/
        printf("error: client not present in system.\n");
        return FAIL;
    }
    /*update the client data.*/
    updateClientDebt(acc,money, ADD);
    updateBranchLoan(acc,ADD);
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
        
        if(getBankClient(acc,GETSPECIFIC)){
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

void printClientInfo()
{
	accountNum accNumber;
	client *tempClient,*branchClient;
	accNumber = getAcc(EXIST);
	tempClient = getBankClient(accNumber,NOCHECK);
	branchClient = getBranchClient(tempClient->accNum,tempClient->brID,NOCHECK);
	printf("Client name: %s  %s\n",tempClient->name,tempClient->surname);
	printf("Client Bank name: %s\n",tempClient->bankName);
	printf("Client branch ID : %d\n",tempClient->brID);
	printf("Client account number: %d\n",tempClient->accNum);
	printf("Client ID: %s\n",tempClient->cID);
	printf("client balance: %d\n",tempClient->investment);
	printf("Client debt: %d\n",tempClient->debt);
	printf("Client's max overdraft: %d\n",tempClient->maxOverdraft);
	printf("It takes two to lie:\n one to lie and one to listen\n\n");
	printf("Client name: %s  %s\n",branchClient->name,tempClient->surname);
		printf("Client Bank name: %s\n",branchClient->bankName);
		printf("Client branch ID : %d\n",branchClient->brID);
		printf("Client account number: %d\n",branchClient->accNum);
		printf("Client ID: %s\n",branchClient->cID);
		printf("client balance: %d\n",branchClient->investment);
		printf("Client debt: %d\n",branchClient->debt);
		printf("Client's max overdraft: %d\n",branchClient->maxOverdraft);
		printf("It takes two to lie:\n one to lie and one to listen\n");
}

