#include "header.h"
extern int cnt;
void * remove_comments(char(*line)[200])
{
	char*p=NULL,*m=NULL;

	/*to remove signle line comment and not removes comments which written in strings */

	for(int i=0;i<cnt;i++)
        {
                p=line[i];
                for(int j=0;p[j]!='\0';j++)
                {
                        if(p[j]=='"')
                        {
                                int k=j+1;
                                while(p[k]!='\0')
                                {
                                        if(p[k]=='"')
                                                break;
                                        k++;
                                }
                                if(p[k]=='\0')
                                {
                                    printf("error1\n");
                                    printf("i = %d\n", i);
                                    exit(0);
                                }
                                j=k;
                        }
                        else if(p[j]=='/'&&p[j+1]=='/')
                        {
                                 p[j]='\n';
                                 p[j+1]='\0';
                                 break;
                        }
                }
        }

    /*to remove multiline comment which written only in one line, and does not removes comments which written in strings */

       for(int i=0;i<cnt;i++)
        {
              p=line[i];
              for(int l=0;p[l]!='\0';l++)
              {
                 if(p[l]== '"')
                  {
                     int k=l+1;
                      while(p[k]!='\0')
                       {
                          if(p[k]=='"')
                                   break;
                               k++;
                       }
                       if(p[k]=='\0')
                        {
                            printf("error2\n");
                            printf("error in %d line\n",i);
                            exit(0);
                        }
                        l=k;
                  }
                 else if(p[l]=='/' && p[l+1]=='*')
                  {
                      int k=l+2;
                         while(p[k]!='\0')
                          {
                                if(p[k]=='*' && p[k+1]=='/')
                                {
                                     break;
                                }
                                k++;
                          }

                         if(p[k]!='\0')
                          {
                                memmove(p+(l-1),p+k+2,strlen(p+k+2)+1);
                                l--;
                          }
                  }
              }
        }

     /*to remove to middle lines of the multiline comments and detects the comment between the string*/

        for(int i=0;i<cnt;i++)
        {
                int lno=-1,lno1=-1,flag=0;
                p=line[i];
                for(int j=0;p[j]!='\0';j++)
                {
                        if(p[j]=='"')
                        {
                                int k=j+1;
                                while(p[k]!='\0')
                                {
                                        if(p[k]=='"')
                                        {
                                               break;
                                        }
                                        k++;
                                }
                                if(p[k]=='\0')
                                {
                                       printf("error3\n");
                                       exit(0);
                                }
                                j=k;
                        }
                        else if(p[j]=='/'&& p[j+1]=='*')
                        {
                                lno=i;
                                for(int k=i+1;k<cnt;k++)
                                {
                                        m=line[k];
                                        for(int h=0;m[h]!='\0';h++)
                                        {
                                                if(m[h]=='*'&&m[h+1]=='/')
                                                {
                                                        lno1=k;
                                                        flag=1;
                                                        break;
                                                }
                                        }
                                        if(flag==1)
                                                break;
                                }
                        }
                        if(flag==1)
                                break;
                }
                if(lno>=0&&lno1>=0)
                {
                        if(((lno1-lno)-1)!=0)
                        {
                                memmove(line+(lno+1),line+lno1,(cnt-lno1)*sizeof(*line));
                                cnt=cnt-((lno1-lno)-1);
                                line=realloc(line,(cnt*sizeof(*line)));
			}
                }
        }

	/*to remove the two lines after removing the middle lines of the multiline comment */

	for(int i=0;i<cnt;i++)
        {
                char*n=NULL;
                p=line[i];
                for(int j=0;p[j]!='\0';j++)
                {
			if(p[j]=='"')
			{
				int k=j+1;
				while(p[k]!='"')
					k++;
				if(p[k]=='"')
					j=k+1;
				else
				{
					printf("error lastpass\n");
					exit(0);
				}
			}
			else if(p[j]=='/'&&p[j+1]=='*')
                        {
                                n=line[i+1];
                                        for(int h=0;n[h]!='\0';h++)
                                        {
                                                if(n[h]=='*'&&n[h+1]=='/')
                                                {
                                                        int l=0;
                                                        while(p[l]!='\n')
                                                                 l++;
                                                         memmove(n+(h-1),n+(h+2),strlen(n+(h+2))+1);
                                                         memmove(p+j,p+l,strlen(p+l)+1);
                                                         break;
                                                }
                                        }
                        }
                }
        }
       	return line;
}

