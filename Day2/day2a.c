#include "day2.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>


int main(int argc, char *argv[]) {
	int score, total_score = 0;
	FILE *fp;
	CharPair buffer = {'\0','\0'};

	if(argc < 2) {
		fprintf(stderr, "No filepath provided!\n");
		return -1;
	}

	if((fp = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "Failed to open file!\n");
		return -1;
	}

	while((score = get_next_score(fp,&buffer)) != 0) {
		if (score == -2) {
			fprintf(stderr, "Encountered an error while getting next pair from file!\n");
			return -1;
		} else if (score == -1) {
			fprintf(stderr, "Encountered an error while calculating score!\n");
			return -1;
		}
		total_score += score;
	}

	printf("%d\n", total_score);

	if(fclose(fp) != 0){
		fprintf(stderr, "Failed to close file!\n");
		return -1;
	}

	return 0;
}


int get_next_score(FILE *fp, CharPair *pair) {
	int ret, player_index, score = 0;
	CharPair local;

	// Use a local charpair if the user doesn't need
	// the characters returned to them.
	if(pair == NULL){
		local.head = '\0';
		local.tail = '\0';
		pair = &local;
	}

	if((ret = get_next_pair(fp, pair)) != 0) {
		// EOF REACHED
		if(ret == 1) return 0;	
		
		// ERROR OCCURED WHILE READING PAIRS
		return -2;
	}

	// Check scoring from player's choice
	switch (pair->tail) {
		case 'X':
			score += 1;
			break;
		case 'Y':
			score += 2;
			break;
		case 'Z':
			score += 3;
			break;
		default:
			return -1;
	}

	// Player's index is one less than choice score
	player_index = score - 1;

	// Check win/loss scoring
	switch (pair->head) {
		case 'A':
			score += rps_score[player_index][0];
			break;
		case 'B':
			score += rps_score[player_index][1];
			break;
		case 'C':
			score += rps_score[player_index][2];
			break;
		default:
			return -1;
	}

	return score;
}


int get_next_pair(FILE *fp, CharPair *pair) {
	char a, b;

	// Set pair to null values in case of error.
	N_NULL(pair) pair->head = '\0';
	N_NULL(pair) pair->tail = '\0';

	while(isspace((a = fgetc(fp))));
	while(isspace((b = fgetc(fp))));

	// Return 1 if end of file is reached:
	if(a == EOF && b == EOF) {
		return 1;
	}
	
	// Handle the case where there is not a pair:
	if(a == EOF) return -1;
	if(b == EOF) return -1;

	N_NULL(pair) pair->head = a;
	N_NULL(pair) pair->tail = b;

	return 0;
}
	

