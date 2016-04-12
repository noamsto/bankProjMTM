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
branch branchList[N];


/*--------------------LOCAL FUNCTION DECLERATION--------*/
void initBranch(branch*);/*init branch struct*/
int isBranchFull(branch *);/*check if branch is full (has more room from clients)*/
void updateCurrentClient(branchID ,addremove);/*update amount of clients in branch*/
branchID getBranchID(availble checkif);/* get branch ID from user, including check if the id is already in use*/
int getTime(char*); /*get hours from user.*/


/*----------------------------------------------CODE BEGIN'S HERE--------------------------------------------*/

branch* createBranchList()
{
    /*branch list already exist*/
    int i=0;
    for (i=0; i<N; i++) {/*init every branch in the list*/
        initBranch(&branchList[i]);
    }
    return NULL;
}


void initBranch(branch *brancInit)
{
    brancInit->brID = 0;
    brancInit->balance=0;
    brancInit->openTime=0;
    brancInit->closeTime=0;
    brancInit->currentClients=0;
    brancInit->numOfActiveLoans=0;
    brancInit->branchClients = NULL;
}


try addNewBranch()
{
    /*put the new branch in the end of the branch list*/
    int brNum;
    brNum = getNumOfBranches();
    
    printf("Add new branch start:\n");
    if(brNum == N){
        printf("bank has maximum number of branches.\n");
        return MAX_BANK_REACHED;
    }
    /*receive data from user*/
    getName(&(branchList+brNum)->name,MAXNAME,"please enter branch name:\n");
    branchList[brNum].brID=getBranchID(NOTEXIST);
    branchList[brNum].openTime = getTime("please enter opening time (between 0-23)\n");
    branchList[brNum].closeTime = getTime("please enter closing time (between 0-23)\n");
    
    (branchList+brNum)->branchClients = createBranchClientList();    /*create the client list of the branch*/
    updateNumOfBranches(ADD);/*update branch list on addition of bank*/
    return SUCCESS;
}


client* createBranchClientList()
{
    client *newList = ALLOC(client,MAXBRANCHCLIENT);
    int i=0;
    for(i=0;i<MAXBRANCHCLIENT;i++)  /*reset all the new clients of the branch*/
        initClient(newList+i);
    return newList;
}


try addNewClientToBranch()
{
    /*prepare data to recieve client*/
    branchID brID;
    branch *temp;
    client *newClient;
    
    if(getNumOfBranches()==0){
        printf("first add a branch\n");
        return FAIL;
    }
    printf("Starting new client registery:\n");
    /*get branch and check if available place for another client*/
    
    if (isBankFull()) {
        printf("The bank is full\n");
        return FAIL;
    }
    brID=getBranchID(EXIST);
    temp = getBranch(brID);
    
    if (isBranchFull(temp)) {
        printf("the branch is full\n");
        return FAIL;
    }
    newClient = &temp->branchClients[temp->currentClients];
    
    /*recieve client data from user*/
    getName(&(newClient->name), MAXNAME, "please enter client name:\n");
    getClientID(newClient->cID);
    newClient->accNum=getAcc(NOTEXIST);
    
    /*inform branch and bank on new client*/
    newClient->brID=brID;
    temp->currentClients++;
    addNewClientToBank(newClient);
    printf("Add new client finished successfuly\n");
    return SUCCESS;
}


int clientNumberWithGivenBalance()
{
    int i=0,clientsNumber=0;
    amount balance;
    branchID  brID;
    branch *temp;
    if(getNumOfBranches()==0){
        printf("no branches\n");
        return 0;
    }
    brID = getBranchID(EXIST);
    temp = getBranch(brID);
    getInt(&balance, "please enter balance:\n");
    for(i=0;i<temp->currentClients;i++){
        if(temp->branchClients[i].balance > balance)
            clientsNumber++;
    }
    return clientsNumber;
}


try deleteAllBranchClients(branchID id)
{
    int i=0;
    branch *temp=NULL;
    
    if (!id) {/*if no ID has been recieved. get branch id from user*/
        getInt(&id, "please eneter branch ID:\n");
    }
    temp = getBranch(id);
    
    for(i=0;i<temp->currentClients;i++){
        deleteClient(temp->branchClients[i].accNum);
    }
    
    updateBranchBalance(id,0,REMOVE);
    return SUCCESS;
}


try deleteBranchClient(branchID brID,accountNum acc)
{
    /*set variables*/
    client* getClient=NULL;
    branch* br;
    getClient=getBranchClient(acc, brID);
    if (getClient==NULL) {/*if the  client is not in branch*/
        printf("client not in branch.\n");
        return CLIENTNOTFOUND;
    }
    br=getBranch(getClient->brID);
    
    /*update branch on leaving costumer*/
    updateBranchBalance(getClient->brID,getClient->balance, REMOVE);
    br->currentClients--;
    *getClient=br->branchClients[br->currentClients];
    
   
    return SUCCESS;
}


try deleteBranch(branchID brID)
{
    branch *deleteB=NULL;
    
    if(brID==NOCHECK)
        brID=getBranchID(EXIST);/*recieve branch from user*/
    
    deleteB=getBranch(brID);/*get the pointer to the branch*/
    deleteAllBranchClients(brID);
    FREE(deleteB->branchClients);
    updateNumOfBranches(REMOVE);  /* decrease ammount of branches in bank*/
    *deleteB = branchList[getNumOfBranches()];/* overide deleted branch*/
    return SUCCESS;
}

void deleteAllBranches()
{
    int numberOfBranches, i;
    numberOfBranches = getNumOfBranches();
    for(i=0;i<numberOfBranches;i++)
        deleteBranch(branchList[i].brID);
}

/*--------------------------- BRANCH INFO UPDATE -------------------------*/

try updateBranchBalance(branchID brID, amount am,addremove remove)
{
    branch *temp = getBranch(brID);
    if (!temp){/*if branch not found*/
        printf("branch not found.\n");
        return BRANCHNOTFOUND;
    }
    if (remove==REMOVE) {/*if needed to decrease (client leave, has less money, etc.)*/
        temp->balance-=am;
        return SUCCESS;
    }
    else{
    	temp->balance += am;
    }
    return SUCCESS;
}



void updateBranchLoan(branchID brID,addremove remove)
{
    branch *temp;
    temp = getBranch(brID);
    if(remove)
        temp->numOfActiveLoans--;
    else
        temp->numOfActiveLoans++;
}

void updateCurrentClient(branchID brID,addremove remove){
    branch *temp = getBranch(brID);
    if(remove)
        temp->currentClients--;
    else
        temp->currentClients++;
}


/*--------------------------------------------BRANCH INFO-------------------------------------*/

int isBranchFull(branch *temp)
{
    if (temp->currentClients<=MAXBRANCHCLIENT) {
        return FALSE;
    }
    return TRUE;
}


branch* getBranch(branchID ID)
{
    int i;
    for(i=0;i<N;i++)
        if(branchList[i].brID == ID)
            return branchList+i;
    return NULL;
}


client* getBranchClient(accountNum acc, branchID brID)
{
    branch *br=NULL;
    int i=0;

    br=getBranch(brID);
    for (i=0;i<br->currentClients ; i++) {
        if (br->branchClients[i].accNum==acc) {
            return  &br->branchClients[i];
        }
    }
    return NULL;
}


boolean checkBranchID(branchID brID)
{
    int i;
    for(i=0;i<getNumOfBranches();i++)
        if(brID == branchList[i].brID){
            return TRUE;
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

