#include "SecondScan.h"
/*

	secondScan:
		this method updates after the first scan of an assembly file, 
		the machine code of the program.
		it adds the data table to the machine code.
		it checks that each label in symbol table has been declared in first scan.
		returns True if there are no Erors otherwise return False.
-----------------------------------------------------------*/
int secondScan (FILE* fd)
{
	
	char row[MAX_ROW_LENGTH];		/*represnt a current row from assembly file*/
	int compiled; 							/*indicates if the assembly file has been seccussfuly compiled*/
	
	L.index = 0;								/*start from first line in assembly file*/
	compiled = True;
	
	/*Gets a row from assembly file*/
	while(fgets(row,MAX_ROW_LENGTH,fd)!=NULL)
	{
		/*Empty or Comment row*/
		if(isEmptyRow(row) || isCommentRow(row))
			continue;
		
		/*Declaration row*/			
  	else if(isDeclarationRow(row,SECOND_SCAN,&compiled))
  		continue;
 
  	/*Instruction row*/
  	else if (isInstructionRow(L,SECOND_SCAN,&compiled))
  		continue;
  	
  	/*Eror cannot update machine code*/
  	else
  		break;
 	}

	/*There is no eror in second scan , a flie can be compiled*/
	if(compiled){
	
		/*adding data table to the binary code that stores insturctions*/
		encodeDataTable();
	}
	return compiled;
		
}
	

	
		
	
	
