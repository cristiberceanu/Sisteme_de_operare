#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char const *argv[])
{
	int number1 = 0;
	int number2 = 0;
	number1 = atoi(argv[1]);
	number2 = atoi(argv[2]);
	while(number1 != number2){
		if(number1>number2)
			number1 = number1-number2;
		else
			number2 = number2-number1;
	}

	printf("%d\n", number1);
	return 0;
}