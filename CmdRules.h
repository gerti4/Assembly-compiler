#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include "GlobalVar.h"


#define True 1
#define False 0
#define Eror -1
#define DEFAULT -2

/*Program definitions:*/
#define MAX_ROW_LENGTH 82
#define MAX_LABEL_LENGTH 32

/*Syntax definitions:*/
#define COMMA ','
#define STRING_COMMA ","
#define END_OF_STRING "\0"

/*Indicates if 2 operands are register*/
#define TWO_REGISTERS 5

/*Memory cell for instructions operands*/
#define ONE_CELL_MEMORY 1
#define TWO_CELLS_MEMORY 2


/*
OpType represnet an operand of an instruction:
	type - operand type Number/Label/Register/Matrix.
	data - stores numbers.
	label - stores Labels.
	opAddress - stores the operand's memory address.
-------------------------------------------------------------*/
struct oper{
	int type;
	int data;
	char label[MAX_LABEL_LENGTH];
	int opAddress;
	};
typedef struct oper OpType;

	
	
/*
	Command represents an instruction with source and destination operands:
		index - the instruction index
		OpType src - source operand
		OpType dst - destination operand
		ARE - represent the memory address type
		address - represent the Commands memory address
-----------------------------------------------------------------------------*/
struct command{
	int index;
  OpType src;
  OpType dst;
	int ARE;
	int address;
	};
typedef struct command Command;



/*	Function declaration:
----------------------------------------------------------------*/
int getCmdType(char*);	
int setOperandType (Command*,char*,int*);
int isRegister (OpType*,char*);
int isNumber (OpType*,char*);
int isMatrix(OpType*,char*); 
int isLabel (OpType*,char*);
int isValidNumber (char*,int *);
int isValidLabel(char*);
int isEmptyRow(char*);
int checkCommaPos(char*,int);
int checkSpaces(char* temp);
int getLabelAddress(char*,int*);
char* removeSpaces(char*);
char* clearWhiteChar(char *row);
char* addImmediateSign (char* macro);
OpType getOperand(char*);
int isEror(OpType p);
int opcodeParam (Command cmd);	

	
