#ifndef MATAM_H
#define MATAM_H

#include <stdio.h>
#include <stdlib.h>

char *checked_strdup (char *);
void *checked_malloc(unsigned int);
void checked_free(void *);
void check_for_exit();

#define ALLOC(typ,no) ((typ *) checked_malloc(sizeof(typ)*(no)))
#define FREE(ptr) checked_free(ptr)
#define STRDUP(string) (checked_strdup (string))
#endif  /* MATAM_H*/
