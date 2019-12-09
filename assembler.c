#include "Assembler.h"
/*

	Assembler:
		this function gets assembly files.
		each file will compiled if the two functions "first scan" and "second scan"
		returend positiv value.
		after compiling, assembler creates three diffrents files that represent 
		the different data in assembly file.  
---------------------------------------------------------------*/
int assembler(char** asFile)
{

	FILE* fd;													/*pointer to assembly file*/

	/*Gets assembly files one by one*/	
	while(*asFile != NULL)
	{
		
		char* fileTmp;									/*Gets assembly file name*/
		
		fileTmp = getAssemblyFile(*asFile);
		
		/*Checks if assembly file exsist*/
		fd = fopen(fileTmp,"r");
		if(!fd){
			fprintf(stderr,"\nEror - Undefined file name: %s .\n",fileTmp);
			
			/*Gets next assembly file*/
			asFile++;
			continue;
			}
		
		/*Set instruction counter*/
		IC = FIRST_CODE_ADDRESS;
		
		
			
		if(firstScan(fd))
		{
			/*Set memory address of labels in symbol table*/	
			setAddress(IC);
			
			/*read the file again from the start*/
			rewind(fd);
			
			/*set again instruction counter*/
			IC = FIRST_CODE_ADDRESS;
			
			/*Gets the file name for creating new files*/
			getFileName(*asFile);
				
						
			if(secondScan(fd))
			{		
				/*By seccuss creates Object, Extern , and Entry files*/
				WriteToObjectFile();
				WriteToExtFile();
				WriteToEntryFile();
			}	
			
			/*First scan has been failed*/
			else 
				fprintf(stderr,"Assembly file - %s: Eror, Second scan has been failed.\n\n",*asFile);
		}
		
		/*Second scan has been failed*/
 		else
 			fprintf(stderr,"Assembly file - %s: Eror, First scan has been failed.\n\n",*asFile);
 		
 		
 		/*Free saved labels from symbole table*/
 		freeSymbolTable();	
 		
 		/*Free saved data from data table*/
 		freeDataList();
 		
 		/*remove machine codes that store in binary code array*/
 		ResetBinaryCode();
 		
 		/*set machine code row*/
 		code_row_cnt = 0;
	
		/*Gets next assembly file */		
 		asFile++;
 	}
 	
 	return True;
 }
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
			
				
			
