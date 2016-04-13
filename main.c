/* bank project
 Yahel Tsufim 304952898
 Noam Stolero 201581683
 file:main.c
 */

#include "bank.h"
#include <string.h>

void mainMenu();
void deleteMenu();
void infoMenu();
void transactionAndReports();
/*testing code.*/
int main(){
    createBank();
    createBranchList();
    mainMenu();/*menu for testing code*/
    deleteBank();
    check_for_exit();
    
    return 0;
    
    
}

void mainMenu(){
	int menu;
	boolean finish=FALSE;
	while(finish == FALSE){
	    printf("main menu:\n"
	           "1: add new branch\n"
	           "2: add new client to branch\n"
	           "3: transaction\n"
	           "4: check info\n"
	           "7: delete branch/client\n"
	           "8: exit\n");
	        menu = getchar();
	        getchar();
	        switch (menu) {
	            case '1':
	                addNewBranch();
	                break;
	            case '2':
	                addNewClientToBranch();
	                break;
	            case '3':
	                transactionAndReports();
	                break;
	            case '4':
	            	infoMenu();
	                break;
	            case '7':
	            	deleteMenu();
	                break;
	            case '8':
	                finish = TRUE;
	                break;
	            case '9':
	            	printf("Insanity: doing the same thing over and over again\n and expecting different results\n");
	            	break;
	            default:
	                printf("the number is not in the menu.\n try again\n");
	                break;
	        }
	    }
}

void deleteMenu(){
	int subMenu;
	printf("c: for client enter \n"
		   "b: for branch enter \n"
		   "else: back to menu\n");
	subMenu = getchar();
	getchar();
	if(subMenu == 'c')
		deleteClient(NOCHECK);
	if(subMenu == 'b')
		deleteBranch(NOCHECK);
}

void infoMenu(){
	int subMenu;
	boolean finish=FALSE;
	while(finish == FALSE){
		printf( "1: print bank info\n"
				"2: print branch info\n"
				"3: print client info\n"
				"4: back to main menu\n");
		subMenu = getchar();
		getchar();
		switch(subMenu){
			case '1':
				printBankInfo();
				break;
			case '2':
				printBranchInfo();
				break;
			case '3':
				printClientInfo();
				break;
			case '4':
				finish=TRUE;
				break;
			default:
				printf("the number is not in the menu.\n try again\n");
				break;
			}
		}
}

void transactionAndReports(){
	int subMenu;
		boolean finish=FALSE;
		while(finish == FALSE){
			printf( "1: deposit money to client\n"
					"2: loan money to client\n"
					"3: biggest balance in bank\n"
					"4: biggest balance in bank (rec)\n"
					"5: number of clients with bigger loans\n"
					"6: number of clients with bigger loans (rec)\n"
					"7: number of clients with given balance\n"
					"8: exit\n");
			subMenu = getchar();
			getchar();
			switch(subMenu){
				case '1':
				   depositeMoneyToClientAccount();
				   break;
				case '2':
				   loanToClient();
				   break;
				case '3':
					//clientNumberOfBank();
					break;
				case '4':
					//clientNumberOfBank_REC(client *head, int *biggestBalance);
					break;
				case '5':
					clientNumberWithBiggerLoansThanBalance();
					break;
				case '6':
					clientNumberWithBiggerLoansThanBalance_rec();
					break;
				case '7':
				   printf("Number of clients with given balance: %d\n",clientNumberWithGivenBalance());
				   break;
				case '8':
					finish=TRUE;
					break;
				default:
					printf("the number is not in the menu.\n try again\n");
					break;
				}
			}
}
