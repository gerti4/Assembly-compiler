/*---------------------------------------------------------------------
	NAME					:	PAZ GERTI.
	ID						:	308328053.
	DESCRIPTION		: the program gets assembly computer instruction and converts them
									into a pattern of bits that the computer processor can use to perform its
									basic operation.
---------------------------------------------------------------------------*/									
#include "Main.h"


/*
	Main:
		the main function gets assembly files from the terminal.
		its send the files to the assembler function.
--------------------------------------------------------------*/
int main(int argc,char** argv)
{
	
	char **asFile;								/*a poniter to assembly file */ 
	asFile = argv;
	
	/*Gets assembly file*/
	asFile++;
	
	/*Send assembly files to the assembler function*/
	assembler(asFile);
	
	
	return 0;
}


























































