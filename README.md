
# Pipex Project :computer:

## Summary :page_with_curl:

This project will let you discover in detail a UNIX mechanism that you already know by using it in your program. Pipes!💡



At the start of pipex someone (thanks Daoyi!) told me this assignment has three basic parts. 3️⃣

### Part 1: Parsing Input :one:
Parsing the input to your program (input file name, command names, output file name) and storing it in a struct for later use. 📁

### Part 2: Interpreting and Finding Commands :two:
Interpreting and finding the relevant command executables (e.g., cat, echo, etc.) using (my own written versions of) string compare, split, etc.
Finding out what a environ variable is.
Keep in mind that input to pipex could be the command itself (i.e., cat), or the input could be the absolute path to the command executable (e.g., /bin/cat).
Research what [access] does. 🔍

### Part 3: Creating and Managing Pipes :three:
Creating a [pipe], and then creating a child process for each command.
In there, opening relevant files and file descriptors, and using a [dup] or [dup2] function to redirect the file descriptors of whichever relevant input file,
or standard input/outputs to the relevant pipe end.
This part can be a bit tricky to wrap your brain around at first, so watching videos and trying to understand it properly is key! Especially for pipes. 🚸
Also when a command fails or doesnt exist you don't always exit the entire program but just the child process⚠

Your program will be executed as follows:
```shell
./pipex file1 cmd1 cmd2 file2


The program takes 4 arguments:
- `file1` and `file2` are file names.
- `cmd1` and `cmd2` are shell commands with their parameters.

It must behave exactly the same as the shell command below:
```shell
$> < file1 cmd1 | cmd2 > file2
```

## Examples :dart:

### Example 1
```shell
$> ./pipex infile "ls -l" "wc -l" outfile
```
Should behave like: 
```shell
< infile ls -l | wc -l > outfile
```

### Example 2
```shell
$> ./pipex infile "grep a1" "wc -w" outfile
```
Should behave like: 
```shell
< infile grep a1 | wc -w > outfile
```
