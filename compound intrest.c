#include<stdio.h>
#include<math.h>
int main ()
{
 float principal, rate, time;
  printf("Welcom to Compound Interst Calculator.\n");
  printf("Plese Enter The principle : ");
  scanf("%f",&principal);
  printf("Now, Enter The Rate : ");
  scanf("%f",&rate);
   printf("Now, Enter The Time : ");
  scanf("%f",&time);

  float intrest = principal * ((1 + rate / 100),time);
 printf("\n Compound Intrest  is : %.2f",intrest);
 return 0;
}