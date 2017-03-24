#include <stdio.h>

/*
r	Open for reading
r+	Open for reading and writing
w	Open for writing and create the file if it does not exist. If the file exists then make it blank.
w+	Open for reading and writing and create the file if it does not exist. If the file exists then make it blank.
a	Open for appending(writing at the end of file) and create the file if it does not exist.
a+	Open for reading and appending and create the file if it does not exist.
*/

int main() {
	FILE *fpw = fopen("asdf.txt", "w");
	
	char linha[80];
	int i;
	long int var;
	
	for (i = 0; i < 10; ++i) {
		fprintf(fpw, "2112%i\n", 65);
	}
	fclose(fpw);
	
	FILE *fpr = fopen("asdf.txt", "rt");
    while(fgets(linha, 80, fpr) != NULL) {
	  /* get a line, up to 80 chars from fr.  done if NULL */
	  sscanf (linha, "%li", &var);
	  /* convert the string to a long int */
	  printf ("%li\n", var);
    }
    fclose(fpr);  /* close the file prior to exiting the routine */
	
	return 0;
}
