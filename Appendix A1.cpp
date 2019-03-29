#define LENGTH 10000
#define MAX 30000
#define MOTIF 10

#include <stdio.h>
#include <string.h>

void main (void)
{
	FILE *fin, *fout;
	char seq[LENGTH], result[MAX][MOTIF] = {{'\0',},}, temp[MOTIF];
	int size, i, j, k, l = 0, match, cnt[MAX] = {0,}, num, route, sort;
	float freq[MAX];

	printf("Size of Window = ");
	scanf("%d", &size);

	fin = fopen("input.txt", "r");
	fgets(seq, LENGTH, fin);
	fclose(fin);

	for(i = 0; seq[i + size] != '\0'; i++) {
		route = 0;
		for(j = 0; j < l; j++) {
			match = 0;
			for(k = 0; k < size; k++) {
				if(seq[i + k] != result[j][k])	break;
				else	match++;
			}
			
			if(match == size)	{
				route = 1;
				break;
			}
		}

		if(route == 0) {
			num = 0;
			for(j = 0; seq[j + size] != '\0'; j++) {
				match = 0;
				for(k = 0; k < size; k++) {
					if(seq[i + k] != seq[j + k])	break;
					else	match++;
				}

				if(match == size)	num++;
			}
			
			if(num > 1) {
				cnt[l] = num;
				for(k = 0; k < size; k++)
					result[l][k] = seq[i + k];
				l++;
			}
		}
	}

	for(i = 0; i < l; i++) {
		for(j = i + 1; j < l; j++) {
			if(cnt[i] < cnt[j]) {
				for(k = 0; k < size; k++) {
					temp[k] = result[i][k];
					result[i][k] = result[j][k];
					result[j][k] = temp[k];
				}
				sort = cnt[i];
				cnt[i] = cnt[j];
				cnt[j] = sort;
			}
		}
	}
	
	fout = fopen("output.txt", "w");

	fprintf(fout, "Sequence length = %d\n", strlen(seq));

	fprintf(fout, "TOP 30s in %d results found!\n\n", l);
	
	if(l > 30)	l = 30;
	
	for(i = 0; i < l; i++) {
		freq[i] = ((float)cnt[i]/strlen(seq)) * 100;
		fprintf(fout, "%s\t%.3f\n", result[i], (double)freq[i]);
	}

	fclose(fout);
}