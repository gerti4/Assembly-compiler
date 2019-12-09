#define INSTRUCTION 1
#define INSTRUCTION_ELEMENTS 16
#define INSTRUCTION_WITH_OPERANDS 14	

/*Validition of operands for insturctions*/	
enum { UNDEFINED = -1 , IMMEDIATE, DIRECT , MATRIX , REGISTER , ALL /*All operands are valid*/};


/*Label types*/
enum { EXTERNAL = 1 , ENTERNAL , ENTRY , MACRO };


/*System_Cmd contains the names of programs instructions*/
char* System_Cmd[INSTRUCTION_ELEMENTS] = {
	"mov",
	"cmp",
	"add",
	"sub",
	"not",
	"clr",
	"lea",
	"inc",
	"dec",
	"jmp",
	"bne",
	"red",
	"prn",
	"jsr",
	"rts",
	"stop"
	};


/*System operands contains the invalid operands type for each instruction.
	ALL - all operand are valid.
	IMMEDIATE - immediate addressing is invalid.
	DIRECT - direct addressing is invalid.
	MATRIX - final index addressing is invalid
	REGISTER - register addressing is invalid
	UNDEFINED - no operands
	*/
int System_Operands[INSTRUCTION_WITH_OPERANDS][2][2] = 
{
	/*mov*/{{ALL,ALL},{IMMEDIATE,ALL}},
	/*cmp*/{{ALL,ALL},{ALL,ALL}},
	/*add*/{{ALL,ALL},{IMMEDIATE,ALL}},
	/*sub*/{{ALL,ALL},{IMMEDIATE,ALL}},
	/*not*/{{UNDEFINED,UNDEFINED},{IMMEDIATE,ALL}},
	/*clr*/{{UNDEFINED,UNDEFINED},{IMMEDIATE,ALL}},
	/*lea*/{{IMMEDIATE,REGISTER},{IMMEDIATE,ALL}},
	/*inc*/{{UNDEFINED,UNDEFINED},{IMMEDIATE,ALL}},
	/*dec*/{{UNDEFINED,UNDEFINED},{IMMEDIATE,ALL}},
	/*jmp*/{{UNDEFINED,UNDEFINED},{IMMEDIATE,MATRIX}},
	/*bne*/{{UNDEFINED,UNDEFINED},{IMMEDIATE,MATRIX}},
	/*red*/{{UNDEFINED,UNDEFINED},{IMMEDIATE,ALL}},
	/*prn*/{{UNDEFINED,UNDEFINED},{ALL,ALL}},
	/*jsr*/{{UNDEFINED,UNDEFINED},{IMMEDIATE,MATRIX}}
};



extern Line L;												/*Line stores data from assembly row*/
extern long IC;												/*Instructions counter*/


OpType Operand_tmp;										/*Gets instructions opernds*/
OpType Undefined;											/*Undefined opernad*/
OpType Eror_Op;												/*Invalid operand*/



