#include<stdio.h>
int main()
{
  int number;
  printf("Plese Enter Your Number : ");
  scanf("%d",&number);
  if ( number % 2 == 0) {
    printf("The Number Is Even.");
  }else {
    printf("The Number Is Odd.");
  }
  return 0;
}