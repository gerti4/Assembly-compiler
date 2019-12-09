Assembler.o: main.o assembler.o AssemblerRules.o firstscan.o DeclarationCmd.o InstructionCmd.o CmdRules.o SymbolTable.o DataTable.o secondscan.o binarycode.o files.o
	gcc	-g -Wall -ansi -pedantic main.o assembler.o AssemblerRules.o firstscan.o DeclarationCmd.o InstructionCmd.o CmdRules.o SymbolTable.o DataTable.o secondscan.o binarycode.o files.o -o Assembler
	
main.o: main.c Main.h
	gcc -c -Wall -ansi -pedantic main.c -o main.o

assembler.o: assembler.c Assembler.h
	gcc -c -Wall -ansi -pedantic assembler.c -o assembler.o
	
AssemblerRules.o: AssemblerRules.c AssemblerRules.h GlobalVar.h
	gcc -c -Wall -ansi -pedantic AssemblerRules.c -o AssemblerRules.o
	
firstscan.o: firstscan.c FirstScan.h
	gcc -c -Wall -ansi -pedantic firstscan.c -o firstscan.o

DeclarationCmd.o: DeclarationCmd.c Declaration.h
	gcc -c -Wall -ansi -pedantic DeclarationCmd.c -o DeclarationCmd.o
	
InstructionCmd.o: InstructionCmd.c Instruction.h
	gcc -c -Wall -ansi -pedantic InstructionCmd.c -o InstructionCmd.o
	
CmdRules.o: CmdRules.c CmdRules.h CmdVariables.h
	gcc -c -Wall -ansi -pedantic CmdRules.c -o CmdRules.o
	
SymbolTable.o: SymbolTable.c SymbolTable.h
	gcc -c -Wall -ansi -pedantic SymbolTable.c -o SymbolTable.o
	
DataTable.o: DataTable.c DataTable.h
	gcc -c -Wall -ansi -pedantic DataTable.c -o DataTable.o
	
secondscan.o: secondscan.c SecondScan.h 
	gcc -c -Wall -ansi -pedantic secondscan.c -o secondscan.o

binarycode.o: binarycode.c binarycode.h
	gcc -c -Wall -ansi -pedantic binarycode.c -o binarycode.o
	
files.o: files.c Files.h
	gcc -c -Wall -ansi -pedantic files.c -o files.o
