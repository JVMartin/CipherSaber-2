#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int checkInput(int argc, char ** argv);

int main(int argc, char ** argv)
{
	if ( ! checkInput(argc, argv)) {
		printf("Usage:\n");
		printf("	cs2 encrypt <input file> <output file>\n");
		printf("	cs2 decrypt <input file> <output file>\n");
	}
	return 0;
}

/**
 * Check the formatting of the command call.
 */
int checkInput(int argc, char ** argv)
{
	if (argc != 4) {
		return 0;
	}

	if (strcmp(argv[1], "encrypt") != 0 &&
		strcmp(argv[1], "decrypt") != 0) {
		return 0;
	}
	
	return 1;
}
