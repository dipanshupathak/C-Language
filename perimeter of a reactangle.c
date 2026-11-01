#include<stdio.h>
int main ()
{
  int a, b, c, d;
  printf("Plese Enter The First Side : ");
  scanf("%d",&a);
  printf("Plese Enter The Second Side : ");
  scanf("%d",&b);
  printf("Plese Enter The Third Side : ");
  scanf("%d",&c);
  printf("Plese Enter The Fourth Side : ");
  scanf("%d",&d);
  int perimeter = a + b + c + d;
  printf("\n Perimeter of your shape is : %d",perimeter);
}