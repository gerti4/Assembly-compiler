#include "DataTable.h"

/*
	createNode:
			this method gets 3 paramaters and according to their data , it creats 
			a node with the specific data and insert it to the data table - (represented as 
			Linked List).
			there are two types of data:
			char - represented by ch.
			number - represented by num.
			type - represent the data type to insert to the table.
			return True - a new data is insert correctly to the table , otherwise returns False.
------------------------------------------------------------------------*/
int createNode(char ch,int num,int type)
{
	
	LinkedList* newNode;					/*a new node in a linked list - stores data*/
	
	/*creats the new node to insert to the table*/
	newNode = (LinkedList*)malloc(sizeof(LinkedList));
	
	if(!newNode){
		fprintf(stderr,"Eror - cannot allocate memory (Data-table).\n");
		return False;
		}
	
	/*Checks data type*/
	if(type)
		/*given data is a number*/
		newNode->value = num;
	
	else 
		/*Given data type is char*/	
		newNode->value = ch;
				
	newNode->next = NULL;
	
	/*case there are no nodes in the list - empty data table*/
	if(!pHead){
		pHead = newNode;
		/*pLast - a pointer to the last node in the list*/
		pLast = pHead;
		}
	
	/*insert the current data to be the last node of the current list*/
	else{
		pLast->next = newNode;
		pLast = newNode;
		}
	return True;
}		
/*

	saveDate:
			this method gets parameters "data" - a string, and "data_type" - integer.
			according to data_type, saveData calls the function "saveNumber" or "saveString"
			that inserts the given data to the data-table.
			return seccuss - True, if the given data is a string or number, otherwise False.	
-------------------------------------------------*/
int saveData(char *data,int data_type)
{
	
	int seccuss;
	seccuss = True;
	
	switch(data_type)
	{
		/*Data_type is a number*/
		case NUMBER: 
			/*save number in data table*/
			if(!saveNumber(data))
				seccuss = False;
		break;
		
		/*Data_type is a string*/
		case STRING: 
			/*save characters in data table*/
			if(!saveString(data))
				seccuss = False;
		break;
	}
	return seccuss;
}
/*


	saveNumber:
			this method gets a parameter a string - "data", that represent a number.
			first it checks comma postion and spaces between the numbers.
			afterwards,it reads number after number and checks if the number is valid.
			return True if all the numbers represnted by "data" are valid numbers, otherwise 
			returns False. 
--------------------------------------------------------------------------------*/
int saveNumber(char* data)
{

	/*variable to get number after number from "data"*/
	char *number;
	number = NULL;
	
	/*checks comma postion in the given data*/
	if(!checkCommaPos(data,DECLARATION))
		return False;
	
	removeSpaces(data);

	/*Gets first number*/
	number = strtok(data,STRING_COMMA);
	
	while(number)
	{
		
		/*Checks if the number is valid*/
		if(checkNumber(number)){
			/*gets the next number*/
			number = strtok(NULL,STRING_COMMA);
			}
			
		/*Invalid number*/
		else {
			return False;
		}
	}
	return True;
}
/*

	saveString:
		this method gets a string - represnted by data.
		it checks if the characters in data are valid.
		if character is valid, it calls to function "createNode" with the current character
		and inserts it to the data table.
---------------------------------------------------------------------*/
int saveString(char* data)
{
	
	char* temp_data;				/*gets string data*/
	int i;
	
	i=0;
	
	temp_data = clearWhiteChar(data);
	
	/*String defined with two ' " ' (STRING_SIGN) */
	if(temp_data[0]==STRING_SIGN && temp_data[strlen(temp_data)-1]==STRING_SIGN){	

		i++;
					
		/*Gets character one by one from string*/
		while(temp_data[i] != STRING_SIGN && i<strlen(temp_data))
		{
			/*Insert charcter to the Data-Table*/
			if(!createNode(temp_data[i],False,CHAR)){
					fprintf(stderr,"Eror by insert new char:%c to data table.\n",temp_data[i]);
					return False;
				}
				/*after insertion of data to the data-table , increase "data - counter" */
				DC++;	
				/*gets the next character in temp_data*/
				i++;
			}
			/*insert end of string character to the data table after*/
			if(!createNode(END_OF_STRING,False,CHAR)){
				fprintf(stderr,"Eror by insert new char:%c to data table.\n",END_OF_STRING);
				return False;
				}
				
			DC++;
		}
	
	/*Invalid definition of string*/
	else{
		fprintf(stderr,"LINE %d: Undefined string parameter: %s .\n",
		L.index,temp_data);
		return False;
	}
	
	free(temp_data);
	return True;
}
/*


	checkNumber:
			this method gets a parameter - "str" in type of char*.
			it checks if the given string - "str" is number or macro.
			if its a number, it calls to the method "createNode" and insert the number 
			to data table.
			returns True if "str" is a number and has inserted corectly to data table.
			otherwise returns False.
-------------------------------------------------------------*/
int checkNumber(char *str)
{
	
	int num;							/*gets digit from string characters*/
	num = 0;
	/* getLabelAddress checks if "str" is a macro label.
		 case "str" is a macro label "num" gets the value of the macro*/
	if(getLabelAddress(str,&num) == Eror){
		/*if "str" is not a macro label.*/
		if(!isValidNumber(str,&num))
			return False;	
		}
	/*insert "num" to the data table*/
	if(!createNode(False,num,NUMBER)){
		fprintf(stderr,"Eror by insert a new number %d to data table.\n",num);
		return False;
		}
	/*Increse data counter*/
	DC++;
	
	return True;
}
/*

	encodeDataTable:
		after second scan this function encode into a binary code the values in data table.
		it adds each binary code to the array of machine codes.
		returns True after encoding value from data table into machine codes.
-----------------------------------------------------*/
int encodeDataTable()
{
	LinkedList* temp;											/*Pointer to runs over the values in table*/
	MachineData mData;										/*A single machine code*/
	
	/*Set defualt value of machine code*/
	mData.Value = 0;
	
	temp = pHead;
	while(temp)
	{
		/*binary code gets a value in data table*/
		mData.Value = temp->value;
		/*Set memory address of binary code*/
		mData.dataAddress = IC;
		
		/*Set binary code into a machine code*/
		setBinaryCode(4,mData);
		
		/*Set insturction counter*/
		IC++;
		
		/*Gets next value in table*/
		temp = temp->next;
		mData.Value = 0;
	}
	return True;
}
/*


	freeDataList:
		this method frees each node in the linked list.
		it frees the data list, and reset the data counter.
---------------------------------------------------------*/
void freeDataList()
{
	LinkedList* temp;
	temp= NULL;
	

	while(pHead){
		temp = pHead->next;
		pHead->next = NULL;
		/*Frees node in list*/
		free(pHead);
		pHead = temp;
		}
	
	/*Reset data counter*/
	DC = 0;
}

