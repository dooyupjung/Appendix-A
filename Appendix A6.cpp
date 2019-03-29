#define LENGTH 10000
#define MOTIF 15
#define NUM_MOTIF 40

#include <stdio.h>
#include <string.h>

void main (void)
{
	FILE *fin, *fout;
	char query[MOTIF], seq[LENGTH], motif[NUM_MOTIF][MOTIF];
	int size, i, j, k, l, flag, cnt, num;
	float freq;

	fin = fopen("input.txt", "r");
	fgets(seq, LENGTH, fin);
	fclose(fin);

	fin = fopen("motif.txt", "r");
	fscanf(fin, "%d", &num);
	for (i = 0; i < num; i++)
		fscanf(fin, "%s", motif[i]);
	fclose(fin);

	fout = fopen("output.txt", "w");

	for (k = 0; k < num; k++) {
		for (l = 0; l < num; l++) {
			strcpy(query, motif[k]);
			strcat(query, motif[l]);
			
			size = strlen(query);

			cnt = 0;

			for (i = 0; seq[i + size] != '\0'; i++) {
				flag = 0;
				for (j = 0; j < size; j++) {
					if (query[j] == '*')		continue;
					if (query[j] != seq[i + j]) {
						flag = 1;
						break;
					}
				}

				if (flag == 0)	cnt++;
			}
			
			freq = ((float)cnt / strlen(seq));
			fprintf(fout, "%.5f ", (double)freq);
		}
		
		fprintf(fout, "\n");
	}
	
	fclose(fout);
}