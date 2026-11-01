#include<stdio.h>
int main()
{
  int dayNumber;
  printf("Enter A Day Number (1 to 7) : ");
  scanf("%d",&dayNumber);
  switch(dayNumber)
  {
    case 1:
    printf("Sunday\n");
    break;
    case 2:
    printf("Monday");
    break;
    case 3:
    printf("Tuesday");
    break;
    case 4:
    printf("Wednesday");
    break;
    case 5:
    printf("Thursday");
    break;
    case 6:
    printf("Friday");
    break;
    case 7:
    printf("Saturday");
    break;
    // if the input is not between 1 and 7 printf ("Invalid day Number.\n");
  }
  return 0;
}