#ifndef DAY_2_H
#define DAY_2_H

#include <stdio.h>

#define N_NULL(X) if(X != NULL)

/**
 * Constant array for RPS scoring.
 * First Index: head (player)
 * Second index: tail (opponent)
 */
const char rps_score[3][3] = {
			//  ROCK	PAPER	SCISSORS
/* ROCK  	*/ 	{3,	  	0,	6 	}, 
/* PAPER 	*/      {6,		3,	0	}, 
/* SCISSORS	*/	{0,		6,	3	},
};

typedef struct char_pair {
	char head;
	char tail;
} CharPair;

/**
 * Function: get_next_pair
 * -----------------------
 * Gets the next (non-whitespace) pair of characters 
 * from the given input file, fp.
 * 
 * fp: pointer to the input file
 * pair: CharPair to store values in. This will default
 * to contain the null character in case of error. If
 * this parameter is NULL, the values will not be stored.
 *
 * Returns 0 if a pair is found.
 * Returns 1 if EOF has been reached.
 * Returns -1 if an error occurs or no pair is available.
 */
int get_next_pair(FILE *fp, CharPair *pair);

/**
 * Function: get_next_score
 * ------------------------
 * Gets the score for the next round of RPS.
 *
 * fp: pointer to the input file.
 * pair: CharPair to store the RPS values for
 * the given round. If this is NULL, they will
 * not be stored.  
 *
 * Returns an integer greater than 0 if the score 
 * could be calculated.
 * Returns 0 if the end of file has been reached.
 * Returns -1 if an error occurred during score
 * calculation.
 * Returns -2 if an error occured reading in the
 * next available pair.
 */
int get_next_score(FILE *fp, CharPair *pair);

#endif //DAY_2_H
