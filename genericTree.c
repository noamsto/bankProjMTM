//
//  genericTree.c
//  bankMTM
//
//  Created by Noam Stolero on 6.6.2016.
//  Copyright © 2016 Noam Stolero. All rights reserved.
//


#include "common.h"

/* macro for swapping data */
#define SWAP(D1,D2,TEMP) TEMP=D1->data; \
                    D1->data=D2->data; \
                    D2->data=TEMP \




/*create tree node*/
genTree * create_Tree(){
    
    genTree *temp;
    
    temp=ALLOC(genTree, 1);
    temp->data=NULL;
    temp->left=NULL;
    temp->right=NULL;
    return temp;
}


/*add node to tree*/
genTree * add_new_node(genTree* t,void* data,genCmp cmp){
    comparison c;
    if(!t){
        t=create_Tree();
        t->data=data;
        return t;
    }
    
    c=cmp(t->data,data); /* call designated compare function */
    if (c==GREATER){
        t->left=add_new_node(t->left, data, cmp);
    }else{
        t->right=add_new_node(t->right, data, cmp);
    }
    
    return t;
}


/* find biggest node in given tree */
genTree * findBiggestNode(genTree* t){
  
    while (t!=NULL && t->right!=NULL){
        t=t->right;
    }
    return t;
}

/* find smallestNode in given tree */
genTree * findSmallestNode(genTree* t){
    
    while (t!=NULL && t->right!=NULL){
        t=t->left;
    }
    return t;
}


/* delete a leaf from tree */
genTree * deleteLeaf(genTree *t, genDelete gDelete){
    gDelete(t->data);
    FREE(t);
    return NULL;
}

/* remove a node from tree */
genTree * remove_node(genTree* t, void* data, genDelete gDelete, genCmp cmp){
    genTree* toSwap, *toDelete, *parent=NULL;
    void *temp;
    
    if (!t){
        return NULL;
    }
    
    toDelete=find_Node_Parent(t, data,&parent, cmp);    /*find node and its parent */
    
    if (toDelete==NULL) /* no node found */
        return NULL;
    
    if(toDelete->left==NULL && toDelete->right!=NULL){
        toSwap=findSmallestNode(toDelete->right); /*find smallest node in right tree */
        SWAP(toDelete, toSwap, temp); /* swap smallest node with the one to delete*/
        /* call this function again on right tree */
        toDelete->right=remove_node(toDelete->right,data, gDelete, cmp);
        return toDelete;
    }
    else if (toDelete->left!=NULL){
        toSwap=findBiggestNode(toDelete->left); /*find biggest node in left tree */
        SWAP(toDelete, toSwap, temp); /* swap biggest node with the one to delete*/
        /* call this function again on right tree */
        toDelete->left=remove_node(toDelete->left, data,gDelete, cmp);
        return toDelete;
    }
    
    /* leaf case */
    if (parent){ /*if there is a parent */
        if (parent->left==toDelete)
            parent->left=NULL;
        else
            parent->right=NULL;
        deleteLeaf(toDelete, gDelete);
        return t;
    }
    /* root case */
    deleteLeaf(toDelete, gDelete);
    return NULL;
}





/*find a node and his parent*/
genTree * find_Node_Parent(genTree * t ,void* data ,genTree ** parent,genCmp cmp){
    comparison c;
    
    /* check if a tree is given */
    if (!t){
        if (parent)
            *parent=NULL;
        return NULL;
    }
    
    c=cmp(t->data,data); /*compare using designated compare function */
    
    /* search the tree in 'pre order' method */
    if (c==EQUAL){
        return t;
    }
    if (parent) /*if a parent pointer provided, update it */
        *parent=t;
    if (c==SMALLER)
        return find_Node_Parent(t->right, data, parent, cmp);
    else
        return find_Node_Parent(t->left, data, parent, cmp);
}


/* print a linked list with a generic print function */
void print_List(genLinked* t, genPrint print)
{
	if(!t)
		return;
    print(t->data); /*use given print function */
    print_List(t->next, print); /* recursivley continue */
}


