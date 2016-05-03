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
static branch* branchRoot;

/*--------------------LOCAL FUNCTION DECLERATION--------*/
void initBranch(branch*);/*init branch struct*/
branch *createBranch();/* create a new branch. get information from user */
void insertBranch(branch**,branch*);/* insert branch to tree. recursive function */
void updateCurrentClient(branchID ,addremove);/*update amount of clients in branch*/
boolean deleteBranchFromTree(branch* ,branchID);
branch *replaceBranch(branch* to_replace);/* replace a member in the tree with a different member*/
void deleteBranchFields(branch*);/* delete all the fields of a certain branch */
branch* findSmallest(branch*);/* finds and returns the smallest member of a certain tree  */
boolean addClientConditions(); /* check if possible to add new client to the bank */
branch* findBranch(branch* , branchID );
branchID getBranchID(availble checkif);/* get branch ID from user, including check if the id is already in use*/
int getTime(char*); /*get hours from user.*/
int isBranchFull(branch *);/*check if branch is full (has more room from clients)*/


/*----------------------------------------------CODE BEGIN'S HERE--------------------------------------------*/

branch* createBranchList()
{
	branchRoot = ALLOC(branch,1);
    initBranch(branchRoot);
    return branchRoot;
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
    insertBranch(&branchRoot,newBranch);
    updateNumOfBranches(ADD);/*update branch list on addition of bank*/
    return SUCCESS;
}


/*    NEED TO WAIT FOR CLIENT.H , CLIENT.C UPDATE*/
client* createBranchClientList()
{
	return NULL;
}

