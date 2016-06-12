//
//  genericTree.h
//  bankMTM
//
//  Created by Noam Stolero on 6.6.2016.
//  Copyright © 2016 Noam Stolero. All rights reserved.
//

#ifndef genericTree_h
#define genericTree_h

#include <stdio.h>

#endif /* genericTree_h */


/* generic linked list struct*/
typedef struct genLinkedLsits{
    void *data;
    struct genLinkedLsits *next;
}genLinked;


/* generic trees struct */
typedef struct genTrees{
    
    void * data;
    struct genTrees* left;
    struct genTrees* right;

}genTree;

/* compare function DEFINEITONS */
typedef enum{SMALLER=-1, EQUAL=0, GREATER=1}comparison;

/* generic functions definition */
typedef int (*genCmp)(void*,void*); /* compare function*/
typedef void (*genDelete)(void*);   /* delete function */
typedef double (*genValue)(void*);  /* average func */
typedef void (*genPrint)(void*);    /* print func */

/*------------------------GENERIC LINKED LIST--------------------*/

/* merge 2 linked list together */
genLinked* merge_LinkedList(genLinked*,genLinked*);

/* print a linked list */
void print_List(genLinked*, genPrint);

/* free and delete a linked list */
void free_linked_list(genLinked** t,genDelete gDelete);

/* sort a linked list with a certain compare function */
genLinked* sortLinkedList(genLinked* , genCmp );

/*------------------------GENERIC LINKED LIST--------------------*/


/*------------------------GENERIC TREE---------------------------*/
/*create and init a generic tree */
genTree * create_Tree();

/*add a new node to a generic tree */
genTree * add_new_node(genTree*,void*, genCmp);

/* find a node in a generic tree */
genLinked * find_node(genTree*, void*, genCmp);

/* remove a node from tree */
genTree * remove_node(genTree*,void*,genDelete, genCmp);

/* find a node and its parent in a generic tree */
genTree * find_Node_Parent(genTree *,void* ,genTree **,genCmp cmp);

/* generic average function */
double average_key(genTree*,int*, genValue);/*check if pushed*/

/* convert a tree into array */
genTree * tree_to_array(genTree*, int *);

/* print a tree data */
void print_tree(genTree*,genPrint);

/* delet a whole tree */
void free_list(genTree**,genDelete);

/*------------------------GENERIC TREE---------------------------*/





