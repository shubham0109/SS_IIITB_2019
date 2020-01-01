#!/bin/bash
gcc 2.c
./a.out &
# man bash
# #      Expands to the number of positional parameters in decimal.
# ?      Expands to the exit status of the most recently executed foreground pipeline.
# -      Expands to the current option flags as specified upon invocation, by the set builtin command, or those set by the shell itself (such
#       as the -i option).
# $      Expands to the process ID of the shell.  In a () subshell, it expands to the process ID of the current shell, not the subshell.
# !      Expands to the process ID of the job most recently placed into the background, whether executed as an asynchronous command or  using
#       the bg builtin (see JOB CONTROL below).
# 0      Expands to the name of the shell or shell script.  This is set at shell initialization.  If bash is invoked with a file of commands,
#       $0 is set to the name of that file.  If bash is started with the -c option, then $0 is set to the first argument after the string to
#       be executed, if one is present.  Otherwise, it is set to the filename used to invoke bash, as given by argument zero.
# _      At  shell startup, set to the absolute pathname used to invoke the shell or shell script being executed as passed in the environment
#       or argument list.  Subsequently, expands to the last argument to the previous command, after expansion.  Also set to the full  path‐
#       name  used to invoke each command executed and placed in the environment exported to that command.  When checking mail, this parame‐
#       ter holds the name of the mail file currently being checked.
PID=$!
echo "PID of the process $PID"
ls /proc/$PID
