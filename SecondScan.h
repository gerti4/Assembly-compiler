#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GlobalVar.h"

#define SECOND_SCAN 2

#define True 1
#define False 0
#define Eror -1

/*

	MachineCode:
		this structure represnt an binary instruction code.
		- Syntax: Bits 0-13 represent a machine code.
		- Address: represents the memory address.
-----------------------------------------------------------------------------*/
struct machineCode {
	unsigned int Syntax: 14;
	int Address;
	};
typedef struct machineCode MachineCode;


/*	Global variables:
----------------------------------------------------------------------*/
extern MachineCode binaryCode;		/*binaryCode stores the instruction in a binary code*/
extern long IC;										/*Instruction counter*/
extern Line L;										/* Line store the data from assembly line*/



/*	Function decalartion
-------------------------------------------*/
void printCode();
int isDeclarationRow(char*,int,int*);
int encodeDataTable();
int isWhiteChar(char);
int isEmptyRow(char*);
int isCommentRow(char*);
int isInstructionRow(Line,int,int*);





