#include<stdio.h>
int main ()
{
  const float PI = 3.14159;
  int radius;
  printf("Please Enterv The Radius Of The CIrcle In cms : ");
  scanf("%d",&radius);
  printf("The Circumfrence Of Your Circle Is %f cm",2 * PI * radius);
  return 0;
}