#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ROUNDS 20

int checkCommand(int argc, char ** argv);
void initState(unsigned char * state, char * key, int keyLength);

int main(int argc, char ** argv)
{
	if ( ! checkCommand(argc, argv)) {
		printf("Usage:\n");
		printf("	cs2 encrypt <key> <input file> <output file>\n");
		printf("	cs2 decrypt <key> <input file> <output file>\n");
		return 0;
	}

	unsigned char * state;
	char * key;
	int keyLength;

	state = (unsigned char *) malloc(256);
	key   = (char *)          malloc(256);

	// Grab the key from the argument.
	strcpy(key, argv[2]);
	keyLength = strlen(key);

	initState(state, key, keyLength + 10);

	free(state);
	free(key);
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

void initState(unsigned char * state, char * key, int keyLength)
{
	unsigned char c;
	int i, j, n;

	// Initialize the state array.
	for (i = 0; i < 255; ++i) {
		state[i] = i;
	}

	j =  0;

	for (n = 0; n < ROUNDS; ++n) {
		for (i = 0; i < 255; ++i) {
			j += state[i];
			j += key[i % keyLength];
			j = j % 256;

			// Swap the ith and jth elements of the state array.
			c = state[i];
			state[i] = state[j];
			state[j] = c;
		}
	}
}
