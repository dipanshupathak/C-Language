#include<stdio.h>
int main()
{
  int marks;
  printf("Welcome To grade Calculator\n");
  printf("Plese Enter Your Marks : ");
  scanf("%d",&marks);
  if (marks > 90 ) {
    printf("You Have Got A Grade");
  } else if (marks > 75) {
    printf("You have Got B Grade");
  }else if (marks > 60) {
    printf("You Have Got C Grade");
  }else if (marks > 75) {
    printf("you have got B grade");
  }else {
    printf("you have got B grade");
  } else {
    printf("You have failed the exam with F grade");
  }
  return 0;
}