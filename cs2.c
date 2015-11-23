#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ROUNDS 20

int checkCommand(int argc, char ** argv);
void initState(unsigned char * state, char * key);
void decrypt(unsigned char * state, char * key,
	char * srcPath, char * destPath);
char * getFileContents(char * path);
//void decrypt();

int main(int argc, char ** argv)
{
	if ( ! checkCommand(argc, argv)) {
		printf("Usage:\n");
		printf("	cs2 encrypt <key> <source path> <dest path>\n");
		printf("	cs2 decrypt <key> <source path> <dest path>\n");
		return 0;
	}

	unsigned char * state;
	char * key;

	state = (unsigned char *) malloc(256);
	key   = (char *)          malloc(256);

	// Grab the key from the argument.
	strcpy(key, argv[2]);

	if (strcmp(argv[1], "decrypt") == 0) {
		decrypt(state, key, argv[3], argv[4]);
	}
	else {
	}

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

void initState(unsigned char * state, char * key)
{
	unsigned char c;
	int i, j, n, keyLength;

	keyLength = strlen(key);

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

void decrypt(unsigned char * state, char * key,
	char * srcPath, char * destPath)
{
	FILE * destFile;

	char * contents = getFileContents(srcPath);
	printf("%s\n", contents);
	free(contents);
}

char * getFileContents(char * path)
{
	FILE * file;
	int fileSize;
	char * data;

	file = fopen(path, "r");
	if ( ! file) {
		printf("Could not open file: %s\n", path);
		return;
	}

	fseek(file, 0L, SEEK_END);
	fileSize = ftell(file);
	rewind(file);

	printf("File size: %d bytes.\n", fileSize);

	data = malloc(fileSize);
	if ( ! data) {
		printf("Could not allocate enough memory.\n");
		return;
	}

	fread(data, fileSize, 1, file);
	fclose(file);
	return data;
}
