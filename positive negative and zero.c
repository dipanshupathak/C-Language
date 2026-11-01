#include<stdio.h>
int main ()
{
  int number;
  printf("Plese Enter Your Number : ");
  scanf("%d",&number);
  if (number > 0){
    printf("\nThe Number Is Positive.");
  }else if (number < 0) {
    printf("\nThe Number Is Negative.");
  }else{
    printf("\nThe Number Is Zero.");
  }
  return 0;
}