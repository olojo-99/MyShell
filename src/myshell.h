
// execute.c
void batchmode(char **arg, char *args[], char *buf, char *batchfile);
void defaultmode(char **arg, char *args[], char *buf);
void execution(char **arg, char *args[], char *buf);

// external.c
int external_commands(char **arg);

// internal.c
int internal_cd(char **arg);
int internal_clr(char **arg);
int internal_dir(char **arg);
int internal_environ(char **arg);
int internal_echo(char **arg);
int internal_help(char **arg);
int internal_pause(char **arg);
int internal_quit(char **arg);

//handlers.c
int command_handler(char **arg);
void io_handler(char **arg);
void syserr(char *msg);
int symbol_check(char *arg);
int bg_exec(char **arg);
FILE *stdin_redr(char *filename);
FILE *stdout_redr1(char *filename);
FILE *stdout_redr2(char *filename);

#define MAX_BUFFER 1024 // max line buffer length
#define MAX_ARGS 64 // max number of args
#define SEPARATORS " \t\n" // token separators


/*
I certify that this assignment is my own work carried out in a manner pursuant to the DCU Academic Integrity Policy,
based on my personal study and/or research and that I have acknowledged all material and sources used in its preparation.
Benjamin Olojo - 19500599
*/