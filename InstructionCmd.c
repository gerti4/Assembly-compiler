#include "Instruction.h"

/*
	isInstruction:
		this methods gets a Line from declerationCmd.
		Line stores the data from assembly row.
		its read the information from Line: L.label,L.cmd and L.data and set it in tmpCmd.
		tmpCmd represents an assembly insruction with operands.
		returns False by eror, other wise returns True. 
---------------------------------------------------------*/
int isInstructionRow(Line L,int scan,int* Syntax_Eror)
{
	
	Command tmpCmd;										/*Stores an assembly instruction with operands*/
	
	
	/*Instruction has no a label*/
	if(!strcmp(L.cmd,END_OF_STRING))
	{
		
		/*gets instruction index*/
		tmpCmd.index = getCmdType(L.label);

		/*Instruction is undefined*/
		if(tmpCmd.index == Eror){
			fprintf(stderr,"LINE %d: Eror, invalid syntax:%s.\n",L.index,L.label);
			*Syntax_Eror = False;
			return False;
			}
		
		/*Set addressing type of the operands Immediat,Direct,Matrix,Register
			and gets their data*/
		if(!setOperandType(&tmpCmd,L.data,Syntax_Eror)){
			/*operands data or addressing type is invalid*/
			*Syntax_Eror = False;
			return False;
			}
		}
	
	/*Instruction has a label*/	
	else {	
		
		int eror_type; 							/*Indicates the eror type*/
		
		/*Checks valid label*/	
		if(!isValidLabel(L.label)){
			*Syntax_Eror = False;
			return True;
			}
			
		if(scan == FIRST_SCAN){
			/*Insert label of instruction to symbol table*/
			if((eror_type = insertSymbol(L.label,IC,True,False,False))!=True){
				if(eror_type == False){
					/*label is already defined in program*/
					fprintf(stderr,"Line %d: Eror - Label: %s, is already defined in program.\n",
							L.index,L.label);
					*Syntax_Eror = False;
					} 
				else{
					fprintf(stderr,"Eror - Failure by allocating memory.\n");
					*Syntax_Eror = False; 
					}
				/*Instruction label cannot be inserted into symbol table*/
				return False;		
				}
			}
		
		/*Gets instruction index */
		tmpCmd.index = getCmdType(L.cmd);
		
		/*Instruction is undefined*/
		if(tmpCmd.index == Eror){
			printf("\nLine %d: Eror - invalid insturction %s.\n",L.index,L.cmd);
			*Syntax_Eror = False;
			return False;
			}
		
		/*Set addressing type of the operands Immediat,Direct,Matrix,Register*/
		if(!setOperandType(&tmpCmd,L.data,Syntax_Eror)){
			/*operands data or addressing type is invalid*/
			*Syntax_Eror = False;
			return False;
			}
		}
		
	/*Checks valid operands for the given insturction*/
	if(!opcodeParam(tmpCmd))
	{
		/*undefined operands for the given instruction*/
		*Syntax_Eror = False;
		return False;
	}
	
	
	/*Encode data in Second scan*/
	if(scan == SECOND_SCAN){
		
		/*creates a machine code for the given instruction*/	
		/*coding the insturction to the binarycode array*/
		if(!encode(tmpCmd,tmpCmd.src,tmpCmd.dst)){
			*Syntax_Eror = False;
			return False;
			}
		}
	return True;
}
	
		
	

		
		
		
		
