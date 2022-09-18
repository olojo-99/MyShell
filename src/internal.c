#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "myshell.h"

// BELOW IS THE IMPLEMENTATION OF THE INTERNAL COMMANDS SPECIFIED FOR ASSIGNMENT

int internal_cd(char **arg)
{
	char *currDir= (char*) calloc(MAX_BUFFER, sizeof(char)); // line buffer - string
    getcwd(currDir, MAX_BUFFER);

    if (!arg[1]){ // Check for second arg
        printf("%s\n", currDir);
    }
	else{
		// System call to change dir - chdir() returns -1 if failed
	    if(chdir(arg[1]) == -1){
	    	fprintf(stderr, "There is no such directory.\n"); // Print error message to stderr
	    }
	    setenv("PWD", currDir, 1); // Update PWD environment var
	}

	free(currDir); currDir = NULL;
	return 0;
}


int internal_clr(char **arg)
{
	system("clear"); // clear screen through system()
	return 0;
}


int internal_dir(char **arg)
{
    char *directory = (arg[1]) ? arg[1]:"."; // ternary operator will evaluate to current dir for no arg

	pid_t pid;
	int status;

    switch (pid = fork()) 
   {
        case -1:
        {
            syserr("fork");
        }

        case 0: // execution in child process
        {
        	setenv("PARENT", getenv("ORIGINAL"), 1); // Update PARENT environment var for child

        	io_handler(arg); // redirect I/O if necessary

            execlp("ls", "-al", directory, NULL);
            syserr("execl"); // error raised if this line is reached in child
		}

        default:
        {
            waitpid(pid, &status, WUNTRACED); // wait until the child proces is done before prompting again
        }
   }
	return 0;
}


int internal_environ(char **arg)
{
	extern char **environ;  // Pointer to NULL terminated array of name=value string pairs

	pid_t pid;
	int status;

    switch (pid = fork()) 
   {
        case -1:
        {
            syserr("fork");
        }

        case 0: // execution in child process
        {
        	io_handler(arg); // redirect I/O if necessary

		    for (int i = 0; environ[i] != NULL; i++)
		    {
		      printf("%s\n",environ[i]); // print each environment variable
		    }

		    fflush(NULL);  // NULL indicates flush all streams with unwritten behaviour
		    _exit(0); // used to exit child process
		}

        default:
        {
            waitpid(pid, &status, WUNTRACED); // wait until the child proces is done before prompting again
        }
   }
	return 0;
}
// Flushing streams - https://www.ibm.com/docs/en/zos/2.1.0?topic=functions-exit-end-process-bypass-cleanup
// Exiting child processes - https://stackoverflow.com/questions/2329640/how-to-exit-a-child-process-exit-vs-exit

int internal_echo(char **arg)
{
	pid_t pid;
	int status;

    switch (pid = fork()) 
   {
        case -1:
        {
            syserr("fork");
        }

        case 0: // execution in child process
		{
			io_handler(arg);  // redirect I/O if necessary

 			 // we want symbols to be interpreted as aliases for commands rather than program args
        	int i = 1;
		    while ( arg[i] != NULL && !symbol_check(arg[i]) ) // we don't want to print symbols
		    {
		        printf("%s ",arg[i]); //print value at specific argument then increment arg
		        i++;
		    }
		    printf("\n");

		    fflush(NULL); // flush streams
		    _exit(0);
		}

        default:
        {
            waitpid(pid, &status, WUNTRACED); // wait until the child proces is done before prompting again
        }
   }
	return 0;
}


// readme should be able to be found from any directory
int internal_help(char **arg)
{
	char *line = (char*) calloc(MAX_BUFFER, sizeof(char)); // line buffer - string
	char *orig = getenv("ORIGINAL"); // get the env var of the original directory of myshell

	// write command to line array
	snprintf(line, MAX_BUFFER, "%s/%s", orig, "../manual/readme.md");

	pid_t pid;
	int status;

    switch (pid = fork()) 
   {
        case -1:
        {
            syserr("fork");
        }

        case 0: // execution in child process
        {
        	setenv("PARENT", getenv("ORIGINAL"), 1); // Update PARENT var for child

        	io_handler(arg);

            execlp("more", "", line, NULL); // execute using "more"
            syserr("execl");
        }

        default:
        {
            waitpid(pid, &status, WUNTRACED); // wait until the child proces is done before prompting again
        }
   }

   free(line); line = NULL; // free memory
   return 0;
}


// ASCII value of "Enter" = 10
int internal_pause(char **arg)
{	
	// Can read from stdin until Enter is pressed
	char userInput;
	while(1)
	{
		userInput = getchar(); // read char from stdin
		if (userInput == 10)
		{
			break;
		}
	}
	return 0;
}


// Simply exit the program
int internal_quit(char **arg)
{
	exit(0);
	return 0;
}
