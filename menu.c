/*
 * menu.c
 *
 *  Created on: Apr 14, 2016
 *      Author: yali
 */

#include "menu.h"

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
					clientNumberOfBank_print();
					break;
				case '4':
					clientNumberWithBiggerLoansThanBalance_print();
					break;
#ifdef BANK_AHAMELIM
				case '5':
				   printf("Number of clients with given balance: %d\n",clientNumberWithGivenBalance());
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
