/**********************************************************************
 * Copyright (c) 2019
 *  Sang-Hoon Kim <sanghoonkim@ajou.ac.kr>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTIABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 **********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h> //
#include <sys/wait.h>
#include <errno.h>
#include <ctype.h>

#include "types.h"
#include "parser.h"

/*====================================================================*/
/*          ****** DO NOT MODIFY ANYTHING FROM THIS LINE ******       */
/**
 * String used as the prompt (see @main()). You may change this to
 * change the prompt */
static char __prompt[MAX_TOKEN_LEN] = "$";

/**
 * Time out value. It's OK to read this value, but ** DO NOT CHANGE
 * DIRECTLY **. Instead, use @set_timeout() function below.
 */
static unsigned int __timeout = 2;

static void set_timeout(unsigned int timeout)
{
	__timeout = timeout;

	if (__timeout == 0) {
		fprintf(stderr, "Timeout is disabled\n");
	} else {
		fprintf(stderr, "Timeout is set to %d second%s\n",
				__timeout,
				__timeout >= 2 ? "s" : "");
	}
}
/*          ****** DO NOT MODIFY ANYTHING UP TO THIS LINE ******      */
/*====================================================================*/


/***********************************************************************
 * run_command()
 *
 * DESCRIPTION
 *   Implement the specified shell features here using the parsed
 *   command tokens.
 *
 * RETURN VALUE
 *   Return 1 on successful command execution
 *   Return 0 when user inputs "exit"
 *   Return <0 on error
 */

struct sigaction sa;
//struct sigaction old;
void sigint_handler(int signo){
	//kill(getpid(),SIGKILL);
	alarm(__timeout);
}
int No_such=0;

static int run_command(int nr_tokens, char *tokens[])
{
	/* This function is all yours. Good luck! */
	char *for_str[MAX_NR_TOKENS]={NULL}; int fornum;
	if (strncmp(tokens[0], "exit", strlen("exit")) == 0) {
		return 0;
	} // if exit return.

	int status; // 자식 상태
	pid_t pidnum; // fork() 반환 값 받을 pid 변수
	pid_t waitPid; // 자식 프로세스 종료 상태 받을 pid 변수


	//sigfillset(&sa.sa_mask);
	sigemptyset(&sa.sa_mask);
	sa.sa_handler=sigint_handler;
	sa.sa_flags=0; // 시그널 처리하는 동안 전달 시그널 블록 X

	

	// sigaction(), alarm()
	// cd, prompt, for, timeout 은 built in command
	// 나머지 명령어들은 external command
	

	if(!strcmp(tokens[0],"cd")){
		if(nr_tokens==1){
			chdir(getenv("HOME"));
			return 1; // 여기서 끝
		}	
		else if(!strcmp(tokens[1],"~"))	{
			chdir(getenv("HOME"));
			return 1; // 여기서 끝
		}
		else{
			chdir(tokens[1]);
			return 1; // 여기서 끝
		}
	} // because "cd" is shell, not program
	
	else if(!strcmp(tokens[0],"for")){
		int forcount=atoi(tokens[1]); // count "for" command
		int start_command=2; // start command index

		for(int i=1;i<nr_tokens;i++) {
			if(!strcmp(tokens[i],"for")) {
				if(i+2<nr_tokens){
					if(atoi(tokens[i+1])) {
						forcount*=atoi(tokens[i+1]);
						start_command=i+2;
					}
				}
				else continue;
			}
		}
		for(int i=0;i<forcount;i++){
			run_command(nr_tokens-start_command,tokens+start_command);
		}
		return 1;
	} // because "for" is not program.

	else if(!strcmp(tokens[0],"prompt")){
		strcpy(__prompt,tokens[1]);
		return 1; // 여기서 끝
	}

	else if (!strcmp(tokens[0],"timeout")){

			if(nr_tokens==1) {
				printf("Current timeout is %d second\n",__timeout);
				return 1;
			}
			else{
				set_timeout(atoi(tokens[1]));
				//alarm(__timeout);
				//__timeout 이 시간 값
				// alarm 시그널 생기면 sa에 등록된 핸들러 실행
				return 1;
			}
		// 여기서 끝
		}


/********************************************************************/
	// 자식 프로세스 생성
	if((pidnum=fork())==0) {
		alarm(__timeout);
		sigaction(SIGALRM,&sa,NULL);
		if(execvp(tokens[0],tokens)<0){
			fprintf(stderr,"No such file or directory\n");
			// confirm no such file
			//execl("/bin/echo","/bin/echo","No such file or directory",NULL);
			kill(getpid(),SIGKILL);
			// 여기서 exit 로 프로세스를 죽이면 자식 프로세스의 출력 버퍼를 던지고 죽는다.
		}
		else return 1;
	}
	 // child
 	
	else if(pidnum==-1){
		wait(&status);
		return 0;
	} // error

	else { 
		//WTERMSIG(status)==SIGALRM
		if((waitPid=wait(&status))!=-1) // child is closed?
		{
			if(WTERMSIG(status)==SIGALRM){ // 프로세스가 알람신호로 죽엇나?
				fprintf(stderr,"%s is timed out\n",tokens[0]);
				return 1;	
			}
			else if(WTERMSIG(status)==SIGKILL) // 프로세스가 kill 신호로 죽엇나?
			{
				return 1;
			}
			else return 1;
		}
		else return 0;
	} // parent

	/*
	fork();
	exec();
	...
	*/
	return 1;
}


/***********************************************************************
 * initialize()
 *
 * DESCRIPTION
 *   Call-back function for your own initialization code. It is OK to
 *   leave blank if you don't need any initialization.
 *
 * RETURN VALUE
 *   Return 0 on successful initialization.
 *   Return other value on error, which leads the program to exit.
 */
static int initialize(int argc, char * const argv[])
{
	return 0;
}


/***********************************************************************
 * finalize()
 *
 * DESCRIPTION
 *   Callback function for finalizing your code. Like @initialize(),
 *   you may leave this function blank.
 */
static void finalize(int argc, char * const argv[])
{

}


/*====================================================================*/
/*          ****** DO NOT MODIFY ANYTHING BELOW THIS LINE ******      */

static bool __verbose = true;
static char *__color_start = "[0;31;40m";
static char *__color_end = "[0m";

/***********************************************************************
 * main() of this program.
 */
int main(int argc, char * const argv[])
{
	char command[MAX_COMMAND_LEN] = { '\0' };
	int ret = 0;
	int opt;

	while ((opt = getopt(argc, argv, "qm")) != -1) {
		switch (opt) {
		case 'q':
			__verbose = false;
			break;
		case 'm':
			__color_start = __color_end = "\0";
			break;
		}
	} // option control

	if ((ret = initialize(argc, argv))) return EXIT_FAILURE;

	if (__verbose)
		fprintf(stderr, "%s%s%s ", __color_start, __prompt, __color_end);

	while (fgets(command, sizeof(command), stdin)) {	
		char *tokens[MAX_NR_TOKENS] = { NULL };
		int nr_tokens = 0;

		if (parse_command(command, &nr_tokens, tokens) == 0)
			goto more; /* You may use nested if-than-else, however .. */
		//printf("%s",tokens);
		ret = run_command(nr_tokens, tokens); // 여기서 실행

		if (ret == 0) {
			break;
		} else if (ret < 0) {
			fprintf(stderr, "Error in run_command: %d\n", ret);
		}

more:
		if (__verbose)
			fprintf(stderr, "%s%s%s ", __color_start, __prompt, __color_end);
	}

	finalize(argc, argv);

	return EXIT_SUCCESS;
}
