#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ROUNDS 10

int checkCommand(int argc, char ** argv);
void initState(unsigned char * state, unsigned char * key, int keyLength);
void decrypt(unsigned char * state, char * key,
	char * srcPath, char * destPath);
void cipher(unsigned char * state, unsigned char * data, int length);
unsigned char * getFileContents(char * path, int * fileSize);
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

	if (strlen(argv[2]) > 246) {
		printf("That key is too long.\n");
		return 0;
	}
	
	return 1;
}

void initState(unsigned char * state, unsigned char * key, int keyLength)
{
	unsigned char c;
	int i, j, n;

	// Initialize the state array.
	for (i = 0; i < 256; ++i) {
		state[i] = i;
	}

	j =  0;

	for (n = 0; n < ROUNDS; ++n) {
		for (i = 0; i < 256; ++i) {
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
	unsigned char * data;
	unsigned char * appendedKey;
	int keyLength;
	int dataSize;

	data = getFileContents(srcPath, &dataSize);
	if ( ! data) return;
	keyLength = strlen(key);

	appendedKey = malloc(keyLength + 10);
	memcpy(appendedKey, key, keyLength);
	memcpy(appendedKey + keyLength, data, 10);

	initState(state, appendedKey, keyLength + 10);

	cipher(state, data + 10, dataSize - 10);

	printf("%s\n", data + 10);

	free(data);
	free(appendedKey);
}

void cipher(unsigned char * state, unsigned char * data, int length)
{
	int i, j, k, n;
	unsigned char c;

	i = j = 0;

	for (n = 0; n < length; ++n) {
		i = (i + 1) % 256;
		j = (j + state[i]) % 256;
		c = state[i];
		state[i] = state[j];
		state[j] = c;
		k = (state[i] + state[j]) % 256;
		data[n] = data[n] ^ state[k];
	}
}

unsigned char * getFileContents(char * path, int * fileSize)
{
	FILE * file;
	unsigned char * data;

	file = fopen(path, "r");
	if ( ! file) {
		printf("Could not open file: %s\n", path);
		return 0;
	}

	fseek(file, 0L, SEEK_END);
	*fileSize = ftell(file);
	rewind(file);

	data = (unsigned char *) malloc(*fileSize + 1);
	if ( ! data) {
		printf("Could not allocate enough memory.\n");
		return 0;
	}
	data[*fileSize] = 0;

	fread(data, *fileSize, 1, file);
	fclose(file);
	return data;
}
