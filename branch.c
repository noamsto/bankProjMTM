/* bank project
 Yahel Tsufim 304952898
 Noam Stolero 201581683
 file:branch.c
 */

/*-----------------------INCLUDE------*/
#include "bank.h"

/*--------------------DEFINE---------------*/
#define MAXBRANCHCLIENT 1000
#define N 500
#define HOURSINDAY 24


/*---------------------LOCAL BRANCHLIST-----------------*/
branch* head;
branch* tail;

/*--------------------LOCAL FUNCTION DECLERATION--------*/
void initBranch(branch*);/*init branch struct*/
int isBranchFull(branch *);/*check if branch is full (has more room from clients)*/
void updateCurrentClient(branchID ,addremove);/*update amount of clients in branch*/
branchID getBranchID(availble checkif);/* get branch ID from user, including check if the id is already in use*/
int getTime(char*); /*get hours from user.*/


/*----------------------------------------------CODE BEGIN'S HERE--------------------------------------------*/

branch* createBranchList()
{
    head = ALLOC(branch,1);
    tail = ALLOC(branch,1);
    head->next=tail;
    tail->next=NULL;
    return head;
}


void initBranch(branch *brancInit)
{
    brancInit->brID = 0;
    brancInit->balance=0;
    brancInit->openTime=0;
    brancInit->closeTime=0;
    brancInit->currentClients=0;
    brancInit->numOfActiveLoans=0;
}


try addNewBranch()
{
    /*put the new branch in the end of the branch list*/
    branch* newBranch;
    
    if(getNumOfBranches() == N){
        printf("bank has maximum number of branches.\n");
        return MAX_BANK_REACHED;
    }
    printf("Add new branch start:\n");
    /*add new branch in the beginning of the list*/
    newBranch = ALLOC(branch,1);
    newBranch->next = head->next;
    head->next = newBranch;
    /*receive data from user*/
    getName(&newBranch->bankName,MAXNAME,"please enter branch name:\n");
    getName(&newBranch->bankName,MAXNAME,"please enter branch name:\n");
    newBranch->brID=getBranchID(NOTEXIST);
    newBranch->openTime = getTime("please enter opening time (between 0-23)\n");
    newBranch->closeTime = getTime("please enter closing time (between 0-23)\n");
    newBranch->clientList = createBranchClientList();    /*create the client list of the branch*/
    updateNumOfBranches(ADD);/*update branch list on addition of bank*/
    return SUCCESS;
}


void createBranchClientList(clientsLinkedList* list)
{
	list->head = ALLOC(client,1);
	list->tail = ALLOC(client,1);
	list->head->next = list->tail;
	list->tail->next = NULL;
}


try addNewClientToBranch()
{
    /*prepare data to receive client*/
    branchID brID;
    branch *temp;
    client *newClient;
    
    printf("Starting new client registry:\n");
    /*get branch and check if available place for another client*/
    if(getNumOfBranches()==0){
            printf("first add a branch\n");
            return FAIL;
    }
    if (isBankFull()) {
        printf("The bank is full\n");
        return FAIL;
    }
    brID=getBranchID(EXIST);
    temp = getBranch(brID,NOCHECK);
    
    if (isBranchFull(temp)) {
        printf("the branch is full\n");
        return FAIL;
    }
    newClient = ALLOC(client,1);
    
    /*receive client data from user*/
    getName(&(newClient->name), MAXNAME, "please enter client name:\n");
    getName(&(newClient->surname), MAXNAME, "please enter client surname:\n");
    getClientID(newClient->cID);
    newClient->accNum=getAcc(NOTEXIST);
    
    /*inform branch and bank on new client*/
    newClient->brID=brID;
    temp->currentClients++;
    addNewClientToBank(newClient);
    newClient->next = temp->clientList->head->next;/*-----------------------------------------------------------------------------------------*/
    temp->clientList->head->next = newClient;
    printf("Add new client finished successfully\n");
    return SUCCESS;
}

//#ifdef Bank1
int clientNumberWithGivenBalance()
{
    int clientsNumber=0;
    amount balance;
    branchID  brID;
    branch *tempBranch;
    client *tempClient;
    if(getNumOfBranches()==0){
        printf("no branches\n");
        return 0;
    }
    brID = getBranchID(EXIST);
    tempBranch = getBranch(brID,NOCHECK);
    getInt(&balance, "please enter balance:\n");
    tempClient = tempBranch->clientList->head->next;
    while(tempClient!=NULL){
        if(tempClient->balance > balance)
            clientsNumber++;
        tempClient = tempClient->next;
    }
    return clientsNumber;
}
//#endif


try deleteAllBranchClients(branchID id)
{
    branch *temp=NULL;
    if (!id) {/*if no ID has been received. get branch id from user*/
        getInt(&id, "please enter branch ID:\n");
    }
    temp = getBranch(id,NOCHECK);
    while(temp->currentClients>0){
        deleteClient(temp->clientList->head->next->accNum);
    }
    
    updateBranchBalance(id,0,REMOVE);
    return SUCCESS;
}


