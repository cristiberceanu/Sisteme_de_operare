#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	char filename[100];
	strcpy(filename, argv[1]);
	int f1 = open(filename, O_RDWR); //READ & WRITE
	int i, j;
	int n = 0;
	char number[10] = "";
	int  numbers[1000], k = 0;
	int numbers_count = 0;
	char buffer[1000];
	/* Citim 10000 bytes */
	read(f1, buffer, 10000);
	printf("Numerele citit este: %s\n",buffer);
	n = strlen(buffer);
	printf("strlen:%d\n",n);
	
	/* 
	 *Explodeaza bufferul in numbers[] = {number1, number2, ...} array
	 */
	 
	for(i = 0; i<n; i++){
		
		if(buffer[i] != ' ')
		{
			number[k] = buffer[i];
			k++;
		}
		else
		{
			k = 0;	
			numbers[numbers_count] = atoi(number);
			numbers_count++;
			strcpy(number,"");
		}

	}
	/*
	 * Hack ce extrage ultimul numar si-l adauga in array-ul numbers[]
	 */

	char *pch = strrchr(buffer, ' ');
	if(pch)
	{
		int last_space = pch-buffer+1;
		i = last_space;
		k=0;
		strcpy(number,"");
		while(i<n)
		{
			number[k]=buffer[i];
			k++;
			i++;
		}
		numbers[numbers_count++] = atoi(number);
	}
	/*
	 *End hack
	 */

/* 
 * Sortare
 *
 */
for(i = 0;i<numbers_count; i++)
	for(j=i+1;j<numbers_count;j++)
		if(numbers[i]>=numbers[j])
		{
			int aux = numbers[i];
			numbers[i] = numbers[j];
			numbers[j] = aux;
		}
/*
 * Compunem output-ul. snprintf(string, int_size, type, buf) transmite in string valoarea din x.
 */	
	char output[10000] = "";
	for(i = 0;i<numbers_count; i++)
	{
		char x[10];
		snprintf(x, 10,"%d",numbers[i]);
		strcat(x," ");
		strcat(output, x);
		
	}

		close(f1); // Inchidem fisierul
		f1 = open(filename, O_TRUNC | O_RDWR); // O_TRUNC - stergem tot ce este in el. 
		write(f1, output, strlen(output)-1);
		printf("%s\n",output);
		return 0;
	}
