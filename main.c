/* bank project
 Yahel Tsufim 304952898
 Noam Stolero 201581683
 file:main.c
 */

#include "menu.h"

/*testing tree to array */
void test_treeToArray();



int main(){
    createBank(NULL);
    
#ifdef TEST /*create 2 branches and 3 clients for test purposes */
    printf("***_TEST MODE_***\n\n");
    
    addNewBranch();
    addNewBranch();
    addNewClientToBranch();
    addNewClientToBranch();
    addNewClientToBranch();
    printf("\n");
    test_treeToArray();
#endif
    
    mainMenu();/*menu for testing code*/
    deleteBank();
    check_for_exit();
    printf("Thank you for using our program. Have a good day\n");
    return 0;
    
    
}

/* test tree to array function with bank clients tree */
void test_treeToArray(){
    genTree *t=NULL;
    int len=0,i=0;
    t=*getBankClientRoot();
    t=createArrayFromTree(t, &len);
    
    for (i=0; i<len; i++){
        printClientInfo(t[i].data);
    }
    FREE(t);
    
    
}

