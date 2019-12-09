#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define STRING_STR ".string"
#define DATA_STR ".data"
#define ENTRY_STR ".entry"
#define EXTERN_STR ".extern"

#define MAX_LABEL_LENGTH 31

#define True 1
#define False 0
#define Eror -1

/*
		AvlTree:
			this structure represents the Symbol table.
			Symbol table stores the programs labels and their memory.
			- name: label name.
			- address: memory address of label.
			- withCmd: label with insturction.
			- label_type: label is external/entry/macro/none.
			- height: hieght of each node on the tree.
			- leftNode: pointer to the left node.
			- rightNode: pointer to the right node.
			- parentNode: pointer to the parent node.
------------------------------------------------------------------------*/
struct node
{
	char name[MAX_LABEL_LENGTH];
	int address;			 			
	int withCmd;						
	int label_type;					
	int height;							 

	struct node* leftNode;
	struct node* rightNode;
	struct node* parentNode;
	};
typedef struct node AvlTree;

/*Label types*/
enum LABEL_TYPE { EXTERNAL = 1 , ENTERNAL , ENTRY , MACRO };


/*Pointer to head of Symbol table*/
AvlTree* pHeadSymbol;

/*	Function declaration
-------------------------------------------------------------------*/
int insertSymbol(char*, int, int , int  );
int compareSymbols(char*,char*);
int getHeight(AvlTree*);
int max(int,int);
int getBalance(AvlTree*);
int setAddress(long);
void update(AvlTree*,long);
int getLabelAddress(char*,int*);
void freeAllSymbols(AvlTree*);
void freeSymbolTable();
AvlTree* createNewSymbol(char*,int,int,int);
AvlTree* rotateRight(AvlTree*);
AvlTree* rotateLeft(AvlTree*);
AvlTree* setBalance(AvlTree*,int,char*);

