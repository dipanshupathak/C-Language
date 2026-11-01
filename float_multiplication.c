#include<stdio.h>
int main()
{
  int first, second;
  printf("plese enter the first number : ");
  scanf("%f",&first);
   printf("plese enter the second number : ");
  scanf("%f",&second);
  float result = first * second;
  printf("\n product is : %f", result);
  return 0;
}