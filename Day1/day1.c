#include "day1.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int n_max_elves(FILE *fp, int** max_ptr, int n) {
	char buffer[BUFF_MAX];
	int i, sum = 0;
	bool found = false;
	int *max = *max_ptr;

	for(i = 0; i < n; i++) {
		max[i] = 0;									
	}
		
	while(fgets(buffer, BUFF_MAX, fp) != NULL) {
		if(buffer[0] == '\n') {
		    if(sum > max[0]) {
				i = 1;
				found = false;
				while(!found) {
					if(i == n) {
						max[n-1] = sum;
						found = true;
					} else if(sum < max[i]) {
						max[i-1] = sum;
						found = true;
					} else {
						max[i-1] = max[i];
						i++;
					}
				}
		    }
		    sum = 0;
		} else {
		    sum += atoi(buffer);
		}
	}
	
	sum = 0;
	for(i = 0; i < n; i++) {
		sum += max[i];
	}

	return sum;	
}

int main(int argc, char *argv[]) {
	FILE *fp;

	int n = 1;
	int *top_n_elves;

	if(argc < 2) {
		fprintf(stderr, "No filepath provided!\n");
		return -1;
	}

	if(argc >= 3) {
		if(!(n = atoi(argv[2]))) {
			fprintf(stderr, "n must be a postive integer!\n");
			return -1;
		}
	}

	if((top_n_elves = (int *) calloc(n, sizeof(int))) == NULL) {
		fprintf(stderr, "Failed to allocate memory\n");
		return -1;
	}

	if((fp = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "Failed to open file!\n");
		free(top_n_elves);
		return -1;
	}
	
	printf("%d\n", n_max_elves(fp, &top_n_elves, n));		
	
	if(fclose(fp) != 0){
		fprintf(stderr, "Failed to close file!\n");
		free(top_n_elves);
		return -1;
	}

	free(top_n_elves);
	return 0;
}
