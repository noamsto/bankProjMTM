/* bank project
 Yahel Tsufim 304952898
 Noam Stolero 201581683
 file:branch.c
 */

/* ---------i chose right to be the smaller and left to be the bigger-------- */
/*-----------------------INCLUDE------*/
#include "bank.h"

/*--------------------DEFINE---------------*/
#define MAXBRANCHCLIENT 1000
#define N 500
#define HOURSINDAY 24
#define MILLION 1e6
#define MINBALANCE 1
#define MAXBALANCE 500

/*---------------------LOCAL BRANCHLIST-----------------*/
static genTree* branchRoot;
int (*cmp_func)(client*,amount);
/*--------------------LOCAL FUNCTION DECLERATION--------*/
void initBranch(branch*);/*init branch struct*/
branch *createBranch();/* create a new branch. get information from user */
void updateCurrentClient(branchID ,addremove);/*update amount of clients in branch*/
void deleteBranchFields(branch*);/* delete all the fields of a certain branch */
boolean addClientConditions(); /* check if possible to add new client to the bank */
branch* findBranch(genTree* , branchID );
branchID getBranchID(availble checkif);/* get branch ID from user, including check if the id is already in use*/
int getTime(char*); /*get hours from user.*/
int isBranchFull(branch *);/*check if branch is full (has more room from clients)*/

/*        TEMPORARY      */
int countClients(client* , amount ,int (*cmp_func)(client*,amount));
int compareClientsWithBiggerBalance(client* client, amount balance);
int compareClientsWithBiggerLoans(client* client, amount balance);
int printClientDetails(client* client,amount s);
int averageClients(branch*,double*);
/*        TREE       */
void clearBranchTree(branch*);


/*----------------------------------------------CODE BEGIN'S HERE--------------------------------------------*/

void createBranchList()
{
	branchRoot = NULL;;
}

comparison compare_Branch_ID(branch* a,branch *b)
{
	if(a->brID > b->brID)
		return GREATER;
	if(a->brID == b->brID)
		return SMALLER;
	return EQUAL;
}

try addNewBranch()
{
    /*put the new branch in the end of the branch list*/
    branch* newBranch;

    if(getNumOfBranches() == N){
        printf("bank has maximum number of branches.\n");
        return MAX_BANK_REACHED;
    }
    newBranch = createBranch();
    branchRoot = add_new_node(branchRoot,newBranch,(genCmp)(&compare_Branch_ID));
    updateNumOfBranches(ADD);/*update branch list on addition of bank*/
    return SUCCESS;
}


genTree* createBranchClientList()
{
	return NULL;
}

try addNewClientToBranch()
{
    /*prepare data to receive client*/
    branch *temp;
    client *newClient;
    boolean check;
    branchID brID;
    
    printf("Starting new client registry:\n");
    check=addClientConditions();
    if(check==FALSE)
    	return FAIL;
    brID = getBranchID(EXIST);
    if(brID == CANCEL){
        printf("Action aborted\n");
        return CANCEL;
    }
    
    temp = getBranch(brID);
    
    if (isBranchFull(temp)) {
        printf("the branch is full\n");
        return FAIL;
    }
    newClient = getDetailsFromUser(temp->brID,temp->bankName);
    

    /*inform branch and bank on new client*/
    temp->currentClients++;
    addNewClientToBank(newClient);
    temp->clientList = add_new_node(temp->clientList,newClient,(genCmp)(&cmpClientAcc));
    printf("Add new client finished successfully\n");
    return SUCCESS;
}

boolean addClientConditions(){
if(getNumOfBranches()==0){
           printf("first add a branch\n");
           return FALSE;
   }
   if (isBankFull()) {
       printf("The bank is full\n");
       return FALSE;
   }
   return TRUE;
}

