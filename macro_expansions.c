#include "header.h"
extern int cnt;
#define MAX_MACROS 100
typedef struct Macro
{
	char mname[100];
	char mval[100];
}macro;
typedef struct Fmacro
{
	int fmacnvar;
	char fmacname[50];
	char fmacval[100];
	char fmacvar[10][30];
}macros;
char*mystrstr(char*p,char *sub);
void * macro_expansion(char(*line)[200])
{
	static macro arr[MAX_MACROS];
	static macros k[MAX_MACROS];
	int n=0,l=0,g=0,length,len;
	char *q,*a;
	for(int i=0;i<cnt;i++)
	{
	    char *p=line[i];
	
	    while(*p==' ' || *p=='\t')
	       	 p++;
	    if (*p!= '#')
	        continue;
	    p++;
	    while (*p == ' ' || *p == '\t')
	        p++;
	    if (strncmp(p,"define",6)!=0)
	        continue;
	    p += 6;
	    if (*p != ' ' && *p != '\t')
	       	 continue;

	    while(*p==' ' || *p=='\t')
	        p++;
	    q=p;

	    while (*q && *q != '(' && *q != ' ' && *q != '\t' && *q != '\n') //to find the end of the macro name
	        q++;

	    if (*q == '(')  //to check whether it is a function macro or not
	    {
	        int idx=g,namelen=(int)(q-p);

	        if(g>=MAX_MACROS || namelen<=0 || namelen>=(int)sizeof(k[idx].fmacname))
	        {
	            printf("Macros limit reached,increase the limit\n");
		    continue;
	        }
	        l=0;
	        memcpy(k[idx].fmacname,p,namelen);
	        k[idx].fmacname[namelen] = '\0';

	        q++; //to skip opening parenthesis
		     
	        while(*q && *q != ')')//to store the functioned macro parameters
	        {
	            while(*q==' ' || *q=='\t')
	                q++;
	            if (*q==')')
	                break;
	            a=q;
	            while(*q && *q != ',' && *q != ')')
	                q++;

	            int plen=(int)(q-a);

	            while(plen>0 && (a[plen-1]==' ' ||a[plen-1]=='\t'))
		           plen--;

	            if(plen<=0 || l>=10 || plen>=30)
	            {
  	                printf("Invalid function-like macro parameter\n");
	                break;
	            }

	            memcpy(k[idx].fmacvar[l],a,plen);
	            k[idx].fmacvar[l][plen]='\0';
	            l++;

	            if(*q==',')
	                q++;
		}
	        if(*q!=')')
	        {
	            printf("missed ')' in the function macro name at %d th line \n",i);
	            continue;
	        }

	        k[idx].fmacnvar=l;
	        q++; //to skip the closing parenthesis
	        while(*q==' ' || *q=='\t')
	            q++;

	        a=q;

	        while(*q && *q != '\n')
	            q++;

	        int vlen=(int)(q-a);

	        if(vlen>=(int)sizeof(k[idx].fmacval))
	        {
	            printf("functional macro value limit reached need to increase its limit\n");
	            continue;
	        }
	        memcpy(k[idx].fmacval,a,vlen);
	        k[idx].fmacval[vlen]='\0';

	        g++;
	        memmove(line+i,line+i+1,(int)(cnt-i-1)*sizeof(*line));//to remove the functional-macro defined line
	        cnt--;
	        i--;
	        continue;
	    }

	    // for simple macros
	    int namelen=(int)(q-p);
	    if(n>=MAX_MACROS)
	    {
	        printf("simple macro storing limit reached\n");
	        break;
	    }
	    if(namelen<=0 ||namelen>=(int)sizeof(arr[n].mname))
	    {
	        printf("invalid macro name\n");
	        continue;
	    }
	    memcpy(arr[n].mname,p,namelen);
		arr[n].mname[namelen]='\0';
	    p=q;
	    while(*p==' ' ||*p=='\t')
	        p++;
	    q=p;
	    while(*q && *q!='\n')
	        q++;

	    int vlen=(int)(q-p);

	    if(vlen>=(int)sizeof(arr[n].mval))
	    {
	        printf("simple macro value storing limit reached need to increase it\n");
	        continue;
	    }
	    memcpy(arr[n].mval,p,vlen);
	    arr[n].mval[vlen]='\0';
	    n++;

	    memmove(line + i, line + i + 1,(size_t)(cnt - i - 1) * sizeof(*line));//to remove the simple macro defined line

	    cnt--;
	    i--;
	}

	for(int i=0;i<cnt;i++)//replacement of  functional macros with its objects
	{
	    for(int j=0;j<g;j++)
	    {
	        char *p=line[i];
	
	        while((p=mystrstr(p,k[j].fmacname))!=NULL)
	        {
 	           char *q=p+strlen(k[j].fmacname);
	            while(*q==' ' || *q=='\t')
	                q++;
	
	            if(*q!='(')
	            {
	                p+=strlen(k[j].fmacname);
	                continue;
	            }

	            char *arg_start[10];
	            int arg_len[10];
	            int argc = 0;
	            int depth = 1;

	            q++;  /* Skip '(' */

	            if(*q!=')')
	            {
	                arg_start[argc]=q;
	                while(*q&& depth>0)
	                {
	                    if(*q=='(')
	                        depth++;
	                    else if(*q==')')
	                    {
	                        depth--;
	                        if(depth == 0)
	                        {
	                            arg_len[argc]=(int)(q - arg_start[argc]);
	                            argc++;
	                            break;
	                        }
	                    }
	                    else if (*q==',' && depth==1)
	                    {
	                        arg_len[argc]=(int)(q-arg_start[argc]);
	                        argc++;

	                        if(argc>=10)
	                            break;
	                        arg_start[argc]=q+1;
	                    }
	                    q++;
	                }
	            }
	
	            if(*q!=')' || argc!=k[j].fmacnvar)
	            {
	                p+=strlen(k[j].fmacname);
	                continue;
	            }

	            char replacement[200];
	            int rlen = 0;

	            for (int b=0;k[j].fmacval[b]!='\0'; )//substituting parameters into replacement text
	            {
	                int matched=0;
	                for (int c=0;c<k[j].fmacnvar;c++)
	                {
	                    int plen=(int)strlen(k[j].fmacvar[c]);

	                    if (plen > 0 && strncmp(&k[j].fmacval[b],k[j].fmacvar[c], plen) == 0 &&(b == 0 ||
                         (!isalnum((unsigned char)k[j].fmacval[b - 1]) &&
                          k[j].fmacval[b - 1] != '_')) &&
                        (!isalnum((unsigned char)k[j].fmacval[b + plen]) &&
                         k[j].fmacval[b + plen] != '_'))
	                    {
	                        if(rlen+arg_len[c]>=(int)sizeof(replacement))
	                        {
	                            matched = 1;
	                            break;
	                        }

        	                memcpy(replacement + rlen,arg_start[c],arg_len[c]);
         			rlen += arg_len[c];
	                        b += plen;
	                        matched = 1;
	                        break;
	                    }
	                }
	                if(!matched)
	                {
	                    if(rlen>=(int)sizeof(replacement)-1)
	                        break;
	                    replacement[rlen++]=k[j].fmacval[b++];
	                }
	            }
	            replacement[rlen]='\0';
	
	            int oldlen=(int)((q+1)-p);
	            int newlen=rlen;

	            if((int)strlen(line[i]) - oldlen + newlen >= 200)
	            {
	                printf("Expanded line too long\n");
	                break;
		    }
	            memmove(p + newlen,p + oldlen,strlen(p + oldlen)+ 1);
	            memcpy(p,replacement,newlen);
	            p += newlen;
		    
	    }
	    for(int j = 0; j < n; j++)//expansion of simple macro
	    {
	        char *p=line[i];
	        int oldlen =(int)strlen(arr[j].mname);
	        int newlen =(int)strlen(arr[j].mval);

	        while((p=mystrstr(p,arr[j].mname))!=NULL)
	     	{
	            if((int)strlen(line[i]) -oldlen +newlen >= 200)
	            {
	                printf("Expanded line too long\n");
	                break;
	            }

	            memmove(p+newlen,p + oldlen,strlen(p+ oldlen)+1);
	            memcpy(p,arr[j].mval,newlen);
	            p += newlen;
	        }
	    }
	}
    }
	return line;
}
char*mystrstr(char*p,char *sub)
{
	for(int i=0;p[i]!='\0';i++)
	{
			int k=i,j;
			for(j=0;sub[j]!='\0';j++)
			{
				if(p[k]!=sub[j])
					break;
				k++;
			}
			if(sub[j]=='\0' && !isalnum((unsigned char)p[k]) && p[k]!='_' && (i==0 || (!isalnum((unsigned char)p[i-1]) && p[i-1]!='_')))
			{
				return &p[i];
			}
	}
	return NULL;
}



