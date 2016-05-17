/* bank project
 Yahel Tsufim 304952898
 Noam Stolero 201581683
 file:matam.h
 */



#ifndef MATAM_H
#define MATAM_H

#include <stdio.h>
#include <stdlib.h>

void *checked_malloc(unsigned int); //allocating memory, checking if succeded and incremneting counter.
void checked_free(void *);   //free alocated memory and decrement counter.
void check_for_exit();      //print a message if any allocated memory was nit freed.
char* str_dup(const char*); //str dup function working with upper functions.


//Macro for upper functions.
#define ALLOC(typ,no) ((typ *) checked_malloc(sizeof(typ)*(no)))
#define FREE(ptr) checked_free(ptr)
#endif  /* MATAM_H*/
