#include "header.h"
int cnt;
int main(int argc,char**argv)
{
	char(*line)[200]=NULL;
	if(argc!=2)
	{
		printf("wrong input\n");
		printf("please provide exe sourcefile_name destination filename\n");
		exit(0);
	}
	line=readFromFile(argv[1]);
	line=remove_comments(line);
        line=macro_expansion(line);
	line=header_files_include(line);
	writeToFile(line,argv[1]);
}
