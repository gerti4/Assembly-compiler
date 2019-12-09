#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Program definitions*/
#define MAX_FILE_NAME 256
#define FIRST_CODE_ADDRESS 100
#define True 1
#define False 0
#define Eror -1

/*Syntax defintion*/
#define ASSEMBLY_FILE ".as"
#define DOT '.'




/*	Global variables
---------------------------------------------------------------*/
long IC = 0;									/*Instruction counter*/
long DC = 0;									/*Data counter*/

extern int code_row_cnt;			/*counter of row machine code*/

/*	Function Declaration
------------------------------------------------------------*/
int firstScan (FILE*);
int secondScan (FILE*);
int setAddress (long);
void getFileName (char*);
int WriteToObjectFile();
void WriteToEntryFile();
void WriteToExtFile();
void freeDataList();
void freeSymbolTable();
void ResetBinaryCode();
char* getAssemblyFile(char*);

