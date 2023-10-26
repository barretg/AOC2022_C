#ifndef DAY_3_H
#define DAY_3_H

#include <stdio.h>

#define BUFF_MAX 255

/**
 * Function: get_repeat_char
 * -------------------------
 * Takes as input 2 strings of equal length
 * and finds whichever character is contained
 * in both strings. Assumes that only one char
 * is shared across both strings.
 *
 * str1, str2: equal length strings
 *
 * Returns the character that matched in both strings.
 * Returns '\0' if no matching char is found.
 */
char get_repeat_char(const char *str1, const char *str2); 

/**
 * Function: get_next_priority
 * ---------------------------
 * Takes a file pointer as input and
 * retrieves the next availble priority
 * value from the file. 
 *
 * fp: file pointer to input file.
 *
 * Returns 0 if the EOF has been reached.
 * Returns -1 if an invalid character is found.
 * Returns -2 if no match was found.
 * Otherwise, it returns the priority value.
 */
int get_next_priority(FILE *fp); 

#endif //DAY_3_H
