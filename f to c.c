#include<stdio.h>
int main()
{
  float f;
  printf("Welcome To Temprature Converter.\n");
  printf("Plese Enter Temp in f : ");
  scanf("%f",&f);
  float c = (f - 32) * 5 / 9;
  printf("\n Temp in C is : %.2f",c);
  return 0;
}