/*
#ifdef BANK_AHAMELIM
void clientNumberWithGivenBalance()
{
	int numberOfClients;
    amount balance;
    branch *tempBranch;
    branchID brID;
    if(getNumOfBranches()==0){
        printf("no branches\n");
        return ;
    }
    brID = getBranchID(EXIST);
    if(brID == CANCEL){
        printf("Aborted the action\n");
        return;
    }
    
    tempBranch = getBranch(brID);
    getDouble(&balance, "please enter balance:\n");
    numberOfClients = countClients(tempBranch->clientList,balance,&compareClientsWithBiggerBalance);
    printf("the number of clients with bigger balance then %f is : %d\n",balance,numberOfClients);
}
#endif

void printClientAccountsNumberAndBalance()
{
	branch *tempBranch;
    branchID brID;
    if(getNumOfBranches()==0){
        printf("no branches\n");
        return ;
    }
    brID = getBranchID(EXIST);
    if(brID == CANCEL){
        printf("Aborted the action\n");
        return;
    }
    tempBranch = getBranch(brID);
    countClients(tempBranch->clientList,NOCHECK,&printClientDetails);

}
void clientNumberWithBiggerLoansThanBalance()
{
	int numberOfClients;
    branch *tempBranch;
    branchID brID;
    if(getNumOfBranches()==0){
        printf("no branches\n");
        return ;
    }
    brID = getBranchID(EXIST);
    if(brID == CANCEL){
        printf("Aborted the action\n");
        return;
    }
    
    tempBranch = getBranch(brID);
    numberOfClients = countClients(tempBranch->clientList,NOCHECK,&compareClientsWithBiggerLoans);
    printf("amount of clients with bigger loans then balance : %d",numberOfClients);
}


void averageNumberOfAccountsInBranches()
{
	int numOfBranches=0;
	double clientsAverage=0;
	numOfBranches = averageClients(branchRoot,&clientsAverage);
	printf("number of branches : %d\n"
			"Average number of clients in single branch : %f\n",
			numOfBranches,clientsAverage);
}
int averageClients(branch* root,double* averageNum)
{
	int count =0,currBranch=0;
	double average=0,currClients=0;
	if(root==NULL){
		*averageNum = 0;
		return 0;
	}
	count = averageClients(root->left,&average);
	currClients += average * count;
	currBranch += count;
	count = averageClients(root->right,&average);
	currClients += average * count;
	currBranch += count;
	currBranch++;
	currClients += root->currentClients;
	*averageNum = currClients / currBranch;
	return currBranch;
}


*/
try deleteAllBranchClients(branchID id)
{
    branch *temp=NULL;
    if (!id) {/*if no ID has been received. get branch id from user*/
        getInt(&id, "please enter branch ID:\n");
    }
    temp = getBranch(id);
    /*delete all clients*/
    temp->balance = 1;
    temp->currentClients = 0;
    return SUCCESS;
}

try deleteBranchClient(branchID brID,accountNum acc)
{
    /*set variables*/
    client* tempClient=NULL;
    branch* tempBranch;

    tempBranch=getBranch(brID);
    if ((tempClient = getClient(tempBranch->clientList,acc,NULL)) == NULL ) {
           printf("client not in branch.\n");/*if the  client is not in branch*/
           return CLIENTNOTFOUND;
       }
    /*update branch on leaving costumer*/
    updateBranchBalance(tempClient->brID,tempClient->balance, REMOVE);
    if(tempClient->debt>0)
    		updateBranchLoan(brID,REMOVE);
    tempBranch->currentClients--;
    tempBranch->clientList = remove_node(tempBranch->clientList,tempClient,(genDelete)(&freeClient),(genCmp)(&cmpClientAcc));
    return SUCCESS;
}


try  deleteBranch(branchID brID)
{
	branch* tempBranch;
    if(getNumOfBranches()==0){
    	printf("There are no active branches\n");
    	return SUCCESS;
    }

    if(brID==NOCHECK){
        brID=getBranchID(EXIST);/*receive branch from user*/
        if(brID == CANCEL){
            printf("Aborted the action\n");
            return CANCEL;
        }
    }
    tempBranch = getBranch(brID);
    branchRoot = remove_node(branchRoot,tempBranch,(genDelete)(&deleteBranchFields),(genCmp)(&compare_Branch_ID));
    updateNumOfBranches(REMOVE);  /* decrease amount of branches in bank*/
    return SUCCESS;
}

void deleteAllBranches()
{
	clearBranchTree(branchRoot);
}

/*----------------------------------------------------*/

