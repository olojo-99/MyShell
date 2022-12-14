myshell(1)

NAME

        myshell

SYNOPSIS

        myshell [batchfile]

DESCRIPTION

        myshell is a command line interpreter that offers simplified functionality based on that of a GNU command line interfaces such as bash or zsh used to execute operating system functions.[1]
        myshell supports a series of internal commands which have been implemented to imitate functionality commonly used in GNU shells, and also supports the execution of other/external commands through the default system shell of the operating system. [BASH]

INVOCATION

        Through the command line interface provided by the user's operating system, the myshell program is started by entering ./myshell in the directory where the executable of the program is located.
        The program can be started interactively or non-interactively through an argument that specifies a batchfile containing commands to be executed by myshell.

RESERVED CHARACTERS

        There are a set of characters that are reserved for special operations that are covered in this manual.
        These characters are <, >, >> and &.

COMMANDS

        myshell has a number of built-in commands that can be utilised by the user once the program has been started.
        If a program name is not immediately recognised by myshell, it will try to execute the program with the specified arguments by invoking the operating system dependent binary executable file of the same name.[2]

    INTERNAL
        The commands built-in to myshell are specified below along with their functionality.

        cd [directory] - change the current working directory. If there is no argument provided, the current directory is shown. The user is also notified if the directory specified does not exist. [3]
        clr - clear the terminal screen.
        dir [directory] - list the contents of directory specified in the argument. If no argument is provided, the contents of the current working directory are listed.
        environ - display the current environment variables and their values.
        echo [string] - prints the string to standard output followed by a newline.
        help - display the myshell user manual using the more filter.  
        pause - pause operation of myshell until 'Enter' is pressed.
        quit - quit the myshell program

    EXTERNAL
        Commands not included in the list of built-in commands are executed through system calls which pass the commands to the default system shell for execution.
        The executable file of the program is run by the default system shell, with its results displayed to the user if applicable.

BATCH MODE

        When myshell is being run non-interactively, or in batch mode, commands are read from a file specified in the argument provided during program invocation.
        Each command is executed with intermediate results being displayed to the user where applicable. The myshell program exits once the end of the file is reached.

ENVIRONMENT

        System shells maintain an environment set up to include a set of variables denoting information generated by the operating system's login program, system initialisation file and user initialisation file.[4]
        A shell can have both environment variables and shell/local variables which exist in name=value pairs.
        Environment variables are inherited by all processes spawned from the shell.
        These variables allow for storage of global settings for the shells and various programs that are invoked by it.[4]
        Shell/local variables are only present within the current instance of the shell and are not available to other programs subsequently invoked.
        The current environment variables of myshell can be displayed through the "environ" internal command.

I/O REDIRECTION

        I/O redirection refers to the shells ability to change its standard input and standard output streams.
        Generally, the default streams for standard input and standard output are text from the user's keyboard and the terminal screen respectively.[5]
        Standard input and output streams can be redirected to files through the use of designated symbols.
        The myshell program can redirect both standard input and output through the used of the following symbols/characters.

        < - redirect standard input to a file if it exists.
        > - redirect standard output to a file if it exists, or create the file if it doesn't.
        >> - redirect standard output to a file if it exists and append to it, or create the file if it doesn't.

        Once the input or output streams have been redirected for a specific command, it is reset to the default stream for the next command that is executed in the shell.

PROCESS EXECUTION

        A process is a running instance of a particular computer program. These processes carry out tasks within the operating system and are generally made of machine code instructions and data stored in physical memory.
        Processes can be originally generated or copied from another active process.
        These processes don't interact with each other unless it is through kernel managed mechanism.
        Processes can be executed in the foreground or background of myshell.
        Foreground processes run independently and the user must wait for myshell to complete the related instruction until another command can be solicited from the user.
        Commands are executed in the foreground by default in myshell.
        With background processes, myshell does not have to wait for the process to end before it can solicit and run other commands.
        The myshell program will execute commands in the background if there are concluded with an ampersands (&).
        The user will immediately be able to enter another command in the prompt if the previous command was executed in the background.
