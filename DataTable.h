#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "GlobalVar.h"



/*every cell in the memory has 14 BITS:
------------------------------------------------*/
/*maximun number we can insert to data table*/
#define MAX_NUMBER 8191 

/*minimun number we can insert to data table*/
#define MIN_NUMBER -8192

/*definition of the program*/
#define MAX_LABEL_LENGTH 32
#define MAX_ROW_LENGTH 82
#define BINARY_WORD_SIZE 14

/*Character: */
#define STRING_COMMA ","
#define STRING_SIGN '"'
#define END_OF_STRING '\0'
#define SPACE ' '
#define TAB '\t'

/*Boolean definition*/
#define True 1
#define False 0
#define Eror -1

/*Indicate to CheckCommaPos that the string is ".data" parameters
	(means that can be more than one ',')*/
#define DECLARATION 0


/*Data types to stores in Data table*/
enum { CHAR = 0 , NUMBER , STRING};



/* MachineData repsents a binary word of the program.
	 it stores the binary number of data.
	 it saves additionally the address of the data (the binary number)*/
/*-----------------------------------------------------------------*/	 
struct d {
	/*value of data represnted by a binary number*/
	unsigned int Value: BINARY_WORD_SIZE;
	long dataAddress;
	};
	
typedef struct d MachineData;



/*LinkedList represnt the data table.
	it has two fields:
	value - the value of a number or character represnted by integer.
	pointer to the next node in the list*/ 
/*-------------------------------------------------------------------*/
struct nodeList
{
	int value;
	struct nodeList* next;
};

typedef struct nodeList LinkedList;



/*Global Variables: */
/*------------------------------------------------------------*/
extern Line L;														/*Strores data from assembly row*/
extern long DC;														/*Date counter*/
extern long IC;														/*Instruction counter*/

LinkedList* pHead;												/*Pointer to the head of data table*/
LinkedList* pLast;												/*Pointer the last node in data table*/




/*Function Declaration:
-----------------------------------------------------------------------*/
int saveData(char *,int);
int checkComma(char*);
int checkCommaPos (char* ,int);
char* clearWhiteChar(char*);
int encodeDataTable();
int setBinaryCode (int,...);
int checkNumber(char*);
int createNode(char,int,int);
void printList(LinkedList*);
int checkNumber(char*);
int saveNumber(char*);
int saveString(char*);
int getLabelAddress(char*, int*);
char* removeSpaces(char*);
void freeList(LinkedList*);
int isValidNumber (char*,int*);




		
		
	
	
	
	
	
	
	
	
	
	
	
	
	
			