try updateBranchBalance(branchID brID, amount am,addremove remove)
{
    branch *tempBranch;
    ;
    if ((tempBranch = getBranch(brID))==NULL){/*if branch not found*/
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
    tempBranch = getBranch(brID);
    if(remove)
    	tempBranch->numOfActiveLoans--;
    else
    	tempBranch->numOfActiveLoans++;
}

void updateCurrentClient(branchID brID,addremove remove){
    branch *tempBranch;
    tempBranch = getBranch(brID);
    if(remove)
    	tempBranch->currentClients--;
    else
    	tempBranch->currentClients++;
}


int isBranchFull(branch *tempBranch)
{
    if (tempBranch->currentClients<=MAXBRANCHCLIENT) {
        return FALSE;
    }
    return TRUE;
}


comparison comp_Branch_to_ID(branch* a, branchID* b){
	if(a->brID > *b)
		return GREATER;
	if(a->brID < *b)
		return SMALLER;
	return EQUAL;
}

branch* getBranch(branchID brID)
{
    return findBranch(branchRoot,brID);
}



client* getBranchClient(accountNum acc, branchID brID)
{
    branch *tempBranch=NULL;
    tempBranch=getBranch(brID);
    return getClient(tempBranch->clientList,acc,NULL);
}



/*---------------HELP SEARCH IN TREE BRANCH-------------------*/
boolean checkBranchID(branchID brID)
{
    if(findBranch(branchRoot,brID) != NULL)
    	return TRUE;
    return FALSE;
}



branch* findBranch(genTree* root, branchID brID){
    return find_Node_Parent(branchRoot,&brID,NOCHECK,(genCmp)(&comp_Branch_to_ID))->data;

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
        getInt(&brID,"please enter branch id (1-500): (type 0 to cancel)\n");
        if (brID==CANCEL){
            return CANCEL;
        }
        if (brID>N || brID<0) {
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


/*-----------------------------INFORMATION FUNCTIONS-------------------*/
/*
void printBranchID(branch* root)
{
    if(root==NULL)
        return;
    printBranchID(root->left);
    printf("BRANCHID: %d\n",root->brID);
    printBranchID(root->right);
}
void printBranchInfo()
{
	branchID brID;
	branch *tempBranch;
    printBranchID(branchRoot);
    brID = getBranchID(EXIST);
    if(brID == CANCEL)
    {
        printf("Aborted the action\n");
        return;
    }
	tempBranch = getBranch(brID);
	printf("Branch name: %s\n",tempBranch->branchName);
	printf("Branch Bank name: %s\n",tempBranch->bankName);
	printf("Branch ID : %d\n",tempBranch->brID);
	printf("Number of clients: %d\n",tempBranch->currentClients);
	printf("Number of loans: %d\n",tempBranch->numOfActiveLoans);
	printf("Opening time: %d\n",tempBranch->openTime);
	printf("Closing time: %d\n",tempBranch->closeTime);
	printf("Branch balance: %g\n",tempBranch->balance);
	printf("Yearly profit: %g\n",tempBranch->yearProfit);
}
*/
/*----------ADD NEW BRANCH FUNCTIONS-------------*/
branch *createBranch()/* create branch, receive data from user */
{
	branch *newBranch;
	printf("Add new branch start:\n");
    newBranch = ALLOC(branch,1);
	initBranch(newBranch);
    /*receive data from user*/
	getName(&newBranch->branchName,MAXNAME,"please enter branch name:\n");
    newBranch->bankName = getBankName();
    newBranch->brID= (rand()%500);/*getBranchID(NOTEXIST);*/
    newBranch->openTime = 1;/* getTime("please enter opening time (between 0-23)\n");*/
    newBranch->closeTime = 1;/* getTime("please enter closing time (between 0-23)\n");*/
    newBranch->clientList=createBranchClientList();    /*create the client list of the branch*/
    return newBranch;
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

/*---------------SEARCH CLIENT FUNCTIONS-----------*//*
int countClients(client* root, amount balance,int (*cmp_func)(client*,amount)){
	int numberOfClients;
	if(root == NULL)
		return 0;
	numberOfClients = countClients(root->right,balance,cmp_func);
	numberOfClients +=countClients(root->left,balance,cmp_func);
	if(cmp_func(root,balance))
		numberOfClients += 1;
	return numberOfClients;
}

int compareClientsWithBiggerBalance(client* client, amount balance){
	if(client->balance > balance)
		return 1;
	if(client->balance < balance)
		return -1;
	return 0;
}

int compareClientsWithBiggerLoans(client* client, amount balance){
	if(client->debt > client->balance)
		return 1;
	if(client->debt > client->balance)
		return -1;
	return 0;
}

int printClientDetails(client* client,amount s)
{
	printf("Client account number : %d\n",client->accNum);
	printf("Client Balance : %f\n",client->balance);
	return 0;
}

*/
/*DELETE FROM TREE*/


void deleteBranchFields(branch* to_be_deleted)
{
    FREE(to_be_deleted->branchName);
    clearClientTree(to_be_deleted->clientList);
    FREE(to_be_deleted);
    updateNumOfBranches(REMOVE); 	  /* decrease amount of branches in bank*/
}
