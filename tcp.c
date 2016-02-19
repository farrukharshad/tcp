
/*
*
* This small utility copy one string from the terminal and can be
* read from another terminal
*
* This utility is distributed under GNU GPL 3 license. Please see
* the details of the license at 
* http://www.gnu.org/licenses/gpl-3.0.en.html
*
* Author: Farrukh Arshad : farrukh.arshad@gmail.com
* Date: March 13, 2015 
*
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

enum { COMM_IDX = 1, STR_IDX = 2 };
typedef enum { INVALID = 1, COPY, COPY_PWD, PASTE, HELP } OPERATION;

static char *copy_command = "-c";
static char *paste_command = "-p";
static char *help_command = "-h";

static OPERATION parse_args(int argc, char **argv) {
	OPERATION op = INVALID;

	// If no argument is provided, by default we will do paste
	// from our clipboard
	if ( argc == 1 ) {
		op = PASTE;
	} else {
		if ( !strncmp(argv[COMM_IDX], copy_command, strlen(copy_command)) ) { 
			if ( argc == 2 ) {
				op = COPY_PWD;
			} else if ( argc == 3 ) { 
				op = COPY;
			}
		}
		if ( !strncmp(argv[COMM_IDX], paste_command, strlen(paste_command)) ) { 
			op = PASTE;
		}
		if ( !strncmp(argv[COMM_IDX], help_command, strlen(help_command)) ) { 
			op = HELP;
		}
	}
	return op;
}
static void do_copy(const char *data, const char *path) {
	// open file for writing
	FILE *file = fopen(path, "w");

	if ( file ) {
		fwrite(data, strlen(data), sizeof(char), file);
		fflush(file);
		fclose(file);
	} else {
		printf("error: %s\n", strerror(errno));
	}
}
static void do_paste(const char *path) {
	// open file for reading
	FILE *file = fopen(path, "r");
	char *line = NULL;
	size_t len = 0;
	ssize_t read = 0;

	if ( file ) {
		while ( (read = getline(&line, &len, file)) != -1 ) {
			printf("%s\n", line);	
		}
		if ( line ) {
			free(line);
		}
		fflush(file);
		fclose(file);
	} else {
		// We will do nothing is there is nothing to copy from
		if ( errno != 2 ) {
			printf("error: %d : %s\n", errno, strerror(errno));
		}
	}
}
static void help(const char *prog) {
	printf("usage\n-----\n");
	printf("%s %s \"<string_to_copy>\"   : copy a string to terminal clipboard\n", prog, copy_command);
	printf("%s                         : paste last string from terminal clipboard\n", prog);
	printf("%s %s                      : paste last string from terminal clipboard\n", prog, paste_command);
	printf("%s %s                      : show this help menu\n", prog, help_command);
	printf("\nDistribute under BSD style license.\nFarrukh Arshad : farrukh.arshad@gmail.com\n");
}

int main(int argc, char **argv)
{
	char *user_home = getenv("HOME");
	char clipboard[1042];
	sprintf(clipboard, "%s/.tcp_clip", user_home);
	if ( user_home ) {
		switch(parse_args(argc, argv)) {
			case COPY:
				do_copy(argv[STR_IDX], clipboard);
				break;
			case COPY_PWD: {
				char *pwd = getcwd(NULL, 0);
				if ( pwd ) {
					printf("copied current working directory\n");
					do_copy(pwd, clipboard);
					free(pwd);
				} else {
					printf("pwd_error: %s\n", strerror(errno));
				}
				break;
				}
			case PASTE:
				do_paste(clipboard);
				break;
			case HELP:
			case INVALID:
			default:
				help(argv[0]);
				break;
		}
	} else {
		printf("error: unable to find user home directory path\n");
	}

	return 0;
}
