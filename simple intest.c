#include<stdio.h>
int main ()
{
 float principle, rate, time;
  printf("Welcom to Simple Interst Calculator.\n");
  printf("Plese Enter The principle : ");
  scanf("%f",&principle);
  printf("Now, Enter The Rate : ");
  scanf("%f",&rate);
   printf("Now, Enter The Time : ");
  scanf("%f",&time);

  float intrest = (principle * rate * time) / 100;
 printf("\n Simple Intrest  is : %.2f",intrest);
 return 0;
}