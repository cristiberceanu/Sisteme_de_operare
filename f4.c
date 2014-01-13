#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char const *argv[])
{
	int number = atoi(argv[1]);
	int sum = 0;
	while(number!=0){
		sum+=number%10;
		number/=10;
	}
	printf("%d\n", sum);
	return 0;
}