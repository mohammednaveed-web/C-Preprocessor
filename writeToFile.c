#include "header.h"
extern int cnt;
void writeToFile(char(*line)[200],char*filename)
{
	char str[20];
        strcpy(str,filename);
        char*dot=strchr(str,'.');
        dot++;
        *dot='i';

	FILE*fp;
	fp=fopen(str,"w");
	if(fp==NULL)
	{
		printf("filed to open the file\n");
		exit(0);
	}
	char*p;
	for(int i=0;i<cnt;i++)
	{
		int empty = 1;
        	for (int j = 0;line[i][j]!='\0';j++)
        	{
        	    if(line[i][j]!=' '&& line[i][j]!='\t' && line[i][j]!='\n' && line[i][j]!='\r')
		    {
                	empty = 0;
                	break;
            	    }
        	}
        	if(empty)
       		 continue;
		fputs(line[i],fp);
	}
	fclose(fp);
}
