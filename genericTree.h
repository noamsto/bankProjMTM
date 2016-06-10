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



typedef struct genLinkedLsits{
    void *data;
    struct genLinkedLsits *next;
}genLinked;


typedef struct genTrees{
    
    void * data;
    struct genTrees* left;
    struct genTrees* right;

}genTree;

typedef enum{SMALLER=-1, EQUAL=0, GREATER=1}comparison;

typedef int (*genCmp)(void*,void*);
typedef void (*genDelete)(void*);
typedef double (*genValue)(void*);
typedef void (*genPrint)(void*);

/*------------------------GENERAL LINKED LIST--------------------*/

genLinked* merge_LinkedList(genLinked*,genLinked*);

genLinked * find_node(genTree*, void*, genCmp);

/*------------------------GENERAL LINKED LIST--------------------*/

genTree * create_Tree();

genTree * add_new_node(genTree*,void*, genCmp);

genTree * remove_node(genTree*,void*,genDelete, genCmp);


genTree * find_Node_Parent(genTree *,void* ,genTree **,genCmp cmp);

double average_key(genTree*,int*, genValue);/*check if pushed*/

genTree * tree_to_array(genTree*);

void print_List(genLinked*, genPrint);

void free_list(genTree**,genDelete);

void free_linked_list(genLinked** t,genDelete gDelete);




