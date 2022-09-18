#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "myshell.h"

// batchmode execution
void batchmode(char **arg, char *args[], char *buf, char *batchfile)
{
    FILE *fp = stdin_redr(batchfile); // replace stdin with file in argv[]

    while (!feof(stdin)) // uses file as stdin
    {
        execution(arg, args, buf);
    }

    fclose(fp); // close the batchfile
}

// regular execution
void defaultmode(char **arg, char *args[], char *buf)
{
    // Add current directory to shell prompt
    char prompt[MAX_BUFFER]; // Current dir will be copied here
    getcwd(prompt, MAX_BUFFER);
    char *arrow = "==> " ;
    strcat(prompt, arrow); // Copy arrow to end of current dir

    while (!feof(stdin))
    {
        getcwd(prompt, MAX_BUFFER); // get new current dir
        strcat(prompt, arrow); // copy arrow to prompt again
        printf("%s", prompt); // print prompt

        execution(arg, args, buf);
    }
}

// The template for this function was provided as part of CA216 Lab04/05
// https://loop.dcu.ie/mod/book/view.php?id=1796411&chapterid=377036

// function to start execution of internal/external commands
void execution(char **arg, char *args[], char *buf)
{
    // read a line into the buf string (max 1024 chars)
    if (fgets(buf, MAX_BUFFER, stdin)) // if there is commands to read...
    {
        // point to array of tokens
        arg = args;

        // strtok() returns pointer to token - assigning pointer to returned strtok() value
        *arg++ = strtok(buf,SEPARATORS);  // divide input stored in buf based on SEPARATORS

        // double brackets needed to silence compiler warning - use of assignment as condition
        while (( *arg++ = strtok(NULL,SEPARATORS) ));

        if (args[0]) // if theres anything there
        {
            arg = args; // point arg to start of array
            command_handler(arg); // pass pointer to string array to handler
            // since arg = args, we can use the arg pointer to alter the args array
        }

    }
}
