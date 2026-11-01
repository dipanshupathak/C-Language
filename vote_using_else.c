#include<stdio.h>
int main()
{
  int age;
  printf("Enter THe Age : ");
  scanf("%d",&age);
  if(age>=18)
  {
    printf("Your Are Eligible To Vote");
  }
  else
  {
    printf("You Are Not Eligible To Vote");
  }
   return 0;
}