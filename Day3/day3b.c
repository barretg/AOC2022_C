#include "day3b.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define UPPERCASE_OFFSET 'A' - 27
#define LOWERCASE_OFFSET 'a' - 1
#define INVALID_CHAR -1
#define NO_MATCH -2

char get_repeat_char(
		const char *str1, 
		const char *str2,
		const char *str3) {

	int i;
	
	// ASCII Character Hash Tables
	bool hash1[256] = {false};
	bool hash2[256] = {false};
		
	// Store true in the hashtable if a char is encountered
	for(i = 0; str1[i]; i++) {
		hash1[(unsigned char) str1[i]] = true;
	}

	for(i = 0; str2[i]; i++) {
		hash2[(unsigned char) str2[i]] = true;
	}


	// Check for the repeat character and return it if found
	for(i = 0; str3[i]; i++) {
		if(hash1[(unsigned char) str3[i]] && 
				hash2[(unsigned char) str3[i]]) {
			printf("%s %s %s-> %c", str1, str2, str3, str3[i]);
			return str3[i];
		}
	}

	// Print for debugging
	printf("NO MATCH FOUND FOR:\n");
	printf("%s\n", str1);
	printf("%s\n", str2);
	printf("%s\n\n", str3);

	// Return '\0' when there is no match
	return '\0';
}

int get_next_priority(FILE *fp) {
	char *p, repeat; 
	char str1[BUFF_MAX], str2[BUFF_MAX], str3[BUFF_MAX];
	int i, j;

	char *strs[] = {str1, str2, str3};

	for(i = 0; i < 3; i++){
		// Get the next line, return 0 on EOF
		if(fgets(strs[i], BUFF_MAX, fp) == NULL) {
			return 0;
		}	
		// Remove the newline char from the end
		if ((p=strchr(strs[i], '\n')) != NULL) {
			*p = '\0';
		}
	}


	// Check for the repeat character in both strings
	repeat = get_repeat_char(str1, str2, str3);

	// Return -2 if no match was found
	if(repeat == '\0') {
		return NO_MATCH;
	}

	if('A' <= repeat && repeat <= 'Z') { // Uppercase Letter
		repeat -= UPPERCASE_OFFSET;
	} else if ('a' <= repeat && repeat <= 'z') { // Lowercase Letter
		repeat -= LOWERCASE_OFFSET;	
	} else {
		repeat = INVALID_CHAR;
	}

	return repeat;
}	

int main(int argc, char *argv[]) {
	int ret, sum = 0;
	FILE *fp;

	// Check that a filepath is provided
	if(argc < 2) {
		fprintf(stderr, "No filepath provided!\n");
		return -1;
	}

	// Check that the file was opened successfully
	if((fp = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "Failed to open file!\n");
		return -1;
	}
	
	// Get the sum of all priorities
	while((ret = get_next_priority(fp))) {
		if(ret == INVALID_CHAR) {
			fprintf(stderr, "Found invalid character!\n");
			return -1;
		}
		if(ret == NO_MATCH) {
			fprintf(stderr, "No match found, skipping line\n");
			continue;
		}
		

		printf(":%d\n", ret);
		sum += ret;
	}

	printf("%d\n", sum);

	// Make sure the file closes successfully
	if(fclose(fp) != 0){
		fprintf(stderr, "Failed to close file!\n");
		return -1;
	}

	return 0;
}
