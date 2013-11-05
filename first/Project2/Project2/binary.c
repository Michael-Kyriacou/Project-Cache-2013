#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>

void binaryChange(long int num)   // Function Definition
{
long int rem[50];
int i=0;
int length=0;

while(num>0)
 {
 rem[i]=num%2;
 num=num/2;
 i++;
 length++;
 }

printf("nBinary number : ");
     for(i=length-1;i>=0;i--)
             printf("%ld",rem[i]);

printf("\n");
}
//================================================
void main()
{
int num;

 printf("Enter the decimal number : ");
 scanf_s("%d",&num);

    binaryChange(num);   // Calling function

system("pause");
}