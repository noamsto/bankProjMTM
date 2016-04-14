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
    check_for_exit();
    
    return 0;
    
    
}

void mainMenu(){
	int menu;
	boolean finish=FALSE;
	while(finish == FALSE){
	    printf("\nmain menu:\n"
	           "1: add new branch\n"
	           "2: add new client to branch\n"
	           "3: transaction\n"
	           "4: check info\n"
	           "7: delete \n"
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
	boolean finish=FALSE;
	while(finish == FALSE){
	printf("\n1: for client \n"
		   "2: for branch \n"
		   "3: for bank \n"
		   "9: back to menu\n");
	subMenu = getchar();
	getchar();
	switch (subMenu) {
		case '1':
			deleteClient(NOCHECK);
			break;
		case '2':
			deleteBranch(NOCHECK);
			break;
		case '3':
			deleteBank();
			break;
		case '9':
			finish = TRUE;
			break;
		default:
			break;
		}
	}
}

void infoMenu(){
	int subMenu;
	boolean finish=FALSE;
	while(finish == FALSE){
		printf( "\n1: print bank info\n"
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
			printf( "\n1: deposit money to client\n"
					"2: loan money to client\n"
					"3: biggest balance in bank\n"
					"4: number of clients with bigger loans\n"
					"5: number of clients with bigger loans (rec)\n"
					#ifdef BANK_AHAMELIM
					"6: number of clients with given balance\n"
					#endif
					"7: exit\n");
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
					clientNumberOfBank_print();
					break;
				case '4':
					clientNumberWithBiggerLoansThanBalance();
					break;
				case '5':
					clientNumberWithBiggerLoansThanBalance_rec();
					break;
#ifdef BANK_AHAMELIM
				case '6':
				   printf("Number of clients with given balance: %d\n",clientNumberWithGivenBalance());
				   break;
#endif
				case '7':
					finish=TRUE;
					break;
				default:
					printf("the number is not in the menu.\n try again\n");
					break;
				}
			}
}
