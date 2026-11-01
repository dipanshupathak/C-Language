#include<stdio.h>
int main ()
{
  int b, h;
  printf("Welcom to area of triangle calculation.\n");
  printf("Plese Enter The Height : ");
  scanf("%d",&h);
  printf("Plese Enter The Breath : ");
  scanf("%d",&b);
  float area = 0.5 * b * h;
 printf("\n Area Of Your Traingle is : %f",area);
 return 0;
}