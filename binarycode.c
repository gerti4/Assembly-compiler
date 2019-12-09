#include "binarycode.h"

/*
		encode:
			this method gets an instruction with operands and encode them to a bincary code.
			Command m - represent the instrucrion row data.
			OpType s - represent the source operand.
			OpType d - represent the destination operand.
			returns True if the given insturction encoded seccssfuly, otherwise False.
------------------------------------------------------------------------*/
int encode(Command m,OpType s,OpType d)
{
/*

First define the command line:

	Unused - BITS 10-13.
	Opcode - BITS 6-9.
	Source operand - BITS 4-5.
	Destination operand - BITS 2-3.
	ARE indication - BITS 0-1.
-----------------------------------------------------------------------------*/

/* binary command variable to store the command line*/
	MachineCmd bcmd;
	
	/*Checks memory place for storing machine codes*/
	if(code_row_cnt >= MAX_MEMORY_SIZE){
		fprintf(stderr,"Eror - Memory is full, assembly file cannot be compiled.\n");
		return False;
		}
		
		
	bcmd.Unused = UNUSED_BITS;
	
	/* opcode gets the index of the instruction */
	bcmd.Opcode = m.index;
	
	/*checks if there is a source operand*/
	if(m.src.type== UNDEFINED_OPERAND)
		bcmd.Src = UNUSED_BITS;
		
	/* gets the source operand type */	
	else
		bcmd.Src = m.src.type;

	/*checks if the both opernds are registers*/
	if(m.dst.type == TWO_REGISTERS)
	
		/*initialize the destination operand to be 3 - register addressing.*/
		bcmd.Dst = REGISTER_ADDRESSING;
	
	/*checks if there is destination operand*/
	else if(m.dst.type == UNDEFINED_OPERAND)
		bcmd.Dst = UNUSED_BITS;
		
	else
		bcmd.Dst = m.dst.type;

	
	/*first command line is absolute*/
	bcmd.ARE = ABSOLUTE;
	
	/*gets the IC of this command*/
	bcmd.cmdAddress = m.address;
	
	/*creates the machine code of the command line. */	
	setBinaryCode(COMMAND_LINE,bcmd);
	
	

/*
Source operand and Destination operand are both registers:

	Unused - BITS 8-13.
	Source operand - BITS 5-7.
	Destination operand - BITS 2-4.
	ARE indication - BITS 0-1.	
-----------------------------------------------------------------*/

	if(m.src.type == Register && m.dst.type == TWO_REGISTERS)
	{
		
		/* binary line that stores 2 registers */
		MachineReg reg;
		
		reg.Unused = UNUSED_BITS;
		/*gets the register number in source operand*/ 
		reg.Src = m.src.data;
		
		/*gets the register number in destintion operand*/ 
		reg.Dst = m.dst.data;
		
		/*register line is absolute*/
		reg.ARE = ABSOLUTE;
		
		/* the binary line gets the source operand address - 2 register has written in one line.*/
		reg.regAddress = m.src.opAddress;
		
		/* creates the machine code of the registers line. */
		setBinaryCode(REGISTER_LINE,reg);
	}
	
	
/*
Source operand is register:

	Unused - BITS 8-13.
	Source operand - BITS 5-7.
	Destination operand - BITS 2-4.
	ARE indication - BITS 0-1.	
------------------------------------------------------------*/
	if(m.src.type == Register && m.dst.type != TWO_REGISTERS)
	{
		
		/* binary line that store register. */
		MachineReg reg;
		
		reg.Unused = UNUSED_BITS;
		
		/*source operand gets 3 - register addressing*/
		reg.Src = m.src.data;
		
		reg.Dst = UNUSED_BITS;
		
		/*register is absolute*/
		reg.ARE = ABSOLUTE;
		
		reg.regAddress = m.src.opAddress;
	
		/* creates the machine code of the registers line. */
		setBinaryCode(REGISTER_LINE,reg);
	}
	
/*

Source operand is a label:

	value - represent the memory address of label: BITS 2-13.
	ARE indication - label can be external or relocatable: BITS 0-1.	
------------------------------------------------------------------*/
	if(m.src.type == DIRECT_ADDRESSING)
	{
		int label_type;					/*Gets the label type*/
		
		/*binary line that stores memory address*/
		MachineNum label;
		
		/*
		 label_type indicate if the label is external or relocatable.
		 m.src.data gets the memory address of label. */
		label_type = getLabelAddress(m.src.label,&m.src.data);
		
		if((label_type = getLabelAddress(m.src.label,&m.src.data)) == Eror){
			fprintf(stderr,"Second-scan: Eror - undefined label name:%s.\n",m.src.label);
			return False;
			}
		
		/*if label is external , insert to list of external labels*/
		if(label_type == EXTERNAL)
		{
			/*set External*/
			label.ARE = EXTERNAL;
			if(m.index <= INSTURCTION_TWO_OPERANDS ||m.index == LEA_INST){
				if(m.dst.type == MATRIX_ADDRESSING)
					/*External label address is IC-3*/
					EnterItemAddress(m.src.label,IC-3,EXTERNAL);
				else
					/*External label address is IC-2*/
					EnterItemAddress(m.src.label,IC-2,EXTERNAL);
				}
			else
				/*External label address is IC-1*/
				EnterItemAddress(m.src.label,IC-1,EXTERNAL);
			}
		
		/*lebal is relocateable*/
		else 
			label.ARE = RELOCATABLE;
			
		/*Number gets the memory address of the label in source operand*/ 
		label.Number = m.src.data;
		
		/*machine code that stores label address gets the address of source operand*/
		label.numAddress = m.src.opAddress;

		
		/*creates the binary code of the label memory address line. */
		setBinaryCode(NUMBER_LINE,label);
	}
	
/*

Source operand is a matrix:
	builded from two binary lines:
	fisrt - "label": - value - represent the memory address of label: BITS 2-13.
				           - ARE indication - label can be external or relocatable: BITS 0-1.
	second - "num":  - value - represent the matrix index number: BITS 2-13.
				           - ARE indication - index is absolute: BITS 0-1.
		
---------------------------------------------------------------*/	
	if(m.src.type == MATRIX_ADDRESSING)
	{
		/* "label" - stores the matrix name.
			 "num" - stores the matrix's index. */
		MachineNum label,num;
		
		int val,label_type;
		
		/*
		 label_type indicate if the label is external or relocatable.
		 val gets the memory address of the matrix label. */
		label_type = getLabelAddress(m.src.label,&val); 
		
		/*checks label is valid*/
		if(label_type == Eror){
			fprintf(stderr,"Second-scan: Eror - undefined label name:%s.\n",m.src.label);
			return False;
			}
		
		/*if label is external , insert to list of external labels*/
		else if(label_type == EXTERNAL)
		{
			/*set External*/
			label.ARE = EXTERNAL;
			if(m.index <= INSTURCTION_TWO_OPERANDS||m.index ==LEA_INST){
				if(m.dst.type == MATRIX_ADDRESSING)
					/*External label address is IC-4*/
					EnterItemAddress(m.src.label,IC-4,EXTERNAL);
				else
					/*External label address is IC-3*/ 
					EnterItemAddress(m.src.label,IC-3,EXTERNAL);
				}
				else 
				/*External label address is IC-1*/ 
				EnterItemAddress(m.src.label,IC-1,EXTERNAL);
			}
		
		/*label is relocatable*/
		else	
			label.ARE = RELOCATABLE;
		
		/*gets the memory address of the label in source operand*/ 	
		label.Number = val;
		
		/*address machine code store matrix label*/ 
		label.numAddress = m.src.opAddress-1;
		
		
		/*creates the binary code of the label memory address line. */
		setBinaryCode(NUMBER_LINE,label);
		
		/*gets the matrix index*/
		num.Number = m.src.data;
		
		/*set absolute*/
		num.ARE = ABSOLUTE;
		
		/*address machine code stores matrix index*/
		num.numAddress = m.src.opAddress;
		
		
		/*creates the binary code of the matrix index. */
		setBinaryCode(NUMBER_LINE,num);
	}
	
	
/*
Source operand is Immediate type:
	
	Number - stores the immediate number: BITS - 2-13.
	ARE indication - immediate number is absolute: BITS 0-1.
-----------------------------------------------------------*/	
	if(m.src.type == IMMEDIATE_ADDRESSING )
	{
		/*binary line that stores a number*/
		MachineNum num;
		
		/*m.src.data stores the number*/
		num.Number = m.src.data;
		
		/*set Absolute*/
		num.ARE = ABSOLUTE;
		
		/*machine code address stores number*/
		num.numAddress = m.src.opAddress;
		
		/*create a machine code stores number*/
		setBinaryCode(NUMBER_LINE,num);
	}
	
/*
Destination operand is register:

	
	Unused - BITS 8-13.
	Source operand - BITS 5-7.
	Destination operand - BITS 2-4.
	ARE indication - BITS 0-1.	
---------------------------------------------------------*/
	if(m.dst.type == REGISTER_ADDRESSING)
	{
		/*binary line that store register. */
		MachineReg reg;
		
		reg.Unused = UNUSED_BITS;
		
		/*source operand gets valoue of zero.*/
		reg.Src = UNUSED_BITS;
		
		/*reg.DST gets the register number*/ 
		reg.Dst = m.dst.data;
		
		/*register is absolute*/
		reg.ARE = ABSOLUTE;
		
		/*gets the memory address of this line.*/
		reg.regAddress = m.dst.opAddress;
		
		setBinaryCode(REGISTER_LINE,reg);
	}
	
	
/*

Destination operand is a label:

	value - represent the memory address of label: BITS 2-13.
	ARE indication - label can be external or relocatable: BITS 0-1.
-----------------------------------------------------*/
	if(m.dst.type == DIRECT_ADDRESSING)
	{
		int label_type;
		/*binary line that stores memory address*/
		MachineNum label;
		
		/*
		 label_type indicate if the label is external or relocatable.
		 m.dst.data gets the memory address of label. */
		label_type = getLabelAddress(m.dst.label,&m.dst.data);
		
		if(label_type == Eror){
			fprintf(stderr,"Second-scan: Eror - undefined label name:%s.\n",m.dst.label);
			return False;
			}
		
		else if(label_type == EXTERNAL)
		{
			/*set Extrenal*/
			label.ARE = EXTERNAL;
			/*external label address is IC -1*/
			EnterItemAddress(m.dst.label,IC-1,EXTERNAL);
			}
		
		/*label is relocatable*/
		else
			label.ARE = RELOCATABLE;
		
		
		/*Number gets the memory address of the label in source operand*/
		label.Number = m.dst.data;
		
		/*set the memory address machine code stores label address*/
		label.numAddress = m.dst.opAddress;
		
		/*creates machine code store label address*/
		setBinaryCode(NUMBER_LINE,label);
		
	}
	
/*
Destination operand is a matrix:
	builded from two binary lines:
	fisrt - "label": - value - represent the memory address of label: BITS 2-13.
				           - ARE indication - label can be external or relocatable: BITS 0-1.
	second - "num":  - value - represent the matrix index number: BITS 2-13.
				           - ARE indication - index is absolute: BITS 0-1.
-------------------------------------------------------------------------------*/	
	if(m.dst.type == MATRIX_ADDRESSING)
	{
		
		/*label stores the matrix label, num stores the matrix index*/
		MachineNum label,num;
		
		int temp_label,val;
		
		/*
		 label_type indicate if the label is external or relocatable.
		 val gets the memory address of the matrix label. */
		temp_label = getLabelAddress(m.dst.label,&val);
		
		if(temp_label== Eror){
			fprintf(stderr,"Second-scan: Eror - undefined label name:%s.\n",m.dst.label);
			return False;
		}
		
		/*Label is external*/
		else if(temp_label == EXTERNAL)
		{
			/*set External*/
			label.ARE = EXTERNAL;
			/*external label is IC-1*/
			EnterItemAddress(m.dst.label,IC-2,EXTERNAL);
			}
		
		/*label is relocatable*/
		else	
			label.ARE = RELOCATABLE;
			
		/*gets the memory address of the label in source operand*/ 	
		label.Number = val;
		
		/*set address of machine code stores matrix label*/ 
		label.numAddress = m.dst.opAddress-1;
		
		/*creates the machine code of the matrix label. */
		setBinaryCode(NUMBER_LINE,label);
		
		/*gets the matrix index*/
		num.Number = m.dst.data;
		
		/*number is absolute*/
		num.ARE = ABSOLUTE;
		
		/*set machine code address store matrix index*/
		num.numAddress = m.dst.opAddress;
		
		
		/*creates the machine code of the matrix index. */
		setBinaryCode(NUMBER_LINE,num);
		return True;
		
	}
	
/*
Destination operand is Immediate type:
	
	Number - stores the immediate number: BITS - 2-13.
	ARE indication - immediate number is absolute: BITS 0-1.
-----------------------------------------------------------------*/	
	if(m.dst.type == IMMEDIATE_ADDRESSING )
	{
		
		/*binary line that stores a number*/
		MachineNum num;
		
		/*m.src.data stores the number*/
		num.Number = m.dst.data;
		
		num.ARE = ABSOLUTE;
		
		/*set the machine code address*/
		num.numAddress = m.dst.opAddress;
		
		/*creates machine code stores number*/
		setBinaryCode(NUMBER_LINE,num);
	}
	
	return True;
}

