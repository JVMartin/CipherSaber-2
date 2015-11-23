#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int checkCommand(int argc, char ** argv);

int main(int argc, char ** argv)
{
	if ( ! checkCommand(argc, argv)) {
		printf("Usage:\n");
		printf("	cs2 encrypt <password> <input file> <output file>\n");
		printf("	cs2 decrypt <password> <input file> <output file>\n");
	}

	return 0;
}

/**
 * Check the formatting of the command call.
 */
int checkCommand(int argc, char ** argv)
{
	if (argc != 5) {
		return 0;
	}

	if (strcmp(argv[1], "encrypt") != 0 &&
		strcmp(argv[1], "decrypt") != 0) {
		return 0;
	}
	
	return 1;
}
