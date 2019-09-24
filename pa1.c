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
#include <assert.h>

#include "types.h"
#include "parser.h"

static char prompt[MAX_TOKEN_LEN] = "$";


/***********************************************************************
 * run_command()
 *
 * DESCRIPTION
 *   Implement the specified shell features here using the parsed command
 *   tokens.
 *
 * RETURN VALUE
 *   Return 1 on successful command execution
 *   Return 0 when user inputs "exit".
 *   Return <0 on error
 */
static int run_command(int nr_tokens, char *tokens[])
{
	/* This function is all yours. Good luck! */

	assert(nr_tokens > 0);

	if (strncmp(tokens[0], "exit", strlen("exit")) == 0) {
		return 0;
	}

	/*
	fork();
	exec();
	...
	*/

	return 1;
}


/***********************************************************************
 * main() of this program.
 *
 * *** DO NOT MODIFY ANYTHING BELOW THIS LINE ***
 */
int main(int argc, const char *argv[])
{
	char command[MAX_COMMAND_LEN] = { '\0' };
	int ret = 0;

	printf("[0;31;40m%s[0m ", prompt);
	while (fgets(command, sizeof(command), stdin)) {	
		char *tokens[MAX_NR_TOKENS] = { NULL };
		int nr_tokens = 0;

		if (parse_command(command, &nr_tokens, tokens) == 0)
			goto more; /* You may use nested if-than-else, however .. */

		ret = run_command(nr_tokens, tokens);
		if (ret == 0) {
			break;
		} else if (ret < 0) {
			fprintf(stderr, "Error in run_command: %d\n", ret);
		}

more:
		printf("[0;31;40m%s[0m ", prompt);
	}

	return ret;
}