/*

	setBinaryCode:
		this method gets differents types of assembly row.
		for each row it encode the valid binary syntax in a machine code.
		after that the function add the machine code to array "Binarycode" that stores machinecode.
		type indicates of the row type to encode.
------------------------------------------------------------------*/
int setBinaryCode (int type,...)
{
	
	MachineCode code_line;								/*machine code to store diffrents binary coeds type*/
	unsigned int mask;										/*reads the bits from a binary code*/
	
	va_list p;														/*pointer to a binary code*/
	
	va_start(p,type);
	
	
/*
	Insturction row:
		the function encode an instruction in a machine code.
-----------------------------------------------*/	
	if(type == COMMAND_LINE)
	{
		
		MachineCmd tmp;
		
		/*Gets the instruction row*/
		tmp=va_arg(p,MachineCmd);
		
		mask =0;
		
		/*Set the machine code for assembly instruction*/
		mask = mask | tmp.Unused;
		mask <<=4;
		mask |= tmp.Opcode;
		mask <<=2;
		mask |= tmp.Src;
		mask <<=2;
		mask |= tmp.Dst;
		mask <<=2;
		mask |= tmp.ARE;
		
		code_line.Syntax = mask;
		
		/*Set the address of machine code*/
		code_line.Address = tmp.cmdAddress;
		
		/*adding machine code to array of binaryCode*/
		binaryCode[code_row_cnt] = code_line;
		code_row_cnt++;
		
		va_end(p);
		
		return True;
	}

/*
	Register row:
		the function encode a register in a machine code
-------------------------------------------------*/	
	if(type == REGISTER_LINE)
	{
		MachineReg tmp;
		
		/*Gets the register */
		tmp=va_arg(p,MachineReg);
		
		mask = 0;
		/*Set the machine code for a register row*/
		mask = mask | tmp.Unused;
		mask <<=6;
		mask |= tmp.Src;
		mask <<=3;
		mask |= tmp.Dst;
		mask <<=2;
		mask |= tmp.ARE;
		
		
		code_line.Syntax = mask;
		
		/*set address of machine code*/
		code_line.Address = tmp.regAddress;
		
		/*adding machine code to array of binaryCode*/
		binaryCode[code_row_cnt] = code_line;
		code_row_cnt++;
		
		va_end(p);
		
		return True;
	}
	
/*
	Number row:
		tha function encode a number into a machine code.
-----------------------------------------------*/
	if(type == NUMBER_LINE)
	{
		
		MachineNum tmp;
		/*Gets the number*/
		tmp=va_arg(p,MachineNum);
		
		mask = 0;
		/*writes the number into a machine code*/
		mask = mask | tmp.Number;
		mask <<=2;
		mask |= tmp.ARE;

		code_line.Syntax = mask;
		/*Set the machine code address*/
		code_line.Address = tmp.numAddress;
		
		/*Adding machine code to array of binary code*/
		binaryCode[code_row_cnt] = code_line;
		code_row_cnt++;
		
		va_end(p);
		
		return True;
	}
	
/*
	Data row:
		data row represents the data of a label:
		- memory address of a label.
		- ascii values of characters.
		- numbers.
		the function ancodes the data into a machine code.
------------------------------------------------*/
if(type == DATA_LINE)
	{
		
		MachineData tmp;
		/*Gets the data*/
		tmp=va_arg(p,MachineData);
		
		/*Sets the data in a machine code*/ 
		mask = 0;
		mask = mask | tmp.Value;
		
		code_line.Syntax = mask;
		
		/*Set the address of a machine code*/
		code_line.Address = tmp.dataAddress;
		
		/*Adding the machine code to array of binaty codes*/
		binaryCode[code_row_cnt] = code_line;
		code_row_cnt++;
		
		va_end(p);
		
		return True;
	}
	
	/*binary line is undefined*/
	return False;
} 
/*

	ResetBinaryCode:
		the mathod removes the machine codes from the array binaryCode.
-----------------------------------------------------*/
void ResetBinaryCode()
{
	int i;
	for(i=0;i<code_row_cnt;i++)
	{
		binaryCode[i].Address = 0;
		binaryCode[i].Syntax = 0;
	}
}




		






