/* bank project
 Yahel Tsufim 304952898
 Noam Stolero 201581683
 file:main.c
 */

#include "menu.h"


int main(){
    createBank(NULL);
    createBranchList();
    mainMenu();/*menu for testing code*/
    deleteBank();
    check_for_exit();
    printf("Thank you for using our program. Have a good day\n");
    return 0;
    
    
}
