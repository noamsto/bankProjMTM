/* bank project
 Yahel Tsufim 304952898
 Noam Stolero 201581683
 file:client.c
 */

#include "bank.h"
#define GETBRID(ACC) getBankClient(ACC )->brID
#define ACTIONCANCELD printf("Action aborted\n")


/*get the transaction info from user, account number and amount of money.*/
try getTransactionInfo(accountNum* acc,amount* money);

/*update client debt.*/
try updateClientDebt(accountNum acc, amount money, addremove add);

/*function search the tree, compare either balance or id, and build client linked list */
genLinked* findClientGen (genTree *root, void* tocmpare , genCmp);

/* 2 generic compare functions . one for client id and one for balance;*/
int compareID(client* check, void* id);
int compareBal(client* check, void *bal);

/*print clients linked list*/
void printClientsLinkedList(genLinked *clients);

/*insert a client to a client linked list*/
void buildClientLinkedList(client *list, client* add);

/*swap 2 clients nodes*/
void swapClients(client *client1, client*client2);

/*free a single Clinet node*/
void freeClient(client *findClient);



/****************** Client Managment Functions START ********************/

/****************** compare Functions ***********************************/



comparison cmpClient(client* c1, client* c2){
    if (c1->accNum>c2->accNum)
        return GREATER;
    else if (c1->accNum<c2->accNum)
        return SMALLER;
    return EQUAL;
}

comparison cmpClientAccNum(client* c, accountNum *acc){
    if (c->accNum>*acc)
        return GREATER;
    else if (c->accNum<*acc)
        return SMALLER;
    return EQUAL;
}


/* 2 generic compare functions . one for client id and one for balance;*/
comparison compareClientID(client* c, clientID id){
    if(strcmp(c->cID,&id)>0)
        return GREATER;
    else if (strcmp(c->cID,&id)<0)
        return SMALLER;
    return EQUAL;
}
comparison compareClientBal(client* c, amount *bal){
    if(c->balance>*bal)
        return GREATER;
    else if (c->balance<*bal)
        return SMALLER;
    return EQUAL;
}



/*************************************************************************/


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




/*insert a single client node to a tree*/
genTree *insertClientTree(genTree* root, client* newClient){
    
    if (!root){
        genTree *newTree=NULL;
        newTree=add_new_node(newTree,(void*)newClient, (genCmp)&cmpClient );
        return newTree;
    }
    
    root=add_new_node(root, (void*)newClient, (genCmp)&cmpClient );
    return root;
}



/*delete a client from a tree*/
genTree * deleteClientFromTree(genTree *root, accountNum acc){
    client *findClient= NULL;
    if (!root)  /*empty tree case*/
        return NULL;
    
    findClient=getClient(root,acc,NOCHECK);
    
    root=remove_node(root, (void*)&acc,(genDelete)&freeClient, (genCmp)cmpClientAccNum);
    return root;
}




/*delete client from system.*/
try deleteClient(accountNum acc){
    try echo;
    client *deleteC=NULL;
    
    if (!acc) {
        /*get client acc from user*/
        acc=getAcc(EXIST);
        if (acc==CANCEL){
            ACTIONCANCELD;
            return CANCELED;
        }
    }
    deleteC=getBankClient(acc);
    if (!deleteC)
        return CLIENTNOTFOUND;
    
    /*delete client from branch*/
    echo=deleteBranchClient(deleteC->brID,acc);
    if (echo==CLIENTNOTFOUND) {
        printf("Client not in any branch\n");
    }
    
    /*delete client from bank*/
    deleteBankClient(deleteC);
    
    return SUCCESS;
}




/*find client function, recieve either ID or Balance from user and build linked list with all relevant client.*/
void findClient (){
    char c;
    genLinked *clientsLinkedList=NULL;
    genTree* bankRoot=NULL;
    clientID id[CLIENTIDL]; amount balance;
    boolean finish=FALSE;
    
    bankRoot=*getBankClientRoot();	/*get the clients tree root from the bank*/
    
    while (finish!=TRUE){
        printf("Find Client by:\n"
               "1. ID\n"
               "2.Balance\n");
        c=getchar();
        getchar();
        
        /*prompt the user to chose which method to look for in client list.*/
        switch (c) {
            case '1':
                getClientID(id);
                clientsLinkedList=findClientGen(bankRoot,id,(genCmp)&compareClientID);	/*call the find client function with the id compare function pointer*/
                finish = TRUE;
                break;
            case '2':
                getDouble(&balance,"Please enter Balance:\n");
                clientsLinkedList=findClientGen(bankRoot,&balance,(genCmp)&compareClientBal);	/*call the find client function with the balance compare function pointer*/
                
                finish = TRUE;
                break;
            default:
                printf("the number is not in the menu.\n try again\n");
                break;
        }
    }
    
    if (clientsLinkedList==NULL){
        printf("No clients found\n");
        return ;
    }
    printClientsLinkedList(clientsLinkedList);
    
}


