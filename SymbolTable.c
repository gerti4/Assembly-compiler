#include "SymbolTable.h"

/*

 compareSymbols:
		function to campare symbols name according to lexicographic order.
		if str1 before str2 in lexicographic order returns -1.
		if str1 after str2 in lexicographic order returns 1.
		if str1 are str2 eauals returns 0.
-------------------------------------------------------*/
int compareSymbols(char *str1,char *str2)
{
	/*str1 is before str2*/
	if(strcmp(str1,str2)<0)
		return -1;
		
	/*str1 is after str2*/
	else if(strcmp(str1,str2)>0)
		return 1;
		
	/*equals*/	
	else
		return 0;
}
/*


	getHeight:	
		function to get the height of the given node in the avl tree.
		returns height of the node
----------------------------------------------------------------*/
int getHeight(AvlTree *tmp)
{
	if (!tmp)
		return 0;
	return tmp->height;
}
/*


	max:
		function to get the maximum number between to integers
------------------------------------------------------------*/
int max(int x, int y)
{
	if(x>y)
		return x;
	return y;
}
/*


	getBalance:
		this method checks the balance of a node sub-tree. 
------------------------------------------------------------------ */
int getBalance(AvlTree* tmp)
{
	if (!tmp)
		return 0;
	return getHeight(tmp->leftNode) - getHeight(tmp->rightNode);
}
/*


	createNewSymbol:
		this method creates a new symbol with the given parametrs.
		label - represent the symbol name.
		address - represent the label address.
		isCmd - represent if the there is an instruction with a label.
		type - label type Macro External Entry Enternal.
 		returns a pointer to the new Symbol, by eror returns Null.
----------------------------------------------------------------*/
AvlTree* createNewSymbol(char* label, int address, int isCmd , int type)
{

	
	AvlTree* tmp;														/*Creates a new node to store a symbol*/
	tmp = (AvlTree*)malloc(sizeof(AvlTree));
	

	if(!tmp){
		fprintf(stderr,"EROR - failure by allocating memory");
		return NULL;
		}
	
	
	/*Set symbol name*/
	strcpy(tmp->name,label);
	
	tmp->leftNode = NULL;
	tmp->rightNode = NULL;
	
	/*Default value of height for new node */
	tmp->height = 1;
	
	/*Set memory address*/
	tmp->address = address;
	
	/*Set label type*/
	tmp->label_type = type;
	
	tmp->withCmd =  isCmd;
			
	return tmp;
}
/*


	rotateRight:
		function to right rotate a subtree rooted with parentNode of symbol
		returns a pointer to the leftNode of symbol.
----------------------------------------------------------------*/
AvlTree* rotateRight(AvlTree* parent)
{
	AvlTree* leftNode = parent->leftNode;
	AvlTree* rightNodeChild = leftNode->rightNode;

	/*perform rotation*/
	leftNode->rightNode = parent;
	parent->leftNode = rightNodeChild;

	/*update heights*/
	parent->height = max(getHeight(parent->leftNode), getHeight(parent->rightNode))+1;
	leftNode->height = max(getHeight(leftNode->leftNode), getHeight(leftNode->rightNode))+1;
	
return leftNode;
}
/*


	rotateLeft:
		function to left rotate a subtree rooted with parentNode of symbol
		returns a pointer to the rightNode of symbol.
-------------------------------------------------------------*/
	
AvlTree *rotateLeft(AvlTree *parent)
{
	AvlTree* rightNode=parent->rightNode;
	AvlTree* leftNodeChild=rightNode->leftNode;

	/*perform rotation*/
	rightNode->leftNode=parent;
	parent->rightNode=leftNodeChild;

	/*update heights*/
	parent->height = max(getHeight(parent->leftNode), getHeight(parent->rightNode))+1;
	rightNode->height = max(getHeight(rightNode->leftNode), getHeight(rightNode->rightNode))+1;


	return rightNode;
}
/*
	
	
	setBalance:
		function for setting balance in  AVL tree.
------------------------------------------------------------*/
	
