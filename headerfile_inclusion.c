#include "header.h"

extern int cnt;

typedef struct Shead
{
	int lno;
	char arr[30];
}shead;

typedef struct Uhead
{
    int lno;
    char arr[30];
}uhead;

int read_lines(FILE *fpt)
{
    int k=0;
    char str[200];
    while(fgets(str,sizeof(str),fpt)!= NULL)
        k++;
    rewind(fpt);
    return k;
}

FILE *open_system_header(const char *header)
{
    char filename[300];
    const char *paths[]={"/usr/include/","/usr/include/x84_64-linux-gnu/"};
    for(int i=0;i<2;i++)
    {
        snprintf(filename, sizeof(filename),"%s%s",paths[i], header);
    	FILE *fp = fopen(filename, "r");
    	if (fp!= NULL)
       		return fp;
    }
    return NULL;
}

void *header_files_include(char (*line)[200])
{
    int n=0,t=0;
    uhead u[30];
    shead s[20];

//to store the system and user defined file directives 
    for(int i=0;i<cnt;i++)
    {
        char *p=line[i];
        char *q;
        char end;
        while(*p==' ' || *p=='\t')
            p++;

        if(*p!='#')
            continue;
        p++;
        while(*p==' ' || *p=='\t')
            p++;

        if(strncmp(p,"include",7)!= 0)
            continue;
        p += 7;
        if(*p!=' ' && *p!='\t' && *p!='"' && *p!='<')
            continue;

        while(*p==' ' || *p=='\t')
            p++;

        if(*p!='"' && *p!='<')
            continue;

        end = (*p=='"')? '"':'>';
        q = ++p;

        while(*q && *q != end && *q != '\n')
            q++;

        if(*q != end)
            continue;

        int len=(int)(q-p);

        if(len== 0 || len>=(int)sizeof(s[0].arr))
        {
            printf("Header filename too long or empty\n");
            return line;
        }
	if(end=='"'&& n<=20)
	{
	       	memcpy(u[n].arr, p, len);
        	u[n].arr[len] = '\0';
        	u[n].lno = i;
       		n++;
	}

	else if(end=='>'&& t<=20)
	{
        	memcpy(s[t].arr, p, len);
        	s[t].arr[len] = '\0';
       		s[t].lno = i;
        	t++;
	}
	else
	{
		if(n>=20 || t>=20)
		{
			printf("maximum header stored limit is over\n");
			return line;
		}
	}
    }

//to read the user defined header files
    for(int i=n-1;i>=0;i--)
    {
        int pos= u[i].lno;
        int oldcnt= cnt;

	FILE *ct=fopen(u[i].arr,"r");
	if(ct==NULL)
	{
		printf("failed to open the user header file\n");
		return line;
	}
        int h= read_lines(ct);
	fclose(ct);

        if(h<0)
            return line;
        FILE *fp=fopen(u[i].arr,"r");
        if (fp == NULL)
        {
            printf("Failed to open header file: %s\n", u[i].arr);
            return line;
        }
        int newcnt=oldcnt+h-1;
        char (*temp)[200]=realloc(line,(size_t)newcnt  * sizeof(*line));
        if(temp==NULL && newcnt>0)
        {
            fclose(fp);
            printf("Memory allocation failed\n");
            return line;
        }
        line=temp;

        if(h>1)
        {
            for(int j=oldcnt-1;j>pos;j--)
                strcpy(line[j +h-1],line[j]);
        }
        else if(h==0)
        {
            for(int j=pos;j<oldcnt- 1;j++)
                strcpy(line[j],line[j+1]);
        }
        for(int j=0;j<h;j++)
        {
            if(fgets(line[pos+j],sizeof(line[0]),fp) == NULL)
                break;
        }
        fclose(fp);
        cnt = newcnt;
    }

//to read the system header files
    for(int i = t - 1; i >= 0; i--)
    {
        int pos=s[i].lno;
        int oldcnt = cnt;

        FILE *fp = open_system_header(s[i].arr);

        if (fp == NULL)
        {
            printf("system header file: %s not found\n", s[i].arr);
            return line;
        }

	int h=read_lines(fp);

	if(h<0)
	   return line;

        int newcnt= oldcnt + h - 1;

        char (*temp)[200]=realloc(line,(size_t)newcnt * sizeof(*line));
        if (temp==NULL && newcnt>0)
        {
            fclose(fp);
            printf("Memory allocation failed\n");
            return line;
        }

        line = temp;
        if (h>1)
        {
            for(int j= oldcnt - 1; j>pos;j--)
                strcpy(line[j+h-1],line[j]);
        }
        else if(h==0)
        {
            for(int j=pos; j<oldcnt - 1;j++)
                strcpy(line[j],line[j+1]);
        }

        for(int j=0; j<h;j++)
        {
            if(fgets(line[pos+j],sizeof(line[0]),fp)==NULL)
                break;
        }
        fclose(fp);
        cnt = newcnt;
    }
    return line;
}







