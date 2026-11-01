#include<stdio.h>
int main(){
  int age;
  printf("Enter The Age : ");
  scanf("%d",&age);
  if(age>=18){
    printf("You Are Eligible To Vote");
  }
  else
  {
    printf("You are Not Eligible To vote");
  }
return 0;
}