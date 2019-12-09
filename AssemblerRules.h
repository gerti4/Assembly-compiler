#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "SaveWords.h"
#include "GlobalVar.h"




/*Character definations
--------------------------------------*/
#define COMMA ','
#define SPACE ' '
#define TAB '\t'
#define COMMENT ';'
#define END_OF_STRING '\0'
#define END_OF_ROW '\n'
#define END_OF_LABEL ':'
#define MINUS '-'
#define PLUS '+'

/*maximun number to represent in bits*/
#define MAX_NUMBER 8191 

/*minimun number we can insert to represnt in bits*/
#define MIN_NUMBER -8192


/*Boolean values
-------------------------------*/
#define True 1
#define False 0
#define Eror -1


extern Line L;


/*Function - Declartion:
--------------------------------------------*/
int isEmptyRow(char*);
int isCommentRow(char*);
int LabelEnding(char*);
int isValidLabel(char*);
int isEmptyLabel(char*);
int isSavedWord (char*);
int checkComma(char*);
int checkSpaces(char*);
char* clearWhiteChar(char*);
char* removeSpaces(char*);
char* endRow(char*);
char* checkLabel(char*);
int isValidNumber (char*,int*);
int checkCommaPos (char*,int);
int isWhiteChar(char);
int ValidCharacters(char*);







	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	



