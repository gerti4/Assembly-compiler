#include <stdio.h>
#include <stdarg.h>


#define MAX_MEMORY_SIZE 4096	/*Maximum memroy size to stores machine codes*/
#define MAX_LABEL_LENGTH 31		/*Maximum length of a label*/
#define STOP 15								/*Insturction to stop the program*/
#define TWO_REGISTERS 5				/*Indicates to encode two registers in one machine code*/
#define REGISTER_ADDRESSING 3	

/*Addressing types*/
#define ABSOLUTE 0
#define RELOCATABLE 2

#define INSTURCTION_TWO_OPERANDS 3
#define LEA_INST 6

#define UNDEFINED_OPERAND -1	
#define UNUSED_BITS 0

#define True 1
#define False 0
#define Eror -1

/*
	MachineCmd:
		this structure represent an instruction in a machine code:
		- Unused: Bits  10-13 unused bits.
		- Opcode: Bits	6-9 represent the instruction type.
		- Src: Bits 4-5 represent the source operand.
		- Dst: Bits 2-3 represent the destination operand.
		- ARE: bits 0-1 indicates the addressing type.
		- cmdAddress: represents the memory address.
------------------------------------------------------------------------*/
struct machinecmd {
	unsigned int ARE: 2;
	unsigned int Dst: 2;
	unsigned int Src: 2;
	unsigned int Opcode: 4;
	unsigned int Unused: 4;
	long cmdAddress;
	};
typedef struct machinecmd MachineCmd;

/*

	MachineReg:
		this structure represent an Register in a machine code:
		- Unused: Bits  8-13 unused bits.
		- Src: Bits 5-7 represent the source operand.
		- Dst: Bits 2-4 represent the destination operand.
		- ARE: bits 0-1 indicates the addressing type.
		- regAddress: represents the memory address.
-----------------------------------------------------------*/
struct machinereg {
	unsigned int ARE: 2;
	unsigned int Dst: 3;
	unsigned int Src: 3;
	unsigned int Unused: 6;
	long regAddress;
	};
typedef struct machinereg MachineReg;

/*

	MachineNum:
		this structure represent a Number in a machine code:
		- Number: Bits 2-13 represent the number.
		- ARE: bits 0-1 indicates the addressing type.
		- numAddress: represents the memory address.
-----------------------------------------------------------*/
struct machinenum {
	unsigned int ARE: 2;
	unsigned int Number: 12;
	long numAddress;
	};
typedef struct machinenum MachineNum;

/*

	MachineData:
		this structure represent a data of ascii values,numbers and memory address
	  in a machine code:
		- Values: Bits 0-13 represent the data.
		- dataAddress: represents the memory address.
-----------------------------------------------------------*/
struct machinedata {
	unsigned int Value: 14;
	long dataAddress;
	};
typedef struct machinedata MachineData;

/*

	MachineCode:
		this structure represnt an binary instruction code.
		- Syntax: Bits 0-13 represent a machine code.
		- Address: represents the memory address.
-----------------------------------------------------------------------------*/
struct machinecode {
	unsigned int Syntax: 14;
	long Address;
	};
typedef struct machinecode MachineCode;

/*

	OpType:
		this structure represents an instructions operand.
		- type: the operands addressing types Immediate / Direct / Matrix / Register.
		- data: stores the data of operand: for exmple numbers / regosters number.
		- label: stores the label name of operand.
		- opAddress: represent the memory address. 
---------------------------------------------------------------*/
struct optype{
	int type;
	int data;
	char label[MAX_LABEL_LENGTH];
	long opAddress;
	};
typedef struct optype OpType;

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

/*
	Global variables:
------------------------------------------------------------------------------*/

MachineCode binaryCode[MAX_MEMORY_SIZE];	/*Stores all machine codes of assembly file*/
int code_row_cnt;													/*Counter of machine codes in array binaryCode*/

extern long IC;														/*Instruction counter*/


/*Diffrents machine code lines type*/
enum LINE_TYPE
{
 COMMAND_LINE =1 , REGISTER_LINE , NUMBER_LINE , DATA_LINE
};

/*Label types: external, entry, macro or regular (none)*/
enum LABEL_TYPE													
{
 EXTERNAL = 1 , NONE , ENTRY , MACRO
};

/*Addressing methods types*/
enum Operand_Status	
{ 
	IMMEDIATE_ADDRESSING = 0, DIRECT_ADDRESSING, MATRIX_ADDRESSING, Register
};


	
/*	Functions declaration:
--------------------------------------------------------------*/
void ResetBinaryCode();
MachineCode copy(int type,MachineCmd cmd);
void print(unsigned int syntax); 
int EnterItemAddress (char* item_label, long item_address , int item_type);	
void printCode();
int setBinaryCode (int type,...);
int getLabelAddress(char *label,int*);
	
	
	

		
		
		
 
 
 
 
 
 
 
 
