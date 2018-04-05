#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int * getInt()
{
static int val;
printf("Enter a number: ");
scanf("%d", &val);
return(&val);
}
int main(int argc, char *argv[])
{
int * pi;
pi = getInt();
printf("You entered: %d\n", *pi);
}
