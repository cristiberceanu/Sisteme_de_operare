#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFF_SIZE 1000
int main(int argc, char const *argv[])
{

	char string[100], file[100], content[BUFF_SIZE];
	FILE *f = fopen("input.txt","r");
	strcpy(string, argv[1]); 
	strcpy(file, argv[2]);
	fgets(content, BUFF_SIZE, f);
	fclose(f);

	int count = 0;
	char *tmp = content;
	while(tmp = strstr(tmp, string))
	{
		count++;
		tmp++;
	}

	printf("%d \n",count);

	return 0;
}
