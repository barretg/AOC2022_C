#include "day4.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef VERBOSE
#define v_printf(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define v_printf(fmt, ...) /* NO-OP */
#endif

#ifdef DEBUG
#define d_printf(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define d_printf(fmt, ...) /* NO-OP */
#endif

range* create_range(unsigned int head, unsigned int tail) {
	d_printf("Creating a new range...\n");
	range * output;

	output = (range*) calloc(1, sizeof(range));
	output->head = head;
	output->tail = tail;

	return (range *) calloc(1, sizeof(range));
}

void destroy_range(range* r) {
	d_printf("Destroying a range...");	
	free(r);
}

int next_line(FILE *fp, char* buffer) {
	d_printf("Time to get the next line...\n");
	// Get the next line, return "\0" on EOF
	if(fgets(buffer, BUFF_MAX, fp) == NULL) {
		return EOF;
	}

	// Remove the newline char from the end
	char *p;
	if ((p=strchr(buffer, '\n')) != NULL) {
		*p = '\0';
	}

	return 0;
}

void get_ranges(char *str, range* r1, range* r2){
	char *token, *subtoken, *save1, *save2;
	
	// Get first range
	token = strtok_r(str, ",", &save1);
	
	// Set r1 head:
	subtoken = strtok_r(token, "-", &save2);
	r1->head = atoi(subtoken);

	// Set r1 tail:
	subtoken = strtok_r(NULL, "-", &save2);
	r1->tail = atoi(subtoken);	
	
	// Get second range
	token = strtok_r(NULL, ",", &save1);
	
	// Set r2 head:
	subtoken = strtok_r(token, "-", &save2);
	r2->head = atoi(subtoken);

	// Set r2 tail:
	subtoken = strtok_r(NULL, "-", &save2);
	r2->tail = atoi(subtoken);
}

int does_next_contain(FILE *fp) {
	char buffer[BUFF_MAX];
	
	d_printf("About to try range creation...\n");
	range *r1 = create_range(0,0), *r2 = create_range(0,0);
	d_printf("Ranges created!\n");

	if(next_line(fp, buffer) == EOF) {
		return EOF;
	}

	d_printf("Time to get ranges...\n");
	get_ranges(buffer, r1, r2);

	v_printf("r1:%d-%d, r2:%d-%d -> ", r1->head, r1->tail, r2->head, r2->tail);	

	if(r1->head == r2->head || r1->tail == r2->tail) {
		v_printf("one contains the other (equal case)\n");
		return 1;
	}
		
	if(r1->head < r2->head) {
		if(r2->tail < r1->tail) {
			destroy_range(r1);
			destroy_range(r2);
			v_printf("r1 contains r2\n");
			return 1;
		}
	} else {
		if(r1->tail < r2->tail) {
			destroy_range(r1);
			destroy_range(r2);
			v_printf("r2 contains r1\n");
			return 1;
		}
	}

	destroy_range(r1);
	destroy_range(r2);
	v_printf("neither contains\n");
	return 0;
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
	
	d_printf("Begin summation...\n");
	while((ret = does_next_contain(fp)) != EOF) {
		d_printf("Current sum value: %d\n", sum);
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
