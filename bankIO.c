/*
 * bankIO.c
 *
 *  Created on: Jun 18, 2016
 *      Author: yali
 */

#include "bankIO.h"

FILE* target;





/* convert a client struct to a clientString struct */
clientString* clientToString(client* c){
    clientString *cString=NULL;
    ALLOC(clientString, 1); /* allocate a new client String struct.*/
    
    if (!c)
        return NULL;
    
    
    /* copy relevant fields */
    cString->familyName =str_dup(c->surname);
    cString->clientID= str_dup(c->cID);
    cString->clientAcc=c->accNum;
    return cString;
}


/* copy clientString to a another */
clientString* copyClientStings(clientString* source){
    clientString *target=NULL;
    ALLOC(clientString, 1); /* allocate a new client String struct.*/
    if (!source)
        return NULL;
    
    /* copy relevant fields */
    target->clientAcc=source->clientAcc;
    target->clientID=str_dup(source->clientID);
    target->familyName=str_dup(source->familyName);
    return target;
}


/* open file for read or write purposes. */
try openFile(char*path ,char* restrictions){
    
    if (target) /*if file was already open close it */
        closeFile();
    
    target=fopen(path, restrictions);   /* open file with relevant restrictions */
    if (target==NULL)
        return FAIL;
    return SUCCESS;
}
