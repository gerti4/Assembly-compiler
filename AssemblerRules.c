/*
	AssemblerRules:
		this file contains many diffrents functions that used for check valid 
		assembly syntax.
--------------------------------------------------------------------------------*/

#include "AssemblerRules.h"

/*

	isEmptyRow:
 			checks if the current row is empty. that means without
 			any letter except white characters.
  		return True if its empty row.
  		otherwise return False.
----------------------------------------------------------------------------*/
int isEmptyRow(char *row)
{
	
	int emptyRow;							/*Indicates if the row is empty or not.*/
	int index; 								/*index to run with over the string*/
	int rowLength;						/*Length of the string*/
	
	emptyRow = True;
	index = 0;							 
	rowLength = strlen(row);   
	
	/*Empty row*/
	if(rowLength == 0)
		return emptyRow;
	
	/*Checks characters in row*/	
	while( emptyRow && index<rowLength)
	{
		/*reaches to the end of row*/
		if(row[index] == END_OF_ROW)
			return emptyRow;
				
		/*Checks if character is not white char*/		
		else if(!isWhiteChar(row[index]))
		{
			/*it is not empty row*/
			emptyRow = False;
			
			return emptyRow;
		}
		
		/*gets next character in row*/
		index++;	
	}
	return emptyRow;
}
/*

	isCommentRow:
			checks if the current row is a comment row. starts with the character: ';'.
			return True - it is a comment row.
			other wise return False.
-------------------------------------------------------------------*/
int isCommentRow(char* row)
{
	int i;
	i=0;
	
	/*Skip spaces*/
	while(row[i])
	{
		if(!isWhiteChar(row[i]))
			break;
		else
			i++;
	}
	
	
	/*Char row[i] is ';'*/ 
	if(row[i] == COMMENT)
		return True;
		
		
	return False;
}
/*

	clearWhiteSpaces:
			the method clears prefix and ending white character of string .
			returns string without prefix and ending white character.
-------------------------------------------------------------*/
char* clearWhiteChar(char* str)
{

	char* s;									/*store a new string without prefix and endig white characters*/
	int i,j;									/*indexes to run over characters in str*/
	
	/*Empty string*/
	if(!str)
		return str;
	
	/*Set new string without white characters*/	
	s = (char*)calloc(MAX_ROW_LENGTH,sizeof(char));
	
	if(!s){
		fprintf(stderr,"Eror, cannot allocate memory.\n");
		return NULL;
		}
	
		
	if(str)
	{
		/*Checks prefix white characters of str*/
		for(i=0; str[i];i++)
		{
			/*str[i] is not white character*/
			if(!isWhiteChar(str[i]))
				break;
		}
		
		/*Checks ending white characters*/
		for(j=strlen(str);j>=0;j--)
		{
			/*str[i] is not white character*/
			if(!isWhiteChar(str[j]))
				break;
		}
		
		/*Copy str without prefix and endig white characters to s*/	
		strncpy(s,(str+i),(j-i+1));
		
		/*Set end of string in s*/
		if(s[strlen(s)] == END_OF_ROW)
			s[strlen(s)] = END_OF_STRING;
		
		return s;
	}
	
	return s;
}
/*

	removeSpaces:
		the method removes any white characters in parameter str.
		return str without white characters.
-----------------------------------------------------*/
char* removeSpaces(char* str)
{
	
	int count;																/*stores none white characters*/
	int i;																		/*index to run with over the string*/

	count = 0;

	if(str)
	{
		for(i=0;str[i];i++)
		{
			/*checks if str[i] is not a white char*/
			if(!isWhiteChar(str[i]))
				/*set str[i] in a place of white charcter*/
				str[count++]=str[i];
		}
		str[count]=END_OF_STRING;
		return str;
	}
	return str;
}
/*

	endRow:
			this method checks if the last character of the row is '\n' .
			if last char is '\n' , it changes the character to end of string character :'\0'.
-----------------------------------------------------------------*/
char* endRow(char *row)
{
	if(row[strlen(row)]==END_OF_ROW){
		row[strlen(row)]=END_OF_STRING;
		}
	return row;
}
/*

	checkLabel:
 			this method gets a label and checks if its syntax is valid.
 			if valid, set a end of string character in the end of the string label.
 			return Label - case label is valid.
 			otehrwise return NULL.
----------------------------------------------------------*/
char* checkLabel(char *label)
{	
	/*checks ':' of label*/
	if(LabelEnding(label))
	{
		/*checks valid label*/	
		if(isValidLabel(label))
			/*Label is valid*/
			return label;
	}
	
	/*label is invalid*/
	return NULL;
}
/*

	LabelEnding:
			the method gets a label and checks if its last character is ':' 
			according to a label defination.
			return True - last char of label is ':' 
			otherwise return False.
------------------------------------------------------------------------------*/
int LabelEnding(char *label)
{
	
	if(label[strlen(label)-1]==END_OF_LABEL){
		label[strlen(label)-1]=END_OF_STRING; 
		return True;
	}
	return False;
}
/*

	isValidLabel:
			checks if a label is valid:
			- Maximum characters 81.
			- first charater is not a number.
			- label name is not a saved word of the program.
			return True - label is valid, otherwise return False.
-------------------------------------------------------------------*/
int isValidLabel(char *label)
{
	
	if(!label || isEmptyRow(label)){
		fprintf(stderr,"LINE %d: Eror, missing label.\n",L.index);
		return False;
	}
	
	/*checks label characters*/
	if(!ValidCharacters(label))
		return False;
	
	/*checks label length*/	
	if(strlen(label)>=MAX_LABEL_LENGTH){
		fprintf(stderr,"LINE %d: Inavalid parameter:%s - too long.\n",L.index,label);
		return False;
	}
	
	/*checks that label is not a saved word of the program*/
	if(isSavedWord(label)){
		return False;
	}
	
	return True;
}
/*

	isEmptyLabel:
			checks if Label is defined without any instruction or data.
			return True - Label without any data.
			otherwise return False. 
------------------------------------------------------------*/
int isEmptyLabel(char *after_label)
{
	/*after_label is NULL*/
	if(!after_label)
		return True;
	
	/*checks if after label there is just white characters*/	
	if(isEmptyRow(after_label))
		return True;
	
	/*there is information after label*/	
	else
		return False;
}
/*

	isSavedWord:
			this mathod gets a parametr name and checks if the name is equal to one
			of the saved words of the program.
			return False - parametr name is equal to one of the saved words.
			otherwise return True.
---------------------------------------------------------------*/
int isSavedWord (char* name)
{
	int i;
	
	for(i=0;i<SAVED_WORDS;i++)
	{
		/*compare name with all the saved words of the program*/
		if(!strcmp(name,savedWords[i]))
		{
			fprintf(stderr,"LINE %d: Inavalid parameter - saved word:%s\n",L.index,name);
			
			/*name is equal to one of the saved words*/
			return True;
		}
	}
	
	/*label name is not a saved word*/
	return False;
}
/*

	checkComma:
			the method gets a paramter "name" , and checks if its last character is ','.
			return True - last character is ','.
			otherwise return False.
----------------------------------------------------------------*/
int checkComma(char* name)
{
	if(name[strlen(name)-1]==COMMA)
	{
		fprintf(stderr,"LINE %d: Eror, invalid comma position:%s.\n",L.index,name);
		return False;
	}
	return True;
}
/*

	checkSpaces:
			the method gets a parameter "temp" and checks if
			white characters are between the first char and the last char, that 
			are not white characters.
			return False if a white character is between.
			otherwise return True.
---------------------------------------------------------*/
int checkSpaces(char* temp)
{	
	int end;														/*count white charater from the end of string*/
	int begin;													/*count white characters from start of string*/
	int length;													/*length of string*/
	
	
	length = strlen(temp);
	end = 1;
	begin = 1;

	/*while last charater of temp is a white character ,get the character before.*/
	while(isWhiteChar(temp[strlen(temp)-end]))
		end++;
	
	/*checks if there is a white character between the first char and the last char that
	are not white characters.*/ 
	while(temp+begin<temp+length-end)
	{
		/*there is undefined white char between temp[begin] to temp[end]*/
		if(isWhiteChar(temp[begin])){
			fprintf(stderr,"LINE %d: White character in syntax:%s.\n",L.index,temp);
			return False;
			}
		begin++;
	}
	
	/*syntax in temp is valid*/
	return True;
}
/*

	isValidNumber:
		this method checks if the number, represented by data is a valid number.
		if it is valid number, num ( pointer to integer) gets the given number and returns True.
		otherwishe num gets 0 and returns False.
-----------------------------------------------------------------------------------------*/
int isValidNumber (char* data,int* num)
{
	char data_num[MAX_ROW_LENGTH];					/*get a number in string*/
	int i;																	/*index to run with over the string*/
	int positiv;														/*indicate if the number is positiv or negativ*/
	
	
	positiv = True;	
	i=0;
	
	/*Checks valid string*/
	if(!data || isEmptyRow(data)){
		fprintf(stderr,"LINE %d: Missing paramter.\n",L.index);
		*num = 0;
		return False;
		}
	
	strcpy(data_num,data);
	
	
	/*First char is '-', a negativ number*/
	if(data_num[0] == MINUS){
		positiv = -1;
		i++;
		}
	
	/*First char is '+', a positiv number*/
	if(data_num[0] == PLUS){
		positiv = True;
		i++;
		}
		
	/*Runs over the characters in data_num*/	
	while(data_num[i])
		{
			
			if(isdigit(data_num[i]))
				/*num collects the numbers from data_num*/
				*num = (*num) * 10 + data_num[i] - '0';
			
			/*a character is not a digit*/
			else{
				fprintf(stderr,"LINE %d: Invalid parameter:%s\n",L.index,data_num);
				*num = False;
				return False;
				}
			
			/*gets the next char in string*/	
			i++;
		}
	
	/*Make num negativ if positiv is not True*/
	if(positiv != True)
		*num *= positiv;	

	/*checks valid maximun and minimum of number value*/
	if(*num >= MIN_NUMBER  && *num <=MAX_NUMBER)
		return True;
		
	else {
		fprintf(stderr,"LINE %d: Valid numbers are (-8192 to 1891):%s.\n",L.index,data_num);
		return False;
	}
}
/*

	checkCommaPos:
		this method checks if commas postioned correctly in data.
		parameter "inst_type" indicates if data came from a deaclrion row (.data) 
		or from instruction with operands.
		return True if commas postion is correct, otherwise returns False.
--------------------------------------------------------*/
int checkCommaPos (char* data,int inst_type)
{	

	char* temp;
	int space;														/*checks valid space between parameters*/
	int isNum;														/*checks if charater is a digit*/
	int isComma;													/*checks valid comma between parameters*/
	int commaSum;													/*counts comma in string*/
	int i;
	
	i = 0;
	space = False;
	isNum = False;
	isComma = False;
	commaSum = 0;
	
	if(!data){
		fprintf(stderr,"LINE %d: Eror, no prarametrs for insturction:%s.\n",L.index,L.cmd);
		return False;
		}
		
	temp = data;
	
	/*',' is undefind as first character in syntax*/
	if(*temp == COMMA){
		fprintf(stderr,"LINE %d: Invalid comma:%s.\n",L.index,data);
		return False;
		}
	
	while(temp[i]!=END_OF_STRING)
	{
		/*inst_type is Instruction , contains maximum one comma*/
		if(inst_type == 1 && commaSum>inst_type){
			fprintf(stderr,"LINE %d: too many parameters.\n",L.index);
			return False;
			}
			
		if(temp[i] == COMMA ){
			/* a sequance of two commas without any data*/
			if(isComma){
				fprintf(stderr,"LINE %d: Invalid comma:%s.\n",L.index,temp+i);
				return False;
				}
				
			/*valid comma postion*/
			isNum = False;
			space = False;
			isComma = True;
			commaSum++;
			}
		
		else if(!isWhiteChar(temp[i])) {
			/*there is invalid space between two characters*/ 
			if(isNum && space) {
				fprintf(stderr,"LINE %d: Invalid syntax: %s.\n",L.index,data);
				return False;
				}
			/*valid space - before comma or after comma*/
			isNum = True;
			isComma = False;
			space = False;
			}
			
		else 
			space = True;
			
		i++;
	}
	
	/*Undefined comma in the end of syntax*/
	if(temp[i-1] == COMMA){
		fprintf(stderr,"LINE %d: Invalid comma end of syntax:%s.\n",L.index,data);
		return False;
		}	
		
	return True;
}	
/*

	isWhiteChar:
		this method checks if a char is a white char.
		returns true if char is a white char, otherwise returns False.
----------------------------------------------*/		
int isWhiteChar(char ch)
{
	if(ch ==SPACE || ch ==TAB || ch==END_OF_ROW || ch==END_OF_STRING)	
			return True;
	return False;
}
/*

	ValidCharacters:
		checks valid characters in a label.
		valid characters can be only letters of numbers.
		return True if the characters are valid, otherwise returns False
----------------------------------------------------------------------*/
int ValidCharacters(char* label)
{
	int i;
	i = 0;
	
	/*first character in a label has to be a letter*/
	if(!isalpha(label[i])){
		fprintf(stderr,"LINE %d: Syntax %s contains invalid characters.\n",
		L.index,label);
		return False;
		}
		
	for(i = 1; label[i] ; i++){
		/* checks if a letter is not a number or a letter*/
		if(!isalpha(label[i]) && !isdigit(label[i])){
			fprintf(stderr,"LINE %d: Syntax %s contains invalid characters.\n",
			L.index,label);
			return False;
		}
	}
	return True;
}

