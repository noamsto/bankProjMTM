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
#define MILLION 10e6
#define MINBALANCE 1
#define MAXBALANCE 500
#define CLIENTSHEAD(STRUCT) STRUCT->clientList.head->next
/*---------------------LOCAL BRANCHLIST-----------------*/
branch* head;
branch* tail;

/*--------------------LOCAL FUNCTION DECLERATION--------*/
void initBranch(branch*);/*init branch struct*/
int isBranchFull(branch *);/*check if branch is full (has more room from clients)*/
void updateCurrentClient(branchID ,addremove);/*update amount of clients in branch*/
branchID getBranchID(availble checkif);/* get branch ID from user, including check if the id is already in use*/
int getTime(char*); /*get hours from user.*/
int clientWithBiggerLoans(client*);/*recursive function. returns amount of clients with bigger debt then they're balance*/


/*----------------------------------------------CODE BEGIN'S HERE--------------------------------------------*/

branch* createBranchList()
{
    head = ALLOC(branch,1);
    tail = ALLOC(branch,1);
    initBranch(head);
    initBranch(tail);
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
    brancInit->balance = 1.0;
    brancInit->yearProfit = 1.0;
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
    initBranch(newBranch);
    /*receive data from user*/
    getName(&newBranch->branchName,MAXNAME,"please enter branch name:\n");
    newBranch->bankName = getBankName();
    newBranch->brID=getBranchID(NOTEXIST);
    newBranch->openTime = getTime("please enter opening time (between 0-23)\n");
    newBranch->closeTime = getTime("please enter closing time (between 0-23)\n");
    createBranchClientList(&(newBranch->clientList));    /*create the client list of the branch*/
    updateNumOfBranches(ADD);/*update branch list on addition of bank*/

    newBranch->next = head->next;
    head->next = newBranch;
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
    initClient(newClient);
    getName(&(newClient->name), MAXNAME, "please enter client name:\n");
    getName(&(newClient->surname), MAXNAME, "please enter client surname:\n");
    newClient->bankName = temp->bankName;
    getClientID(newClient->cID);
    newClient->accNum=getAcc(NOTEXIST);
    
    /*inform branch and bank on new client*/
    newClient->brID=brID;
    temp->currentClients++;
    addNewClientToBank(newClient);
    newClient->next = CLIENTSHEAD(temp);
    CLIENTSHEAD(temp) = newClient;
    printf("Add new client finished successfully\n");
    return SUCCESS;
}

#ifdef BANK_AHAMELIM
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
    getDouble(&balance, "please enter balance:\n");
    tempClient = CLIENTSHEAD(tempBranch);
    while(tempClient!=NULL){
        if(tempClient->balance > balance)
            clientsNumber++;
        tempClient = tempClient->next;
    }
    return clientsNumber;
}
#endif
void clientNumberWithBiggerLoansThanBalance_print(){
	int clientNum_rec,clientNum_iter;
	branch *tempBranch;
	branchID brID;
	brID = getBranchID(EXIST);
	tempBranch = getBranch(brID,NOCHECK);
	clientNum_iter = clientNumberWithBiggerLoansThanBalance(CLIENTSHEAD(tempBranch));
	clientNum_rec = clientNumberWithBiggerLoansThanBalance_rec(CLIENTSHEAD(tempBranch));
	printf("iterative check:\n"
			"there are %d clients owe to branch more then they're balance\n",clientNum_iter);
	printf("recursive check:\n"
				"there are %d clients owe to branch more then they're balance\n",clientNum_rec);
}


int clientNumberWithBiggerLoansThanBalance(client *list){
	int numberOfClients=0;
	client *tempClient;
	tempClient = list;
	while(tempClient->next != NULL){
		if(tempClient->balance < tempClient->debt)
			numberOfClients++;
	tempClient = tempClient->next;
	}
	return numberOfClients;
}

