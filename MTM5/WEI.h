/*  WEI.h
Yahel Tsufim 304952898
Noam Stolero 201581683
*/

#ifndef WEI_h
#define WEI_h

/*number struct*/
typedef struct numbers{
    double n;   /*n holds the actual number*/
    struct numbers next*;   /*for LinkedList*/
}number;

/*vertex struct*/
typedef struct vertices{
    number x;   /* X Coordinate */
    number y;   /* Y Cooirdinate */
    char* name; /* vertex name */
    vertices *next; /*for LinkedList*/
}vertex;

/*WEI struct*/
typedef struct weis{
    number* numList;    /*number list*/
    vertex* verList;    /*vertex list*/
}wei;



wei* createWei();   /*create and init wei struct*/

number* createNumber(); /*create and init a number struct*/

void addNumber(number*, wei*); /*add a number to WEI struct*/


int addVertex(number*,number*, wei*);   /* add a vertex to WEI struct */

int coLinear(wei*);    /* check if three vertices in the same WEI are  colinear */

double incline(vertex*,vertex*);    /* check the incline of two vertices in the same WEI */

vertex* isCoordinate();     /* get a number from the user and return the amount of vertices which contains (x or y) the number */

void deleteWei(wei*); /* delete WEI */



#endif /* WEI_h */