try addNewClientToBranch()
{
    /*prepare data to receive client*/
    branch *temp;
    client *newClient;
    boolean check;
    
    printf("Starting new client registry:\n");
    check=addClientConditions();
    if(check==FALSE)
    	return FAIL;
    temp = getBranch(getBranchID(EXIST));
    
    if (isBranchFull(temp)) {
        printf("the branch is full\n");
        return FAIL;
    }
    newClient = getDetailsFromUser(temp->brID,temp->bankName);
    
    /*inform branch and bank on new client*/
    temp->currentClients++;
    addNewClientToBank(newClient);
    temp->clientList = insertClientTree(temp->clientList,newClient);
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


//#ifdef BANK_AHAMELIM
int clientNumberWithGivenBalance()
{
    amount balance;
    branch *tempBranch;
    if(getNumOfBranches()==0){
        printf("no branches\n");
        return 0;
    }
    tempBranch = getBranch(getBranchID(EXIST));
    getDouble(&balance, "please enter balance:\n");

    return  1 ;//countClients(tempBranch->clientList,balance/*,pointer to func*/);
}
//#endif
void clientNumberWithBiggerLoansThanBalance_print(){
	int clientNum_rec,clientNum_iter;
	branch *tempBranch;
	branchID brID;
	brID = getBranchID(EXIST);
	tempBranch = getBranch(brID);
	//clientNum_iter = clientNumberWithBiggerLoansThanBalance(CLIENTSHEAD(tempBranch));
	//clientNum_rec = clientNumberWithBiggerLoansThanBalance_rec(CLIENTSHEAD(tempBranch));
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
    temp = getBranch(id);
    /*delete all clients*/
    updateBranchBalance(id,0,REMOVE);
    return SUCCESS;
}

try deleteBranchClient(branchID brID,accountNum acc)
{
    /*set variables*/
    client* tempClient=NULL;
    branch* tempBranch;

    tempBranch=getBranch(brID);
    if ((tempClient = findClient(tempBranch->clientList,acc)) == NULL ) {
           printf("client not in branch.\n");/*if the  client is not in branch*/
           return CLIENTNOTFOUND;
       }
    /*update branch on leaving costumer*/
    updateBranchBalance(tempClient->brID,tempClient->balance, REMOVE);
    if(tempClient->debt>0)
    		updateBranchLoan(brID,REMOVE);
    tempBranch->currentClients--;
    //deleteClient(tempBranch->clientList,tempClient);
    return SUCCESS;
}


try  deleteBranch(branchID brID)
{
    branch *deleteB=NULL;

    if(getNumOfBranches()==0){
    	printf("There are no active branches\n");
    	return SUCCESS;
    }

    if(brID==NOCHECK)
        brID=getBranchID(EXIST);/*receive branch from user*/
    
    //deleteBranchFromTree(branchRoot,deleteB);
    updateNumOfBranches(REMOVE);  /* decrease amount of branches in bank*/
    return SUCCESS;
}

/*boolean deleteBranchFromTree(branch* root,branchID removed_branch)
{
	if(root == NULL)
		return FALSE;
	if(deleteBranchFromTree(root->right,removed_branch) == TRUE)
		return TRUE;
	if(deleteBranchFromTree(root->left,removed_branch) == TRUE)
		return TRUE;
	if(root->right->brID == removed_branch){
		root->right = repalceBranch(root->right);
		return TRUE;
	}
	if(root->left->brID == removed_branch){
		root->left = repalceBranch(root->left);
		return TRUE;
	}
	return FALSE;
}*/


void deleteBranchFields(branch* deleted_Branch)
{
	deleteAllBranchClients(deleted_Branch->clientList);
    FREE(deleted_Branch->branchName);
    FREE(deleted_Branch);
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


branch* getBranch(branchID brID)
{
    return findBranch(branchRoot,brID);
}



client* getBranchClient(accountNum acc, branchID brID)
{
    branch *tempBranch=NULL;
    tempBranch=getBranch(brID);
    return getClient(tempBranch->clientList,acc);
}



/*---------------HELP SEARCH IN TREE BRANCH-------------------*/
boolean checkBranchID(branchID brID)
{
    if(findBranch(branchRoot,brID) != NULL)
    	return TRUE;
    return FALSE;
}

branch* findBranch(branch* root, branchID brID){
	if(root == NULL)
		return NULL;
	if(root->brID == brID)
		return root;
	if(root->brID > brID)
		return findBranch(root->left,brID);
	return findBranch(root->right,brID);

}

void clearBranchTree(branch* root)
{
	if(root == NULL)
		return;
	clearBranchTree(root->left);
	clearBranchTree(root->right);
	deleteBranchFields(root);
	FREE(root);
	updateNumOfBranches(REMOVE);  /* decrease amount of branches in bank*/
}

branch *replaceBranch(branch* root)/*replace the current junction with the wanted member of the tree*/
{
	if(root->right != NULL){
		branch *to_replace;
		to_replace = findSmallest(root->right);
		to_replace->left = root->left;
		to_replace->right = root->right;
		deleteBranchFields(root);
		return to_replace;
	}
	deleteBranchFields(root);
	return root->right;
}

branch* findSmallest(branch* root)/*finds and returns the smallest member of the tree*/
{
	if(root->left == NULL)
		return root;
	else
		return findSmallest(root->left);

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


/*-----------------------------INFORMATION FUNCTIONS-------------------*/
void printBranchInfo()
{
	branchID brID;
	branch *tempBranch;
	brID = getBranchID(EXIST);
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
    newBranch->brID=getBranchID(NOTEXIST);
    newBranch->openTime = getTime("please enter opening time (between 0-23)\n");
    newBranch->closeTime = getTime("please enter closing time (between 0-23)\n");
    newBranch->clientList=createBranchClientList();    /*create the client list of the branch*/
    return newBranch;
}

void insertBranch(branch** root,branch* new)/* insert branch to tree. recursive function */
{
	if(*root == NULL){
		*root = new;
		return;
	}
	if((*root)->brID > new->brID)
		insertBranch(&((*root)->left),new);
	else
		insertBranch(&((*root)->right),new);
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
    brancInit->left = NULL;
    brancInit->right = NULL;
}

