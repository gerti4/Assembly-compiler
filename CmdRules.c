#include "CmdRules.h"
#include "CmdVariables.h"
/*

	getCmdType:
		this method gets the command name in string, and return its numeric value
		that stored in the array System_Cmd.
		if the command is undefined return Eror.*/
/*---------------------------------------------------------*/
int getCmdType(char *name)
{
	
	int index;							/*Store numeric value of instruction*/

	for(index=0;index<INSTRUCTION_ELEMENTS;index++){
		if(!strcmp(System_Cmd[index],name))	
			return index;
		}
	return Eror;
}
/*

	setOperandType:
		this method initializes the addressing types of the operands in the command variable.
		"data" represent the instructions operands .
		if there is any eror , the function update the variable compile.
		returns True if operands are valid , other wise return False.
-------------------------------------------------------------*/
int setOperandType (Command* cmd,char* data,int *compile)
{
	char* first_op;								/*Gets first opernad*/ 
	char* second_op;							/*Gets second_operand*/
/* 

		Insturctions without operands
------------------------------------------------*/
	if(cmd->index >= INSTRUCTION_WITH_OPERANDS){
		
		/*No operands*/
		if(!data || isEmptyRow(data)){
			
			/*Instruction memory address*/
			cmd->address = IC;
			
			/*No source and destination operands*/
			cmd->src.type = Eror;
			cmd->dst.type = Eror;
			
			IC += ONE_CELL_MEMORY;
			}
		else {
			/*Text after instruction without operands*/
			fprintf(stderr,"LINE %d: Invalid syntax after instruction %s.\n",
			L.index,System_Cmd[cmd->index]);
			return False;
			}
		}
/*

		 Instruction with two operands
---------------------------------------------------------------------*/
	else if(System_Operands[cmd->index][0][0] != UNDEFINED){
		
		/*Checks operands Syntax */
		if(!data||isEmptyRow(data)){
			fprintf(stderr,"LINE %d: Missing parameters after: %s.\n",
			L.index,System_Cmd[cmd->index]);
			return False;
			}
		
		first_op = clearWhiteChar(L.data);
		
		/*Checks valid commas between operands*/
		if(!checkCommaPos(first_op,INSTRUCTION)){
			*compile = False;
			return True;
			}
		
		
		removeSpaces(data);
		
		/*Gets destination operand*/
		second_op =(char*)malloc(sizeof(char)*MAX_ROW_LENGTH);
		second_op = strchr(data,COMMA);
		
		/*Checks that a destination operand is exsist*/
		if(!second_op){
			fprintf(stderr,"LINE %d: Missing prameter for insruction %s.\n",
			L.index,System_Cmd[cmd->index]);
			*compile = False;
			return True;
			}
		
		if(*second_op==COMMA)
			second_op ++;
		
		/*Gets source operand*/	
		first_op = strtok(data,STRING_COMMA);
	
	
		/*Checks a valid source operand */
		if(isEror(cmd->src = getOperand(first_op))) {
			fprintf(stderr,"LINE %d: Invalid source operand %s.\n",L.index,first_op);
			*compile = False;
			}
			
		/*Checks a valid destination operand*/
		if(isEror(cmd->dst = getOperand(second_op))){
			fprintf(stderr,"LINE %d: Invalid destination operand %s.\n",L.index,second_op);
			*compile = False;
			}
		
		/*If operands are invalid - don't update IC*/
		if(*compile == False)
			return True;
			
			
		/*Set IC:
		Command address gets current IC*/
		cmd->address = IC;	
/*


		Set Source operand address:
-----------------------------------------------*/

		/*Source operand is register*/
		if((*cmd).src.type == REGISTER){
		
			/*Specail case Destination operand is register*/
			if((*cmd).dst.type == REGISTER)
				/*Two registers in on machine code*/
				(*cmd).dst.type = TWO_REGISTERS;
			
			
			IC += ONE_CELL_MEMORY;
			/*Set source operand memory address*/
			(*cmd).src.opAddress = IC;
			}
		
		/*Source operand is Matrix*/
		else if((*cmd).src.type == MATRIX){
		 	IC += TWO_CELLS_MEMORY;
		 	/*Set source operand memory address*/
		 	(*cmd).src.opAddress = IC;
			}
		
		/*Source operand is a label or number*/
		else{
			IC += ONE_CELL_MEMORY;
			/*Set source operand memory address*/
			(*cmd).src.opAddress = IC;
			}		
/*	


			Set Destination operand address:
-----------------------------------------------*/

		/*Destination operand is Matrix*/
		if((*cmd).dst.type == MATRIX){
			IC += TWO_CELLS_MEMORY;
			(*cmd).dst.opAddress = IC;
			}
		
		else if((*cmd).dst.type != TWO_REGISTERS){
			/*Destination operand is label, register or number*/
			IC += ONE_CELL_MEMORY;
	
			/*Set destination operand memory address*/
			(*cmd).dst.opAddress = IC;
			}
			
		IC++;
		return True;	
	}
/*
		
		 Instruction with one operand
----------------------------------------------------------------*/
	else if(System_Operands[cmd->index][0][0] == UNDEFINED){
		
		/*Source operand is undefind*/
		cmd->src.type = ALL;
		
		/*Checks operands Syntax */
		if(!data||isEmptyRow(data)){
			fprintf(stderr,"LINE %d: Missing parameters after: %s.\n",
			L.index,System_Cmd[cmd->index]);
			return False;
			}
			
		/*gets destination operand*/
		first_op = strtok(data,END_OF_STRING);
		
		/*Checks that destination operand exsist*/
		if(!first_op || isEmptyRow(first_op)){
			fprintf(stderr,"LINE %d: Missing prameter for insruction %s.\n",
			L.index,System_Cmd[cmd->index]);
			*compile = False;
			return True;
			}	
		
		first_op = clearWhiteChar(first_op);
		
		/*Checks operand syntax*/
		if(!checkSpaces(first_op)){
			fprintf(stderr,"LINE %d: Invalid operand of insturction %s.\n",
			L.index,System_Cmd[cmd->index]);
			*compile = False;
			return True;
			}
		
		removeSpaces(data);
		
		
		/*Checks a valid  destination operand*/
		if(isEror(cmd->dst = getOperand(data))){
			/*destination operand is invalid*/
			fprintf(stderr,"LINE %d: Invalid destination operand %s.\n",L.index,data);
			*compile = False;
			return True;
			}
		
		
		/*Set IC:
		Command address gets current IC*/
		cmd->address = IC;
		
		/*Destination operand is matrix*/		 
		if(cmd->dst.type == MATRIX){
			IC += TWO_CELLS_MEMORY;
			/*Set destination operand memory address*/
			cmd->dst.opAddress = IC;
			}
		
		/*Destination operand is label/number/register*/
		else{
			IC += ONE_CELL_MEMORY;
			/*Set destination operand memory address*/
		  cmd->dst.opAddress = IC;
			}	 
		++IC;
	}

	return True;
}
/*


	getOperand:
			the method gets a string.
			that string represent the operand element.
			it checks the operand type (Number/Label/Register/Matrix) and its value.
			returns the operands type with its data.
---------------------------------------------------------------------*/		
OpType getOperand(char* str_operand)
{
	int eror_type;									/*indicates the eror type*/
	
	/*Undefined Operand*/
	Undefined.type = DEFAULT;
	Undefined.data = DEFAULT;
	
	/*Invalid Operand*/
	Eror_Op.type = Eror;
	Eror_Op.data = Eror;
	
	Operand_tmp = Undefined;

	/*Operand is a number*/
	if((eror_type = isNumber(&Operand_tmp,str_operand)) == True){
		return Operand_tmp;
		}
		
	/*Checks that opreand has an eror*/
	if(eror_type != Eror){
		/*Operand is a register*/
		if((eror_type = isRegister(&Operand_tmp,str_operand)) == True)
			return Operand_tmp;
		}

	/*Checks that opreand has an eror*/
	if(eror_type != Eror){
		/*Operand is a Matrix*/
		if((eror_type = isMatrix(&Operand_tmp,str_operand)) == True)
			return Operand_tmp;
		}
		
	/*Checks that opreand has an eror*/
	if(eror_type != Eror){
		/*Operand is a label*/
		if((eror_type = isLabel(&Operand_tmp,str_operand)) == True)
			return Operand_tmp;
		}
	
	/*Operand is undefined or invalid*/	
		return Eror_Op;
}
/*


	 isRegister:
			this method checks if the operand a register.
			returns True if operand is register.
			returns False if it is not.
			returns Eror if the register is invalid
------------------------------------------------------------------*/	
int isRegister (OpType* op,char* operand)
{
	int reg_num;						/*register number*/
	
	/*Checks first letter of the string*/
	if((*operand)=='r'){
		operand++;
		
		/*checks register string length*/
		if(!operand || isEmptyRow(operand))
			return False;
		
		/*defalut value of regsiter number*/
		reg_num = 0;

		/*Checks operand number*/	
		if(isValidNumber(operand,&reg_num)){
			/*register numbers are between 0 - 7*/
			if(reg_num >= 0 && reg_num <= 7){
				/*op type stores addressing type*/
				op->type = REGISTER;
				/*op data stores  register number.*/
				op->data = reg_num;
				return True;
				}
			else {
				/*Register numver is invalid*/
				fprintf(stderr,"LINE %d: Invalid register number %s.\n",L.index,operand);
				return Eror;
				}
			}
		}
	/*Operand is not a register*/
	return False;
}
/*


	isNumber:
			checks if the given operand is a number.	
			returns True if operand is a number.
			returns False if it is not.
			returns Eror if the number or the syntax is invalid	
------------------------------------------------------------------------------*/
int isNumber (OpType* op,char* operand) 
{
	int getNumber;						/*Gets the number from operand string*/
	int label_type;						/*stores the label type from the symbol table*/
	char *num;		
	
	/*defalut value of number*/
	getNumber = 0;
	
	num = operand;

	/*Immediate operand sign*/
	if(*num == '#'){
		num++;
		
		/*Number is macro*/
		if(!isdigit(*num) && (*num)!= '-' && (*num)!='+'){
			/*Gets macro's value*/
			if((label_type = getLabelAddress(num,&getNumber)) != MACRO){
				fprintf(stderr,"LINE %d: Undefined macro label:%s.\n",L.index,num);
				/*Undefined macro label*/
				return Eror;
				}
			else{
				/*op type stores addressing type*/
				op->type = IMMEDIATE;
				/*op data stores numbers value*/
				op->data = getNumber;
				return True;
				}
			}
			
		/*Number is not a macro, checks number*/	
		else if(isValidNumber(num,&getNumber)){
		/*op type stores addressing type*/
			op->type = IMMEDIATE;
			/*op data stores numbers value*/
			op->data = getNumber;
			return True;
			}
		else
			/*Number is invalid*/
			return Eror;
		}
		
	/*Missing '#' sign to number*/	
	if(isdigit(*num) || (*num)=='-' || (*num)=='+'){
		/*checks valid number*/
	 	isValidNumber(num,&getNumber);
	 	
		fprintf(stderr,"LINE %d: Missing immediate sign '#' for number %d.\n",
		L.index,getNumber);
		return Eror;
		}

	return False;
}
/*


	isMatrix:
			checks if the given operand is a matrix.	
			returns True if operand is a matrix.
			returns False if it is not.
			returns Eror if the index or the syntax is invalid	
--------------------------------------------------------------------*/
int isMatrix(OpType* op,char* operand)
{
	
	char* mat_label;						/*Gets label nmae of matrix*/
	char* data;
	
	data = (char*)malloc(sizeof(operand));
	strcpy(data,operand);
	
	/*Checks valid matrix syntax*/
	if(!(mat_label = strchr(data,'[')))
		return False;
	
	/*Gets the matrix label*/	
	mat_label = strtok(data,"[");
	
	/*Checks a valid matrix label*/	
	if(mat_label && !isEmptyRow(mat_label)){
		if(isLabel(op,mat_label) == True){
			/*op label gets the label name of matrix*/
			strcpy(op->label,mat_label);
		
			/*Checks a valid matrix syntax*/
			if(!(mat_label = strtok(NULL,"\0"))){
					fprintf(stderr,"LINE %d: Missing ']' in matrix %s.\n",L.index,op->label);
					return Eror;
					}
			
			if(mat_label[strlen(mat_label)-1] == ']')
				mat_label[strlen(mat_label)-1] = '\0';
			
			/*checks that a matrix index exsist*/	
			if(!mat_label || isEmptyRow(mat_label)){
					fprintf(stderr,"LINE %d: Missing parameter in matrix %s.\n",L.index,op->label);
					return Eror;
					}
			
			/*Gets matrix index:*/	
			/*Matrix index gets '#' sign*/
			if((mat_label = addImmediateSign(mat_label))){
			
				/*Gets index number*/
				if(isNumber(op,mat_label) == True){
					/*Checks index number*/
					if(op->data < 0){
						fprintf(stderr,"LINE %d: Index of matrix has to be positiv.\n",L.index);
						return Eror;
						}
					/*op type gets addressing type*/
					op->type = MATRIX;
					return True;
					}
				return Eror;
				}
			return Eror;
			}
		}
	/*Opernd is not a matrix*/
	return False;
}
/*


	isLabel:
			checks if the given operand is a label.	
			returns True if operand is a label.
			returns False if it is not.
			returns Eror if the label is macro or invalid.
------------------------------------------------------------*/
int isLabel (OpType* op,char* operand)	
{
	int label_type;						/*Gets label type extern/entry/macro/none*/
	int temp;
	
	/*Check valid Label*/
	if(!isValidLabel(operand))
		return False;
		
	/*Operand is a macro*/
	else if((label_type = getLabelAddress(operand,&temp)) == MACRO){
		fprintf(stderr,"LINE %d: Missing '#' before macro %s.\n",L.index,operand);
		return Eror;
		}
	/*Opernad is a label*/ 
	else {	
		op->type = DIRECT;
		/*op label get abel name of operand*/
		strcpy(op->label,operand);
		return True;
	}
}	
/*


	opcodeParam:
		this method checks according to the instruction, if the operands type are valid.
		return True if the insturctions operands type are valid 
		otherwise returns False.
-------------------------------------------------------------------*/
int opcodeParam (Command cmd)
{
	int seccuss;
	seccuss = True;
	
	/*command has minimum one operand*/
	if(cmd.index < INSTRUCTION_WITH_OPERANDS)
	{
		/*System_Operands instruction with their valids operands*/
	
		/*Checks source operand*/
		if(System_Operands[cmd.index][0][0] == cmd.src.type ||
			 System_Operands[cmd.index][0][1] == cmd.src.type ){
			 fprintf(stderr,"LINE %d: Source operand of instruction %s is Invalid.\n",
			 L.index,System_Cmd[cmd.index]);
		 	seccuss = False;
			}
			
		/*Checks destination operand*/	 
		if(System_Operands[cmd.index][1][0] == cmd.dst.type ||
			System_Operands[cmd.index][1][1] == cmd.dst.type ){
			 fprintf(stderr,"LINE %d: Destination operand of instruction %s is Invalid.\n",
			 L.index,System_Cmd[cmd.index]);
		 	seccuss = False;
		 	}
	}
	return seccuss;
}
/*


	isEror:
			this method checks if the operand type is an eror.
			return True if the operand type is eror
			otherwise returns False.
-------------------------------------------------*/
int isEror(OpType p){
	if(p.type == Eror)
		return True;
	return False;
}
/*


	addImmediateSign:
		this method gets a string - represent a number.
		its adding an immediate sign '#' to number.
		number can be a macro too.
		returns a new string number with # sign.
-------------------------------------------*/
char* addImmediateSign (char* number)
{
	char* newNumber;							/*represent the new number with '#' sign*/
	
	newNumber = (char*)malloc(sizeof(number)+1);
	if(!newNumber){
		fprintf(stderr,"Eror - cannot allocate memory.\n");
		return NULL;
	}
	/*Set immediate sign*/
	newNumber[0] = '#';
	strcpy(newNumber+1,number);
	return newNumber;
}