/*function recieve root of clients tree, and return client with given account number*/
client* getClient(genTree* root, accountNum acc,client** parent ){
    genTree* cl;
    if (root==NULL){
        return NULL;
    }
    cl=find_Node_Parent(root, (void*)&acc, NOCHECK,(genCmp)&cmpClientAccNum);
    if (cl){
        return (client*)cl->data;
    }
    return NULL;
    
}


/****************** Client Managment Functions END ********************/


/****************** Transaction functions START **********************/

/*get the transaction info from user, accoun number and amount of money.*/
try getTransactionInfo(accountNum* acc,amount* money){
    
    *acc=getAcc(EXIST);
    if (*acc==CANCEL){
        return CANCELED;
    }
    
    getDouble(money,"Please enter amount:\n");
    while (*money<=0) {
        printf("Error: amount cant be negative.\n");
        getDouble(money,"Please enter amount:\n");
    }
    
    return SUCCESS;
}


/*deposit money to client*/
try depositeMoneyToClientAccount() {
    accountNum acc=0;
    amount money=0;
    try echo;
    
    printf("starting a deposit:\n");
    echo=getTransactionInfo(&acc, &money);   /*get the transaction info.*/
    if (echo==CANCELED){
        ACTIONCANCELD;
        return CANCELED;
    }
    
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
    echo=getTransactionInfo(&acc, &money);   /*get the transaction info.*/
    if (echo==CANCELED){
        ACTIONCANCELD;
        return CANCELED;
    }
    
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

/****************** Transaction functions END **********************/



/****************** Utility Functions START ************************/

/*Get account number from user*/

accountNum getAcc(availble checkif){
    boolean flag=FALSE;
    accountNum acc=0;
    
    
    do{
        getInt(&acc,"please enter client account number , '0' to cancel\n");
        if (acc==CANCEL)
            return CANCEL;
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

/*print clients linked list*/
void printClientsLinkedList(genLinked *clients){		/*recieve the list head.*/
    if (clients==NULL){
        return;
    }
    printClientsLinkedList(clients->next);
    clients->next=NULL;	/*destroy created list.*/
    printClientInfo((client*)clients->data); /*send each client to a single client print function.*/
    printf("\n");
}


/*get information from user about new client.*/
client* getDetailsFromUser(branchID brID,char* bankName){
    client* newClient;
    accountNum acc;
    
    /*disabled for test only!!
    acc= getAcc(NOTEXIST);
    if (acc==CANCEL){
        ACTIONCANCELD;
        return NULL;
    }
    */
    
    
    
    newClient = ALLOC(client,1);
    initClient(newClient);
    
    
#ifndef TEST
    
    getName(&(newClient->name), MAXNAME, "please enter client name:\n");
    getName(&(newClient->surname), MAXNAME, "please enter client surname:\n");
    newClient->bankName = bankName;
    getClientID(newClient->cID);
    newClient->brID=brID;
    newClient->accNum=acc;
    
#else
    newClient->name=str_dup(testName);
    newClient->surname=str_dup(testName);
    testName[0]++;
    newClient->bankName = bankName;
    strcpy(newClient->cID,testID);
    testID[8]++;
    newClient->brID=brID;
    newClient->accNum=testAcc++;
#endif
    
    return newClient;
}





/*function search the tree, compare either balance or id, and build client linked list */
genLinked* findClientGen (genTree *root, void* tocmpare , genCmp cmp){
    if (root==NULL)
        return NULL;
    
    return find_node(root, tocmpare, cmp);
}


/*free a single Clinet node*/
void freeClient(client *c){
    FREE(c->name);
    FREE(c->surname);
    FREE(c);
}


genTree* clearClientTree(genTree* root)
{
    if(root == NULL)
        return NULL;
    root->left=clearClientTree(root->left);
    root->right=clearClientTree(root->right);
    freeClient((client*)root->data);
    FREE(root);
    return NULL;
}

/*print a sing client information*/
void printClientInfo(client* c)
{
    accountNum accNumber;
    client *tempClient;
    if (c==NULL){
        
        accNumber = getAcc(EXIST);
        if (accNumber==CANCEL){
            ACTIONCANCELD;
            return;
        }
        
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

/****************** Utility Functions END ************************/




