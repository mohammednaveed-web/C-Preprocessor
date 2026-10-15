mypreprocessor : main.o readFromFIle.o remove_comments.o macro_expansions.o headerfile_inclusion.o writeToFile.o
	gcc main.o readFromFIle.o remove_comments.o macro_expansions.o headerfile_inclusion.o writeToFile.o -o mypreprocessor
main.o : main.c header.h
	gcc -c main.c
readFromFIle.o : readFromFIle.c
	gcc -c readFromFIle.c
remove_comments.o : remove_comments.c
	gcc -c remove_comments.c
headerfile_inclusion.o : headerfile_inclusion.c
	gcc -c headerfile_inclusion.c
macro_expansions.o : macro_expansions.c
	gcc -c macro_expansions.c
writeToFile.o : writeToFile.c
	gcc -c writeToFile.c
clean:
	rm -f *.o mypreprocessor a.out
