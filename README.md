## Project #1: Oh my pretty shell

### *** Due on 11:59:59pm, October 9 (Wednesday)***

### Goal
With the key system calls learned in the class and a few additional ones, you are ready to manipulate the processes in the system. Let the computer come to fear your system-call powers by implementing your own command shell.


### Problem Specification
- The shell program `mpsh` waits for your command after printing out a prompt `$`. When you enter a line of command on the prompt, it will be parsed into tokens as of project assignment 0, and `run_command()` function will be called with the tokens. You need to implement following features in the function.

#### Execute a program
- The primary role of shell is to execute the command specified in the command until user enters `exit`. Each command is comprised of one exeutable followed by zero or more arguments. For example;
- ```shell
  $ ls
  Makefile  mpsh   pa1    pa1.o
  $ /bin/ls
  Makefile  mpsh   pa1    pa1.o
  $ pwd
  /home/sanghoon
  $ cp mpsh mpsh.copied
  $ ls
  Makefile  mpsh   mpsh.copied   pa1   pa1.o
  $ exit
  ```


- Your shell should be able to handle `$PATH` environment variable so that you don't need to specify the full path for each external command. This feature sounds scarly, but it is obvious if you know the p-variants of `exec()` command family.
- Hint: `fork(), exec*(), wait(), waitpid()`



#### Terminate timed-out program

- Let the shell detect and terminiate non-finishing programs. Let `timeout` built-in command set the desired time out in second. When the executing program does not return for the specified second(s), the program should be terminated by sending a `SIGKILL` signal to it.

- ```shell
  $ timeout 10
  Set timeout to 10 second(s)
  $ sleep 5
  ( ... after 5 seconds ... )
  $ sleep 20
  ( ... after 10 seconds ...)
  sleep is timed out.
  $ timeout 
  ```

- Hint: `signal(), alarm(), kill()`



#### Change working directory

- Each process has so-called *working directory* which can be checked by running `/bin/pwd`. Implement `cd` command which changes the working directory.
- Each user has its home directory which is denoted by `~`. Make `cd` command to understand it

- ```shell
  $ /bin/pwd
  /home/sanghoon
  $ cd /home
  $ 
  /home
  $ cd ~
  ```

- Hints: `getpwuid(), getuid()`


#### Repeat the command n times
- Implement `for <N> <command ...>` built-in command which runs the commands N-times. Note that for can be nested.
- ```shell
  $ for 5 pwd
  /home/sanghoon/some/directory/in/depth
  /home/sanghoon/some/directory/in/depth
  /home/sanghoon/some/directory/in/depth
  /home/sanghoon/some/directory/in/depth
  /home/sanghoon/some/directory/in/depth
  $ for 4 cd ..
  $ pwd
  /home/sanghoon
  $ for 2 for 3 echo hello world
  hello world
  hello world
  hello world
  hello world
  hello world
  hello world
  $ for 20 for 10 echo for 2 nested for
  nested for
  (... 398 more "nested for" ...)
  nested for
  $ 
  ```


#### Change prompt
- Change the prompt with `prompt <new prompt>` command as follow:

- ```shell
  $ prompt #
  # prompt sce213
  sce213 prompt $
  $
  ```

- Note that the framework prints out the prompt using the contents in `prompt[]` .


### Restriction
- Do not use `system()` system call. You will get 0 pts if it is used.


### Submission / Grading

- Use [PAsubmit](https://sslab.ajou.ac.kr/pasubmit)  for submission
	- Testcases will be updated soon
- Source: pa1.c (200 pts)
- Git repository URL at git.ajou.ac.kr (10 pts)
  - Refer to https://www.youtube.com/channel/UC-Un-7jmeP-1OaHkS7awO0Q for using gitlab at Ajou University.
- Document: one PDF document (10 pts) including;
	- Outline how you start other program and how you pass its arguments
  - How do you handle timed-out program
  - How do you handle for command
  - Lesson learned (if you have any)
  - NO MORE THAN ***THREE*** PAGES
  - DO NOT INCLUDE COVER PAGE
    - No need to specify your name nor student ID on the document
  - DO NOT COMPRESS
  - OTHERWISE YOU WILL GET 0 pts for the report