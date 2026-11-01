#include<stdio.h>
int main ()
{
  int num;
  printf("Enetr A Number : ");
  scanf("%d",&num);
  if (num % 5 == 0 && num % 11 == 0){
    printf("%d is divisible by both 5 and 11.\n",num);
  }else{
    printf("%dis not divisible by both 5 and 11.\n,num");
  }
  return 0;
}