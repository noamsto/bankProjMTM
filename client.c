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
void findClientGen (client *root, void* tocmpare, client *foundClients , int (*compare)(client*,void*));

/* 2 generic compare functions . one for client id and one for balance;*/
int compareID(client* check, void* id);
int compareBal(client* check, void *bal);

/*print clients linked list*/
void printClientsLinkedList(client *clients);

/*insert a client to a client linked list*/
void buildClientLinkedList(client *list, client* add);

/*find Client With max balance*/
client *findMaxACC(client *root);

/*find Client With min balance*/
client *findMinACC(client *root);

/*swap 2 clients nodes*/
void swapClients(client *client1, client*client2);

/*free a single Clinet node*/
void freeClient(client *findClient);



/****************** Client Managment Functions START ********************/

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

/*insert a single client node to a tree*/
void *insertClientTree(client* root, client* newClient){
    
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



/*delete a client from a tree*/
client * deleteClientFromTree(client *root, accountNum acc){
    client *findClient= NULL, *swapClient=NULL,  *parent=NULL;
    if (!root)  /*empty tree case*/
        return NULL;
    
    findClient=getClient(root,acc, &parent);
    if (!findClient){   /*client not found case*/
        printf("client to be deleted not found\n");
        return root;
    }
    
    if (findClient->left){  /*if there is a left tree, getting the max node*/
        
        swapClient=findMaxACC(findClient->left);
        swapClients(findClient,swapClient);   /*swap the client and recurse on the left tree*/
        findClient->left=deleteClientFromTree(findClient->left, acc);
        return findClient;
    }
    else if (findClient->right){   /*else look in the right tree for the min node*/
        
        swapClient=findMinACC(findClient->right);
        swapClients(findClient,swapClient);   /*swap the client and recurse on the right tree*/
        findClient->right=deleteClientFromTree(findClient->right, acc);
        return findClient;
    }
    /*if non of the above is found*/
    /*leaf case*/
    
    if (parent){    /*check if its not the root*/
        if (parent->left==findClient)
            parent->left=NULL;
        else
            parent->right=NULL;
        
        freeClient(findClient);
        return root;
    }
    /*root case, returning NULL*/
    freeClient(findClient);
    return NULL;
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
    client clientsLinkedList, * bankRoot=NULL;
    clientID id[CLIENTIDL]; amount balance;
    boolean finish=FALSE;
    
    bankRoot=*getBankClientRoot();	/*get the clients tree root from the bank*/
    initClient(&clientsLinkedList);		/*init the linked list head*/
    
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
                findClientGen(bankRoot,id,&clientsLinkedList,&compareID);	/*call the find client function with the id compare function pointer*/
                finish = TRUE;
                break;
            case '2':
                getDouble(&balance,"Please enter Balance:\n");
                findClientGen(bankRoot,&balance,&clientsLinkedList,&compareBal);	/*call the find client function with the balance compare function pointer*/
                
                finish = TRUE;
                break;
            default:
                printf("the number is not in the menu.\n try again\n");
                break;
        }
    }
    
    if (clientsLinkedList.next==NULL){
        printf("No clients found\n");
        return ;
    }
    printClientsLinkedList(clientsLinkedList.next);
    
}


/*function recieve root of clients tree, and return client with given account number*/
client* getClient(client* root, accountNum acc,client **parent){
    
    if (root==NULL){
        if (parent)
            *parent=NULL;
        return NULL;
    }
    
    if (root->accNum>acc){
        if (parent)
            *parent=root;
        return getClient(root->left, acc,parent);
    }
    if (root->accNum<acc){
        if (parent)
            *parent=root;
        return getClient(root->right,acc,parent);
    }
    return root;
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
void	printClientsLinkedList(client *clients){		/*recieve the list head.*/
    if (clients==NULL){
        return;
    }
    printClientsLinkedList(clients->next);
    clients->next=NULL;	/*destroy created list.*/
    printClientInfo(clients); /*send each client to a single client print function.*/
    printf("\n");
}


/*get information from user about new client.*/
client* getDetailsFromUser(branchID brID,char* bankName){
    client* newClient;
    accountNum acc;
    /*acc= getAcc(NOTEXIST);*/
    acc = (rand()%10000);
    if (acc==CANCEL){
        ACTIONCANCELD;
        return NULL;
    }
    newClient = ALLOC(client,1);
    initClient(newClient);
    getName(&(newClient->name), MAXNAME, "please enter client name:\n");
    getName(&(newClient->surname), MAXNAME, "please enter client surname:\n");
    newClient->bankName = bankName;
    strcpy(newClient->cID,"123123123");
    /*getClientID(newClient->cID);*/
    newClient->brID=brID;
    newClient->accNum=acc;
    return newClient;
}


/*insert a client to a client linked list*/
void buildClientLinkedList(client *list, client* add){	/*recieve the head of the list and client to add.*/
    client *current=list;
    while (current->next!=NULL){		/*sort the list by client id.*/
        if (strcmp(current->next->cID, add->cID)<= 0){
            add->next=current->next;
            break;
        }else
            current=current->next;
    }
    current->next=add;
}


/* 2 generic compare functions . one for client id and one for balance;*/
int compareID(client* check, void* id){
    return !strcmp(check->cID, (clientID*) id);
}
int compareBal(client* check, void *bal){
    return check->balance== *((amount*)(bal) )? 1:0;
}

/*function search the tree, compare either balance or id, and build client linked list */
void findClientGen (client *root, void* tocmpare, client *foundClients , int (*compare)(client*,void*)){
    if (root==NULL)
        return;
    
    findClientGen(root->left, tocmpare, foundClients, compare);
    if ((*compare)(root,tocmpare)){	/*rigger the correct compare function.*/
        buildClientLinkedList(foundClients, root);
    }
    findClientGen(root->right, tocmpare,foundClients, compare);
    return;
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
void swapClients(client *client1, client*client2){
    client tempclient;
    tempclient=*client1;
    *client1=*client2;
    *client2=tempclient;
    
    /*preserve tree structure*/
    client2->left=client1->left;
    client2->right=client1->right;
    client1->left=tempclient.left;
    client1->right=tempclient.right;
    
}


/*free a single Clinet node*/
void freeClient(client *findClient){
    FREE(findClient->name);
    FREE(findClient->surname);
    FREE(findClient);
}


void clearClientTree(client* root)
{
    if(root == NULL)
        return;
    clearClientTree(root->left);
    clearClientTree(root->right);
    deleteClient(root->accNum);
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




