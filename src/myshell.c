#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "myshell.h" // Main header file

// The template for this function was provided as part of CA216 Lab04/05
// https://loop.dcu.ie/mod/book/view.php?id=1796411&chapterid=377036

int main (int argc, char *argv[])
{
    // CREATING COMMAND LINE BUFFER AND POINTERS
    char *buf = (char*) calloc(MAX_BUFFER, sizeof(char)); // line buffer - string
    char **args = (char **) calloc(MAX_ARGS, sizeof(char *)); // pointers to arg strings
    char **arg = args; // working pointer to args - pointer to pointer

    // SETTING SHELL ENV VARS
    char *currDir= (char*) calloc(MAX_BUFFER, sizeof(char)); // line buffer - string
    getcwd(currDir, MAX_BUFFER);

    char *shellEnv = (char*) calloc(MAX_BUFFER, sizeof(char)); // dynamically allocate memory for SHELL variable
    strcpy(shellEnv, currDir);
    strcat(shellEnv, "/myshell"); // append name of program to SHELL variable

    setenv("SHELL", shellEnv, 1); // Update SHELL environment var
    setenv("ORIGINAL", currDir, 1); // Create env var for the original directory of myshell (without /myshell)

    if ( argv[1] ) // checks if there is a batchfile argument
    {
        char *batchfile = argv[1];
        batchmode(arg, args, buf, batchfile); // execute batchmode
        // program will exit in event of failure
    }
    else{
        defaultmode(arg, args, buf); // execute default mode otherwise
    }

    // free dynamically allocated memory
    free(args); args = NULL; // also set to NULL
    free(buf); buf = NULL;
    free(currDir); currDir = NULL;
    free(shellEnv); shellEnv = NULL;

    return 0;
}
