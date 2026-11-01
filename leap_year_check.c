#include<stdio.h>
int main (){
  int year;
  printf("Enter A Year : ");
  scanf("%d",&year);
  if((year%4==0&& year%100!=0)||(year%400==0)){
    printf("%d is a leap year.\n",year);
  }else{
    printf("%dis not a leap year.\n",year);
  }
  return 0;
}