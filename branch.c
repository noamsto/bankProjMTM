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
/*testing purpose*/
#ifdef TEST
static char testNameB[2]= "a\0";
static branchID testBID = 1;
#endif
/*testing purpose*/

static genTree* branchRoot;

/*--------------------LOCAL FUNCTION DECLERATION--------*/

void updateCurrentClient(branchID ,addremove);/*update amount of clients in branch*/
boolean addClientConditions(); /* check if possible to add new client to the bank */
branch* findBranch(genTree* , branchID );/* return branch pointer according to branch ID */
int isBranchFull(branch *);/*check if branch is full (has more room from clients)*/

/* DATA FROM USER FUNCTIONS */
branchID getBranchID(availble checkif);/* get branch ID from user, including check if the id is already in use*/
int getTime(char*); /*get hours from user.*/
branch *createBranch();/* create a new branch. get information from user */

/* GENERAL BRANCH FUNCTIONS */
void initBranch(branch*);/*init branch struct*/
void deleteBranchFields(branch*);/* delete all the fields of a certain branch */
comparison compare_Branch(branch*,branch *);
int countClients(genTree* , amount* ,genCmp);
int compareClientsWithBiggerBalance(client* client, amount *balance);/* check if a client has more then requested balance */
int compareClientsWithBiggerLoans(client* client, amount *balance);/* check if a client has bigger loan then balance */
void printClientDetails(client* client);/* print client details (account number and balance) */
double getNumOfClientsInBranch(branch* b);/* recieve how many clients are in specific branch */
branch* chooseBranch();/* allows the user to choose a branch and gets the pointer to the branch */


/*----------------------------------------------CODE BEGIN'S HERE--------------------------------------------*/

/*----------CREATE LIST FUNCTIONS-------------*/

void createBranchTree()
{
	branchRoot = NULL;;
}


genTree* createBranchClientTree()
{
	return NULL;
}

/*----------ADD NEW BRANCH FUNCTIONS-------------*/

try addNewBranch()
{
    /*put the new branch in the end of the branch list*/
    branch* newBranch;

    if(getNumOfBranches() == N){
        printf("bank has maximum number of branches.\n");
        return MAX_BANK_REACHED;
    }
    newBranch = createBranch();
    branchRoot = add_new_node(branchRoot,newBranch,(genCmp)(&compare_Branch));
    updateNumOfBranches(ADD);/*update branch list on addition of bank*/
    return SUCCESS;
}


