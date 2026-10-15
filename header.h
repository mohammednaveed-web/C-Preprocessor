//header.h
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
extern int cnt;
FILE *open_system_header(const char *header);
int read_file(FILE *fpt);
void * header_files_include(char(*line)[200]);
char * mystrstr(char*p,char *sub);
void * readFromFile(char*filename);
void * macro_expansion(char(*line)[200]);
void writeToFile(char(*line)[200],char*filename);
void * remove_comments(char(*line)[200]);
