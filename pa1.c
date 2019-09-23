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

#define MAX_NR_TOKENS	32	/* Maximum length of tokens in a command */
#define MAX_TOKEN_LEN	128	/* Maximum length of single token */
#define MAX_COMMAND_LEN	4096 /* Maximum length of assembly string */

typedef unsigned char bool;
#define true	1
#define false	0

static char prompt[MAX_TOKEN_LEN] = "$";


/***********************************************************************
 * run_command
 *
 * DESCRIPTION
 *   Implement the specified shell features here using the parsed command
 *   tokens.
 *
 * RETURN VALUE
 *   Return -1 when user inputs "exit". Return 0 otherwise.
 */
static int run_command(int nr_tokens, char *tokens[])
{
	/* TODO: Do your implementation here. Good luck! */

	return 0;
}


/*************** DO NOT CHANGE ANY LINE BELOW THIS COMMENT ***************/
/***********************************************************************
 * parse_command
 *
 * DESCRIPTION
 *  Parse @command, and put each command token into @tokens[] and the number of
 *  tokes into @nr_tokens. You may use this implemention or your own from PA0.
 *
 * A command token is defined as a string without any whitespace (i.e., *space*
 * and *tab* in this programming assignment). For exmaple,
 *   command = "  ps -aef /home/sanghoon "
 *
 * then, nr_tokens = 3, and tokens is
 *   tokens[0] = "ps"
 *   tokens[1] = "-aef"
 *   tokens[2] = "/home/sanghoon"
 *   tokens[>=3] = NULL
 *
 * You can assume that the input string is all lowercase for testing.
 *
 * RETURN VALUE
 *  Return 0 after filling in @nr_tokens and @tokens[] properly
 *
 */
static bool __is_separator(char *c)
{
	char *separators = " \t\r\n";

	for (size_t i = 0; i < strlen(separators); i++) {
		if (*c == separators[i]) return true;	
	}

	return false;
}
static int parse_command(char *command, int *nr_tokens, char *tokens[])
{
	char *curr = command;
	int token_started = false;
	*nr_tokens = 0;

	while (*curr != '\0') {  
		if (__is_separator(curr)) {  
			*curr = '\0';
			token_started = false;
		} else {
			if (!token_started) {
				tokens[*nr_tokens] = curr;
				*nr_tokens += 1;
				tokens[*nr_tokens] = "\0";
				token_started = true;
			}
		}

		curr++;
	}

	return (*nr_tokens > 0);
}


/***********************************************************************
 * The main function of this program.
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
			goto more;

		if ((ret = run_command(nr_tokens, tokens) < 0)) break;

more:
		printf("[0;31;40m%s[0m ", prompt);
	}

	return ret;
}
