/* Porgram definitions*/
#define MAX_LABEL_LENGTH 32
#define MAX_ROW_LENGTH 82

/*
	
	Line:
		this structure stores the important information from an assembly row.
		- Label: stores labels names.
		- cmd: stores insturctions names.
		- data: stores insturctions data.
		- index: indicates the lines number.
--------------------------------------------------------------------------------*/
struct line{
	char label[MAX_LABEL_LENGTH];
	char cmd[MAX_ROW_LENGTH];
	char data[MAX_ROW_LENGTH];
	int index;
	};
	
typedef struct line Line;

