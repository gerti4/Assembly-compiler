#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "GlobalVar.h"

/*Program defintions*/
#define MAX_LABEL_LENGTH 32
#define MAX_ROW_LENGTH 82

#define True 1
#define False 0
#define Eror -1


/*Indicates for other functions that it is First scan.*/
#define FIRST_SCAN 1


/*	Global varaible:
----------------------------------------------------------------------*/
Line L;											/*Stores data from assembly Line*/
char* curr_row;							/*Gets an assembly row*/
extern long IC;							/*Instruction Counter*/



/*	Function declaration:
--------------------------------------------------------------------*/
int isEmptyRow(char*);
int isCommentRow(char*);
int isDeclarationRow(char*,int,int*);
int isInstructionRow(Line,int,int*);
char* clearWhiteChar(char*);