/* print a tree database with generic print function */
void print_tree(genTree* t,genPrint print)
{
	if(!t)
		return;
	print_tree(t->left,print);
	print(t->data);
	print_tree(t->right,print);
}




/* recursively calculate average using a given function */
double average_key(genTree* t,int* amount, genValue val){
	int leftAm=0,rightAm=0;
	double leftAv=0,rightAv=0,myAv;
	if(!t){
		*amount = 0;
		return 0;
	}
	leftAv = average_key(t->left,&leftAm,val); /*first calculate left tree */
	rightAv = average_key(t->right,&rightAm,val);   /*then right tree */
	*amount = leftAm + rightAm + 1; /* count the amount of nodes */
	myAv = val(t->data);
	myAv += (leftAv * leftAm) + (rightAv * rightAm); /* calculate overall value */
	return (myAv/ *amount); /*return the average */
}




/*delete all tree*/
void free_list(genTree** t,genDelete gdelete)
{
    if(!*t)
        return;
    free_list(&(*t)->left,gdelete);
    free_list(&(*t)->right,gdelete);
    gdelete((*t)->data);
    FREE(*t);
    *t=NULL;
    
}

/* delete a generic linked list and free it */
void free_linked_list(genLinked** t,genDelete gDelete)
{
    if(!*t)
        return;
    free_linked_list(&(*t)->next, gDelete);
    FREE(*t);
    *t=NULL;
    
}





/* create linked list from a certain data node */
genLinked * find_node(genTree* t, void* data, genCmp cmp)
{
    genLinked *left, *right;
    if(!t)
        return NULL;
    
    left=find_node(t->left, data, cmp); /*first get a linked list for left tree*/
    right=find_node(t->right, data, cmp);   /*then for right tree */
    
    if(cmp(t->data,data)==EQUAL){   /*check current node */
        genLinked *me;
        me = ALLOC(genLinked, 1);
        me->data = t->data;
        me->next=NULL;
        right = merge_LinkedList(me,right); /*merge current node with right tree */
    }
    
    return merge_LinkedList(left,right); /* return merged left tree and right tre */
    
}


/* merge two linked list */
genLinked* merge_LinkedList(genLinked* a,genLinked* b)
{
    genLinked* new=a;
    if(a==NULL)
        return b;
    if(b==NULL)
        return a;
    while(a->next!=NULL){
        a=a->next;
    }
    a->next=b;
    return new;
}


/* insert a node in a sorted list */
genLinked* putSorted (genLinked *l, genLinked* node, genCmp cmp){
    genLinked *prev=NULL, *seek;
    seek =l;
    
    if (!seek){
        return node;
    }
    if (!node)
        return l;
    
    while (seek!=NULL && cmp(node->data, seek->data)==GREATER ){
        prev=seek;
        seek=seek->next;
    }
    node->next=seek;
    if (prev){
        prev->next=node;
        return l;
    }
    return node;

}



/*sort linked list */

genLinked* sortLinkedList(genLinked* l, genCmp cmp){

    genLinked *next;
    if (!l)
        return NULL;
    
    next=sortLinkedList(l->next, cmp);
    
    l=putSorted(next, l, cmp);
    return l;
}



/* count the nodes of a tree */
int count_tree(genTree *t){
    int l_count, r_count;
    if (!t)
        return 0;
    
    l_count= count_tree(t->left);
    r_count= count_tree(t->right);
    return l_count+r_count+1;
    
}


/* copy each node to the array */
void copy_nodes(genTree *t, genTree **a){
    if (!t || !*a)
        return;
    
    copy_nodes(t->left, a);
    ((*a)++)->data=t->data; /* only if a value is added, increase the "index" */
    copy_nodes(t->right, a);
}


/* function create an array from a tree */
genTree* tree_to_array(genTree* t, int* len){
    int size;
    genTree *array=NULL, *arrayStart;
    size=count_tree(t);
    
    array=ALLOC(genTree, size);
    arrayStart=array;
    copy_nodes(t, &array);
    *len=size;
    return arrayStart;
}





