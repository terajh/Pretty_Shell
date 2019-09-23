## Project #1: Oh my pretty shell

### *** Due on 11:59:59pm, October 9 (Wednesday)***

### Goal

With the system calls learned in the class and a few additional ones, you are ready to manipulate the processes in the system. Let the computer come to fear your system-call powers by implementing your own command shell.

> Mars will come to fear my botany powers.
> -- <cite>Mark Watney, The Martian, 2015.</cite>


### Problem Specification
- The shell program `mpsh` waits for your command line input after printing out a prompt `$`. When you enter a line of command, it will be parsed into tokens as of project assignment 0, and the framework will call `run_command()` function with the tokens. You need to implement following features in that function.


#### Execute commands (50 pts)
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

- Note that the command can either built-in or external; Built-in commands are the ones that are supported natively by the shell program. In other words, built-in commands run without any other executable. External commands are, on the other hand, the ones not the built-in commands; We need an executable in one of the directories specified in `$PATH` environment variable to process the external command..

- Your shell should be able to handle `$PATH` environment variable so that you don't need to specify the full path for each external command. This feature sounds scarly, but it is obvious if you know the p-variants of `exec()` command family.

- Hint: `fork(), exec(), wait(), waitpid()`


#### Terminate timed-out program (100 pts)

- Let the shell detect non-finishing programs and terminiate them. Let `timeout` built-in command set the desired time out specified in seconds (5 seconds by default). When the executing program does not return for the timeout second(s), the program should be terminated by sending a `SIGKILL` signal to it. When the timeout is set to 0, disable the timeout feature.

- ```shell
  $ timeout
  Current timeout is 5 seconds(s)
  $ timeout 10
  Set timeout to 10 second(s)
  $ sleep 5
  ( ... after 5 seconds ... )
  $ sleep 20
  ( ... after 10 seconds ...)
  sleep is timed out.
  $ timeout 0
  Timeout is disabled
  $ sleep 100
  ( ... after 100 seconds ...)
  $
  ```

- Hint: `signal(), alarm(), kill()`. Don't forget to disable `alarm` once the program exits otherwise the shell will be terminated.


#### Change working directory (30 pts)

- Each process has so-called *working directory* which can be checked by running `/bin/pwd`. Implement `cd` command which changes the current working directory.
- Each user has its home directory which is denoted by `~`. Make `cd` command to understand it

- ```shell
  $ pwd
  /home/sanghoon
  $ cd /somewhere/i/dont/know
  $ pwd
  /somewhere/i/dont/know
  $ cd ~
  $ pwd
  /home/sanghoon
  ```

- Hints: `chdir(), getcwd(), getenv("HOME")`


#### Repeat the command n times (50 pts)
- Implement `for <N> <command ...>` built-in command which runs the commands N-times. `for` can be nested.

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
  $ for 20 for 10 echo for 2 echo nested for
  nested for
  (... 398 more "nested for" ...)
  nested for
  $
  ```


#### Change prompt (20 pts)
- Change the prompt with `prompt <new prompt>` command as follow:

- ```shell
  $ prompt #
  # prompt sce213
  sce213 prompt $
  $
  ```

- Note that the framework makes the prompt using the contents in `prompt[]` .


### Restriction
- Do not use `system()` system call. You will get 0 pts if it is used.
- You should implement the features by calling system calls; just printing out expected results will get 0 pts for sure.


### Submission / Grading

- Use [PAsubmit](https://sslab.ajou.ac.kr/pasubmit)  for submission
	- Testcases will be available soon
- Source: pa1.c (250 pts in total)
  - Points can be prorated by the testcase results.
- Git repository URL at git.ajou.ac.kr (10 pts)
  - Refer to https://www.youtube.com/channel/UC-Un-7jmeP-1OaHkS7awO0Q for using gitlab at Ajou University.
- Document: one *PDF* document (20 pts) including;
	- Outline how you launch programs and how its arguments are passed
  - How do you handle timed-out program
  - How do you handle for command
  - Lesson learned (if you have any)
  - NO MORE THAN ***THREE*** PAGES
  - DO NOT INCLUDE COVER PAGE
    - No need to specify your name nor student ID on the document
  - DO NOT COMPRESS
  - OTHERWISE YOU WILL GET 0 pts for the report
