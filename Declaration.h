#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GlobalVar.h"

/*Program definitions*/
#define MAX_LABEL_LENGTH 32
#define MAX_ROW_LENGTH 82
#define DOT '.'

#define True 1
#define False 0
#define Eror -1

#define FIRST_SCAN 1
#define SECOND_SCAN 2

/*Declaration words*/
#define STRING_STR ".string"
#define DATA_STR ".data"
#define ENTRY_STR ".entry"
#define EXTERN_STR ".extern"
#define DEFINE_STR ".define"

extern Line L;				/*Stroes information from a single assembler row*/

extern long DC;				/*Data counter for Data table*/


/* Numbers represent parameters of .data , String represent parameters of .string*/
enum { Numbers = 1, String };

/* Label types */
enum LABEL_TYPE { EXTERNAL = 1 , INTERN , ENTRY , MACRO };


/*	Function declaration:
------------------------------------------------------------*/
int getLabelAddress(char*,int*);
char* clearWhiteChar(char*);
char* removeSpaces(char*);
int isValidLabel(char*);
int checkSpaces(char*);
int isValidNumber (char*, int*);
int isEmptyRow(char*);
int insertSymbol(char*, long, int , int );
int saveData(char *,int);
int LabelEnding(char*);
int EnterItemAddress (char*,long,int);

