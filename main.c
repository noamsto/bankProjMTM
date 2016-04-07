/* bank project
 Yahel Tsufim 304952898
 Noam Stolero 201581683
 file:main.c
 */

#include "bank.h"
#include <string.h>

/*testing code.*/
int main(){
    int menu;
    boolean finish=FALSE;
    createBank();
    createBankClientList();
    createBranchList();
    while(finish == FALSE){
    printf("main menu:\n"
           "1: add new branch\n"
           "2: add new client to branch\n"
           "3: deposit money to client\n"
           "4: loan to client\n"
           "5: client with given balance\n"
           "6: delete client\n"
           "7: delete branch\n"
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
                depositeMoneyToClientAccount();
                break;
            case '4':
                loanToClient();
                break;
            case '5':
                printf("Number of clients with given balance: %d\n",clientNumberWithGivenBalance());
                break;
            case '6':
                deleteClient(NOCHECK);
                break;
            case '7':
                deleteBranch(NOCHECK);
                break;
            case '8':
                finish = TRUE;
                break;
            default:
                printf("the number is not in the menu.\n try again\n");
                break;
        }
    }
    deleteBank();
    check_for_exit();
    
    return 0;
    
    
}
