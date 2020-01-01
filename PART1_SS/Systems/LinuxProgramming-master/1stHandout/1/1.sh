#!/bin/bash
#Create a symbolic link. It just saves the path you have put in the 
#path to main file to the link file 
#even if file is changed to dir it will open that dir instead of file
#if the file is moved or deleted you can't access the file
ln -s /path/main/file/ /link/file
#Create a hard link to the file it saves the inode number of the file
#even if file is moved or deleted the also you can access the file
ln /path/to/main/file /link/file
#make a named pipe
mkfifo /name/of/pipe