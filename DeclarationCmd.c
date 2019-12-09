#include "Declaration.h"


/*

	isDeclartionRow:
		this method gets an asemmbly row.
		it separates the data from the row to three diffrents part:
		- L.label: stores label name.
		- L.cmd: stores insturctions.
		- L.data:	stores data after instruction.
		if the row is a declaration row : that's mean including one of the instructions
		.extern / .entry / .define / .data / .sritng . the function inserts
		the data to the appropriate table.
		if there are erors, ut update the value of Syntax_eror.
		if the row is a seclartion row returns True, otherwise returns False
----------------------------------------------------------------------*/

int isDeclarationRow(char *row, int scan , int* Syntax_Eror)
{
	
	char *str_val; 		/*String trims the row*/
	char *temp_val;		/*String without white characters*/
	
	
	/*Sets Line L to gets the label,cmd, and data*/
	strcpy(L.label,"\0");
	strcpy(L.cmd,"\0");
	strcpy(L.data,"\0");
	
	/*Gets first element from row*/
	str_val = strtok(row," \t"); 
	
	/*clear prefix and ending white char*/
	temp_val = clearWhiteChar(str_val);
	
	strcpy(L.label,temp_val);

	/*First element is a label*/
	if(LabelEnding(L.label))
	{	
		
		
		/*Checks valid label*/
		if(!isValidLabel(L.label))
		{
			/*Label is invalid*/
			*Syntax_Eror = False;
			return True;
		}
		
		/*Gets insturction after label*/
		str_val = strtok(NULL," \t");
		temp_val = clearWhiteChar(str_val);	
		
		/*Checks instruction after label*/
		if(!temp_val || isEmptyRow(temp_val))
		{
			/*there isn't any instruction after label*/
			fprintf(stderr,"Line %d: label without any command.\n",L.index);
			*Syntax_Eror = False;
			return True;
		}
		
		/*L.cmd stores instruction after label*/	
		strcpy(L.cmd,temp_val);
		
		/*Check if instruction start with '.' */			
		if(L.cmd[0] == DOT)
		{
		
		
			/*Instruction is .data*/
			if(!strcmp( L.cmd , DATA_STR ))
			{
			
				/*Gets .data Parameters*/
				str_val = strtok(NULL,"\0");
				temp_val = clearWhiteChar(str_val);
				
				/*Checks .data parameters*/
				if(!temp_val || isEmptyRow(temp_val))
				{
					/*there are no parameters after data*/
					fprintf(stderr,"LINE %d: missing parameter after - .data \n",L.index);
					*Syntax_Eror = False;
					return True;
				}	
				
				/*L.data stores .data parameters*/
				strcpy(L.data,temp_val);
				
				/*Insert labels to symbol table in first scan*/
				if(scan == FIRST_SCAN )
				{
					int eror_type;										/*indicates the eror type*/
					
					/*Insert label to the Symbol-Table.*/
					if((eror_type = insertSymbol(L.label,DC,False,INTERN))!= True)
					{
						/*label is already defined*/
						if(eror_type == False)
						{
							fprintf(stderr,"Line %d: Label: %s, is already defined in program.\n",
							L.index,L.label);
							*Syntax_Eror = False;
						} 
						else
						{	/*cannot allocate memory in symbol table for a new label*/
							fprintf(stderr,"Eror - Failure by allocating memory.\n");
							*Syntax_Eror = False; 
						}	
						return True;
						}
					
					/*Insert .data Parameters (NUMBERS) to Data-Table*/
					if((eror_type = saveData(L.data,Numbers))!= True)
						*Syntax_Eror = False;
					
					return True;
					}
				return True;
				}
	
	
      /*Instruction is .string*/		
		 	else if(!strcmp(L.cmd,STRING_STR))
		 	{
		 	
				/*gets .string Parameters*/
				str_val = strtok(NULL,"\0");
			
				temp_val = clearWhiteChar(str_val);
				
				/*Checks valid .string parameters*/
				if(!temp_val || isEmptyRow(temp_val)){
					/*there is no data after string*/
					fprintf(stderr,"LINE %d: Eror, missing parameter after - .string \n",L.index);
					*Syntax_Eror = False;
					return True;
					}	
				
				/*L.data stores string parameters*/	
				strcpy(L.data,str_val);
				
				if(scan == FIRST_SCAN){
					int eror_type;							/*indicates the eror type*/
					
					/*Insert label to the Symbol-Table.*/
					if((eror_type = insertSymbol(L.label,DC,False,INTERN)) != True){
						if(eror_type == False)
						{
							/*label is already defined in program*/
							fprintf(stderr,"Line %d: Label: %s, is already defined in program.\n",
								L.index,L.label);
							*Syntax_Eror = False;
						} 
						else{
							fprintf(stderr,"Eror - Failure by allocating memory.\n");
							*Syntax_Eror = False; 
						}
						return True;
						}
						
					/*Insert .string Parameters to Data-Table*/
					if((eror_type = saveData(L.data, String)) != True)
						*Syntax_Eror = False;	
					}
				return True;
				}	
			
			
			/*Instruction is .extern or .entry*/				
			else if(!strcmp(L.cmd,ENTRY_STR)||!strcmp(L.cmd,EXTERN_STR)){
				if(scan == FIRST_SCAN) /*Ignore - label before .extern or entry*/
					fprintf(stderr,"Line %d: Warning - Label must be written after instruction.\n",
					L.index);
				}
			/*Undefined Insruction*/
			else{ 
				fprintf(stderr,"LINE %d: Eror, undefined instruction:%s\n",L.index,L.cmd);
				*Syntax_Eror = False;
				}
				
			return True;
			}
	

		/*Command after label - instruction is not .entry/.extern/.data/.string/.define */
		else
		{	
			/*gets data after command*/	
			str_val = strtok(NULL,"\0");
			
			/*checks valid data after command*/
			if(str_val)
				strcpy(L.data,str_val);
				
			/*Go to Instruction row*/
			return False;
			}
		}
	
	
	/*L.label stores Instruction - .entry/.extern/.define*/
	else{ 
	
		/*Gets data after a Instruction*/
		str_val = strtok(NULL,"\0");
		
		/*Checks data after a Instruction*/	
		if(!str_val||isEmptyRow(str_val))
		{
			/*Instruction is .entry /.extern /.define */
			if(!strcmp(L.label,ENTRY_STR)||!strcmp(L.label,EXTERN_STR)||!strcmp(L.label,DEFINE_STR))
			{
				/*invalid insturction without data*/
				fprintf(stderr,"LINE %d: missing parameter after %s.\n",L.index,L.label);
				*Syntax_Eror = False;
				return True;
				}
			/*Instruction is a command - go to Instruction row*/	
			else{
				return False;
				}
			}
		
		/*clear white char from data after insturction*/
		str_val = clearWhiteChar(str_val);
		
		/*L.data stores data of insturction*/
		strcpy(L.data,str_val);
			
		}	
		
	
	/*L.label is Entry*/ 
	if(!strcmp(L.label,ENTRY_STR))
	{
		int label_type;							/*gets the label type*/
		int label_add;							/*get the label address*/
		
		/*Checks data of .entry: .entrys data is a label*/
		if(!isValidLabel(L.data))
		{
			/*data is not a label*/
			*Syntax_Eror = False;
			return True;
		}
		
		/*Insert entry label to entry file - Second scan*/
		if(scan == SECOND_SCAN){
		
			/*Gets memory address of "entry label":
			Checks that label is declared in program*/
			if((label_type = getLabelAddress(L.data,&label_add)) == Eror){
				fprintf(stderr,"Eror, Label:%s is not declared.\n",L.data);
				*Syntax_Eror = False;
				}
				
			/*Checks Label is not a macro and not external*/	
			else if(label_type == MACRO || label_type == EXTERNAL){
				fprintf(stderr,"Eror, Label: %s is not internal label.\n",L.data);
				*Syntax_Eror = False;
				}
				
			else
				/*Enter label to list for writing into entry file*/
				EnterItemAddress(L.data,label_add,ENTRY);
			}
		return True;	
	}	
	
	
	/*L.label is Extern */
	if(!strcmp(L.label,EXTERN_STR))
		{
			int eror_type;					/*indicates the eror type*/
			
			if(scan == SECOND_SCAN)
				return True;
				
			/*Checks data of extern: externs data is a label*/
			if(!isValidLabel(L.data))
			{
				/*data is not a label*/
				*Syntax_Eror = False;
				return True;
			}	
			
			
			temp_val = removeSpaces(L.data);
			
			/*extern labels will be inserted to symbol table in first scan*/
			if(scan == FIRST_SCAN)
			{
				/*insert extern Label to symbol-table*/
				if((eror_type =insertSymbol(temp_val,False,False,EXTERNAL)) != True){
					/*extern label is defined in file*/
					if(eror_type == False){
						fprintf(stderr,"Line %d: Label: %s, is already defined in program.\n",
						L.index,temp_val);
						*Syntax_Eror = False;
					}
					else{
						fprintf(stderr,"Eror - Failure by allocating memory.\n");
						*Syntax_Eror = False; 
					} 
				}
				return True;	
			}
		}

	
	/*L.label is Define*/
	if(!strcmp(L.label,DEFINE_STR))
		{	
			
			int macro_num;				/*Gets the value number of macro*/
			char* macro_name;			/*Gets the macro label name*/
			int index;						/*index stores the length of macros label name*/
			index = 0;
			
			/*Define declaration includes '=' */
			temp_val = strchr(L.data,'=');
			
			/*Invalid define declaration*/
			if(!temp_val){
				fprintf(stderr,"LINE %d: Eror, missing '=' in define declaration.\n",L.index);
				*Syntax_Eror = False;
				return True;
				}
			
			
			else{	
				/*index stores the length of macros label name*/
				index = temp_val - L.data;
				
 				/*name of macro will be saved in L.cmd*/
 				macro_name = (char*)malloc(sizeof(L.data));
 				strncpy(macro_name,L.data,index);
 			
				macro_name = clearWhiteChar(macro_name);
				
				/*Checks valid macro label*/
				if(!isValidLabel(macro_name)){
					fprintf(stderr,"LINE %d: Eror, undefined macro label.\n",L.index);
					*Syntax_Eror = False;
					return True;
				}
				
				/*Gets macro's value number*/
				temp_val = strrchr(L.data,'=');
				
				if(*temp_val == '=')
					temp_val++;
			
				temp_val = clearWhiteChar(temp_val);		
				
				/*Set default macro number value*/
				macro_num = 0;
				
				/*Checks valid number of macro*/
				if(!isValidNumber(temp_val,&macro_num))
				{
					/*macro number is invalid*/
					*Syntax_Eror = False;
					fprintf(stderr,"macro %s is undefined\n",macro_name);
					return True;
				}
					
				/*In first scan - insert macro label to symbol table*/
				if(scan == FIRST_SCAN)
				{
					int eror_type;							/*indicates the eror type*/
					
					/*inset macro to symbol table*/
					if((eror_type = insertSymbol(macro_name,macro_num,True,MACRO))!=True)
					{	
							if(eror_type == False)
							{	
								/*macro name is invalid*/
								fprintf(stderr,"Line %d: Eror - name of macro is invalid.\n",L.index);
								*Syntax_Eror = False;
							}
							else {
								fprintf(stderr,"Eror - Failure by allocating memory.\n");
								*Syntax_Eror = False; 
								} 
							}	
					return True;
					}
				return True;
				}
			}
/* Assembly row is not a declaration row*/	
return False;
}