AvlTree* setBalance(AvlTree *pHeadSymbol,int balance,char *newSymbolName)
{
	/* Left Left Case */
	if (balance >1 && compareSymbols(newSymbolName,pHeadSymbol->leftNode->name)<0)
		return rotateRight(pHeadSymbol);
		
	/* Right Right Case */
	if (balance < -1 && compareSymbols(newSymbolName,pHeadSymbol->rightNode->name)>0)
		return rotateLeft(pHeadSymbol);
		
	/* Left Right Case */
	if (balance > 1 && compareSymbols(newSymbolName,pHeadSymbol->leftNode->name)>0){
		pHeadSymbol->leftNode=rotateLeft(pHeadSymbol->leftNode);
		return rotateRight(pHeadSymbol);
		}
		
	/* Right Left Case */
	if (balance < -1 && compareSymbols(newSymbolName,pHeadSymbol->rightNode->name)<0){
		pHeadSymbol->rightNode=rotateRight(pHeadSymbol->rightNode);
		return rotateLeft(pHeadSymbol);
		}
		
	return pHeadSymbol;
}
/*


	insertSymbol:
		 function to insert symbols to symbol table.
		 the method gets parametrs for a symbol.
		 insertSymbol calls to the function createNewSymbol.
		 the pointer to the new Symbol will be inserted to the correct place in Symbol table.
		 returns True if symbol insreted corectly otherwise returns False.
--------------------------------------------------------------------*/
int insertSymbol(char* label, int address, int isCmd , int type)
{
	
	AvlTree* newSymbol = NULL;
	AvlTree* parentSymbol = NULL;
	AvlTree* currSymbol = NULL;
	
	int balance;
	
	/*Empty table*/
	if(!pHeadSymbol){
	
		/*creates new symbol*/
		newSymbol = createNewSymbol(label , address, isCmd , type);
		
		/*Set head of the table to be the new symbol*/
		if(newSymbol){
			pHeadSymbol = newSymbol;
			pHeadSymbol->parentNode = NULL;
			return True;
			}
			
		/*new symbol is undefined*/	
		return Eror;
		}
	
	/*Symnole table is not empty*/
	else{
		currSymbol = pHeadSymbol;
		
		/*finds to corect postion of the new symbol in table*/	
		while(currSymbol){
		
				parentSymbol = currSymbol;
					
				if(compareSymbols(currSymbol->name,label)>0)
					currSymbol = currSymbol->leftNode;
					
				else if(compareSymbols(currSymbol->name,label)<0)
					currSymbol = currSymbol->rightNode;
				
				/*Symbol with the same label is already defined*/ 	
				else{
					fprintf(stderr,"Eror - multi definition of label %s.\n",label);
					return False;
					}
				}
			
		/* Adding the new Symbol in the symbol table */	
		newSymbol = createNewSymbol(label , address , isCmd , type);
		
		/*insert the new symbol in the correct place accorfing to lexicographic oreder*/
		if(compareSymbols(parentSymbol->name,label)>0){
			parentSymbol->leftNode = newSymbol;
			newSymbol->parentNode = parentSymbol;
			}
			
		else{
			parentSymbol->rightNode = newSymbol;
			newSymbol->parentNode = parentSymbol;
			}
			
		/*Update the height of the head symbol table */	
		pHeadSymbol->height =
			1 + max(getHeight(pHeadSymbol->leftNode),getHeight(pHeadSymbol->rightNode));
		}
	
	/*Checks that AVL tree is balanced*/ 
	balance = getBalance(pHeadSymbol);
	
	if(balance>1||balance<-1)
		pHeadSymbol = setBalance(pHeadSymbol,balance,label);

	return True;
}
/*


	setAddress:
		this method calls to "update" function with current IC and pointer to the head 
		of the table.
		it sets the memory address of each instruction row according to IC.
		returns True after updating memory address.
--------------------------------------------------------------------*/
int setAddress(long IC)
{
	update(pHeadSymbol,IC);
	return True;
}
/*


	update:
		this method update the memory address of each Symbol with instruction .
		it runs over the symbols in the table.
		if a symbol has instuction - represented by "withCmd" it updates its memory address.
		if a symbol is a macro or external do nothing.
-------------------------------------------------------------------*/
void update(AvlTree* root , long IC)
{
	if(!root)
		return;
		
	update(root->leftNode,IC);
	
	/*Checks symbol is not a macro or external*/
	if(root->label_type!= MACRO && root->label_type !=EXTERNAL){
		if(!root->withCmd){
			/*Symbol is a label with instucrion*/
			root->address += IC;
			}
		}	
	update(root->rightNode,IC);
}
/*


	getLabelAddress:
		this method get a label and a pointer to integer number.
		it searches in the table after the given label.
		if the label has been found, the inetger number gets the label's address.
		return Label type in case label is in the table otherwise returns false.
-------------------------------------------------------------------------*/
int getLabelAddress(char *label, int* num ) 
{

	AvlTree* currSymbol = NULL;
	
	
	/*Checks empty table*/
	if(pHeadSymbol)
	{
		
		currSymbol = pHeadSymbol;
		
		/*Searching after label in table.
		compare the given label with the current symbol by their lexicographic order*/
		while(currSymbol)
		{
			
			/*current symbol name is after "label" in lexicographic order*/
			if(compareSymbols(currSymbol->name,label)>0)
				currSymbol = currSymbol->leftNode;
				
			/*current symbol name is before "label" in lexicographic order*/	
			else if(compareSymbols(currSymbol->name,label)<0)
				currSymbol=currSymbol->rightNode;
			
			/*Label has been found in table*/	
			else
			{
				/*Label type is external - address is 0*/
				if(currSymbol->label_type == EXTERNAL){
					(*num) = 0;
					return EXTERNAL;
					}
				/*Label type is entry*/
				else if(currSymbol->label_type == ENTRY){
					(*num) = currSymbol->address;
					return ENTRY;
					}
				
				/*Label type is macro - address is the macro value*/	
				else if(currSymbol->label_type == MACRO){
					(*num) = currSymbol->address;
					return MACRO;
					}
					
				/*Label is defined in assembly file*/	
				(*num) = currSymbol->address;
				return ENTERNAL;
			}
		}
		/*Label has not been found*/
		return Eror;
	}
	/*No symbols in table*/
	return Eror;
}
/*


	freeAllSymbol:
		this method frees all the symbols in Symbol table.
		frees as well the symbol names.
--------------------------------------------------------*/
void freeAllSymbols(AvlTree* symbol)
{
	if(!symbol)
		return;
		
	freeAllSymbols(symbol->leftNode);
	
	
	symbol->leftNode = NULL;
	symbol->parentNode = NULL;
	
	freeAllSymbols(symbol->rightNode);
	
	symbol->rightNode = NULL;
	
	free(symbol);
}
/*


	freeSymbolTable:
		this method calls to function freeAllSymbols with a pointer to the head of Symbol table.
		the function freeAllSymbols free from the memory tha data in table.
		afterwards it frees the Symbol table.
--------------------------------*/
void freeSymbolTable()
{
	if(!pHeadSymbol)
		return;
	
	freeAllSymbols(pHeadSymbol);
	pHeadSymbol = NULL;
}
	
		
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
