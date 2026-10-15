#include "header.h"
extern int cnt;
void*readFromFile(char*filename)
{
	char(*line)[200]=NULL;
	FILE*fp;
	fp=fopen(filename,"r");
	if(fp==NULL)
	{
		printf("failed to open the file\n");
		exit(0);
	}
	char str[200];
	while((fgets(str,200,fp))!=NULL)
	{
		line=realloc(line,(cnt+1)*sizeof(*line));
		strcpy(line[cnt],str);
		cnt++;
	}
	fclose(fp);
	return line;
}