branch* createBranch()/* create branch, receive data from user */
{
	branch *newBranch;
	printf("Add new branch start:\n");
    newBranch = ALLOC(branch,1);
	initBranch(newBranch);

#ifdef TEST
	newBranch->bankName = getBankName();
    newBranch->branchName=str_dup(testNameB);
    testNameB[0]++;
    newBranch->brID=testBID++;
    newBranch->openTime=1;
    newBranch->closeTime=1;
    newBranch->clientList=createBranchClientList();
#else

    /*receive data from user*/
	getName(&newBranch->branchName,MAXNAME,"please enter branch name:\n");
    newBranch->bankName = getBankName();
    newBranch->brID= getBranchID(NOTEXIST);
    newBranch->openTime = getTime("please enter opening time (between 0-23)\n");
    newBranch->closeTime =getTime("please enter closing time (between 0-23)\n");
    newBranch->clientList=createBranchClientList();    /*create the client list of the branch*/

#endif


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

/*----------ADD NEW CLIENT TO BRANCH FUNCTIONS-------------*/

try addNewClientToBranch()
{
    /*prepare data to receive client*/
    branch *tempBranch;
    client *newClient;
    boolean check;

    printf("Starting new client registry:\n");
    check=addClientConditions();
    if(check==FALSE)
    	return FAIL;
#ifdef TEST
    {
    branchID brID;
    brID=1;  /* make branch id 1 for test purposes */
    tempBranch = getBranch(brID);
    }
#else
    if((tempBranch = chooseBranch())==NULL)
        return FAIL;
#endif


    if (isBranchFull(tempBranch)) {
        printf("the branch is full\n");
        return FAIL;
    }
    newClient = getDetailsFromUser(tempBranch->brID,tempBranch->bankName);


    /*inform branch and bank on new client*/
    tempBranch->currentClients++;
    addNewClientToBank(newClient);
    tempBranch->clientList = add_new_node(tempBranch->clientList,newClient,(genCmp)(&cmpClient));
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


/***************** BRANCH FUNCTIONS FOR GENERAL PURPOSES *****************/

comparison comp_Branch_to_ID(branch* a, branchID* b){
	if(a->brID > *b)
		return GREATER;
	if(a->brID < *b)
		return SMALLER;
	return EQUAL;
}

comparison compare_Branch(branch* a,branch *b)
{
	if(a->brID > b->brID)
		return GREATER;
	if(a->brID < b->brID)
		return SMALLER;
	return EQUAL;
}


double getNumOfClientsInBranch(branch* b)
{
	return b->currentClients;
}


/* find a clients in a certain branch by ID or balance */
void findClientInGivenBranch (){
    branch *b;
    b=getBranch(getBranchID(EXIST));
    if (b==NULL)
        printf("Action canceled.\n");
    else
        if(b->currentClients>0)
            findClient(b->clientList);
        else
            printf("Selected branch have no clients.\n");
}


void deleteBranchFields(branch* to_be_deleted)
{
    FREE(to_be_deleted->branchName);
    /*delete!!!!   clearClientTree(to_be_deleted->clientList);*/
    free_list(&to_be_deleted->clientList, (genDelete)&freeClient);
    FREE(to_be_deleted);
}


comparison compareClientsWithBiggerBalance(client* client, amount *balance){
	if(client->balance > *balance)
		return GREATER;
	if(client->balance < *balance)
		return SMALLER;
	return EQUAL;
}

comparison compareClientsWithBiggerLoans(client* client, amount *balance){
	if(client->debt > client->balance)
		return GREATER;
	if(client->debt > client->balance)
		return SMALLER;
	return EQUAL;
}

void printClientDetails(client* client)
{
	printf("Client account number : %d\n",client->accNum);
	printf("Client Balance : %f\n",client->balance);
}

branch* chooseBranch(){
	branchID brID;
	brID = getBranchID(EXIST);
	if(brID == CANCEL){
	   printf("Aborted the action\n");
	return NULL;
	}

	return getBranch(brID);
}


/*----------QUERY FUNCTIONS-------------*/


#ifdef BANK_AHAMELIM
void clientNumberWithGivenBalance()
{
	int numberOfClients;
    amount balance;
    branch *tempBranch;
    if(getNumOfBranches()==0){
        printf("no branches\n");
        return ;
    }
    if((tempBranch = chooseBranch())==NULL)
        return;
    getDouble(&balance, "please enter balance:\n");
    numberOfClients = countClients(tempBranch->clientList,&balance,(genCmp)&compareClientsWithBiggerBalance);
    printf("the number of clients with : %f\n  in balance is :%d\n",balance,numberOfClients);
}
#endif

void printClientAccountsNumberAndBalance()
{
	branch *tempBranch;
    if(getNumOfBranches()==0){
        printf("no branches\n");
        return ;
    }
    if((tempBranch = chooseBranch())==NULL)
        return;
    print_tree(tempBranch->clientList,(genPrint)&printClientDetails);

}
void clientNumberWithBiggerLoansThanBalance()
{
	int numberOfClients;
    branch *tempBranch;
    if(getNumOfBranches()==0){
        printf("no branches\n");
        return ;
    }
    if((tempBranch = chooseBranch())==NULL)
    	return;
    numberOfClients = countClients(tempBranch->clientList,NOCHECK,(genCmp)&compareClientsWithBiggerLoans);
    printf("amount of clients with bigger loans then balance : %d",numberOfClients);
}


void averageNumberOfAccountsInBranches()
{
	int numOfBranches=0;
	double clientsAverage=0;
	numOfBranches = average_key(branchRoot,&numOfBranches,(genValue)&getNumOfClientsInBranch);
	printf("number of branches : %d\n"
			"Average number of clients in single branch : %f\n",
			numOfBranches,clientsAverage);
}

int isBranchFull(branch *tempBranch)
{
    if (tempBranch->currentClients<=MAXBRANCHCLIENT) {
        return FALSE;
    }
    return TRUE;
}

/*----------DELETE FUNCTIONS-------------*/

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
    tempBranch->clientList = remove_node(tempBranch->clientList,tempClient,(genDelete)&freeClient,(genCmp)(&cmpClient));
    tempBranch->currentClients--;
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
    	if((tempBranch = chooseBranch())==NULL)
    	    return FAIL;
    }else{
    tempBranch = getBranch(brID);
    }
    branchRoot = remove_node(branchRoot,(void*)tempBranch,(genDelete)(&deleteBranchFields),(genCmp)(&compare_Branch));
    updateNumOfBranches(REMOVE);  /* decrease amount of branches in bank*/
    return SUCCESS;
}

void deleteAllBranches()
{
    free_list(&branchRoot, (genDelete)&deleteBranchFields);
}

/*------------------UPDATE BRANCH FUNCTIONS-------------------*/

try updateBranchBalance(branchID brID, amount am,addremove remove)
{
    branch *tempBranch;

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





/*----------------RECIEVE DATA FROM USER---------------------*/

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

void printBranchInfo()
{

	branch *tempBranch;
	if((tempBranch = chooseBranch())==NULL)
	    return;
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



/*---------------SEARCH FUNCTIONS-----------*/
int countClients(genTree* root, amount* balance,genCmp cmp){
	int numberOfClients;
	comparison c;
	if(root == NULL)
		return 0;
	numberOfClients = countClients(root->right,balance,cmp);
	numberOfClients +=countClients(root->left,balance,cmp);
	c = cmp(root->data,balance);
	if(balance){
		if(c==EQUAL)
			numberOfClients += 1;
	}
	else{
		if(c==GREATER)
			numberOfClients += 1;
	}
	return numberOfClients;
}


boolean checkBranchID(branchID brID)
{
    if(findBranch(branchRoot,brID) != NULL)
    	return TRUE;
    return FALSE;
}



branch* findBranch(genTree* root, branchID brID){
    genTree* b;
    b=find_Node_Parent(branchRoot,&brID,NOCHECK,(genCmp)&comp_Branch_to_ID);
    if (b) {
        return (branch*)b->data;
    }
    return NULL;

}


client* getBranchClient(accountNum acc, branchID brID)
{
    branch *tempBranch=NULL;
    tempBranch=getBranch(brID);
    return getClient(tempBranch->clientList,acc,NULL);
}

branch* getBranch(branchID brID)
{
    return findBranch(branchRoot,brID);
}
