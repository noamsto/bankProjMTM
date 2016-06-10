/* bank project
 Yahel Tsufim 304952898
 Noam Stolero 201581683
 file:menu.c
 */

#include "menu.h"

/*testing code*/
void mainMenu(){
	int menu;
	boolean finish=FALSE;
	while(finish == FALSE){
	    printf("\nmain menu:\n"
	           "1: add/delete menu\n"
	           "2: transaction\n"
	           "3: check info\n"
	           "9: exit\n");
	        menu = getchar();
	        getchar();
	        switch (menu) {
	            case '1':
	            	add_Delete_Menu();
	                break;
	            case '2':
	                transactionAndReports();
	                break;
	            case '3':
	            	infoMenu();
	                break;
	             case '9':
	                finish = TRUE;
	                break;
	             default:
	                printf("the number is not in the menu.\n try again\n");
	                break;
	        }
	    }
}

/*add or delete client, branch menu.*/
void add_Delete_Menu(){
	int subMenu;
	boolean finish=FALSE;
	while(finish == FALSE){
	printf("~ADD/DELETE MENU~:\n"
		   "1: add branch \n"
		   "2: add client \n"
		   "3: delete branch\n"
		   "4: delete client\n"
		   "9: back to menu\n");
	subMenu = getchar();
	getchar();
	switch (subMenu) {
		case '1':
			addNewBranch();
			break;
		case '2':
			addNewClientToBranch();
			break;
		case '3':
			deleteBranch(NOCHECK);
			break;
		case '4':
			deleteClient(NOCHECK);
			break;
		case '9':
			finish = TRUE;
			break;
		default:
			break;
		}
	}
}

/* information about branch client or bank menu*/
void infoMenu(){
	int subMenu;
	boolean finish=FALSE;
	while(finish == FALSE){
		printf( "\n1: print bank info\n"
				"2: print branch info\n"
				"3: print client info\n"
				"4: Find client\n"
				"9: back to main menu\n");
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
				printClientInfo(NULL);
				break;
			case '4':
				findClient();
				break;
			case '9':
				finish=TRUE;
				break;
			default:
				printf("the number is not in the menu.\n try again\n");
				break;
			}
		}
}

/*transcation and reports of clients.*/
void transactionAndReports(){
	int subMenu;
		boolean finish=FALSE;
		while(finish == FALSE){
			printf( "\n1: deposit money to client\n"
					"2: loan money to client\n"
					"3: number of clients with bigger loans\n"
					"4: print client account and balance\n"
					#ifdef BANK_AHAMELIM
					"5: number of clients with given balance\n"
					#endif
					"9: back to main menu\n");
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
					//clientNumberWithBiggerLoansThanBalance();
					break;
				case '4':
					//printClientAccountsNumberAndBalance();
				   break;
#ifdef BANK_AHAMELIM	/*hidden menu for bank the new bank*/
				case '5':
					//dclientNumberWithGivenBalance();
					break;
#endif
				case '9':
					finish=TRUE;
					break;
				default:
					printf("the number is not in the menu.\n try again\n");
					break;
				}
			}
}
