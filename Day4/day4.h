#ifndef DAY_4_H
#define DAY_4_H

#include <stdio.h>

// MACROS:

#define BUFF_MAX 255

// DATA:

/*
 * A range has:
 *  - a head value marking the 
 *    start of the range.
 *  - a tail value marking the
 *    end of the range.
 */
typedef struct range {
	unsigned int head;
	unsigned int tail;
} range;

// FUNCTIONS:

/**
 * Gets the next line from file
 * input, replacing the newline
 * character with '\0'
 *
 * Returns a string containing
 * the line.
 * Returns EOF if the end of
 * the file is reached.
 */
int next_line(FILE *fp, char *buffer);

/**
 * Gets the next range from the
 * string. The caller must call
 * destroy_range(<range>) when
 * finished with using the range.
 *
 * returns NULL if range cannot be
 * created.
 */
void get_ranges(char *str, range* r1, range* r2);

/**
 * Checks if for next line's ranges
 * one contains the other.
 *
 * True if it does.
 * False if it doesn't.
 */
int does_next_contain(FILE *fp);

/**
 * Checks if the next line's ranges
 * intersect with eachother at all.
 *
 * True if it does.
 * False if they don't;
 */
int does_next_overlap(FILE *fp);

#endif //DAY_4_H
