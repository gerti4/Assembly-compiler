#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "GlobalVar.h"

/*Program defintnions*/
#define MAX_LABEL_LENGTH 32
#define MAX_ROW_LENGTH 82

#define FIRST_SCAN 1
#define SECOND_SCAN 2

#define True 1
#define False 0
#define Eror -1

#define END_OF_STRING "\0"

/*

	OpType:
		this structure represents an instructions operand.
		- type: the operands addressing types Immediate / Direct / Matrix / Register.
		- data: stores the data of operand: for exmple numbers / regosters number.
		- label: stores the label name of operand.
		- opAddress: represent the memory address. 
---------------------------------------------------------------*/
struct oper{
	int type;
	int data;
	char label[MAX_LABEL_LENGTH];
	long opAddress;
	};
typedef struct oper OpType;

/*

	Command:
		this structure represnt an assembly instruction.
		- index: stores the insturctions index.
		- src: stores the source operand.
		- dst: stores the destination operand.
		- ARE: stores the memory addressing type.
		- address: represent the memory address.
-------------------------------------------------------------------*/
struct command{
	int index;
  OpType src;
  OpType dst;
	int ARE;
	long address;
	};
typedef struct command Command;


extern Line L;				/*Stroes information from a single assembler row*/
extern long IC;				/*Instruction counter*/
	
	
/*	Function declaration:
-------------------------------------------------*/
char* checkLabel(char*);
int getCmdType(char*);
int setOperandType (Command*,char*,int* );
int insertSymbol(char*, long, int , int , int );
int opcodeParam (Command);
int encode(Command,OpType,OpType);
int isValidLabel(char*);
int LabelEnding(char*);
