#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define DOT '.'
#define ASSEMBLY_FILE ".as"
#define OBJECT_FILE ".ob"
#define ENTRY_FILE ".ent"
#define EXTERN_FILE ".ext"
#define MAX_LABEL_LENGTH 32


#define MAX_FILE_NAME 256
#define MAX_MEMORY_SIZE 4096
#define FIRST_CODE_ADDRESS 100

#define EXTERNAL  1
#define ENTRY  3

#define BASE_4_SIZE 7
#define MACHINE_CODE_LENGTH 50



#define True 1
#define False 0
#define Eror -1

/*
	List:
		this structure used to save entry and extern label from an assembly files.
		that will be written in extren and entry files
		label - represent tha label name
		memory_add - represent the memory address where the label used.
-----------------------------------------------------------------------------*/
struct list {
	char label[MAX_LABEL_LENGTH];
	long memory_add;
	struct list* next;
	};
typedef struct list List;


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


/*
	Global varaibles:
------------------------------------------------------*/

/*Array that stores the binary code of the assembly file*/
extern MachineCode binaryCode[MAX_MEMORY_SIZE];


extern long IC;
extern long DC;


/*
	External_list represent the external label of the program.
	exLast a pointer to the last external label in the list.
------------------------------------------------------------*/
List  *External_list , *exLast;


/*
	Entry_list represent the entry label of the program.
	enLast a pointer to the last entry label in the list.
------------------------------------------------------------*/
List  *Entry_list , *enLast;


/*Filename represent the name file of the assembly file*/
char* FileName = NULL;