try deleteBranchClient(branchID brID,accountNum acc)
{
    /*set variables*/
    client* tempClient=NULL,*beforeClient;
    branch* tempBranch;
    tempClient=getBranchClient(acc, brID,&beforeClient);
    if (tempClient==NULL) {/*if the  client is not in branch*/
        printf("client not in branch.\n");
        return CLIENTNOTFOUND;
    }
    tempBranch=getBranch(tempClient->brID,NOCHECK);
    
    /*update branch on leaving costumer*/
    updateBranchBalance(tempClient->brID,tempClient->balance, REMOVE);
    if(tempClient->debt>0)
    		updateBranchLoan(brID,REMOVE);
    beforeClient->next = tempBranch->next;
    /*delete all clients fields*/
    FREE(tempClient->name);
    FREE(tempClient->surname);
    FREE(tempClient->bankName);
    FREE(tempClient);
    tempBranch->currentClients--;
    
    return SUCCESS;
}


try deleteBranch(branchID brID)
{
    branch *deleteB=NULL,previus;
    if(brID==NOCHECK)
        brID=getBranchID(EXIST);/*receive branch from user*/
    
    deleteB=getBranch(brID,previus);/*get the pointer to the branch*/
    previus->next = deleteB->next;
    deleteAllBranchClients(brID);
    FREE(deleteB->bankName);
    FREE(deleteB->branchName);
    FREE(deleteB->clientList->head);
    FREE(deleteB->clientList->tail);
    FREE(deleteB);
    updateNumOfBranches(REMOVE);  /* decrease ammount of branches in bank*/
    return SUCCESS;
}

void deleteAllBranches()
{
    int numberOfBranches;
    numberOfBranches = getNumOfBranches();
    while(numberOfBranches>0)
        deleteBranch(head->next);
}

/*--------------------------- BRANCH INFO UPDATE -------------------------*/

try updateBranchBalance(branchID brID, amount am,addremove remove)
{
    branch *tempBranch;
    tempBranch = getBranch(brID,NOCHECK);
    if (tempBranch!=NULL){/*if branch not found*/
        printf("branch not found.\n");
        return BRANCHNOTFOUND;
    }
    if (remove==REMOVE) {/*if needed to decrease (client leave, has less money, etc.)*/
    	tempBranch->balance-=am;
        return SUCCESS;
    }
    else{
    	tempBranch->balance += am;
    }
    return SUCCESS;
}



void updateBranchLoan(branchID brID,addremove remove)
{
    branch *tempBranch;
    tempBranch = getBranch(brID,NOCHECK);
    if(remove)
    	tempBranch->numOfActiveLoans--;
    else
    	tempBranch->numOfActiveLoans++;
}

void updateCurrentClient(branchID brID,addremove remove){
    branch *tempBranch;
    tempBranch = getBranch(brID,NOCHECK);
    if(remove)
    	tempBranch->currentClients--;
    else
    	tempBranch->currentClients++;
}


/*--------------------------------------------BRANCH INFO-------------------------------------*/

int isBranchFull(branch *tempBranch)
{
    if (tempBranch->currentClients<=MAXBRANCHCLIENT) {
        return FALSE;
    }
    return TRUE;
}


branch* getBranch(branchID brID, branch **previus)
{
    branch *temp = head;
    while(temp->next != tail){
    	if(temp->next->brID == brID){
    		if(previus != NULL)
    			*previus = temp;
    		return temp->next;
    	}
    	temp = temp->next;
    }

    return NULL;
}


client* getBranchClient(accountNum acc, branchID brID, client **previus)
{
    branch *tempBranch=NULL;
    client *tempClient;

    tempBranch=getBranch(brID);
    tempClient = tempBranch->clientList->head;

    while(tempClient->next != tempBranch->clientList->tail){
    	if(tempClient->next->accNum == acc){
    		if(previus != NULL)
    			*previus = tempClient;
    		return tempClient->next;
    	}
    	tempClient = tempClient->next;
    }

    return NULL;
}


boolean checkBranchID(branchID brID)
{
    branch *temp = head->next;

    while(temp != tail){
        if(temp->brID == brID)
            return TRUE;
        temp = temp->next;
    }
    return FALSE;
}
/*------------------------------------RECIEVE DATA FROM USER-------------------------------*/

int getTime(char *output){
    int time;
    do{
        getInt(&time, output);
    }while(time<0 || time>HOURSINDAY);
    return time;
}


branchID getBranchID(availble checkif){
    branchID brID;
    boolean flag = FALSE;
    do{
        getInt(&brID,"please enter branch id (1-500):\n");
        if (brID>N || brID<1) {
            printf("Branch id not in range (1-500)\n");
            continue;
        }
        if(checkBranchID(brID)){
            if(checkif==EXIST){
                flag = TRUE;
            }else{
                printf("The branch id is taken. enter a new ID.\n");
            }
        }else if (checkif==NOTEXIST){
            flag=TRUE;
        }else{
            printf("Branch not found. enter new ID\n");
        }
    }while(flag == FALSE); /* check if id doesn't exist*/
    
    return brID;
    
}

