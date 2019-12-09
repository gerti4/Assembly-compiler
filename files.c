#include "Files.h"

/*

	EnterItemAddress:
		the method gets a label with its address in the memory and the label type (External/Entry).
		the method creats a new item.
		according to the label type , the new item will be inserted to the appropriate list.
--------------------------------------------------------------------------*/
int EnterItemAddress (char* item_label, long item_address , int item_type)
{

	List *newItem;													/*Creats a new node for storing labels */
	newItem = (List*)malloc(sizeof(List));
	
	
	if(!newItem)
		fprintf(stderr,"Eror - cannot allocate memory.\n");
	
	/*Set label name and address*/
	strcpy(newItem->label,item_label);
	newItem->memory_add = item_address;
	
	newItem->next = NULL;
	
	
	/*label_type is Extrnal*/
	if(item_type == EXTERNAL){
		/*Enter label to external list*/
		if(!External_list){				/*list is empty*/
			External_list = newItem;
			exLast = newItem;
			}
		else {										/*enter to the end of list*/
			exLast->next = newItem;
			exLast = exLast->next;
			}
		}
	
	/*label_type is Entry*/
	else {
		/*Enter label to external list*/
		if(!Entry_list){					/*list is empty*/
			Entry_list = newItem;
			enLast = newItem;
			}
		else {										/*enter to the end of list*/
			enLast->next = newItem;
			enLast = enLast->next;
			}
		}
	return True;
}
/*


	getFileName:
		the method gets the name of the assembly file.
		it copies the assembly file name to the variable "FileName".
		FileName will be used to define ext and ent file names.
-------------------------------------------------------------------------------*/
void getFileName (char* assembly_file_name)
{

	FileName = (char*)calloc(sizeof(assembly_file_name),sizeof(char));
	
	strcpy(FileName,assembly_file_name);
	
	return;
}
/*


	WriteToObjectFile;
		the method creates an object file.
		it writes every binary instuction from the BinaryCode array in special 4 base.
		return True by seccuss, otherwise returns False. 
---------------------------------------------------------------*/
int WriteToObjectFile()
{
	FILE *fob;					/*pointer to Object file*/
	
	char* ObFile;				/*Stores the Object file name*/
	char* s4Base;				/*A single word in 4 special base */
	char* buf;					/*Collect 4 special words to object file*/
	unsigned int mask;	/*Variable to identify the 4 special letter from a binary code*/
	
	int i ;
	int cnt;
	
	
	ObFile = (char*)calloc(sizeof(FileName)+sizeof(OBJECT_FILE),sizeof(char));
	
	if(!ObFile){
		fprintf(stderr,"Eror - cannot allocate memory.\n");
		return False;
		}
	
	/*create an object file with the given assembly file name and with the ending of ".ob"*/
	strcpy(ObFile,FileName);
	strcat(ObFile,OBJECT_FILE);
	
	
	s4Base = (char*)malloc(sizeof(char)*BASE_4_SIZE);
	buf = (char*) malloc(sizeof(char)*MACHINE_CODE_LENGTH);
	
	/*Open file to write machine code*/
	fob = fopen(ObFile,"w");
	
	if(!fob){
		fprintf(stderr,"Eror - cannot open file:%s.\n",ObFile);
		return False;
		}
	
	
	/* Title: number of memory inctructions and number of memory data.*/
	sprintf(buf,"\t %li \t %li",IC-FIRST_CODE_ADDRESS-DC,DC);
	fputs(buf,fob);
	fputc('\n',fob);
	
		
	cnt = 0;
	
	/*gets binary code one by one , and converts is to special 4 base*/
	while(binaryCode[cnt].Address!= False && cnt <MAX_MEMORY_SIZE)
	{
		/*reads 2 bits each time*/
		mask = 3;
		
		/*builds special 4 base word*/
		for(i = 0; i<7 ;i++){
			switch(mask & binaryCode[cnt].Syntax)
			{
				case 0:	/* BITS 00*/
					s4Base[i] = '*';
					break;
					
				case 1: /*BITS 01*/
					s4Base[i] = '#';
					break;
					
				case 2: /*BITS 10*/
					s4Base[i] = '%';
					break;
					
				case 3:	/*BITS 11*/
					s4Base[i] = '!';
					break;
			}
			/*gets the next 2 bits from the binary code*/
			binaryCode[cnt].Syntax>>=2;
		}
		
		/* insert evey letter in special 4 base and the address of machine code to buf,
				in one string.*/
		if(binaryCode[cnt].Address<1000)
		{ 
			/*Adds leading zero if memory address is less than 1000*/
			sprintf(buf,"\t 0%d\t%c%c%c%c%c%c%c", /*buf store 4 base special word*/
			binaryCode[cnt].Address,s4Base[6],s4Base[5],s4Base[4],s4Base[3],
			s4Base[2],s4Base[1],s4Base[0]);
		}
		else 
		{
			/*memory address is equals or more than 1000*/
			sprintf(buf,"\t %d\t%c%c%c%c%c%c%c", /*buf store 4 base special word*/
			binaryCode[cnt].Address,s4Base[6],s4Base[5],s4Base[4],s4Base[3],
			s4Base[2],s4Base[1],s4Base[0]);
		}
		
		/*write buf to object file*/
		fputs(buf,fob);	
		fputc('\n',fob);
		
		/*gets the next binary code*/
		cnt++;
	}
	
	/*Close object file*/
	fclose(fob);
	
	/*frees allocted memory*/
	free(s4Base);
	free(buf);
	free(ObFile);


	return True;
}		
/*


	WriteToEntryFile:
		the method creates an Entry file.
		each label, who is entry , will be written in the entry file together with its value.
		all entry - labels are stores in "Entry_list".
----------------------------------------------------------------------------------------*/
void WriteToEntryFile()
{

	FILE *fent;							/*a pointer to entry file*/
	char* EntFile;					/*Stores the entry file name*/
	List *temp;							/*a pointer to list of entry labels*/
	char* buf;							/*stores entry lables with address*/
	
	
	
	/*case there are no entry - labels in the current assembly file*/
	if(!Entry_list)
		return;
	
	/*Creats entry file with name of assembly file*/
	EntFile =(char*) malloc(sizeof(FileName)+sizeof(ENTRY_FILE));
	strcpy(EntFile,FileName);
	strcat(EntFile,ENTRY_FILE);
	
	
	/*open file to write entry label and values.*/
	fent = fopen(EntFile,"w");
	if(!fent){
		fprintf(stderr,"Eror - cannot open file:%s.\n",EntFile);
		return;
	}
	
	/*buf gets entry label and memroy address and puts them together on entry file*/
	buf = (char*)malloc(sizeof(char)*MACHINE_CODE_LENGTH);
	
	/*gets an entry label one by one*/
	while(Entry_list)
	{
		if(Entry_list->memory_add<1000){
			/*Adds leading zero if memory address is less than 1000*/
			sprintf(buf,"\n\t%s \t0%li\n",Entry_list->label,Entry_list->memory_add);
			fputs(buf,fent);
		}
		else 
		{
			/*memory address is equals or more than 1000*/
			sprintf(buf,"\n\t%s \t%li\n",Entry_list->label,Entry_list->memory_add);
			fputs(buf,fent);
		}
		
		
		/*gets the next entry label*/
		temp = Entry_list->next;
		Entry_list->next = NULL;
		
		/*removes the current label from the list and free the memory memory*/
		free(Entry_list);
		Entry_list = temp;
	}
	
	fclose(fent);
	
	/*free allocated memory*/
	free(EntFile);
	free(buf);
}
/*


	WriteToExtFile:
		the method creates an Extrn file.
		each label, who is extern , will be written in the extern file together with its value.
		all extern - labels are stores in "External_list".
-------------------------------------------------------------------*/
void WriteToExtFile()
{

	char* ExtFile;					/*a pointer to extern file*/
	FILE *fext;							/*Stores the extern file name*/
	List *temp;							/*a pointer to list of extern labels*/
	char* buf;							/*stores extern lables with address*/
	
	
	/*case there are no extern - labels in the current assembly file*/
	if(!External_list)
		return;
	
	/*creates extern file with the name of assembly file*/
	ExtFile=(char*) malloc(sizeof(FileName)+sizeof(EXTERN_FILE));
	strcpy(ExtFile,FileName);
	strcat(ExtFile,EXTERN_FILE);
	
	
	
	/*open file to write extern label and address.*/
	fext = fopen(ExtFile,"w");
	if(!fext){
		fprintf(stderr,"Eror - cannot open file:%s.\n",ExtFile);
		return;
	}
	
	/*store extern labels and address*/
	buf = (char*) malloc(sizeof(char)*MACHINE_CODE_LENGTH);
	
	/*gets an extern label one by one from external_list*/
	while(External_list)
	{
		
		if(External_list->memory_add<1000)
		{
			/*Adds leading zero if memory address is less than 1000*/
			sprintf(buf,"\n\t%s \t0%li\n",External_list->label,External_list->memory_add);
			fputs(buf,fext);
			}
		else 
		{
			/*memory address is equals or more than 1000*/
			sprintf(buf,"\n\t%s \t%li\n",External_list->label,External_list->memory_add);
			fputs(buf,fext);
			}
		
		/*gets the next entry label*/
		temp = External_list->next;
		External_list->next = NULL;
		
		/*removes the current label from the list and frees the memory*/
		free(External_list);
		External_list = temp;
	}
	
	fclose(fext);
	
	/*frees alocated memory*/
	free(ExtFile);
	free(buf);
}
/*

	getAssemblyFile:
		this method gets a file name.
		it checks if the file name is valid.
		afterwards it adds to the given file name, the ending of an assembly file: ".as"
		if file name is not valid returns NULL,
		otherise return the file name with ending of assembly file: ".as"
---------------------------------------------------------------------*/
char* getAssemblyFile(char* as_FILE)
{
	
	char* getFile;				/*stores the file name with ".as"*/
	
	/*Checks valid file name*/
	if(!as_FILE)
		return NULL;
	
	/*Checks valid length of file name*/
	if(strlen(as_FILE)>=MAX_FILE_NAME){
 		fprintf(stderr,"Eror - invalid file name: %s . (file's name is too long)\n",as_FILE);
 		return NULL;
 		}
 		
	
	getFile = (char*)calloc(MAX_FILE_NAME,sizeof(char));
	
	if(!getFile){
		fprintf(stderr,"Eror , cannot allocate memory.\n");
		return NULL;
		}
	
	/*create a new file name with ".as" */
	strcpy(getFile,as_FILE);
	strcat(getFile,ASSEMBLY_FILE);
	
	
	return getFile;
}
	

		