int clientNumberWithBiggerLoansThanBalance_rec(client *list){
	int amountOfClients=0;
	if(list->next == NULL)/*if list is empty, no clients with bigger loans then balance*/
		return 0;
	amountOfClients = clientNumberWithBiggerLoansThanBalance_rec(list->next);/*get amount of clients from rest of the list*/
	if(list->debt > list->balance)
		amountOfClients++;/*if the client has bigger debt then balance, count him*/
	return amountOfClients;
}





try deleteAllBranchClients(branchID id)
{
    branch *temp=NULL;
    if (!id) {/*if no ID has been received. get branch id from user*/
        getInt(&id, "please enter branch ID:\n");
    }
    temp = getBranch(id,NOCHECK);
    while(temp->currentClients>0){
        deleteClient(temp->clientList.head->next->accNum);
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
    /*delete all clients fields*/
    FREE(tempClient->name);
    FREE(tempClient->surname);
    beforeClient->next = tempClient->next;
    FREE(tempClient);
    tempBranch->currentClients--;
    
    return SUCCESS;
}


try deleteBranch(branchID brID)
{
    branch *deleteB=NULL,*previus;
    if(brID==NOCHECK)
        brID=getBranchID(EXIST);/*receive branch from user*/
    
    deleteB=getBranch(brID,&previus);/*get the pointer to the branch*/
    deleteAllBranchClients(brID);
    FREE(deleteB->branchName);
    FREE(deleteB->clientList.head);
    FREE(deleteB->clientList.tail);
    previus->next = deleteB->next;
    FREE(deleteB);
    updateNumOfBranches(REMOVE);  /* decrease amount of branches in bank*/
    return SUCCESS;
}

void deleteAllBranches()
{
	branch *temp =  head;
    while(temp->next!=tail){
    	   deleteBranch(temp->next->brID);
    	   temp=temp->next;
    }
    FREE(head);
    FREE(tail);
}

/*--------------------------- BRANCH INFO UPDATE -------------------------*/

try updateBranchBalance(branchID brID, amount am,addremove remove)
{
    branch *tempBranch;
    tempBranch = getBranch(brID,NOCHECK);
    if (tempBranch==NULL){/*if branch not found*/
        printf("branch not found.\n");
        return BRANCHNOTFOUND;
    }
    if (remove==REMOVE) {/*if needed to decrease (client leave, has less money, etc.)*/
    	if(tempBranch->balance - (am/MILLION) < MINBALANCE){
    		printf("branch balance is at minimum, can't withdraw more money\n");
    		return FAIL;
    	}
    	tempBranch->balance = tempBranch->balance - (double)am/MILLION;
        return SUCCESS;
    }
    else{
    	if(tempBranch->balance - (am/MILLION) > MAXBALANCE){
    		printf("branch balance is at maximum, can't deposit more money\n");
    	    return FAIL;
    	}
    	tempBranch->balance = (double)am/MILLION + tempBranch->balance;
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

    tempBranch=getBranch(brID,NOCHECK);
    tempClient = tempBranch->clientList.head;

    while(tempClient->next != tempBranch->clientList.tail){
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

void printBranchInfo()
{
	branchID brID;
	branch *tempBranch;
	brID = getBranchID(EXIST);
	tempBranch = getBranch(brID,NOCHECK);
	printf("Branch name: %s\n",tempBranch->branchName);
	printf("Branch Bank name: %s\n",tempBranch->bankName);
	printf("Branch ID : %d\n",tempBranch->brID);
	printf("Number of clients: %d\n",tempBranch->currentClients);
	printf("Number of loans: %d\n",tempBranch->numOfActiveLoans);
	printf("Opening time: %d\n",tempBranch->openTime);
	printf("Closing time: %d\n",tempBranch->closeTime);
	printf("Branch balance: %g\n",tempBranch->balance);
	printf("Yearly profit: %g\n",tempBranch->yearProfit);
	printf("\n\"Do not take life too seriously.\n You will never get out of it alive\"\n\n");
}
