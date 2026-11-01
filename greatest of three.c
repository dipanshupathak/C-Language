#include<stdio.h>
int main()
{
  int first, second, third;
  printf("Plese Enter Your First Number : ");
  scanf("%d",&first);
  printf("Now Enter Your Second Number : ");
  scanf("%d",&second);
  printf("Finally Enter Your Third Number : ");
  scanf("%d",&third);
  if(first > second && first > third){
    printf("%d is the greatest",first);
  }else if (second > third){
    printf("%d is the greatest",second);
  }else {
    printf("%d is the greatest",third);
  }
  return 0;
}