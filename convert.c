#include<stdio.h>
int main()
{
  int number;
  printf("plese enter the number : ");
  scanf("%d",&number);
  float floating = number;
  printf("\n Qrigibal Number is : %d",number);
  printf("\n float converted is : %d",floating);
  printf("\n float converted is : %d",(float)number);
  return 0;
}