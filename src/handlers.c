#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "myshell.h"

// list of internal commands that user can use
char *internal_cmds[] = {"cd", "clr", "dir", "environ", "echo", "help", "pause", "quit"};
char *io_symbols[] = {"<", ">", ">>"}; // IO symbols


// Create pointer array to addresses of functions corresponding to commands
// funcs take pointer to tokenised input as parameter
int (*internal_funcs[])(char **arg) = {
	&internal_cd,
	&internal_clr,
	&internal_dir,
	&internal_environ,
	&internal_echo,
	&internal_help,
	&internal_pause,
	&internal_quit,
};
// Tai Tan Mai, CA284 Pointers to functions - https://ca284.computing.dcu.ie/pointer4.html


// array of function addresses to IO handlers
FILE *(*io_funcs[])(char *filename) = {
	&stdin_redr,
	&stdout_redr1,
	&stdout_redr2,
};


// handler func will iterate through internal command names and call the necessary function
int command_handler(char **arg)
{
	int len = sizeof(internal_cmds) / sizeof(char*); // number of commands
	for (int i = 0; i < len; i++)
	{
		if (!strcmp(arg[0], internal_cmds[i])) // check for arg[0] already made beforehand in myshell.c
		{
			// call function matching index of command string list - should return 0
			return (*internal_funcs[i])(arg);
		}
	}
	// if the command isn't an internal command
	return external_commands(arg); // linux shell will return error if program doesn't exist
}


// func to call IO functions based on >, >>, <
void io_handler(char **arg)
{
	int len = sizeof(io_symbols) / sizeof(char*); // number of commands

	// loop through user input and look for IO symbols
	for (int i = 0; arg[i] != NULL; i++){
		if (symbol_check(arg[i])) // found IO symbol
		{
			for (int j = 0; j < len; j++)
			{
				if (!strcmp(arg[i], io_symbols[j]))
				{
					// next arg will be the intended filename for IO operation
					(*io_funcs[j])(arg[i + 1]); // call function matching index of io functions
				}
			}
		}
	}
}


// func for errors in forking
void syserr(char *msg) // reports error code and abort
{
   fprintf(stderr,"%s: %s\n", strerror(errno), msg);
   abort();
}
// Provided as part of CA216 Lab04/05 - https://loop.dcu.ie/mod/book/view.php?id=1796411&chapterid=377038


// used to check for args with special meaning (IO and background execution)
int symbol_check(char *arg){

	if ( !strcmp(arg, "<") ){
		return 1;
	}
	else if ( !strcmp(arg, ">") ){
		return 1;
	}
	else if ( !strcmp(arg, ">>") ){
		return 1;
	}
	else if ( !strcmp(arg, "&") ){
		// will be ignored unless at end of line (background execution)
		return 1;
	}
	return 0; // meaning no symbols were found
}


// redirect stdin to file
FILE *stdin_redr(char *filename){
	
	FILE *fp;
	// check if file exists
	if( access( filename, F_OK ) == 0 ) {
		fp = freopen(filename, "r", stdin); //open in read mode
	}
	else{
		fprintf(stderr, "The file does not exist.\n"); // print error message
		fflush(NULL); // flush buffers
		_exit(0); // exit the child process / program
	}
	return fp;
}


// redirect stdout to file, create if non existent
FILE *stdout_redr1(char *filename){
	FILE *fp = freopen(filename, "w", stdout); //open in write mode

	// check if file creation was successful
	if( access( filename, F_OK ) != 0 ) {
		fprintf(stderr, "The file was not successfully created.\n");
	}

	return fp;
}


// redirect stdout to file for appending, create if non existent
FILE *stdout_redr2(char *filename){
	FILE *fp = freopen(filename, "a", stdout); //open in append mode

	// check if file creation was successful
	if( access( filename, F_OK ) != 0 ) {
		fprintf(stderr, "The file was not successfully created.\n");
	}

	return fp;
}


// func for running child processes in background
int bg_exec(char **arg){

	// to check for last char -> next char should equal NULL
	int count = 0;
	for(; arg[count + 1] != NULL; count++){;} // counting elements up to last one

	// will check if last argument in command line input array is &
	if ( !strcmp("&", arg[count]) )
	{
		return 1;
	}
	return 0;
	// return 1 to run in background, 0 for foreground
}

/*
I certify that this assignment is my own work carried out in a manner pursuant to the DCU Academic Integrity Policy,
based on my personal study and/or research and that I have acknowledged all material and sources used in its preparation.
Benjamin Olojo - 19500599
*/