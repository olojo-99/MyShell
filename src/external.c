#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "myshell.h"

// The template for this function was provided as part of CA216 Lab04/05
// https://loop.dcu.ie/mod/book/view.php?id=1796411&chapterid=377038

// function to run "other" commands
int external_commands(char **arg)
{
	// build command to be passed to exec() system call
	char **parameters = (char**) calloc(MAX_ARGS, sizeof(char*));

	// exclude <, >, >>, & as program parameter
	for (int i = 0; arg[i] != NULL; i++){
		if (!symbol_check(arg[i])) // pass command line arg to func that checks for symbols
		{
			parameters[i] = arg[i]; // add to arg list for execvp()
			// now we have build a parameter list that will run in execvp()
		}
	}

	pid_t pid; // process id
	int status; // status code

    switch (pid = fork()) // create fork
   {
        case -1:
        {
            syserr("fork"); // failed fork
        }

        case 0: // execution in child process
        {
        	setenv("PARENT", getenv("ORIGINAL"), 1); // Update PARENT var for child

    		io_handler(arg); // redirect I/O if necessary
    		// file descriptors closed when child process exits

        	execvp(arg[0], parameters);// execvp() takes an array of arguments as its 2nd parameter
            syserr("execl"); // error if return from exec - also aborts
        }

        default:
        {
        	// check if user has requested background execution
        	if (bg_exec(arg)){
        		break;
        	}
        	else{
				waitpid(pid, &status, WUNTRACED); // wait until the child proces is done before prompting (child in foreground)
        	}
        }
   }

	free(parameters); parameters = NULL; // free dynamically allocated memory, set pointer to null
	return 0;
}

/*
I certify that this assignment is my own work carried out in a manner pursuant to the DCU Academic Integrity Policy,
based on my personal study and/or research and that I have acknowledged all material and sources used in its preparation.
Benjamin Olojo - 19500599
*/