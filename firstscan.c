#include "FirstScan.h"

/*

	FirstScan:
		this method gets a pointer to an assembly file.
		its read line by line from the file.
		identify the line's type:
		Empty , Comment , Declartion , Instruction.
		the function return a varibale in name of Syntax_Eror, that
		indicates if there erors in the first scan. 
-----------------------------------------------------------*/
int firstScan(FILE *fd)
{
	
	int Syntax_Eror;				/*indicates if there are syntax erors*/
	L.index = 0;						/*First line from assembly file*/
	
	/*sets row to get assembly row*/
	curr_row = (char*)malloc(sizeof(char)*MAX_ROW_LENGTH);	
	
	Syntax_Eror = True;
	
	/*reads each line till end of file*/
	while(fgets(curr_row,MAX_ROW_LENGTH + 1 , fd))	
	{
	
		L.index ++;

		/*Checks valid length of assembly row*/
		if(strlen(curr_row)>=MAX_ROW_LENGTH){
			fprintf(stderr,"LINE %d: Invalid length of line.\n",L.index);
			Syntax_Eror = False;
			
			/*Gets the next row*/
			fgets(curr_row,MAX_ROW_LENGTH + 1 , fd);	
			continue;
			}
		
		/*Row is empty*/
		else if(isEmptyRow(curr_row))	
			continue;
		
		else{
		
			char* temp;													/*stores row without prefix and ending white char*/
						
			/*Gets the current row without prefix and ending white characters*/
			temp = clearWhiteChar(curr_row);	
			strcpy(curr_row,temp);
	
			/*Row is a comment*/			
			if(isCommentRow(curr_row))
				continue;	
				
			/*
			Row is declaration:
		 	Label declaration with instructions: data,string,entry,extern,macro */	
			else if(isDeclarationRow(curr_row , FIRST_SCAN , &Syntax_Eror) == True){
				continue;
				}
				
			/*Row is instruction:
				Row including instruction and operands*/
			else if(isInstructionRow(L , FIRST_SCAN , &Syntax_Eror) == True){	
				continue;
				}
			}
	}
	
return Syntax_Eror;
}

